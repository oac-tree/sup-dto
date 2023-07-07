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
  : m_member_data{name}
{}

StructTypeData::~StructTypeData() = default;

StructTypeData* StructTypeData::Clone() const
{
  auto result = std::unique_ptr<StructTypeData>(new StructTypeData(GetTypeName()));
  for (const auto& member_name : MemberNames())
  {
    std::unique_ptr<AnyType> copy{new AnyType{m_member_data[member_name]}};
    result->m_member_data.AddMember(member_name, std::move(copy));
  }
  return result.release();
}

TypeCode StructTypeData::GetTypeCode() const
{
  return m_member_data.GetTypeCode();
}

std::string StructTypeData::GetTypeName() const
{
  return m_member_data.GetTypeName();
}

void StructTypeData::AddMember(const std::string& name, const AnyType& type)
{
  std::unique_ptr<AnyType> copy{new AnyType{type}};
  m_member_data.AddMember(name, std::move(copy));
}

std::vector<std::string> StructTypeData::MemberNames() const
{
  return m_member_data.MemberNames();
}

std::size_t StructTypeData::NumberOfMembers() const
{
  return m_member_data.NumberOfMembers();
}

bool StructTypeData::HasField(const std::string& fieldname) const
{
  return m_member_data.HasField(fieldname);
}

AnyType& StructTypeData::operator[](const std::string& fieldname)
{
  return m_member_data[fieldname];
}

bool StructTypeData::Equals(const AnyType& other) const
{
  return m_member_data.Equals(other);
}

}  // namespace dto

}  // namespace sup
