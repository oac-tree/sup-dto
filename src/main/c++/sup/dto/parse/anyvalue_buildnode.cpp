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

#include "anyvalue_buildnode.h"

#include <sup/dto/parse/arrayvalue_buildnode.h>

#include <sup/dto/anyvalue_exceptions.h>

namespace sup
{
namespace dto
{

AnyValueBuildNode::AnyValueBuildNode(const AnyTypeRegistry* anytype_registry,
                                     IAnyBuildNode* parent, AnyValue& anyvalue_)
  : IAnyBuildNode(anytype_registry, parent)
  , value_node{}
  , array_node{}
  , member_name{}
  , anyvalue{anyvalue_}
{}

AnyValueBuildNode::~AnyValueBuildNode() = default;

bool AnyValueBuildNode::Bool(boolean b)
{
  if (member_name.empty())
  {
    throw ParseException(
        "AnyValueBuildNode::Bool must be called after member name");
  }
  anyvalue[member_name] = b;
  member_name.clear();
  return true;
}

bool AnyValueBuildNode::Int32(int32 i)
{
  if (member_name.empty())
  {
    throw ParseException(
        "AnyValueBuildNode::Int32 must be called after member name");
  }
  anyvalue[member_name] = i;
  member_name.clear();
  return true;
}

bool AnyValueBuildNode::Uint32(uint32 u)
{
  if (member_name.empty())
  {
    throw ParseException(
        "AnyValueBuildNode::Uint32 must be called after member name");
  }
  anyvalue[member_name] = u;
  member_name.clear();
  return true;
}

bool AnyValueBuildNode::Int64(int64 i)
{
  if (member_name.empty())
  {
    throw ParseException(
        "AnyValueBuildNode::Int64 must be called after member name");
  }
  anyvalue[member_name] = i;
  member_name.clear();
  return true;
}

bool AnyValueBuildNode::Uint64(uint64 u)
{
  if (member_name.empty())
  {
    throw ParseException(
        "AnyValueBuildNode::Uint64 must be called after member name");
  }
  anyvalue[member_name] = u;
  member_name.clear();
  return true;
}

bool AnyValueBuildNode::Double(float64 d)
{
  if (member_name.empty())
  {
    throw ParseException(
        "AnyValueBuildNode::Double must be called after member name");
  }
  anyvalue[member_name] = d;
  member_name.clear();
  return true;
}

bool AnyValueBuildNode::String(const std::string& str)
{
  if (member_name.empty())
  {
    throw ParseException(
        "AnyValueBuildNode::String must be called after member name");
  }
  anyvalue[member_name] = str;
  member_name.clear();
  return true;
}

bool AnyValueBuildNode::Member(const std::string& str)
{
  if (!member_name.empty() || str.empty())
  {
    throw ParseException(
        "AnyValueBuildNode::Member must be called when previous key was resolved and "
        "with non-empty name");
  }
  member_name = str;
  return true;
}

IAnyBuildNode* AnyValueBuildNode::GetStructureNode()
{
  if (value_node || member_name.empty())
  {
    throw ParseException(
        "AnyValueBuildNode::GetStructureNode must be called with non-empty member name "
        "and empty child node");
  }
  value_node.reset(new AnyValueBuildNode(GetTypeRegistry(), this, anyvalue[member_name]));
  return value_node.get();
}

IAnyBuildNode* AnyValueBuildNode::GetArrayNode()
{
  if (array_node || member_name.empty())
  {
    throw ParseException(
        "AnyValueBuildNode::GetArrayNode must be called with non-empty member name "
        "and empty child node");
  }
  AnyValue& member_val = anyvalue[member_name];
  array_node = CreateArrayBuildNode(GetTypeRegistry(), this, member_val);
  return array_node.get();
}

bool AnyValueBuildNode::PopStructureNode()
{
  if (!value_node || member_name.empty())
  {
    throw ParseException(
        "AnyValueBuildNode::PopStructureNode must be called with non-empty member name "
        "and non-empty child node");
  }
  member_name.clear();
  value_node.reset();
  return true;
}

bool AnyValueBuildNode::PopArrayNode()
{
  if (!array_node || member_name.empty())
  {
    throw ParseException(
        "AnyValueBuildNode::PopArrayNode must be called with non-empty member name "
        "and non-empty child node");
  }
  member_name.clear();
  array_node.reset();
  return true;
}

}  // namespace dto

}  // namespace sup
