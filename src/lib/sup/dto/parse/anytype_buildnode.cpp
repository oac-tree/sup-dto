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
 * Copyright (c) : 2010-2024 ITER Organization,
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
#include "sup/dto/anytype.h"
#include "sup/dto/basic_scalar_types.h"

#include <sup/dto/parse/membertype_array_buildnode.h>
#include <sup/dto/parse/serialization_constants.h>

#include <sup/dto/anytype_registry.h>
#include <sup/dto/anyvalue_exceptions.h>

namespace sup
{
namespace dto
{

AnyTypeBuildNode::AnyTypeBuildNode(const AnyTypeRegistry* anytype_registry,
                                   IAnyBuildNode* parent)
  : IAnyBuildNode(anytype_registry, parent)
  , m_element_node{}
  , m_member_array_node{}
  , m_current_member_name{}
  , m_struct_type{false}
  , m_array_type{false}
  , m_type_name{}
  , m_number_elements{}
  , m_array_bound_specified{false}
  , m_member_types{}
  , m_element_type{}
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
  return Uint64(static_cast<uint64>(i));
}

bool AnyTypeBuildNode::Uint64(uint64 u)
{
  if (m_current_member_name != serialization::MULTIPLICITY_KEY)
  {
    throw ParseException(
        "AnyTypeBuildNode::Uint64 must be called after \"multiplicity\" key");
  }
  m_current_member_name.clear();
  m_number_elements = u;
  m_array_bound_specified = true;
  return true;
}

bool AnyTypeBuildNode::String(const std::string& str)
{
  if (m_current_member_name != serialization::TYPE_KEY)
  {
    throw ParseException(
        "AnyTypeBuildNode::String must be called after \"type\" key");
  }
  m_current_member_name.clear();
  m_type_name = str;
  return true;
}

bool AnyTypeBuildNode::Member(const std::string& str)
{
  m_current_member_name = str;
  return true;
}

IAnyBuildNode* AnyTypeBuildNode::GetStructureNode()
{
  if ((IsComplexType()) || (m_current_member_name != serialization::ELEMENT_KEY))
  {
    throw ParseException(
        "AnyTypeBuildNode::GetStructureNode must be called after \"element\" key and with "
        "empty child nodes");
  }
  m_array_type = true;
  m_element_node = std::make_unique<AnyTypeBuildNode>(GetTypeRegistry(), this);
  return m_element_node.get();
}

IAnyBuildNode* AnyTypeBuildNode::GetArrayNode()
{
  if ((IsComplexType()) || (m_current_member_name != serialization::ATTRIBUTES_KEY))
  {
    throw ParseException(
        "AnyTypeBuildNode::GetArrayNode must be called after \"attributes\" key and with "
        "empty child nodes");
  }
  m_struct_type = true;
  m_member_array_node = std::make_unique<MemberTypeArrayBuildNode>(GetTypeRegistry(), this);
  return m_member_array_node.get();
}

bool AnyTypeBuildNode::PopStructureNode()
{
  m_current_member_name.clear();
  m_element_type = m_element_node->GetAnyType();
  m_element_node.reset();
  return true;
}

bool AnyTypeBuildNode::PopArrayNode()
{
  m_current_member_name.clear();
  m_member_types = m_member_array_node->MoveMemberTypes();
  m_member_array_node.reset();
  return true;
}

AnyType AnyTypeBuildNode::GetAnyType() const
{
  if (m_struct_type)
  {
    return GetStructuredType();
  }
  if (m_array_type)
  {
    return GetArrayType();
  }
  return GetTypeFromRegistry();
}

bool AnyTypeBuildNode::IsComplexType() const
{
  return m_struct_type || m_array_type;
}

AnyType AnyTypeBuildNode::GetStructuredType() const
{
  auto result = EmptyStructType(m_type_name);
  for (auto& member : m_member_types)
  {
    (void)result.AddMember(member.first, member.second);
  }
  return result;
}

AnyType AnyTypeBuildNode::GetArrayType() const
{
  return AnyType(m_number_elements, m_element_type, m_type_name);
}

AnyType AnyTypeBuildNode::GetTypeFromRegistry() const
{
  try
  {
    return GetTypeRegistry()->GetType(m_type_name);
  }
  catch(const MessageException& e)
  {
    throw ParseException(
      "AnyTypeBuildNode::GetTypeFromRegistry called with unknown type name");
  }
}

}  // namespace dto

}  // namespace sup
