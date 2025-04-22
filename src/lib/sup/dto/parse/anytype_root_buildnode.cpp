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
 * Copyright (c) : 2010-2025 ITER Organization,
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

#include "anytype_root_buildnode.h"

#include <sup/dto/parse/anytype_buildnode.h>

#include <sup/dto/anyvalue_exceptions.h>

namespace sup
{
namespace dto
{

AnyTypeRootBuildNode::AnyTypeRootBuildNode(const AnyTypeRegistry* anytype_registry,
                                           IAnyBuildNode* parent)
  : IAnyBuildNode(anytype_registry, parent)
  , m_type_node{}
  , m_anytype{}
{}

AnyTypeRootBuildNode::AnyTypeRootBuildNode(const AnyTypeRegistry* anytype_registry)
  : AnyTypeRootBuildNode{anytype_registry, nullptr}
{}

AnyTypeRootBuildNode::~AnyTypeRootBuildNode() = default;

IAnyBuildNode* AnyTypeRootBuildNode::GetStructureNode()
{
  if (m_type_node)
  {
    throw ParseException(
        "AnyTypeRootBuildNode::GetStructureNode must be called with empty child node");
  }
  m_type_node = std::make_unique<AnyTypeBuildNode>(GetTypeRegistry(), this);
  return m_type_node.get();
}

bool AnyTypeRootBuildNode::PopStructureNode()
{
  if (!m_type_node)
  {
    throw ParseException(
        "AnyTypeRootBuildNode::PopStructureNode must be called with a non-empty child node");
  }
  m_anytype = m_type_node->GetAnyType();
  m_type_node.reset();
  return true;
}

AnyType AnyTypeRootBuildNode::MoveAnyType()
{
  return std::move(m_anytype);
}

}  // namespace dto

}  // namespace sup
