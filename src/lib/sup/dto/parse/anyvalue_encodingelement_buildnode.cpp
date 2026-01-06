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
 * Copyright (c) : 2010-2026 ITER Organization,
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

#include "anyvalue_encodingelement_buildnode.h"

#include <sup/dto/parse/anytype_buildnode.h>
#include <sup/dto/parse/anyvalue_buildnode.h>
#include <sup/dto/parse/serialization_constants.h>

#include <sup/dto/anyvalue_exceptions.h>

namespace sup
{
namespace dto
{

AnyValueEncodingElementBuildNode::AnyValueEncodingElementBuildNode(
  const AnyTypeRegistry* anytype_registry, IAnyBuildNode* parent)
  : IAnyBuildNode(anytype_registry, parent)
  , m_member_name{}
  , m_encoding_ok{false}
{}

AnyValueEncodingElementBuildNode::~AnyValueEncodingElementBuildNode() = default;

bool AnyValueEncodingElementBuildNode::String(const std::string& str)
{
  if ((m_member_name.empty()) || (str != serialization::JSON_ENCODING_1_0))
  {
    throw ParseException(
        std::string("AnyValueEncodingElementBuildNode::String encoding must be: ")
        + serialization::JSON_ENCODING_1_0);
  }
  m_member_name.clear();
  m_encoding_ok = true;
  return true;
}

bool AnyValueEncodingElementBuildNode::Member(const std::string& str)
{
  if (((str != serialization::ENCODING_KEY) || (!m_member_name.empty())) || m_encoding_ok)
  {
    throw ParseException(
        "AnyValueEncodingElementBuildNode::Member must be called only once for setting "
        "encoding value");
  }
  m_member_name = str;
  return true;
}

bool AnyValueEncodingElementBuildNode::EncodingOK() const
{
  return m_encoding_ok;
}

}  // namespace dto

}  // namespace sup
