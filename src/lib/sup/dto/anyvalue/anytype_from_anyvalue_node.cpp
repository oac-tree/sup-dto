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
 * SPDX-License-Identifier: MIT
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file LICENSE located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include "anytype_from_anyvalue_node.h"

#include "node_utils.h"

namespace sup
{
namespace dto
{

AnyTypeFromAnyValueNode::AnyTypeFromAnyValueNode(const AnyValue* anyvalue)
  : m_anyvalue{anyvalue}
  , m_n_children{anyvalue->NumberOfChildren()}
  , m_index{0}
  , m_children{}
{
  // Do not descend to children of array type, since their respective AnyType is already
  // available at the AnyValue level
  if (IsArrayValue(*m_anyvalue))
  {
    m_n_children = 0;
  }
}

const AnyValue* AnyTypeFromAnyValueNode::GetSource() const
{
  return m_anyvalue;
}

std::size_t AnyTypeFromAnyValueNode::NextIndex()
{
  if (m_index < m_n_children)
  {
    return m_index++;
  }
  return kInvalidIndex;
}

void AnyTypeFromAnyValueNode::AddChild(std::unique_ptr<AnyType>&& child)
{
  m_children.push_back(std::move(child));
}

std::vector<std::unique_ptr<AnyType>>&& AnyTypeFromAnyValueNode::MoveChildValues()
{
  return std::move(m_children);
}

}  // namespace dto

}  // namespace sup
