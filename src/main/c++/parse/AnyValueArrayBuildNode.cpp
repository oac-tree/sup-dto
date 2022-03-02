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

#include "AnyValueArrayBuildNode.h"

#include "AnyValueArrayElementBuildNode.h"
#include "AnyValueExceptions.h"

namespace sup
{
namespace dto
{

AnyValueArrayBuildNode::AnyValueArrayBuildNode(IAnyBuildNode* parent)
  : IAnyBuildNode{parent}
  , encoding_node{}
  , type_node{}
  , value_node{}
  , processed_nodes{}
  , anyvalue{}
{}

AnyValueArrayBuildNode::~AnyValueArrayBuildNode() = default;

IAnyBuildNode* AnyValueArrayBuildNode::GetStructureNode()
{
  switch (processed_nodes)
  {
  case 0:
    encoding_node.reset(new AnyValueEncodingElementBuildNode(this));
    return encoding_node.get();
  case 1:
    type_node.reset(new AnyValueTypeElementBuildNode(this));
    return type_node.get();
  case 2:
    value_node.reset(new AnyValueValueElementBuildNode(this));
    return value_node.get();
  default:
    throw InvalidOperationException(
      "AnyValueArrayBuildNode::GetStructureNode cannot be called more than 3 times");
  }
}

bool AnyValueArrayBuildNode::PopStructureNode()
{
  if (!element_node)
  {
    throw InvalidOperationException(
        "AnyValueArrayBuildNode::PopStructureNode must be called with a non-empty child node");
  }

  // TODO: move out type or value:
  // anyvalue = element_node->MoveAnyType();
  element_node.reset();
  return true;
}

AnyValue AnyValueArrayBuildNode::MoveAnyValue() const
{
  return std::move(anyvalue);
}

}  // namespace dto

}  // namespace sup
