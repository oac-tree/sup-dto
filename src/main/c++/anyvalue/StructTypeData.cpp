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

#include "StructTypeData.h"

#include "AnyValueExceptions.h"

#include <algorithm>

namespace sup
{
namespace dto
{

StructTypeData::StructTypeData(std::string name_)
  : name{std::move(name_)}
{}

StructTypeData::~StructTypeData() = default;

StructTypeData* StructTypeData::Clone() const
{
  auto result = std::unique_ptr<StructTypeData>(new StructTypeData(name));
  result->members = members;
  return result.release();
}

TypeCode StructTypeData::GetTypeCode() const
{
  return TypeCode::Struct;
}

std::string StructTypeData::GetTypeName() const
{
  return name;
}

void StructTypeData::AddMember(const std::string& name, const AnyType& type)
{
  VerifyMemberName(name);
  if (HasMember(name))
  {
    throw DuplicateKeyException("Cannot add duplicate member keys");
  }
  members.push_back({name, type});
}

bool StructTypeData::HasMember(const std::string& name) const
{
  auto it = std::find_if(members.begin(), members.end(),
                         [name](typename decltype(members)::const_reference member){
                           return member.first == name;
                         });
  return it != members.end();
}

std::vector<std::string> StructTypeData::MemberNames() const
{
  std::vector<std::string> result;
  std::transform(members.begin(), members.end(), std::back_inserter(result),
                 [](typename decltype(members)::const_reference member){
                   return member.first;
                 });
  return result;
}

std::size_t StructTypeData::NumberOfMembers() const
{
  return members.size();
}

AnyType& StructTypeData::operator[](const std::string& fieldname)
{
  return const_cast<AnyType&>(static_cast<const StructTypeData&>(*this)[fieldname]);
}

const AnyType& StructTypeData::operator[](const std::string& fieldname) const
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
  auto& member_type = it->second;
  if (fields.second.empty())
  {
    return member_type;
  }
  return member_type[fields.second];
}

bool StructTypeData::Equals(const AnyType& other) const
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
      auto& other_member_type = other[member.first];
      if (other_member_type != member.second)
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

void VerifyMemberName(const std::string& name)
{
  if (name.empty())
  {
    throw KeyNotAllowedException("Member names cannot be empty");
  }
  if (name.find_first_of(" [].") != std::string::npos)
  {
    throw KeyNotAllowedException("Member names cannot contain spaces, square brackets or dots");
  }
}

std::pair<std::string, std::string> StripFirstFieldName(const std::string& fieldname)
{
  auto pos = fieldname.find_first_of("[.");
  if (pos == std::string::npos)
  {
    return { fieldname, ""};
  }
  auto first = fieldname.substr(0, pos);
  auto rest = fieldname.substr(pos);
  if (rest[0] == '.')
  {
    // Only strip dots
    rest = rest.substr(1);
  }
  return { first, rest };
}

}  // namespace dto

}  // namespace sup
