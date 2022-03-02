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

#include "AnyValueBuildNode.h"

#include "ArrayValueBuildNode.h"
#include "AnyValueExceptions.h"

namespace sup
{
namespace dto
{

AnyValueBuildNode::AnyValueBuildNode(IAnyBuildNode* parent)
  : IAnyBuildNode{parent}
  , value_node{}
  , array_node{}
  , anyvalue{}
{}

AnyValueBuildNode::~AnyValueBuildNode() = default;

IAnyBuildNode* AnyValueBuildNode::GetStructureNode()
{
  if (value_node)
  {
    throw InvalidOperationException(
        "AnyValueBuildNode::GetStructureNode must be called with empty child node");
  }
  value_node.reset(new AnyValueBuildNode(this));
  return value_node.get();
}

IAnyBuildNode* AnyValueBuildNode::GetArrayNode()
{
  if (array_node)
  {
    throw InvalidOperationException(
        "AnyValueBuildNode::GetArrayNode must be called with empty child node");
  }
  array_node.reset(new ArrayValueBuildNode(this));
  return array_node.get();
}

bool AnyValueBuildNode::PopStructureNode()
{
  if (!value_node)
  {
    throw InvalidOperationException(
        "AnyValueBuildNode::PopStructureNode must be called with a non-empty child node");
  }
  anyvalue = value_node->MoveAnyValue();
  value_node.reset();
  return true;
}

bool AnyValueBuildNode::PopArrayNode()
{
  if (!array_node)
  {
    throw InvalidOperationException(
        "AnyValueBuildNode::PopArrayNode must be called with a non-empty child node");
  }
  anyvalue = array_node->MoveAnyValue();
  array_node.reset();
  return true;
}

AnyValue AnyValueBuildNode::MoveAnyValue() const
{
  return std::move(anyvalue);
}

}  // namespace dto

}  // namespace sup
