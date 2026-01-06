/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : SUP - DTO
 *
 * Description   : Data transfer objects for SUP
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

#include "anyvalue_from_anytype_node.h"

#include "node_utils.h"

namespace sup
{
namespace dto
{

AnyValueFromAnyTypeNode::AnyValueFromAnyTypeNode(const AnyType* anytype, Constraints constraints)
  : m_anytype{anytype}
  , m_n_children{anytype->NumberOfChildren()}
  , m_constraints{constraints}
  , m_index{0}
  , m_children{}
{}

const AnyType* AnyValueFromAnyTypeNode::GetSource() const
{
  return m_anytype;
}

Constraints AnyValueFromAnyTypeNode::GetConstraints() const
{
  return m_constraints;
}

std::size_t AnyValueFromAnyTypeNode::NextIndex()
{
  if (m_index < m_n_children)
  {
    return m_index++;
  }
  return kInvalidIndex;
}

Constraints AnyValueFromAnyTypeNode::GetChildConstraints() const
{
  // If source is an array, child always has a locked type; otherwise, just inherit the constraints
  if (IsArrayType(*m_anytype))
  {
    return Constraints::kLockedType;
  }
  return m_constraints;
}

void AnyValueFromAnyTypeNode::AddChild(std::unique_ptr<AnyValue>&& child)
{
  m_children.push_back(std::move(child));
}

std::vector<std::unique_ptr<AnyValue>>&& AnyValueFromAnyTypeNode::MoveChildValues()
{
  return std::move(m_children);
}

}  // namespace dto

}  // namespace sup
