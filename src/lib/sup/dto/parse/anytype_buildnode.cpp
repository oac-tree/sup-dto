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

#include "anytype_buildnode.h"

#include <sup/dto/parse/membertype_array_buildnode.h>
#include <sup/dto/parse/serialization_constants.h>

#include <sup/dto/anytype_registry.h>
#include <sup/dto/anyvalue_exceptions.h>

#include <map>

namespace sup
{
namespace dto
{

AnyTypeBuildNode::AnyTypeBuildNode(const AnyTypeRegistry* anytype_registry,
                                   IAnyBuildNode* parent)
  : IAnyBuildNode(anytype_registry, parent)
  , element_node{}
  , member_array_node{}
  , current_member_name{}
  , struct_type{false}
  , array_type{false}
  , type_name{}
  , number_elements{}
  , array_bound_specified{false}
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
    throw ParseException(
        "AnyTypeBuildNode::Intxx called with negative value");
  }
  return Uint64(i);
}

bool AnyTypeBuildNode::Uint64(uint64 u)
{
  if (current_member_name != serialization::MULTIPLICITY_KEY)
  {
    throw ParseException(
        "AnyTypeBuildNode::Uint64 must be called after \"multiplicity\" key");
  }
  current_member_name.clear();
  number_elements = u;
  array_bound_specified = true;
  return true;
}

bool AnyTypeBuildNode::String(const std::string& str)
{
  if (current_member_name != serialization::TYPE_KEY)
  {
    throw ParseException(
        "AnyTypeBuildNode::String must be called after \"type\" key");
  }
  current_member_name.clear();
  type_name = str;
  return true;
}

bool AnyTypeBuildNode::Member(const std::string& str)
{
  current_member_name = str;
  return true;
}

IAnyBuildNode* AnyTypeBuildNode::GetStructureNode()
{
  if (IsComplexType() || current_member_name != serialization::ELEMENT_KEY)
  {
    throw ParseException(
        "AnyTypeBuildNode::GetStructureNode must be called after \"element\" key and with "
        "empty child nodes");
  }
  array_type = true;
  element_node.reset(new AnyTypeBuildNode(GetTypeRegistry(), this));
  return element_node.get();
}

IAnyBuildNode* AnyTypeBuildNode::GetArrayNode()
{
  if (IsComplexType() || current_member_name != serialization::ATTRIBUTES_KEY)
  {
    throw ParseException(
        "AnyTypeBuildNode::GetArrayNode must be called after \"attributes\" key and with "
        "empty child nodes");
  }
  struct_type = true;
  member_array_node.reset(new MemberTypeArrayBuildNode(GetTypeRegistry(), this));
  return member_array_node.get();
}

bool AnyTypeBuildNode::PopStructureNode()
{
  current_member_name.clear();
  element_type = element_node->MoveAnyType();
  element_node.reset();
  return true;
}

bool AnyTypeBuildNode::PopArrayNode()
{
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
  return MoveTypeFromRegistry();
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

AnyType AnyTypeBuildNode::MoveTypeFromRegistry() const
{
  try
  {
    return GetTypeRegistry()->GetType(type_name);
  }
  catch(const InvalidOperationException& e)
  {
    throw ParseException(
      "AnyTypeBuildNode::MoveTypeFromRegistry called with unknown type name");
  }
}

}  // namespace dto

}  // namespace sup
