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
  , member_node{}
  , member_types{}
{}

MemberTypeArrayBuildNode::~MemberTypeArrayBuildNode() = default;

IAnyBuildNode* MemberTypeArrayBuildNode::GetStructureNode()
{
  if (member_node)
  {
    throw ParseException(
        "MemberTypeArrayBuildNode::GetStructureNode must be called with an empty member node");
  }
  member_node.reset(new MemberTypeBuildNode(GetTypeRegistry(), this));
  return member_node.get();
}

bool MemberTypeArrayBuildNode::PopStructureNode()
{
  if (!member_node)
  {
    throw ParseException(
        "MemberTypeArrayBuildNode::GetStructureNode must be called with a non-empty member node");
  }
  member_types.push_back(member_node->MoveMemberType());
  member_node.reset();
  return true;
}

std::vector<std::pair<std::string, AnyType>> MemberTypeArrayBuildNode::MoveMemberTypes()
{
  return std::move(member_types);
}

}  // namespace dto

}  // namespace sup
