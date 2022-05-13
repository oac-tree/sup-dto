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

#include "AnyValueValueElementBuildNode.h"

#include "AnyValueBuildNode.h"
#include "sup/dto/AnyValueExceptions.h"
#include "ArrayValueBuildNode.h"
#include "SerializationConstants.h"

namespace sup
{
namespace dto
{

AnyValueValueElementBuildNode::AnyValueValueElementBuildNode(
  const AnyTypeRegistry* anytype_registry, IAnyBuildNode* parent, AnyValue& anyvalue_)
  : IAnyBuildNode(anytype_registry, parent)
  , value_node{}
  , array_node{}
  , member_name{}
  , anyvalue{anyvalue_}
{}

AnyValueValueElementBuildNode::~AnyValueValueElementBuildNode() = default;

bool AnyValueValueElementBuildNode::Null()
{
  if (member_name != serialization::INSTANCE_KEY)
  {
    throw ParseException(
        "AnyValueValueElementBuildNode::Null must be called after \"instance\" key");
  }
  anyvalue = AnyValue{};
  member_name.clear();
  return true;
}

bool AnyValueValueElementBuildNode::Bool(boolean b)
{
  if (member_name != serialization::INSTANCE_KEY)
  {
    throw ParseException(
        "AnyValueValueElementBuildNode::Bool must be called after \"instance\" key");
  }
  anyvalue = b;
  member_name.clear();
  return true;
}

bool AnyValueValueElementBuildNode::Int32(int32 i)
{
  if (member_name != serialization::INSTANCE_KEY)
  {
    throw ParseException(
        "AnyValueValueElementBuildNode::Int32 must be called after \"instance\" key");
  }
  anyvalue = i;
  member_name.clear();
  return true;
}

bool AnyValueValueElementBuildNode::Uint32(uint32 u)
{
  if (member_name != serialization::INSTANCE_KEY)
  {
    throw ParseException(
        "AnyValueValueElementBuildNode::Uint32 must be called after \"instance\" key");
  }
  anyvalue = u;
  member_name.clear();
  return true;
}

bool AnyValueValueElementBuildNode::Int64(int64 i)
{
  if (member_name != serialization::INSTANCE_KEY)
  {
    throw ParseException(
        "AnyValueValueElementBuildNode::Int64 must be called after \"instance\" key");
  }
  anyvalue = i;
  member_name.clear();
  return true;
}

bool AnyValueValueElementBuildNode::Uint64(uint64 u)
{
  if (member_name != serialization::INSTANCE_KEY)
  {
    throw ParseException(
        "AnyValueValueElementBuildNode::Uint64 must be called after \"instance\" key");
  }
  anyvalue = u;
  member_name.clear();
  return true;
}

bool AnyValueValueElementBuildNode::Double(float64 d)
{
  if (member_name != serialization::INSTANCE_KEY)
  {
    throw ParseException(
        "AnyValueValueElementBuildNode::Double must be called after \"instance\" key");
  }
  anyvalue = d;
  member_name.clear();
  return true;
}

bool AnyValueValueElementBuildNode::String(const std::string& str)
{
  if (member_name != serialization::INSTANCE_KEY)
  {
    throw ParseException(
        "AnyValueValueElementBuildNode::String must be called after \"instance\" key");
  }
  anyvalue = str;
  member_name.clear();
  return true;
}

bool AnyValueValueElementBuildNode::Member(const std::string& str)
{
  if (!member_name.empty() || str != serialization::INSTANCE_KEY)
  {
    throw ParseException(
      "AnyValueValueElementBuildNode::Member must be called once with \"instance\" key");
  }
  member_name = str;
  return true;
}

IAnyBuildNode* AnyValueValueElementBuildNode::GetStructureNode()
{
  if (value_node || member_name != serialization::INSTANCE_KEY)
  {
    throw ParseException(
      "AnyValueValueElementBuildNode::GetStructureNode must be called after \"instance\" key "
      "and with empty child node");

  }
  value_node.reset(new AnyValueBuildNode(GetTypeRegistry(), this, anyvalue));
  return value_node.get();
}

IAnyBuildNode* AnyValueValueElementBuildNode::GetArrayNode()
{
  if (array_node || member_name != serialization::INSTANCE_KEY)
  {
    throw ParseException(
        "AnyValueValueElementBuildNode::GetArrayNode must be called after \"instance\" key "
      "and with empty child node");
  }
  array_node = CreateArrayBuildNode(GetTypeRegistry(), this, anyvalue);
  return array_node.get();
}

bool AnyValueValueElementBuildNode::PopStructureNode()
{
  if (!value_node)
  {
    throw ParseException(
      "AnyValueValueElementBuildNode::PopStructureNode must be called with non-empty child node");
  }
  member_name.clear();
  value_node.reset();
  return true;
}

bool AnyValueValueElementBuildNode::PopArrayNode()
{
  if (!array_node)
  {
    throw ParseException(
      "AnyValueValueElementBuildNode::PopArrayNode must be called with non-empty child node");
  }
  member_name.clear();
  array_node.reset();
  return true;
}

}  // namespace dto

}  // namespace sup
