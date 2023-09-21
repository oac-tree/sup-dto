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

#include "anyvalue_array_buildnode.h"

#include <sup/dto/parse/anyvalue_encodingelement_buildnode.h>
#include <sup/dto/parse/anyvalue_typeelement_buildnode.h>
#include <sup/dto/parse/anyvalue_valueelement_buildnode.h>

#include <sup/dto/anyvalue_exceptions.h>

namespace sup
{
namespace dto
{

AnyValueArrayBuildNode::AnyValueArrayBuildNode(const AnyTypeRegistry* anytype_registry,
                                               IAnyBuildNode* parent)
  : IAnyBuildNode(anytype_registry, parent)
  , m_encoding_node{}
  , m_type_node{}
  , m_value_node{}
  , m_processed_nodes{}
  , m_anyvalue{}
{}

AnyValueArrayBuildNode::~AnyValueArrayBuildNode() = default;

IAnyBuildNode* AnyValueArrayBuildNode::GetStructureNode()
{
  if ((m_encoding_node || m_type_node) || m_value_node)
  {
    throw ParseException(
      "AnyValueArrayBuildNode::GetStructureNode cannot be called when a node is still active "
      "(not popped with PopStructureNode)");
  }
  switch (m_processed_nodes)
  {
  case 0:
    m_encoding_node.reset(new AnyValueEncodingElementBuildNode(GetTypeRegistry(), this));
    return m_encoding_node.get();
  case 1:
    m_type_node.reset(new AnyValueTypeElementBuildNode(GetTypeRegistry(), this));
    return m_type_node.get();
  case 2:
    m_value_node.reset(new AnyValueValueElementBuildNode(GetTypeRegistry(), this, m_anyvalue));
    return m_value_node.get();
  default:
    throw ParseException(
      "AnyValueArrayBuildNode::GetStructureNode cannot be called more than 3 times");
  }
}

bool AnyValueArrayBuildNode::PopStructureNode()
{
  switch (m_processed_nodes)
  {
  case 0:
    if ((!m_encoding_node) || (!m_encoding_node->EncodingOK()))
    {
      throw ParseException(
          "AnyValueArrayBuildNode::PopStructureNode called first time with empty encoding node "
          " or invalid encoding");
    }
    m_encoding_node.reset();
    break;
  case 1:
    if (!m_type_node)
    {
      throw ParseException(
          "AnyValueArrayBuildNode::PopStructureNode called second time with empty type node");
    }
    {
      const auto anytype = m_type_node->MoveAnyType();
      m_anyvalue = AnyValue(anytype);
    }
    m_type_node.reset();
    break;
  case 2:
    if (!m_value_node)
    {
      throw ParseException(
          "AnyValueArrayBuildNode::PopStructureNode called third time with empty value node");
    }
    m_value_node.reset();
    break;
  default:
    throw ParseException(
      "AnyValueArrayBuildNode::PopStructureNode cannot be called more than 3 times");
  }
  ++m_processed_nodes;
  return true;
}

AnyValue AnyValueArrayBuildNode::MoveAnyValue()
{
  return std::move(m_anyvalue);
}

}  // namespace dto

}  // namespace sup
