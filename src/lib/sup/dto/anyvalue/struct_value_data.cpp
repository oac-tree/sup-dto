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
 * Copyright (c) : 2010-2022 ITER Organization,
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

namespace sup
{
namespace dto
{

StructValueData::StructValueData(const std::string& type_name, value_flags::Constraints constraints)
  : m_member_data{type_name}
  , m_constraints{constraints}
{}

StructValueData::~StructValueData() = default;

StructValueData* StructValueData::Clone(value_flags::Constraints constraints) const
{
  auto result = std::unique_ptr<StructValueData>(new StructValueData(m_member_data, constraints));
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
  auto result = EmptyStructType(m_member_data.GetTypeName());
  for (const auto& member_name : m_member_data.MemberNames())
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
  return m_member_data.AddMember(name, value);
}

std::vector<std::string> StructValueData::MemberNames() const
{
  return m_member_data.MemberNames();
}

std::size_t StructValueData::NumberOfMembers() const
{
  return m_member_data.NumberOfMembers();
}

void StructValueData::Assign(const AnyValue& value)
{
  if (value.GetTypeCode() != TypeCode::Struct)
  {
    IValueData::Assign(value);
  }
  if (value.MemberNames() != MemberNames())
  {
    throw InvalidConversionException("Can't convert AnyValues with different list of fields");
  }
  for (const auto &member_name : m_member_data.MemberNames())
  {
    auto &other_member_value = value[member_name];
    m_member_data[member_name] = other_member_value;
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

StructValueData::StructValueData(const StructDataT<AnyValue>& member_data,
                                 value_flags::Constraints constraints)
  : m_member_data{member_data}
  , m_constraints{constraints}
{}

StructValueData* CreateStructValueData(const AnyType& anytype, value_flags::Constraints constraints)
{
  auto result =
    std::unique_ptr<StructValueData>(new StructValueData(anytype.GetTypeName(), constraints));
  for (const auto& member_name : anytype.MemberNames())
  {
    result->AddMember(member_name, AnyValue(anytype[member_name]));
  }
  return result.release();
}

}  // namespace dto

}  // namespace sup
