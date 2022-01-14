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

#include "StructValueData.h"

#include "AnyValueExceptions.h"
#include "StructTypeData.h"

#include <algorithm>

namespace sup
{
namespace dto
{

StructValueData::StructValueData(std::string type_name_)
  : type_name{std::move(type_name_)}
{}

StructValueData::~StructValueData() = default;

StructValueData* StructValueData::Clone() const
{
  auto result = std::unique_ptr<StructValueData>(new StructValueData(type_name));
  result->members = members;
  return result.release();
}

TypeCode StructValueData::GetTypeCode() const
{
  return TypeCode::Struct;
}

AnyType StructValueData::GetType() const
{
  auto result = EmptyStructType(type_name);
  for (const auto& member : members)
  {
    result.AddMember(member.first, member.second.GetType());
  }
  return result;
}

std::string StructValueData::GetTypeName() const
{
  return type_name;
}

void StructValueData::Assign(const AnyValue& value)
{
  if (value.GetTypeCode() != TypeCode::Struct)
  {
    IValueData::Assign(value);
  }
  if (value.NumberOfMembers() != NumberOfMembers())
  {
    throw InvalidConversionException("Can't convert AnyValues between differently"
                                     " sized structures");
  }
  for (auto &member : members)
  {
    if (!value.HasMember(member.first))
    {
      throw InvalidConversionException("Can't convert AnyValues with differently named"
                                       " member names");
    }
    auto &other_member_value = value[member.first];
    member.second = other_member_value;
  }
}

void StructValueData::AddMember(const std::string& name, const AnyValue& value)
{
  VerifyMemberName(name);
  if (HasMember(name))
  {
    throw DuplicateKeyException("Cannot add duplicate member names");
  }
  members.push_back({name, value});
}

bool StructValueData::HasMember(const std::string& name) const
{
  auto it = std::find_if(members.cbegin(), members.cend(),
                         [name](typename decltype(members)::const_reference member){
                           return member.first == name;
                         });
  return it != members.cend();
}

std::vector<std::string> StructValueData::MemberNames() const
{
  std::vector<std::string> result;
  std::transform(members.cbegin(), members.cend(), std::back_inserter(result),
                 [](typename decltype(members)::const_reference member){
                   return member.first;
                 });
  return result;
}

std::size_t StructValueData::NumberOfMembers() const
{
  return members.size();
}

AnyValue& StructValueData::operator[](const std::string& fieldname)
{
  return const_cast<AnyValue&>(static_cast<const StructValueData&>(*this)[fieldname]);
}

const AnyValue& StructValueData::operator[](const std::string& fieldname) const
{
  using cref_pair_type = decltype(members)::const_reference;
  if (fieldname.empty())
  {
    throw EmptyKeyException("Trying to access a member with empty field name");
  }
  auto fields = StripFirstFieldName(fieldname);
  auto it = std::find_if(members.cbegin(), members.cend(),
                      [&fields](cref_pair_type member){
                        return member.first == fields.first;
                      });
  if (it == members.cend())
  {
    throw UnknownKeyException("Trying to access a member with unknown field name");
  }
  auto& member_value = it->second;
  if (fields.second.empty())
  {
    return member_value;
  }
  return member_value[fields.second];
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
  if (other.NumberOfMembers() != NumberOfMembers())
  {
    return false;
  }
  for (auto& member : members)
  {
    try
    {
      auto& other_member_value = other[member.first];
      if (other_member_value != member.second)
      {
        return false;
      }
    }
    catch(const UnknownKeyException& e)
    {
      return false;
    }
  }
  return true;
}

StructValueData* CreateStructValueData(const AnyType& anytype)
{
  auto result = std::unique_ptr<StructValueData>(new StructValueData(anytype.GetTypeName()));
  for (const auto& member_name : anytype.MemberNames())
  {
    result->AddMember(member_name, AnyValue(anytype[member_name]));
  }
  return result.release();
}

}  // namespace dto

}  // namespace sup
