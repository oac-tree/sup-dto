/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : SUP - DTO
 *
 * Description   : Data transfer objects for SUP
 *
 * Author        : Walter Van Herck (IO)
 *
 * Copyright (c) : 2010-2023 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include "struct_value_data.h"

#include <sup/dto/anyvalue/field_utils.h>

#include <algorithm>

namespace sup
{
namespace dto
{

StructValueData::StructValueData(const std::string& type_name, value_flags::Constraints constraints)
  : m_member_data{type_name}
  , m_constraints{constraints}
{}

StructValueData::StructValueData(const AnyType& anytype, value_flags::Constraints constraints)
  : m_member_data{anytype.GetTypeName()}
  , m_constraints{constraints}
{
  for (const auto& member_name : anytype.MemberNames())
  {
    const auto& member_type = anytype[member_name];
    std::unique_ptr<IValueData> data{CreateValueData(member_type, constraints)};
    m_member_data.AddMember(member_name, MakeAnyValue(std::move(data)));
  }
}

StructValueData::~StructValueData() = default;

StructValueData* StructValueData::Clone(value_flags::Constraints constraints) const
{
  auto result = std::unique_ptr<StructValueData>(new StructValueData(GetTypeName(), constraints));
  for (const auto& member_name : MemberNames())
  {
    const auto& member_val = m_member_data[member_name];
    std::unique_ptr<IValueData> data{CreateValueData(member_val.GetType(), constraints)};
    data->ConvertFrom(member_val);
    result->m_member_data.AddMember(member_name, MakeAnyValue(std::move(data)));
  }
  return result.release();
}

TypeCode StructValueData::GetTypeCode() const
{
  return m_member_data.GetTypeCode();
}

std::string StructValueData::GetTypeName() const
{
  return m_member_data.GetTypeName();
}

AnyType StructValueData::GetType() const
{
  auto result = EmptyStructType(GetTypeName());
  for (const auto& member_name : MemberNames())
  {
    result.AddMember(member_name, m_member_data[member_name].GetType());
  }
  return result;
}

value_flags::Constraints StructValueData::GetConstraints() const
{
  return m_constraints;
}

void StructValueData::AddMember(const std::string& name, const AnyValue& value)
{
  if (IsLockedTypeConstraint(m_constraints))
  {
    throw InvalidOperationException("Cannot add member to struct whose type is locked");
  }
  std::unique_ptr<IValueData> data{CreateValueData(value.GetType(), m_constraints)};
  data->ConvertFrom(value);
  m_member_data.AddMember(name, MakeAnyValue(std::move(data)));
}

std::vector<std::string> StructValueData::MemberNames() const
{
  return m_member_data.MemberNames();
}

std::size_t StructValueData::NumberOfMembers() const
{
  return m_member_data.NumberOfMembers();
}

void StructValueData::ConvertFrom(const AnyValue& value)
{
  if (value.GetTypeCode() != TypeCode::Struct)
  {
    IValueData::ConvertFrom(value);
  }
  if (value.MemberNames() != MemberNames())
  {
    throw InvalidConversionException("Can't convert AnyValues with different list of fields");
  }
  for (const auto& member_name : MemberNames())
  {
    UnsafeConversion(m_member_data[member_name], value[member_name]);
  }
}

bool StructValueData::HasField(const std::string& fieldname) const
{
  return m_member_data.HasField(fieldname);
}

AnyValue& StructValueData::operator[](const std::string& fieldname)
{
  return m_member_data[fieldname];
}

bool StructValueData::Equals(const AnyValue& other) const
{
  return m_member_data.Equals(other);
}

StructValueData* CreateStructValueData(const AnyType& anytype, value_flags::Constraints constraints)
{
  auto result = std::unique_ptr<StructValueData>(new StructValueData(anytype, constraints));
  return result.release();
}

}  // namespace dto

}  // namespace sup
