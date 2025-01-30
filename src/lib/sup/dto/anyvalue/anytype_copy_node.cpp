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

namespace sup
{
namespace dto
{
AnyTypeCopyNode::AnyTypeCopyNode(const AnyType* src, std::vector<std::string>&& child_names)
  : m_src{src}
  , m_index{0}
  , m_child_names{std::move(child_names)}
  , m_children{}
{}

AnyTypeCopyNode::~AnyTypeCopyNode() = default;

const AnyType* AnyTypeCopyNode::GetSource() const
{
  return m_src;
}

std::string AnyTypeCopyNode::NextChildName()
{
  if (m_index < m_child_names.size())
  {
    return m_child_names[m_index++];
  }
  return {};
}

void AnyTypeCopyNode::AddChild(AnyType&& child)
{
  m_children.push_back(std::move(child));
}

std::vector<AnyType> AnyTypeCopyNode::MoveChildTypes()
{
  return std::move(m_children);
}

}  // namespace dto

}  // namespace sup
