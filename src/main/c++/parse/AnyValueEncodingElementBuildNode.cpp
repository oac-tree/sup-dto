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

#include "AnyValueEncodingElementBuildNode.h"

#include "AnyTypeBuildNode.h"
#include "AnyValueBuildNode.h"
#include "AnyValueExceptions.h"
#include "SerializationConstants.h"

namespace sup
{
namespace dto
{

AnyValueEncodingElementBuildNode::AnyValueEncodingElementBuildNode(IAnyBuildNode* parent)
  : IAnyBuildNode{parent}
  , member_name{}
  , encoding_ok{false}
{}

AnyValueEncodingElementBuildNode::~AnyValueEncodingElementBuildNode() = default;

bool AnyValueEncodingElementBuildNode::String(const std::string& str)
{
  if (member_name.empty() || str != serialization::JSON_ENCODING_1_0)
  {
    throw InvalidOperationException(
        std::string("AnyValueEncodingElementBuildNode::String encoding must be: ")
        + serialization::JSON_ENCODING_1_0);
  }
  member_name.clear();
  encoding_ok = true;
  return true;
}

bool AnyValueEncodingElementBuildNode::Member(const std::string& str)
{
  if (str != serialization::ENCODING_KEY || !member_name.empty() || encoding_ok)
  {
    throw InvalidOperationException(
        "AnyValueEncodingElementBuildNode::Member must be called only once for setting "
        "encoding value");
  }
  member_name = str;
  return true;
}

bool AnyValueEncodingElementBuildNode::EncodingOK() const
{
  return encoding_ok;
}

}  // namespace dto

}  // namespace sup
