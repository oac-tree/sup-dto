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

#include "AnyValueArrayElementBuildNode.h"

#include "AnyTypeBuildNode.h"
#include "AnyValueBuildNode.h"
#include "AnyValueExceptions.h"
#include "SerializationConstants.h"

namespace sup
{
namespace dto
{

AnyValueArrayElementBuildNode::AnyValueArrayElementBuildNode(IAnyBuildNode* parent,
                                                             AnyValue& anyvalue_)
  : IAnyBuildNode{parent}
  , type_node{}
  , value_node{}
  , member_name{}
  , encoding_ok{false}
  , anyvalue{anyvalue_}
{}

AnyValueArrayElementBuildNode::~AnyValueArrayElementBuildNode() = default;

bool AnyValueArrayElementBuildNode::String(const std::string& str)
{
  if (member_name != serialization::ENCODING_KEY)
  {
    throw InvalidOperationException(
        "AnyValueArrayElementBuildNode::String must be called only for setting encoding value");
  }
  if (str != serialization::JSON_ENCODING_1_0)
  {
    throw InvalidOperationException(
        std::string("AnyValueArrayElementBuildNode::String encoding must be: ")
        + serialization::JSON_ENCODING_1_0);
  }
  member_name.clear();
  encoding_ok = true;
  return true;
}

bool AnyValueArrayElementBuildNode::Member(const std::string& str)
{
  if (!member_name.empty())
  {
    throw InvalidOperationException(
        "AnyValueArrayElementBuildNode::Member called twice without setting value");
  }
  member_name = str;
  return true;
}

IAnyBuildNode* AnyValueArrayElementBuildNode::GetStructureNode()
{
  if (type_node)
  {
    throw InvalidOperationException(
        "AnyValueArrayElementBuildNode::GetStructureNode must be called with empty child node");
  }
  // TODO: select correct node
  type_node.reset(new AnyTypeBuildNode(this));
  return type_node.get();
}

bool AnyValueArrayElementBuildNode::PopStructureNode()
{
  if (!type_node)
  {
    throw InvalidOperationException(
        "AnyValueArrayElementBuildNode::PopStructureNode must be called with a non-empty child node");
  }
  // TODO: take correct action
  anyvalue = value_node->MoveAnyValue();
  type_node.reset();
  return true;
}

AnyType AnyValueArrayElementBuildNode::MoveAnyType() const
{
  return std::move(anytype);
}

AnyValue AnyValueArrayElementBuildNode::MoveAnyValue() const
{
  return std::move(anyvalue);
}

}  // namespace dto

}  // namespace sup
