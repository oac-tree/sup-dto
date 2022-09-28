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

#include "struct_type_data.h"

namespace sup
{
namespace dto
{

StructTypeData::StructTypeData(const std::string& name)
  : member_data{name}
{}

StructTypeData::~StructTypeData() = default;

StructTypeData* StructTypeData::Clone() const
{
  auto result = std::unique_ptr<StructTypeData>(new StructTypeData(member_data));
  return result.release();
}

TypeCode StructTypeData::GetTypeCode() const
{
  return member_data.GetTypeCode();
}

std::string StructTypeData::GetTypeName() const
{
  return member_data.GetTypeName();
}

void StructTypeData::AddMember(const std::string& name, const AnyType& type)
{
  return member_data.AddMember(name, type);
}

std::vector<std::string> StructTypeData::MemberNames() const
{
  return member_data.MemberNames();
}

std::size_t StructTypeData::NumberOfMembers() const
{
  return member_data.NumberOfMembers();
}

bool StructTypeData::HasField(const std::string& fieldname) const
{
  return member_data.HasField(fieldname);
}

AnyType& StructTypeData::operator[](const std::string& fieldname)
{
  return member_data[fieldname];
}

bool StructTypeData::Equals(const AnyType& other) const
{
  return member_data.Equals(other);
}

StructTypeData::StructTypeData(const StructDataT<AnyType>& member_data_)
  : member_data{member_data_}
{}

}  // namespace dto

}  // namespace sup
