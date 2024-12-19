/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : SUP - DTO
 *
 * Description   : Unit test code
 *
 * Author        : Walter Van Herck (IO)
 *
 * Copyright (c) : 2010-2024 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include "membertype_buildnode.h"

#include <sup/dto/parse/anytype_buildnode.h>

#include <sup/dto/anyvalue_exceptions.h>

namespace sup
{
namespace dto
{

MemberTypeBuildNode::MemberTypeBuildNode(
  const AnyTypeRegistry* anytype_registry, IAnyBuildNode* parent)
  : IAnyBuildNode(anytype_registry, parent)
  , m_type_node{}
  , m_member_name{}
  , m_member_type{}
{}

MemberTypeBuildNode::~MemberTypeBuildNode() = default;

bool MemberTypeBuildNode::Member(const std::string& str)
{
  if (!m_member_name.empty())
  {
    throw ParseException(
        "MemberTypeBuildNode::Member called when previous member not finished");
  }
  m_member_name = str;
  return true;
}

IAnyBuildNode* MemberTypeBuildNode::GetStructureNode()
{
  if (m_type_node || (m_member_name.empty()))
  {
    throw ParseException(
        "MemberTypeBuildNode::GetStructureNode must be called after member name and with "
        "empty child node");
  }
  m_type_node = std::make_unique<AnyTypeBuildNode>(GetTypeRegistry(), this);
  return m_type_node.get();
}

bool MemberTypeBuildNode::PopStructureNode()
{
  if ((!m_type_node) || (m_member_name.empty()))
  {
    throw ParseException(
        "MemberTypeBuildNode::GetStructureNode must be called after member name and with "
        "non-empty child node");
  }
  m_member_type = { m_member_name, m_type_node->GetAnyType() };
  m_member_name.clear();
  return true;
}

std::pair<std::string, AnyType> MemberTypeBuildNode::MoveMemberType()
{
  if (m_member_type.first.empty())
  {
    throw ParseException("MemberTypeBuildNode::MoveMemberType called with empty member");
  }
  return std::move(m_member_type);
}

}  // namespace dto

}  // namespace sup
