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
 * SPDX-License-Identifier: MIT
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file LICENSE located in the top level directory
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

TypeCode StructTypeData::GetTypeCode() const
{
  return m_member_data.GetTypeCode();
}

std::string StructTypeData::GetTypeName() const
{
  return m_member_data.GetTypeName();
}

void StructTypeData::AddMember(const std::string& name, AnyType&& type)
{
  utils::VerifyMemberName(name);
  if (HasChild(name))
  {
    throw InvalidOperationException("Cannot add duplicate member keys");
  }
  auto moved = std::make_unique<AnyType>(std::move(type));
  m_member_data.AddMember(name, std::move(moved));
}

std::vector<std::string> StructTypeData::MemberNames() const
{
  return m_member_data.MemberNames();
}

std::size_t StructTypeData::NumberOfMembers() const
{
  return m_member_data.NumberOfMembers();
}

std::size_t StructTypeData::NumberOfChildren() const
{
  return m_member_data.NumberOfMembers();
}

bool StructTypeData::HasChild(const std::string& child_name) const
{
  return m_member_data.HasChild(child_name);
}

AnyType* StructTypeData::GetChildType(const std::string& child_name)
{
  return m_member_data.GetChild(child_name);
}

AnyType* StructTypeData::GetChildType(std::size_t idx)
{
  return m_member_data.GetChild(idx);
}

std::unique_ptr<ITypeData> StructTypeData::CloneFromChildren(
  std::vector<std::unique_ptr<AnyType>>&& children) const
{
  auto n_members = m_member_data.NumberOfMembers();
  auto result = std::make_unique<StructTypeData>(GetTypeName());
  auto member_names = m_member_data.MemberNames();
  for (std::size_t idx=0; idx < n_members; ++idx)
  {
    result->m_member_data.AddMember(member_names[idx], std::move(children[idx]));
  }
  return result;
}

bool StructTypeData::ShallowEquals(const AnyType& other) const
{
  return m_member_data.ShallowEquals(other);
}

}  // namespace dto

}  // namespace sup
