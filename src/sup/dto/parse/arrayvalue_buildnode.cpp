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

#include <sup/dto/parse/anyvalue_buildnode.h>

#include <sup/dto/anyvalue_exceptions.h>

namespace sup
{
namespace dto
{

template <typename T> bool ArrayValueBuildNode::TryAssign(T val)
{
  if (size == 0 && current_index == anyvalue.NumberOfElements())
  {
    anyvalue.AddElement(AnyValue{element_type});
  }
  if (current_index >= anyvalue.NumberOfElements())
  {
    throw ParseException(
        "ArrayValueBuildNode: trying to add more elements than allowed");
  }
  try
  {
    anyvalue[current_index] = val;
  }
  catch(const InvalidConversionException& e)
  {
    throw ParseException(e.what());
  }
  ++current_index;
  return true;
}

ArrayValueBuildNode::ArrayValueBuildNode(
  const AnyTypeRegistry* anytype_registry, IAnyBuildNode* parent, AnyValue& anyvalue_)
  : IAnyBuildNode(anytype_registry, parent)
  , value_node{}
  , array_node{}
  , current_index{}
  , size{anyvalue_.NumberOfElements()}
  , anyvalue{anyvalue_}
  , element_type{}
{
  try
  {
    element_type = anyvalue.GetType().ElementType();
  }
  catch(const InvalidOperationException& e)
  {
    throw ParseException(e.what());
  }
}

ArrayValueBuildNode::~ArrayValueBuildNode() = default;

bool ArrayValueBuildNode::Bool(boolean b)
{
  return TryAssign(b);
}

bool ArrayValueBuildNode::Int32(int32 i)
{
  return TryAssign(i);
}

bool ArrayValueBuildNode::Uint32(uint32 u)
{
  return TryAssign(u);
}

bool ArrayValueBuildNode::Int64(int64 i)
{
  return TryAssign(i);
}

bool ArrayValueBuildNode::Uint64(uint64 u)
{
  return TryAssign(u);
}

bool ArrayValueBuildNode::Double(float64 d)
{
  return TryAssign(d);
}

bool ArrayValueBuildNode::String(const std::string& str)
{
  return TryAssign(str);
}

IAnyBuildNode* ArrayValueBuildNode::GetStructureNode()
{
  if (value_node || !IsStructType(element_type))
  {
    throw ParseException(
        "ArrayValueBuildNode::GetStructureNode must be called with empty child node "
        "and with structured element type");
  }
  if (size == 0 && current_index == anyvalue.NumberOfElements())
  {
    anyvalue.AddElement(AnyValue{element_type});
  }
  if (current_index >= anyvalue.NumberOfElements())
  {
    throw ParseException(
        "ArrayValueBuildNode::GetStructureNode called while exceeding array size");
  }
  value_node.reset(new AnyValueBuildNode(GetTypeRegistry(), this, anyvalue[current_index++]));
  return value_node.get();
}

IAnyBuildNode* ArrayValueBuildNode::GetArrayNode()
{
  if (array_node || !IsArrayType(element_type))
  {
    throw ParseException(
        "ArrayValueBuildNode::GetArrayNode must be called with empty child node "
        "and with array element type");
  }
  if (size == 0 && current_index == anyvalue.NumberOfElements())
  {
    anyvalue.AddElement(AnyValue{element_type});
  }
  if (current_index >= anyvalue.NumberOfElements())
  {
    throw ParseException(
        "ArrayValueBuildNode::GetArrayNode called while exceeding array size");
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
    const AnyTypeRegistry *anytype_registry, IAnyBuildNode *parent, AnyValue &anyvalue)
{
  if (!IsArrayValue(anyvalue))
  {
    throw ParseException(
        "CreateArrayBuildNode must be called with an array value");
  }
  return std::unique_ptr<IAnyBuildNode>(
      new ArrayValueBuildNode(anytype_registry, parent, anyvalue));
}

}  // namespace dto

}  // namespace sup
