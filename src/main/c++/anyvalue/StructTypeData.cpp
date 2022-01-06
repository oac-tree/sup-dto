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

void StructTypeData::AddMember(std::string name, const AnyType& type)
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
  for (auto& member : members)
  {
    if (name == member.first)
    {
      return true;
    }
  }
  return false;
}

StructTypeData* StructTypeData::Clone() const
{
  auto result = std::make_unique<StructTypeData>(name);
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

std::vector<std::string> StructTypeData::MemberNames() const
{
  std::vector<std::string> result;
  for (auto& member : members)
  {
    result.push_back(member.first);
  }
  return result;
}

AnyType& StructTypeData::operator[](const std::string& fieldname)
{
  return const_cast<AnyType&>(static_cast<const StructTypeData&>(*this)[fieldname]);
}

const AnyType& StructTypeData::operator[](const std::string& fieldname) const
{
  using pair_type = decltype(members)::value_type;
  if (fieldname.empty())
  {
    throw EmptyKeyException("Trying to access a member with empty field name");
  }
  auto fields = StripFirstFieldName(fieldname);
  auto it = std::find_if(members.cbegin(), members.cend(),
                      [&fields](const pair_type& member){
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

bool StructTypeData::Equals(const ITypeData* other) const
{
  if (other->GetTypeCode() != TypeCode::Struct)
  {
    return false;
  }
  if (GetTypeName() != other->GetTypeName())
  {
    return false;
  }
  for (auto& member : members)
  {
    try
    {
      auto& other_member_type = (*other)[member.first];
      if (member.second != other_member_type)
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

void StructTypeData::VerifyMemberName(const std::string& name) const
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
