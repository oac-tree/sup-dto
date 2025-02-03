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
 * Copyright (c) : 2010-2025 ITER Organization,
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

StructValueData::StructValueData(const std::string& type_name, Constraints constraints)
  : m_member_data{type_name}
  , m_constraints{constraints}
{}

StructValueData::StructValueData(const AnyType& anytype, Constraints constraints)
  : StructValueData(anytype.GetTypeName(), constraints)
{
  for (const auto& member_name : anytype.MemberNames())
  {
    const auto& member_type = anytype[member_name];
    auto data = CreateValueData(member_type, constraints);
    m_member_data.AddMember(member_name, MakeAnyValue(std::move(data)));
  }
}

StructValueData::~StructValueData() = default;

std::unique_ptr<IValueData> StructValueData::Clone(Constraints constraints) const
{
  auto result = std::make_unique<StructValueData>(GetTypeName(), constraints);
  for (const auto& member_name : MemberNames())
  {
    const auto& member_val = *m_member_data.GetChild(member_name);
    auto data = CreateValueData(member_val.GetType(), constraints);
    data->ConvertFrom(member_val);
    result->m_member_data.AddMember(member_name, MakeAnyValue(std::move(data)));
  }
  return std::unique_ptr<IValueData>{result.release()};
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
    (void)result.AddMember(member_name, m_member_data.GetChild(member_name)->GetType());
  }
  return result;
}

Constraints StructValueData::GetConstraints() const
{
  return m_constraints;
}

void StructValueData::AddMember(const std::string& name, AnyValue&& value)
{
  if (IsLockedTypeConstraint(m_constraints))
  {
    throw InvalidOperationException("Cannot add member to struct whose type is locked");
  }
  auto member = std::make_unique<AnyValue>(std::move(value));
  m_member_data.AddMember(name, std::move(member));
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
    UnsafeConversion(*m_member_data.GetChild(member_name), value[member_name]);
  }
}

bool StructValueData::HasChild(const std::string& child_name) const
{
  return m_member_data.HasChild(child_name);
}

std::vector<std::string> StructValueData::ChildNames() const
{
  return m_member_data.MemberNames();
}

AnyValue* StructValueData::GetChildValue(const std::string& child_name)
{
  return m_member_data.GetChild(child_name);
}

bool StructValueData::ShallowEquals(const AnyValue& other) const
{
  return m_member_data.ShallowEquals(other);
}

std::unique_ptr<IValueData> CreateStructValueData(const AnyType& anytype, Constraints constraints)
{
  return std::make_unique<StructValueData>(anytype, constraints);
}

}  // namespace dto

}  // namespace sup
