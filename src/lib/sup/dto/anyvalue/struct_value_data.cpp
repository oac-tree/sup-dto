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

StructValueData::~StructValueData() = default;

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

void StructValueData::AddMember(const std::string& name, std::unique_ptr<AnyValue>&& value)
{
  m_member_data.AddMember(name, std::move(value));
}

std::vector<std::string> StructValueData::MemberNames() const
{
  return m_member_data.MemberNames();
}

std::size_t StructValueData::NumberOfMembers() const
{
  return m_member_data.NumberOfMembers();
}

std::size_t StructValueData::NumberOfChildren() const
{
  return m_member_data.NumberOfMembers();
}

bool StructValueData::HasChild(const std::string& child_name) const
{
  return m_member_data.HasChild(child_name);
}

AnyValue* StructValueData::GetChildValue(const std::string& child_name)
{
  return m_member_data.GetChild(child_name);
}

AnyValue* StructValueData::GetChildValue(std::size_t idx)
{
  return m_member_data.GetChild(idx);
}

std::unique_ptr<IValueData> StructValueData::CloneFromChildren(
  std::vector<std::unique_ptr<AnyValue>>&& children, Constraints constraints) const
{
  if (children.size() != NumberOfMembers())
  {
    const std::string error =
      "StructValueData::CloneFromChildren(): Trying to clone struct value with wrong number of "
      "child values";
    throw InvalidOperationException(error);
  }
  auto result = std::make_unique<StructValueData>(GetTypeName(), constraints);
  auto member_names = MemberNames();
  for (std::size_t idx = 0; idx < NumberOfMembers(); ++idx)
  {
    result->m_member_data.AddMember(member_names[idx], std::move(children[idx]));
  }
  return result;
}

bool StructValueData::ShallowEquals(const IValueData* other) const
{
  if (!IsStructTypeCode(other->GetTypeCode()))
  {
    return false;
  }
  if (other->GetTypeName() != GetTypeName())
  {
    return false;
  }
  if (other->MemberNames() != MemberNames())
  {
    return false;
  }
  return true;
}

void StructValueData::ShallowConvertFrom(const AnyValue& value)
{
  if (value.GetTypeCode() != TypeCode::Struct)
  {
    IValueData::ShallowConvertFrom(value);
  }
  if (value.MemberNames() != MemberNames())
  {
    throw InvalidConversionException("Can't convert between structs with different lists of fields");
  }
}

}  // namespace dto

}  // namespace sup
