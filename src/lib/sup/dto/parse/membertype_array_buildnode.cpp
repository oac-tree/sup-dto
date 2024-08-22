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

#include "membertype_array_buildnode.h"

#include <sup/dto/anyvalue_exceptions.h>
#include <sup/dto/parse/membertype_buildnode.h>

namespace sup
{
namespace dto
{

MemberTypeArrayBuildNode::MemberTypeArrayBuildNode(
  const AnyTypeRegistry* anytype_registry, IAnyBuildNode* parent)
  : IAnyBuildNode(anytype_registry, parent)
  , m_member_node{}
  , m_member_types{}
{}

MemberTypeArrayBuildNode::~MemberTypeArrayBuildNode() = default;

IAnyBuildNode* MemberTypeArrayBuildNode::GetStructureNode()
{
  if (m_member_node)
  {
    throw ParseException(
        "MemberTypeArrayBuildNode::GetStructureNode must be called with an empty member node");
  }
  m_member_node.reset(new MemberTypeBuildNode(GetTypeRegistry(), this));
  return m_member_node.get();
}

bool MemberTypeArrayBuildNode::PopStructureNode()
{
  if (!m_member_node)
  {
    throw ParseException(
        "MemberTypeArrayBuildNode::GetStructureNode must be called with a non-empty member node");
  }
  m_member_types.push_back(m_member_node->MoveMemberType());
  m_member_node.reset();
  return true;
}

std::vector<std::pair<std::string, AnyType>> MemberTypeArrayBuildNode::MoveMemberTypes()
{
  return std::move(m_member_types);
}

}  // namespace dto

}  // namespace sup
