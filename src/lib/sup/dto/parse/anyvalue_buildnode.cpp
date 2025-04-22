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

#include "anyvalue_buildnode.h"

#include <sup/dto/parse/arrayvalue_buildnode.h>

#include <sup/dto/anyvalue_exceptions.h>

namespace sup
{
namespace dto
{

AnyValueBuildNode::AnyValueBuildNode(const AnyTypeRegistry* anytype_registry,
                                     IAnyBuildNode* parent, AnyValue& anyvalue)
  : IAnyBuildNode(anytype_registry, parent)
  , m_value_node{}
  , m_array_node{}
  , m_member_name{}
  , m_anyvalue{anyvalue}
{}

AnyValueBuildNode::~AnyValueBuildNode() = default;

bool AnyValueBuildNode::Null()
{
  if (m_member_name.empty())
  {
    throw ParseException(
        "AnyValueBuildNode::Null must be called after member name");
  }
  m_anyvalue[m_member_name].ConvertFrom({});
  m_member_name.clear();
  return true;
}

bool AnyValueBuildNode::Bool(boolean b)
{
  if (m_member_name.empty())
  {
    throw ParseException(
        "AnyValueBuildNode::Bool must be called after member name");
  }
  m_anyvalue[m_member_name].ConvertFrom(b);
  m_member_name.clear();
  return true;
}

bool AnyValueBuildNode::Int32(int32 i)
{
  if (m_member_name.empty())
  {
    throw ParseException(
        "AnyValueBuildNode::Int32 must be called after member name");
  }
  m_anyvalue[m_member_name].ConvertFrom(i);
  m_member_name.clear();
  return true;
}

bool AnyValueBuildNode::Uint32(uint32 u)
{
  if (m_member_name.empty())
  {
    throw ParseException(
        "AnyValueBuildNode::Uint32 must be called after member name");
  }
  m_anyvalue[m_member_name].ConvertFrom(u);
  m_member_name.clear();
  return true;
}

bool AnyValueBuildNode::Int64(int64 i)
{
  if (m_member_name.empty())
  {
    throw ParseException(
        "AnyValueBuildNode::Int64 must be called after member name");
  }
  m_anyvalue[m_member_name].ConvertFrom(i);
  m_member_name.clear();
  return true;
}

bool AnyValueBuildNode::Uint64(uint64 u)
{
  if (m_member_name.empty())
  {
    throw ParseException(
        "AnyValueBuildNode::Uint64 must be called after member name");
  }
  m_anyvalue[m_member_name].ConvertFrom(u);
  m_member_name.clear();
  return true;
}

bool AnyValueBuildNode::Double(float64 d)
{
  if (m_member_name.empty())
  {
    throw ParseException(
        "AnyValueBuildNode::Double must be called after member name");
  }
  m_anyvalue[m_member_name].ConvertFrom(d);
  m_member_name.clear();
  return true;
}

bool AnyValueBuildNode::String(const std::string& str)
{
  if (m_member_name.empty())
  {
    throw ParseException(
        "AnyValueBuildNode::String must be called after member name");
  }
  m_anyvalue[m_member_name].ConvertFrom(str);
  m_member_name.clear();
  return true;
}

bool AnyValueBuildNode::Member(const std::string& str)
{
  if ((!m_member_name.empty()) || (str.empty()))
  {
    throw ParseException(
        "AnyValueBuildNode::Member must be called when previous key was resolved and "
        "with non-empty name");
  }
  m_member_name = str;
  return true;
}

IAnyBuildNode* AnyValueBuildNode::GetStructureNode()
{
  if ((m_value_node || (m_member_name.empty())))
  {
    throw ParseException(
        "AnyValueBuildNode::GetStructureNode must be called with non-empty member name "
        "and empty child node");
  }
  m_value_node = std::make_unique<AnyValueBuildNode>(GetTypeRegistry(), this, m_anyvalue[m_member_name]);
  return m_value_node.get();
}

IAnyBuildNode* AnyValueBuildNode::GetArrayNode()
{
  if ((m_array_node || (m_member_name.empty())))
  {
    throw ParseException(
        "AnyValueBuildNode::GetArrayNode must be called with non-empty member name "
        "and empty child node");
  }
  AnyValue& member_val = m_anyvalue[m_member_name];
  m_array_node = CreateArrayBuildNode(GetTypeRegistry(), this, member_val);
  return m_array_node.get();
}

bool AnyValueBuildNode::PopStructureNode()
{
  if ((!m_value_node) || (m_member_name.empty()))
  {
    throw ParseException(
        "AnyValueBuildNode::PopStructureNode must be called with non-empty member name "
        "and non-empty child node");
  }
  m_member_name.clear();
  m_value_node.reset();
  return true;
}

bool AnyValueBuildNode::PopArrayNode()
{
  if ((!m_array_node) || (m_member_name.empty()))
  {
    throw ParseException(
        "AnyValueBuildNode::PopArrayNode must be called with non-empty member name "
        "and non-empty child node");
  }
  m_member_name.clear();
  m_array_node.reset();
  return true;
}

}  // namespace dto

}  // namespace sup
