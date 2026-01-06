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

#include "anyvalue_root_buildnode.h"

#include <sup/dto/parse/anyvalue_array_buildnode.h>

#include <sup/dto/anyvalue_exceptions.h>

namespace sup
{
namespace dto
{

AnyValueRootBuildNode::AnyValueRootBuildNode(const AnyTypeRegistry* anytype_registry,
                                             IAnyBuildNode* parent)
  : IAnyBuildNode(anytype_registry, parent)
  , m_array_node{}
  , m_anyvalue{}
{}

AnyValueRootBuildNode::AnyValueRootBuildNode(const AnyTypeRegistry* anytype_registry)
  : AnyValueRootBuildNode{anytype_registry, nullptr}
{}

AnyValueRootBuildNode::~AnyValueRootBuildNode() = default;

IAnyBuildNode* AnyValueRootBuildNode::GetArrayNode()
{
  if (m_array_node)
  {
    throw ParseException(
      "AnyValueRootBuildNode::GetArrayNode must be called with empty child node");
  }
  m_array_node = std::make_unique<AnyValueArrayBuildNode>(GetTypeRegistry(), this);
  return m_array_node.get();
}

bool AnyValueRootBuildNode::PopArrayNode()
{
  if (!m_array_node)
  {
    throw ParseException(
        "AnyValueRootBuildNode::PopArrayNode must be called with a non-empty child node");
  }
  m_anyvalue = m_array_node->MoveAnyValue();
  m_array_node.reset();
  return true;
}

AnyValue AnyValueRootBuildNode::MoveAnyValue()
{
  return std::move(m_anyvalue);
}

}  // namespace dto

}  // namespace sup
