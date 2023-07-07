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

#include <sup/dto/anyvalue/field_utils.h>

#include <algorithm>

namespace sup
{
namespace dto
{

StructValueData::StructValueData(const std::string& type_name, value_flags::Constraints constraints)
  : m_name{type_name}
  , m_members{}
  , m_constraints{constraints}
{}

StructValueData::StructValueData(const AnyType& anytype, value_flags::Constraints constraints)
  : m_name{anytype.GetTypeName()}
  , m_members{}
  , m_constraints{constraints}
{
  for (auto& member_name : anytype.MemberNames())
  {
    const auto& member_type = anytype[member_name];
    std::unique_ptr<IValueData> data{CreateValueData(member_type, constraints)};
    m_members.emplace_back(member_name, MakeAnyValue(std::move(data)));
  }
}

StructValueData::~StructValueData() = default;

StructValueData* StructValueData::Clone(value_flags::Constraints constraints) const
{
  auto result = std::unique_ptr<StructValueData>(new StructValueData(m_name, constraints));
  for (auto& member : m_members)
  {
    std::unique_ptr<IValueData> data{CreateValueData(member.second->GetType(), constraints)};
    data->ConvertFrom(*member.second);
    result->m_members.emplace_back(member.first, MakeAnyValue(std::move(data)));
  }
  return result.release();
}

TypeCode StructValueData::GetTypeCode() const
{
  return TypeCode::Struct;
}

std::string StructValueData::GetTypeName() const
{
  return m_name;
}

AnyType StructValueData::GetType() const
{
  auto result = EmptyStructType(m_name);
  for (const auto& member : m_members)
  {
    result.AddMember(member.first, member.second->GetType());
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
  utils::VerifyMemberName(name);
  if (HasField(name))
  {
    throw InvalidOperationException("Cannot add duplicate member keys");
  }
  std::unique_ptr<IValueData> data{CreateValueData(value.GetType(), m_constraints)};
  data->ConvertFrom(value);
  m_members.emplace_back(name, MakeAnyValue(std::move(data)));
}

std::vector<std::string> StructValueData::MemberNames() const
{
  std::vector<std::string> result;
  std::transform(m_members.begin(), m_members.end(), std::back_inserter(result),
                 [](typename decltype(m_members)::const_reference member){
                   return member.first;
                 });
  return result;
}

std::size_t StructValueData::NumberOfMembers() const
{
  return m_members.size();
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
  for (auto& member : m_members)
  {
    member.second->ConvertFrom(value[member.first]);
  }
}

bool StructValueData::HasField(const std::string& fieldname) const
{
  auto fields = utils::StripFirstFieldName(fieldname);
  auto it = std::find_if(m_members.cbegin(), m_members.cend(),
                         [&fields](typename decltype(m_members)::const_reference member){
                           return member.first == fields.first;
                         });
  if (it == m_members.cend())
  {
    return false;
  }
  if (fields.second.empty())
  {
    return true;
  }
  return it->second->HasField(fields.second);
}

AnyValue& StructValueData::operator[](const std::string& fieldname)
{
  using ref_pair_type = typename decltype(m_members)::reference;
  if (fieldname.empty())
  {
    throw InvalidOperationException("Trying to access a member with empty field name");
  }
  auto fields = utils::StripFirstFieldName(fieldname);
  auto it = std::find_if(m_members.begin(), m_members.end(),
                         [&fields](ref_pair_type member) {
                           return member.first == fields.first;
                         });
  if (it == m_members.end())
  {
    throw InvalidOperationException("Trying to access a member with unknown field name");
  }
  auto& member = it->second;
  if (fields.second.empty())
  {
    return *member;
  }
  return member->operator[](fields.second);
}

bool StructValueData::Equals(const AnyValue& other) const
{
  if (other.GetTypeCode() != TypeCode::Struct)
  {
    return false;
  }
  if (other.GetTypeName() != GetTypeName())
  {
    return false;
  }
  if (other.MemberNames() != MemberNames())
  {
    return false;
  }
  for (auto& member : m_members)
  {
    auto& other_member_field = other[member.first];
    if (other_member_field != *member.second)
    {
      return false;
    }
  }
  return true;
}

StructValueData* CreateStructValueData(const AnyType& anytype, value_flags::Constraints constraints)
{
  auto result = std::unique_ptr<StructValueData>(new StructValueData(anytype, constraints));
  return result.release();
}

}  // namespace dto

}  // namespace sup
