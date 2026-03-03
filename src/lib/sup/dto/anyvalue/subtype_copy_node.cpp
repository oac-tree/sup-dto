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


#include "subtype_copy_node.h"

namespace sup
{
namespace dto
{
namespace
{
// Is both types are structs, return an empty struct with the same typename as the super_type.
// Otherwise, just return super_type.
AnyType ShallowCopy(const AnyType& src_type, const AnyType& super_type);
}  // unnamed namespace

SubtypeCopyNode::SubtypeCopyNode(const AnyType* src_type, const AnyType* target_type)
  : m_result{ShallowCopy(*src_type, *target_type)}
  , m_src_type{src_type}
  , m_target_type{target_type}
  , m_mem_names{m_src_type->MemberNames()}
  , m_current_child_idx{0}
{}

SubtypeCopyNode::~SubtypeCopyNode() = default;

SubtypeCopyNode::SubtypeCopyNode(SubtypeCopyNode&&) = default;

SubtypeCopyNode& SubtypeCopyNode::operator=(SubtypeCopyNode&&) = default;

bool SubtypeCopyNode::HasNextChild() const
{
  return m_current_child_idx < m_mem_names.size();
}

std::optional<SubtypeCopyNode> SubtypeCopyNode::GetNextChildNode() const
{
  const auto& mem_name = m_mem_names[m_current_child_idx];
  if (!m_target_type->HasField(mem_name))
  {
    return {};
  }
  const auto* src_member = std::addressof((*m_src_type)[mem_name]);
  const auto* target_member = std::addressof((*m_target_type)[mem_name]);
  return SubtypeCopyNode{src_member, target_member};
}

void SubtypeCopyNode::AddChildNode(SubtypeCopyNode& child_node)
{
  const auto& mem_name = m_mem_names[m_current_child_idx];
  ++m_current_child_idx;
  (void)m_result.AddMember(mem_name, child_node.MoveResult());
}

AnyType SubtypeCopyNode::MoveResult()
{
  return std::move(m_result);
}

namespace
{
AnyType ShallowCopy(const AnyType& src_type, const AnyType& super_type)
{
  if (IsStructType(src_type) && IsStructType(super_type))
  {
    return EmptyStructType(super_type.GetTypeName());
  }
  return super_type;
}

}  // unnamed namespace

}  // namespace dto

}  // namespace sup
