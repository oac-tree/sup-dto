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

#include "AnyValueEncodingElementBuildNode.h"
#include "AnyValueTypeElementBuildNode.h"
#include "AnyValueValueElementBuildNode.h"
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
  if (encoding_node || type_node || value_node)
  {
    throw ParseException(
      "AnyValueArrayBuildNode::GetStructureNode cannot be called when a node is still active "
      "(not popped with PopStructureNode)");
  }
  switch (processed_nodes)
  {
  case 0:
    encoding_node.reset(new AnyValueEncodingElementBuildNode(this));
    return encoding_node.get();
  case 1:
    type_node.reset(new AnyValueTypeElementBuildNode(this));
    return type_node.get();
  case 2:
    value_node.reset(new AnyValueValueElementBuildNode(this, anyvalue));
    return value_node.get();
  default:
    throw ParseException(
      "AnyValueArrayBuildNode::GetStructureNode cannot be called more than 3 times");
  }
}

bool AnyValueArrayBuildNode::PopStructureNode()
{
  AnyType anytype;
  switch (processed_nodes)
  {
  case 0:
    if (!encoding_node || !encoding_node->EncodingOK())
    {
      throw ParseException(
          "AnyValueArrayBuildNode::PopStructureNode called first time with empty encoding node "
          " or invalid encoding");
    }
    encoding_node.reset();
    break;
  case 1:
    if (!type_node)
    {
      throw ParseException(
          "AnyValueArrayBuildNode::PopStructureNode called second time with empty type node");
    }
    anytype = type_node->MoveAnyType();
    anyvalue = AnyValue(anytype);
    type_node.reset();
    break;
  case 2:
    if (!value_node)
    {
      throw ParseException(
          "AnyValueArrayBuildNode::PopStructureNode called third time with empty value node");
    }
    value_node.reset();
    break;
  default:
    throw ParseException(
      "AnyValueArrayBuildNode::PopStructureNode cannot be called more than 3 times");
  }
  ++processed_nodes;
  return true;
}

AnyValue AnyValueArrayBuildNode::MoveAnyValue() const
{
  return std::move(anyvalue);
}

}  // namespace dto

}  // namespace sup
