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

#ifndef SUP_DTO_ANYTYPE_COPY_NODE_H_
#define SUP_DTO_ANYTYPE_COPY_NODE_H_

#include <sup/dto/anytype.h>

#include <limits>

namespace sup
{
namespace dto
{
class AnyTypeCopyNode
{
public:
  explicit AnyTypeCopyNode(const AnyType* src);
  ~AnyTypeCopyNode() = default;

  AnyTypeCopyNode(const AnyTypeCopyNode&) = delete;
  AnyTypeCopyNode& operator=(const AnyTypeCopyNode&) = delete;
  AnyTypeCopyNode(AnyTypeCopyNode&&) = default;
  AnyTypeCopyNode& operator=(AnyTypeCopyNode&&) = default;

  const AnyType* GetSource() const;
  std::size_t NextIndex();
  void AddChild(std::unique_ptr<AnyType>&& child);
  std::vector<std::unique_ptr<AnyType>>&& MoveChildTypes();

private:
  const AnyType* m_src;
  std::size_t m_n_children;
  std::size_t m_index;
  std::vector<std::unique_ptr<AnyType>> m_children;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ANYTYPE_COPY_NODE_H_
