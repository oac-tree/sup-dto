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

#include "arrayvalue_buildnode.h"

#include "anyvalue_buildnode.h"
#include "unboundedarrayvalue_buildnode.h"
#include "sup/dto/anyvalue_exceptions.h"

namespace sup
{
namespace dto
{

ArrayValueBuildNode::ArrayValueBuildNode(
  const AnyTypeRegistry* anytype_registry, IAnyBuildNode* parent, AnyValue& anyvalue_)
  : IAnyBuildNode(anytype_registry, parent)
  , value_node{}
  , array_node{}
  , current_index{}
  , size{anyvalue_.NumberOfElements()}
  , anyvalue{anyvalue_}
{}

ArrayValueBuildNode::~ArrayValueBuildNode() = default;

bool ArrayValueBuildNode::Bool(boolean b)
{
  if (current_index >= size)
  {
    throw ParseException(
        "AnyValueBuildNode::Bool called more than array size");
  }
  anyvalue[current_index++] = b;
  return true;
}

bool ArrayValueBuildNode::Int32(int32 i)
{
  if (current_index >= size)
  {
    throw ParseException(
        "AnyValueBuildNode::Int32 called more than array size");
  }
  anyvalue[current_index++] = i;
  return true;
}

bool ArrayValueBuildNode::Uint32(uint32 u)
{
  if (current_index >= size)
  {
    throw ParseException(
        "AnyValueBuildNode::Uint32 called more than array size");
  }
  anyvalue[current_index++] = u;
  return true;
}

bool ArrayValueBuildNode::Int64(int64 i)
{
  if (current_index >= size)
  {
    throw ParseException(
        "AnyValueBuildNode::Int64 called more than array size");
  }
  anyvalue[current_index++] = i;
  return true;
}

bool ArrayValueBuildNode::Uint64(uint64 u)
{
  if (current_index >= size)
  {
    throw ParseException(
        "AnyValueBuildNode::Uint64 called more than array size");
  }
  anyvalue[current_index++] = u;
  return true;
}

bool ArrayValueBuildNode::Double(float64 d)
{
  if (current_index >= size)
  {
    throw ParseException(
        "AnyValueBuildNode::Double called more than array size");
  }
  anyvalue[current_index++] = d;
  return true;
}

bool ArrayValueBuildNode::String(const std::string& str)
{
  if (current_index >= size)
  {
    throw ParseException(
        "AnyValueBuildNode::String called more than array size");
  }
  anyvalue[current_index++] = str;
  return true;
}

IAnyBuildNode* ArrayValueBuildNode::GetStructureNode()
{
  if (value_node || current_index >= size)
  {
    throw ParseException(
        "ArrayValueBuildNode::GetStructureNode must be called with empty child node "
        "and without exceeding array size");
  }
  value_node.reset(new AnyValueBuildNode(GetTypeRegistry(), this, anyvalue[current_index++]));
  return value_node.get();
}

IAnyBuildNode* ArrayValueBuildNode::GetArrayNode()
{
  if (array_node || current_index >= size)
  {
    throw ParseException(
        "ArrayValueBuildNode::GetArrayNode must be called with empty child node "
        "and without exceeding array size");
  }
  AnyValue& element_value = anyvalue[current_index++];
  array_node = CreateArrayBuildNode(GetTypeRegistry(), this, element_value);
  return array_node.get();
}

bool ArrayValueBuildNode::PopStructureNode()
{
  if (!value_node)
  {
    throw ParseException(
        "ArrayValueBuildNode::PopStructureNode must be called with a non-empty child node");
  }
  value_node.reset();
  return true;
}

bool ArrayValueBuildNode::PopArrayNode()
{
  if (!array_node)
  {
    throw ParseException(
        "ArrayValueBuildNode::PopArrayNode must be called with a non-empty child node");
  }
  array_node.reset();
  return true;
}

std::unique_ptr<IAnyBuildNode> CreateArrayBuildNode(
  const AnyTypeRegistry* anytype_registry, IAnyBuildNode* parent, AnyValue& anyvalue)
{
  if (IsArrayValue(anyvalue))
  {
    return std::unique_ptr<IAnyBuildNode>(
      new ArrayValueBuildNode(anytype_registry, parent, anyvalue));
  }
  else if (IsUnboundedArrayValue(anyvalue))
  {
    return std::unique_ptr<IAnyBuildNode>(
      new UnboundedArrayValueBuildNode(anytype_registry, parent, anyvalue));
  }
  throw ParseException(
        "CreateArrayBuildNode must be called with an (unbounded) array value");
}

}  // namespace dto

}  // namespace sup
