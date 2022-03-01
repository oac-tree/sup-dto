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

namespace sup
{
namespace dto
{

AnyTypeBuildNode::AnyTypeBuildNode(IAnyBuildNode* parent)
  : IAnyBuildNode{parent}
  , element_node{}
  , member_array_node{}
  , current_member_name{}
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
  number_elements = u;
  current_member_name.clear();
  return true;
}

bool AnyTypeBuildNode::String(const std::string& str)
{
  if (current_member_name != serialization::TYPE_KEY)
  {
    throw InvalidOperationException(
        "AnyTypeBuildNode::String must be called after \"type\" key");
  }
  type_name = str;
  current_member_name.clear();
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
  if (HasChildNode() || current_member_name != serialization::ELEMENT_KEY)
  {
    throw InvalidOperationException(
        "AnyTypeBuildNode::GetStructureNode must be called after \"element\" key and with "
        "empty child nodes");
  }
  element_node.reset(new AnyTypeBuildNode(this));
  return element_node.get();
}

IAnyBuildNode* AnyTypeBuildNode::GetArrayNode()
{
  if (HasChildNode() || current_member_name != serialization::ATTRIBUTES_KEY)
  {
    throw InvalidOperationException(
        "AnyTypeBuildNode::GetArrayNode must be called after \"attributes\" key and with "
        "empty child nodes");
  }
  // TODO: create and return member array node
  return {};
}

bool AnyTypeBuildNode::PopStructureNode()
{
  if (!element_node)
  {
    throw InvalidOperationException(
        "AnyTypeBuildNode::PopStructureNode must be called while holding the \"element\" key and "
        "with a non-empty element node");
  }
  return true;
}

bool AnyTypeBuildNode::PopArrayNode()
{
  if (!member_array_node)
  {
    throw InvalidOperationException(
      "AnyTypeBuildNode::PopArrayNode called with empty member array node");
  }
  return true;
}

AnyType AnyTypeBuildNode::GetAnyType() const
{
  // TODO: implement
  return {};
}

bool AnyTypeBuildNode::HasChildNode() const
{
  return element_node || member_array_node;
}

}  // namespace dto

}  // namespace sup
