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

#include "anyvalue_typeelement_buildnode.h"

#include <sup/dto/parse/anytype_buildnode.h>
#include <sup/dto/parse/serialization_constants.h>

#include <sup/dto/anyvalue_exceptions.h>

namespace sup
{
namespace dto
{

AnyValueTypeElementBuildNode::AnyValueTypeElementBuildNode(
  const AnyTypeRegistry* anytype_registry, IAnyBuildNode* parent)
  : IAnyBuildNode(anytype_registry, parent)
  , m_type_node{}
  , m_member_name{}
  , m_anytype{}
{}

AnyValueTypeElementBuildNode::~AnyValueTypeElementBuildNode() = default;

bool AnyValueTypeElementBuildNode::Member(const std::string& str)
{
  if ((!m_member_name.empty()) || (str != serialization::DATATYPE_KEY))
  {
    throw ParseException(
      "AnyValueTypeElementBuildNode::Member must be called once with \"datatype\" key");
  }
  m_member_name = str;
  return true;
}

IAnyBuildNode* AnyValueTypeElementBuildNode::GetStructureNode()
{
  if (m_type_node || (m_member_name != serialization::DATATYPE_KEY))
  {
    throw ParseException(
      "AnyValueTypeElementBuildNode::GetStructureNode must be called after \"datatype\" key "
      "and with empty child node");

  }
  m_type_node.reset(new AnyTypeBuildNode(GetTypeRegistry(), this));
  return m_type_node.get();
}

bool AnyValueTypeElementBuildNode::PopStructureNode()
{
  if (!m_type_node)
  {
    throw ParseException(
      "AnyValueTypeElementBuildNode::PopStructureNode must be called with non-empty child node");
  }
  m_anytype = m_type_node->GetAnyType();
  m_member_name.clear();
  m_type_node.reset();
  return true;
}

AnyType AnyValueTypeElementBuildNode::MoveAnyType()
{
  return std::move(m_anytype);
}

}  // namespace dto

}  // namespace sup
