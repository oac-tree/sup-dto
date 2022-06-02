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

#include "membertype_buildnode.h"

#include "anytype_buildnode.h"
#include "sup/dto/anyvalue_exceptions.h"

namespace sup
{
namespace dto
{

MemberTypeBuildNode::MemberTypeBuildNode(
  const AnyTypeRegistry* anytype_registry, IAnyBuildNode* parent)
  : IAnyBuildNode(anytype_registry, parent)
  , type_node{}
  , member_name{}
  , member_type{}
{}

MemberTypeBuildNode::~MemberTypeBuildNode() = default;

bool MemberTypeBuildNode::Member(const std::string& str)
{
  if (!member_name.empty())
  {
    throw ParseException(
        "MemberTypeBuildNode::Member called when previous member not finished");
  }
  member_name = str;
  return true;
}

IAnyBuildNode* MemberTypeBuildNode::GetStructureNode()
{
  if (type_node || member_name.empty())
  {
    throw ParseException(
        "MemberTypeBuildNode::GetStructureNode must be called after member name and with "
        "empty child node");
  }
  type_node.reset(new AnyTypeBuildNode(GetTypeRegistry(), this));
  return type_node.get();
}

bool MemberTypeBuildNode::PopStructureNode()
{
  if (!type_node || member_name.empty())
  {
    throw ParseException(
        "MemberTypeBuildNode::GetStructureNode must be called after member name and with "
        "non-empty child node");
  }
  member_type = { member_name, type_node->MoveAnyType() };
  member_name.clear();
  return true;
}

std::pair<std::string, AnyType> MemberTypeBuildNode::MoveMemberType()
{
  if (member_type.first.empty())
  {
    throw ParseException("MemberTypeBuildNode::MoveMemberType called with empty member");
  }
  return std::move(member_type);
}

}  // namespace dto

}  // namespace sup
