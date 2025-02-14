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

#include "anytype_copy_node.h"

#include "node_utils.h"

namespace sup
{
namespace dto
{
AnyTypeCopyNode::AnyTypeCopyNode(const AnyType* src)
  : m_src{src}
  , m_n_children{m_src->NumberOfChildren()}
  , m_index{0}
  , m_children{}
{}

const AnyType* AnyTypeCopyNode::GetSource() const
{
  return m_src;
}

std::size_t AnyTypeCopyNode::NextIndex()
{
  if (m_index < m_n_children)
  {
    return m_index++;
  }
  return kInvalidIndex;
}

void AnyTypeCopyNode::AddChild(std::unique_ptr<AnyType>&& child)
{
  m_children.push_back(std::move(child));
}

std::vector<std::unique_ptr<AnyType>>&& AnyTypeCopyNode::MoveChildTypes()
{
  return std::move(m_children);
}

}  // namespace dto

}  // namespace sup
