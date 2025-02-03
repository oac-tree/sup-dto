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
 * Copyright (c) : 2010-2025 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include "anyvalue_copy_node.h"

namespace sup
{
namespace dto
{
AnyValueCopyNode::AnyValueCopyNode(const AnyValue* src, std::vector<std::string>&& child_names,
                                   Constraints constraints)
  : m_src{src}
  , m_index{0}
  , m_child_names{std::move(child_names)}
  , m_constraints{constraints}
  , m_children{}
{}

const AnyValue* AnyValueCopyNode::GetSource() const
{
  return m_src;
}

Constraints AnyValueCopyNode::GetConstraints() const
{
  return m_constraints;
}

std::string AnyValueCopyNode::NextChildName()
{
  if (m_index < m_child_names.size())
  {
    return m_child_names[m_index++];
  }
  return {};
}

Constraints AnyValueCopyNode::GetChildConstraints() const
{
  // If source is an array, child always has a locked type; otherwise, just inherit the constraints
  if (IsArrayValue(*m_src))
  {
    return Constraints::kLockedType;
  }
  return m_constraints;
}

void AnyValueCopyNode::AddChild(std::unique_ptr<AnyValue>&& child)
{
  m_children.push_back(std::move(child));
}

std::vector<std::unique_ptr<AnyValue>> AnyValueCopyNode::MoveChildValues()
{
  return std::move(m_children);
}

}  // namespace dto

}  // namespace sup
