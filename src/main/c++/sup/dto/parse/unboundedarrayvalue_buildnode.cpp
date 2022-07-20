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

#include "unboundedarrayvalue_buildnode.h"

#include <sup/dto/parse/anyvalue_buildnode.h>
#include <sup/dto/parse/arrayvalue_buildnode.h>

#include <sup/dto/anyvalue_exceptions.h>

namespace sup
{
namespace dto
{

UnboundedArrayValueBuildNode::UnboundedArrayValueBuildNode(
  const AnyTypeRegistry* anytype_registry, IAnyBuildNode* parent, AnyValue& anyvalue_)
  : IAnyBuildNode(anytype_registry, parent)
  , value_node{}
  , array_node{}
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

UnboundedArrayValueBuildNode::~UnboundedArrayValueBuildNode() = default;

bool UnboundedArrayValueBuildNode::Bool(boolean b)
{
  AnyValue copy{element_type};
  try
  {
    copy = b;
    anyvalue.Append(copy);
  }
  catch(const InvalidConversionException& e)
  {
    throw ParseException(e.what());
  }
  return true;
}

bool UnboundedArrayValueBuildNode::Int32(int32 i)
{
  AnyValue copy{element_type};
  try
  {
    copy = i;
    anyvalue.Append(copy);
  }
  catch(const InvalidConversionException& e)
  {
    throw ParseException(e.what());
  }
  return true;
}

bool UnboundedArrayValueBuildNode::Uint32(uint32 u)
{
  AnyValue copy{element_type};
  try
  {
    copy = u;
    anyvalue.Append(copy);
  }
  catch(const InvalidConversionException& e)
  {
    throw ParseException(e.what());
  }
  return true;
}

bool UnboundedArrayValueBuildNode::Int64(int64 i)
{
  AnyValue copy{element_type};
  try
  {
    copy = i;
    anyvalue.Append(copy);
  }
  catch(const InvalidConversionException& e)
  {
    throw ParseException(e.what());
  }
  return true;
}

bool UnboundedArrayValueBuildNode::Uint64(uint64 u)
{
  AnyValue copy{element_type};
  try
  {
    copy = u;
    anyvalue.Append(copy);
  }
  catch(const InvalidConversionException& e)
  {
    throw ParseException(e.what());
  }
  return true;
}

bool UnboundedArrayValueBuildNode::Double(float64 d)
{
  AnyValue copy{element_type};
  try
  {
    copy = d;
    anyvalue.Append(copy);
  }
  catch(const InvalidConversionException& e)
  {
    throw ParseException(e.what());
  }
  return true;
}

bool UnboundedArrayValueBuildNode::String(const std::string& str)
{
  AnyValue copy{element_type};
  try
  {
    copy = str;
    anyvalue.Append(copy);
  }
  catch(const InvalidConversionException& e)
  {
    throw ParseException(e.what());
  }
  return true;
}

IAnyBuildNode* UnboundedArrayValueBuildNode::GetStructureNode()
{
  if (value_node || !IsStructType(element_type))
  {
    throw ParseException(
        "UnboundedArrayValueBuildNode::GetStructureNode must be called with empty child node "
        "and with structured element type");
  }
  AnyValue copy{element_type};
  anyvalue.Append(copy);
  std::size_t idx = anyvalue.NumberOfElements() - 1;
  value_node.reset(new AnyValueBuildNode(GetTypeRegistry(), this, anyvalue[idx]));
  return value_node.get();
}

IAnyBuildNode* UnboundedArrayValueBuildNode::GetArrayNode()
{
  if (array_node || !(IsArrayType(element_type) || IsUnboundedArrayType(element_type)))
  {
    throw ParseException(
        "UnboundedArrayValueBuildNode::GetArrayNode must be called with empty child node");
  }
  AnyValue copy{element_type};
  anyvalue.Append(copy);
  std::size_t idx = anyvalue.NumberOfElements() - 1;
  array_node = CreateArrayBuildNode(GetTypeRegistry(), this, anyvalue[idx]);
  return array_node.get();
}

bool UnboundedArrayValueBuildNode::PopStructureNode()
{
  if (!value_node)
  {
    throw ParseException(
        "UnboundedArrayValueBuildNode::PopStructureNode must be called with a non-empty child node");
  }
  value_node.reset();
  return true;
}

bool UnboundedArrayValueBuildNode::PopArrayNode()
{
  if (!array_node)
  {
    throw ParseException(
        "UnboundedArrayValueBuildNode::PopArrayNode must be called with a non-empty child node");
  }
  array_node.reset();
  return true;
}

}  // namespace dto

}  // namespace sup
