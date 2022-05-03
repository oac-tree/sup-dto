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

#include "AnyValueTypeElementBuildNode.h"

#include "AnyTypeBuildNode.h"
#include "AnyValueExceptions.h"
#include "SerializationConstants.h"

namespace sup
{
namespace dto
{

AnyValueTypeElementBuildNode::AnyValueTypeElementBuildNode(
  const AnyTypeRegistry* anytype_registry, IAnyBuildNode* parent)
  : IAnyBuildNode(anytype_registry, parent)
  , type_node{}
  , member_name{}
  , anytype{}
{}

AnyValueTypeElementBuildNode::~AnyValueTypeElementBuildNode() = default;

bool AnyValueTypeElementBuildNode::Member(const std::string& str)
{
  if (!member_name.empty() || str != serialization::DATATYPE_KEY)
  {
    throw ParseException(
      "AnyValueTypeElementBuildNode::Member must be called once with \"datatype\" key");
  }
  member_name = str;
  return true;
}

IAnyBuildNode* AnyValueTypeElementBuildNode::GetStructureNode()
{
  if (type_node || member_name != serialization::DATATYPE_KEY)
  {
    throw ParseException(
      "AnyValueTypeElementBuildNode::GetStructureNode must be called after \"datatype\" key "
      "and with empty child node");

  }
  type_node.reset(new AnyTypeBuildNode(GetTypeRegistry(), this));
  return type_node.get();
}

bool AnyValueTypeElementBuildNode::PopStructureNode()
{
  if (!type_node)
  {
    throw ParseException(
      "AnyValueTypeElementBuildNode::PopStructureNode must be called with non-empty child node");
  }
  anytype = type_node->MoveAnyType();
  member_name.clear();
  type_node.reset();
  return true;
}

AnyType AnyValueTypeElementBuildNode::MoveAnyType() const
{
  return std::move(anytype);
}

}  // namespace dto

}  // namespace sup
