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

#ifndef SUP_DTO_SUBTYPE_COPY_NODE_H_
#define SUP_DTO_SUBTYPE_COPY_NODE_H_

#include <sup/dto/anytype.h>

#include <vector>
#include <string>
#include <optional>

namespace sup
{
namespace dto
{
class SubtypeCopyNode
{
public:
  SubtypeCopyNode(const AnyType* src_type, const AnyType* target_type);
  ~SubtypeCopyNode();

  SubtypeCopyNode(const SubtypeCopyNode&) = delete;
  SubtypeCopyNode& operator=(const SubtypeCopyNode&) = delete;
  SubtypeCopyNode(SubtypeCopyNode&&) noexcept;
  SubtypeCopyNode& operator=(SubtypeCopyNode&&) & noexcept;

  bool HasNextChild() const;

  // The user has to check first if there is a next child to avoid throwing exceptions.
  std::optional<SubtypeCopyNode> GetNextChildNode() const;

  void AddChildNode(SubtypeCopyNode& child_node);

  AnyType MoveResult();

private:
  AnyType m_result;
  const AnyType* m_src_type;
  const AnyType* m_target_type;
  std::vector<std::string> m_mem_names;
  std::size_t m_current_child_idx;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_SUBTYPE_COPY_NODE_H_
