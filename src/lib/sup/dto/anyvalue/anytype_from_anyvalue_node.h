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

#ifndef SUP_DTO_ANYTYPE_FROM_ANYVALUE_NODE_H_
#define SUP_DTO_ANYTYPE_FROM_ANYVALUE_NODE_H_

#include <sup/dto/anyvalue.h>

namespace sup
{
namespace dto
{
struct AnyTypeFromAnyValueNode
{
  AnyTypeFromAnyValueNode(const AnyValue* anyvalue);
  ~AnyTypeFromAnyValueNode() = default;

  AnyTypeFromAnyValueNode(const AnyTypeFromAnyValueNode&) = delete;
  AnyTypeFromAnyValueNode& operator=(const AnyTypeFromAnyValueNode&) = delete;
  AnyTypeFromAnyValueNode(AnyTypeFromAnyValueNode&&) = default;
  AnyTypeFromAnyValueNode& operator=(AnyTypeFromAnyValueNode&&) = default;

  const AnyValue* GetSource() const;
  std::size_t NextIndex();
  void AddChild(std::unique_ptr<AnyType>&& child);
  std::vector<std::unique_ptr<AnyType>> MoveChildValues();

private:
  const AnyValue* m_anyvalue;
  std::size_t m_n_children;
  std::size_t m_index;
  std::vector<std::unique_ptr<AnyType>> m_children;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ANYTYPE_FROM_ANYVALUE_NODE_H_
