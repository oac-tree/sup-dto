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
 * Copyright (c) : 2010-2025 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 * SPDX-License-Identifier: MIT
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file LICENSE located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include "anyvalue_valueelement_buildnode.h"

#include <sup/dto/parse/anyvalue_buildnode.h>
#include <sup/dto/parse/arrayvalue_buildnode.h>
#include <sup/dto/parse/serialization_constants.h>

#include <sup/dto/anyvalue_exceptions.h>

namespace sup
{
namespace dto
{

AnyValueValueElementBuildNode::AnyValueValueElementBuildNode(
  const AnyTypeRegistry* anytype_registry, IAnyBuildNode* parent, AnyValue& anyvalue)
  : IAnyBuildNode(anytype_registry, parent)
  , m_value_node{}
  , m_array_node{}
  , m_member_name{}
  , m_anyvalue{anyvalue}
{}

AnyValueValueElementBuildNode::~AnyValueValueElementBuildNode() = default;

bool AnyValueValueElementBuildNode::Null()
{
  if (m_member_name != serialization::INSTANCE_KEY)
  {
    throw ParseException(
        "AnyValueValueElementBuildNode::Null must be called after \"instance\" key");
  }
  m_anyvalue.ConvertFrom(AnyValue{});
  m_member_name.clear();
  return true;
}

bool AnyValueValueElementBuildNode::Bool(boolean b)
{
  if (m_member_name != serialization::INSTANCE_KEY)
  {
    throw ParseException(
        "AnyValueValueElementBuildNode::Bool must be called after \"instance\" key");
  }
  m_anyvalue.ConvertFrom(AnyValue{b});
  m_member_name.clear();
  return true;
}

bool AnyValueValueElementBuildNode::Int32(int32 i)
{
  if (m_member_name != serialization::INSTANCE_KEY)
  {
    throw ParseException(
        "AnyValueValueElementBuildNode::Int32 must be called after \"instance\" key");
  }
  m_anyvalue.ConvertFrom(i);
  m_member_name.clear();
  return true;
}

bool AnyValueValueElementBuildNode::Uint32(uint32 u)
{
  if (m_member_name != serialization::INSTANCE_KEY)
  {
    throw ParseException(
        "AnyValueValueElementBuildNode::Uint32 must be called after \"instance\" key");
  }
  m_anyvalue.ConvertFrom(u);
  m_member_name.clear();
  return true;
}

bool AnyValueValueElementBuildNode::Int64(int64 i)
{
  if (m_member_name != serialization::INSTANCE_KEY)
  {
    throw ParseException(
        "AnyValueValueElementBuildNode::Int64 must be called after \"instance\" key");
  }
  m_anyvalue.ConvertFrom(i);
  m_member_name.clear();
  return true;
}

bool AnyValueValueElementBuildNode::Uint64(uint64 u)
{
  if (m_member_name != serialization::INSTANCE_KEY)
  {
    throw ParseException(
        "AnyValueValueElementBuildNode::Uint64 must be called after \"instance\" key");
  }
  m_anyvalue.ConvertFrom(u);
  m_member_name.clear();
  return true;
}

bool AnyValueValueElementBuildNode::Double(float64 d)
{
  if (m_member_name != serialization::INSTANCE_KEY)
  {
    throw ParseException(
        "AnyValueValueElementBuildNode::Double must be called after \"instance\" key");
  }
  m_anyvalue.ConvertFrom(d);
  m_member_name.clear();
  return true;
}

bool AnyValueValueElementBuildNode::String(const std::string& str)
{
  if (m_member_name != serialization::INSTANCE_KEY)
  {
    throw ParseException(
        "AnyValueValueElementBuildNode::String must be called after \"instance\" key");
  }
  m_anyvalue.ConvertFrom(str);
  m_member_name.clear();
  return true;
}

bool AnyValueValueElementBuildNode::Member(const std::string& str)
{
  if ((!m_member_name.empty()) || (str != serialization::INSTANCE_KEY))
  {
    throw ParseException(
      "AnyValueValueElementBuildNode::Member must be called once with \"instance\" key");
  }
  m_member_name = str;
  return true;
}

IAnyBuildNode* AnyValueValueElementBuildNode::GetStructureNode()
{
  if (m_value_node || (m_member_name != serialization::INSTANCE_KEY))
  {
    throw ParseException(
      "AnyValueValueElementBuildNode::GetStructureNode must be called after \"instance\" key "
      "and with empty child node");
  }
  m_value_node = std::make_unique<AnyValueBuildNode>(GetTypeRegistry(), this, m_anyvalue);
  return m_value_node.get();
}

IAnyBuildNode* AnyValueValueElementBuildNode::GetArrayNode()
{
  if (m_array_node || (m_member_name != serialization::INSTANCE_KEY))
  {
    throw ParseException(
      "AnyValueValueElementBuildNode::GetArrayNode must be called after \"instance\" key "
      "and with empty child node");
  }
  m_array_node = CreateArrayBuildNode(GetTypeRegistry(), this, m_anyvalue);
  return m_array_node.get();
}

bool AnyValueValueElementBuildNode::PopStructureNode()
{
  if (!m_value_node)
  {
    throw ParseException(
      "AnyValueValueElementBuildNode::PopStructureNode must be called with non-empty child node");
  }
  m_member_name.clear();
  m_value_node.reset();
  return true;
}

bool AnyValueValueElementBuildNode::PopArrayNode()
{
  if (!m_array_node)
  {
    throw ParseException(
      "AnyValueValueElementBuildNode::PopArrayNode must be called with non-empty child node");
  }
  m_member_name.clear();
  m_array_node.reset();
  return true;
}

}  // namespace dto

}  // namespace sup
