/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : SUP - Sequencer
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

AnyType& StructTypeData::operator[](std::string fieldname)
{
  throw std::out_of_range("REPLACE THIS!!!");
}

const AnyType& StructTypeData::operator[](std::string fieldname) const
{
  throw std::out_of_range("REPLACE THIS!!!");
}

void StructTypeData::VerifyMemberName(const std::string& name) const
{
  if (name.find_first_of(" [].") != std::string::npos)
  {
    throw KeyNotAllowedException("Member names cannot contain spaces, square brackets or dots");
  }
}

}  // namespace dto

}  // namespace sup
