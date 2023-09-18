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
 * Copyright (c) : 2010-2023 ITER Organization,
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
  if (m_size == 0 && m_current_index == m_anyvalue.NumberOfElements())
  {
    m_anyvalue.AddElement(AnyValue{m_element_type});
  }
  if (m_current_index >= m_anyvalue.NumberOfElements())
  {
    throw ParseException(
        "ArrayValueBuildNode: trying to add more elements than allowed");
  }
  try
  {
    m_anyvalue[m_current_index] = val;
  }
  catch(const MessageException& e)
  {
    throw ParseException(e.what());
  }
  ++m_current_index;
  return true;
}

ArrayValueBuildNode::ArrayValueBuildNode(
  const AnyTypeRegistry* anytype_registry, IAnyBuildNode* parent, AnyValue& anyvalue)
  : IAnyBuildNode(anytype_registry, parent)
  , m_value_node{}
  , m_array_node{}
  , m_current_index{}
  , m_size{anyvalue.NumberOfElements()}
  , m_anyvalue{anyvalue}
  , m_element_type{}
{
  try
  {
    m_element_type = m_anyvalue.GetType().ElementType();
  }
  catch(const MessageException& e)
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
  if (m_value_node || !IsStructType(m_element_type))
  {
    throw ParseException(
        "ArrayValueBuildNode::GetStructureNode must be called with empty child node "
        "and with structured element type");
  }
  if (m_size == 0 && m_current_index == m_anyvalue.NumberOfElements())
  {
    m_anyvalue.AddElement(AnyValue{m_element_type});
  }
  if (m_current_index >= m_anyvalue.NumberOfElements())
  {
    throw ParseException(
        "ArrayValueBuildNode::GetStructureNode called while exceeding array size");
  }
  m_value_node.reset(new AnyValueBuildNode(GetTypeRegistry(), this, m_anyvalue[m_current_index]));
  ++m_current_index;
  return m_value_node.get();
}

IAnyBuildNode* ArrayValueBuildNode::GetArrayNode()
{
  if (m_array_node || !IsArrayType(m_element_type))
  {
    throw ParseException(
        "ArrayValueBuildNode::GetArrayNode must be called with empty child node "
        "and with array element type");
  }
  if (m_size == 0 && m_current_index == m_anyvalue.NumberOfElements())
  {
    m_anyvalue.AddElement(AnyValue{m_element_type});
  }
  if (m_current_index >= m_anyvalue.NumberOfElements())
  {
    throw ParseException(
        "ArrayValueBuildNode::GetArrayNode called while exceeding array size");
  }
  AnyValue& element_value = m_anyvalue[m_current_index];
  ++m_current_index;
  m_array_node = CreateArrayBuildNode(GetTypeRegistry(), this, element_value);
  return m_array_node.get();
}

bool ArrayValueBuildNode::PopStructureNode()
{
  if (!m_value_node)
  {
    throw ParseException(
        "ArrayValueBuildNode::PopStructureNode must be called with a non-empty child node");
  }
  m_value_node.reset();
  return true;
}

bool ArrayValueBuildNode::PopArrayNode()
{
  if (!m_array_node)
  {
    throw ParseException(
        "ArrayValueBuildNode::PopArrayNode must be called with a non-empty child node");
  }
  m_array_node.reset();
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
