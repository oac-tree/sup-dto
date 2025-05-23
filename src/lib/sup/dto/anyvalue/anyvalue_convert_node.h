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

#ifndef SUP_DTO_ANYVALUE_CONVERT_NODE_H_
#define SUP_DTO_ANYVALUE_CONVERT_NODE_H_

#include <sup/dto/anyvalue.h>

namespace sup
{
namespace dto
{
struct AnyValueConvertNode
{
  AnyValueConvertNode(AnyValue* left, const AnyValue* right);
  ~AnyValueConvertNode() = default;

  AnyValueConvertNode(const AnyValueConvertNode&) = delete;
  AnyValueConvertNode& operator=(const AnyValueConvertNode&) = delete;
  AnyValueConvertNode(AnyValueConvertNode&&) = default;
  AnyValueConvertNode& operator=(AnyValueConvertNode&&) = default;

  AnyValue* m_left;
  const AnyValue* m_right;
  std::size_t m_n_children;
  std::size_t m_index;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ANYVALUE_CONVERT_NODE_H_
