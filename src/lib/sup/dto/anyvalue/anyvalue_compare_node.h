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

#ifndef SUP_DTO_ANYVALUE_COMPARE_NODE_H_
#define SUP_DTO_ANYVALUE_COMPARE_NODE_H_

#include <sup/dto/anyvalue.h>

namespace sup
{
namespace dto
{
struct AnyValueCompareNode
{
  AnyValueCompareNode(const AnyValue* left, const AnyValue* right,
                     std::vector<std::string>&& child_names);
  ~AnyValueCompareNode() = default;

  AnyValueCompareNode(const AnyValueCompareNode&) = default;
  AnyValueCompareNode& operator=(const AnyValueCompareNode&) = default;
  AnyValueCompareNode(AnyValueCompareNode&&) = default;
  AnyValueCompareNode& operator=(AnyValueCompareNode&&) = default;

  const AnyValue* m_left;
  const AnyValue* m_right;
  std::size_t m_index;
  std::vector<std::string> m_child_names;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ANYVALUE_COMPARE_NODE_H_
