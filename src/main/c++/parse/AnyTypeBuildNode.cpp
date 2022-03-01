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

#include "AnyTypeBuildNode.h"

#include "AnyValueExceptions.h"
#include "MemberTypeArrayBuildNode.h"
#include "SerializationConstants.h"

#include <map>

namespace sup
{
namespace dto
{

AnyTypeBuildNode::AnyTypeBuildNode(IAnyBuildNode* parent)
  : IAnyBuildNode{parent}
  , element_node{}
  , member_array_node{}
  , current_member_name{}
  , struct_type{false}
  , array_type{false}
  , type_name{}
  , number_elements{}
  , member_types{}
  , element_type{}
{}

AnyTypeBuildNode::~AnyTypeBuildNode() = default;

bool AnyTypeBuildNode::Int32(int32 i)
{
  return Int64(i);
}

bool AnyTypeBuildNode::Uint32(uint32 u)
{
  return Uint64(u);
}

bool AnyTypeBuildNode::Int64(int64 i)
{
  if (i < 0)
  {
    throw InvalidOperationException(
        "AnyTypeBuildNode::Intxx called with negative value");
  }
  return Uint64(i);
}

bool AnyTypeBuildNode::Uint64(uint64 u)
{
  if (current_member_name != serialization::MULTIPLICITY_KEY)
  {
    throw InvalidOperationException(
        "AnyTypeBuildNode::Uint64 must be called after \"multiplicity\" key");
  }
  current_member_name.clear();
  number_elements = u;
  return true;
}

bool AnyTypeBuildNode::String(const std::string& str)
{
  if (current_member_name != serialization::TYPE_KEY)
  {
    throw InvalidOperationException(
        "AnyTypeBuildNode::String must be called after \"type\" key");
  }
  current_member_name.clear();
  type_name = str;
  return true;
}

bool AnyTypeBuildNode::Member(const std::string& str)
{
  if (!current_member_name.empty())
  {
    throw InvalidOperationException(
        "AnyTypeBuildNode::Member called when previous member not finished");
  }
  current_member_name = str;
  return true;
}

IAnyBuildNode* AnyTypeBuildNode::GetStructureNode()
{
  if (IsComplexType() || current_member_name != serialization::ELEMENT_KEY)
  {
    throw InvalidOperationException(
        "AnyTypeBuildNode::GetStructureNode must be called after \"element\" key and with "
        "empty child nodes");
  }
  array_type = true;
  element_node.reset(new AnyTypeBuildNode(this));
  return element_node.get();
}

IAnyBuildNode* AnyTypeBuildNode::GetArrayNode()
{
  if (IsComplexType() || current_member_name != serialization::ATTRIBUTES_KEY)
  {
    throw InvalidOperationException(
        "AnyTypeBuildNode::GetArrayNode must be called after \"attributes\" key and with "
        "empty child nodes");
  }
  struct_type = true;
  member_array_node.reset(new MemberTypeArrayBuildNode(this));
  return member_array_node.get();
}

bool AnyTypeBuildNode::PopStructureNode()
{
  if (!element_node || current_member_name != serialization::ELEMENT_KEY)
  {
    throw InvalidOperationException(
        "AnyTypeBuildNode::PopStructureNode must be called while holding the \"element\" key and "
        "with a non-empty element node");
  }
  current_member_name.clear();
  element_type = element_node->MoveAnyType();
  element_node.reset();
  return true;
}

bool AnyTypeBuildNode::PopArrayNode()
{
  if (!member_array_node || current_member_name != serialization::ATTRIBUTES_KEY)
  {
    throw InvalidOperationException(
      "AnyTypeBuildNode::PopArrayNode called with empty member array node");
  }
  current_member_name.clear();
  member_types = member_array_node->MoveMemberTypes();
  member_array_node.reset();
  return true;
}

AnyType AnyTypeBuildNode::MoveAnyType() const
{
  if (struct_type)
  {
    return MoveStructuredType();
  }
  if (array_type)
  {
    return MoveArrayType();
  }
  return MoveSimpleType();
}

bool AnyTypeBuildNode::IsComplexType() const
{
  return struct_type || array_type;
}

AnyType AnyTypeBuildNode::MoveStructuredType() const
{
  auto result = EmptyStructType(type_name);
  for (auto& member : member_types)
  {
    result.AddMember(member.first, member.second);
  }
  return result;
}

AnyType AnyTypeBuildNode::MoveArrayType() const
{
  return AnyType(number_elements, element_type, type_name);
}

AnyType AnyTypeBuildNode::MoveSimpleType() const
{
  static const std::map<std::string, AnyType> type_map{
    { EMPTY_TYPE_NAME, EmptyType },
    { BOOLEAN_TYPE_NAME, Boolean },
    { CHAR8_TYPE_NAME, Character8 },
    { INT8_TYPE_NAME, SignedInteger8 },
    { UINT8_TYPE_NAME, UnsignedInteger8 },
    { INT16_TYPE_NAME, SignedInteger16 },
    { UINT16_TYPE_NAME, UnsignedInteger16 },
    { INT32_TYPE_NAME, SignedInteger32 },
    { UINT32_TYPE_NAME, UnsignedInteger32 },
    { INT64_TYPE_NAME, SignedInteger64 },
    { UINT64_TYPE_NAME, UnsignedInteger64 },
    { FLOAT32_TYPE_NAME, Float32 },
    { FLOAT64_TYPE_NAME, Float64 },
    { STRING_TYPE_NAME, sup::dto::String }
  };
  auto it = type_map.find(type_name);
  if (it == type_map.end())
  {
    throw InvalidOperationException(
      "AnyTypeBuildNode::MoveSimpleType called with unknown type name");
  }
  return it->second;
}

}  // namespace dto

}  // namespace sup
