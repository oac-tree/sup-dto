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

#include "AnyValueValueElementBuildNode.h"

#include "AnyValueBuildNode.h"
#include "AnyValueExceptions.h"
#include "ArrayValueBuildNode.h"
#include "SerializationConstants.h"

namespace sup
{
namespace dto
{

AnyValueValueElementBuildNode::AnyValueValueElementBuildNode(IAnyBuildNode* parent,
                                                             AnyValue& anyvalue_)
  : IAnyBuildNode{parent}
  , value_node{}
  , array_node{}
  , member_name{}
  , anyvalue{anyvalue_}
{}

AnyValueValueElementBuildNode::~AnyValueValueElementBuildNode() = default;

bool AnyValueValueElementBuildNode::Member(const std::string& str)
{
  if (!member_name.empty() || str != serialization::INSTANCE_KEY)
  {
    throw InvalidOperationException(
      "AnyValueValueElementBuildNode::Member must be called once with \"instance\" key");
  }
  member_name = str;
  return true;
}

IAnyBuildNode* AnyValueValueElementBuildNode::GetStructureNode()
{
  if (value_node || member_name != serialization::INSTANCE_KEY)
  {
    throw InvalidOperationException(
      "AnyValueValueElementBuildNode::GetStructureNode must be called after \"instance\" key "
      "and with empty child node");

  }
  value_node.reset(new AnyValueBuildNode(this, anyvalue));
  return value_node.get();
}

IAnyBuildNode* AnyValueValueElementBuildNode::GetArrayNode()
{
  if (array_node || member_name != serialization::INSTANCE_KEY)
  {
    throw InvalidOperationException(
        "AnyValueValueElementBuildNode::GetArrayNode must be called after \"instance\" key "
      "and with empty child node");
  }
  array_node.reset(new ArrayValueBuildNode(this, anyvalue));
  return array_node.get();
}

bool AnyValueValueElementBuildNode::PopStructureNode()
{
  if (!value_node)
  {
    throw InvalidOperationException(
      "AnyValueValueElementBuildNode::PopStructureNode must be called with non-empty child node");
  }
  member_name.clear();
  value_node.reset();
  return true;
}

bool AnyValueValueElementBuildNode::PopArrayNode()
{
  if (!array_node)
  {
    throw InvalidOperationException(
      "AnyValueValueElementBuildNode::PopArrayNode must be called with non-empty child node");
  }
  member_name.clear();
  array_node.reset();
  return true;
}

}  // namespace dto

}  // namespace sup
