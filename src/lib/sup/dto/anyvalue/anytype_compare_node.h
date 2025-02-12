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

#ifndef SUP_DTO_ANYTYPE_COMPARE_NODE_H_
#define SUP_DTO_ANYTYPE_COMPARE_NODE_H_

#include <sup/dto/anytype.h>

namespace sup
{
namespace dto
{
struct AnyTypeCompareNode
{
  AnyTypeCompareNode(const AnyType* left, const AnyType* right);
  ~AnyTypeCompareNode() = default;

  AnyTypeCompareNode(const AnyTypeCompareNode&) = delete;
  AnyTypeCompareNode& operator=(const AnyTypeCompareNode&) = delete;
  AnyTypeCompareNode(AnyTypeCompareNode&&) = default;
  AnyTypeCompareNode& operator=(AnyTypeCompareNode&&) = default;

  const AnyType* m_left;
  const AnyType* m_right;
  std::size_t m_n_children;
  std::size_t m_index;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ANYTYPE_COMPARE_NODE_H_
