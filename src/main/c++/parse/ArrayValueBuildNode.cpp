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

#include "ArrayValueBuildNode.h"

#include "AnyValueExceptions.h"

namespace sup
{
namespace dto
{

ArrayValueBuildNode::ArrayValueBuildNode(IAnyBuildNode* parent)
  : IAnyBuildNode{parent}
  , value_node{}
  , array_node{}
  , anyvalue{}
{}

ArrayValueBuildNode::~ArrayValueBuildNode() = default;

IAnyBuildNode* ArrayValueBuildNode::GetStructureNode()
{
  if (value_node)
  {
    throw InvalidOperationException(
        "ArrayValueBuildNode::GetStructureNode must be called with empty child node");
  }
  value_node.reset(new ArrayValueBuildNode(this));
  return value_node.get();
}

IAnyBuildNode* ArrayValueBuildNode::GetArrayNode()
{
  if (array_node)
  {
    throw InvalidOperationException(
        "ArrayValueBuildNode::GetArrayNode must be called with empty child node");
  }
  array_node.reset(new ArrayValueBuildNode(this));
  return array_node.get();
}

bool ArrayValueBuildNode::PopStructureNode()
{
  if (!value_node)
  {
    throw InvalidOperationException(
        "ArrayValueBuildNode::PopStructureNode must be called with a non-empty child node");
  }
  anyvalue = value_node->MoveAnyValue();
  value_node.reset();
  return true;
}

bool ArrayValueBuildNode::PopArrayNode()
{
  if (!array_node)
  {
    throw InvalidOperationException(
        "ArrayValueBuildNode::PopArrayNode must be called with a non-empty child node");
  }
  anyvalue = array_node->MoveAnyValue();
  array_node.reset();
  return true;
}

AnyValue ArrayValueBuildNode::MoveAnyValue() const
{
  return std::move(anyvalue);
}

}  // namespace dto

}  // namespace sup
