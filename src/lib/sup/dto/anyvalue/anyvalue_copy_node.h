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

#ifndef SUP_DTO_ANYVALUE_COPY_NODE_H_
#define SUP_DTO_ANYVALUE_COPY_NODE_H_

#include <sup/dto/anyvalue.h>

#include <sup/dto/anyvalue/i_value_data.h>

namespace sup
{
namespace dto
{
class AnyValueCopyNode
{
public:
  AnyValueCopyNode(const AnyValue* src, std::vector<std::string>&& child_names,
                   Constraints constraints);
  ~AnyValueCopyNode() = default;

  AnyValueCopyNode(const AnyValueCopyNode&) = default;
  AnyValueCopyNode& operator=(const AnyValueCopyNode&) = default;
  AnyValueCopyNode(AnyValueCopyNode&&) = default;
  AnyValueCopyNode& operator=(AnyValueCopyNode&&) = default;

  const AnyValue* GetSource() const;
  Constraints GetConstraints() const;
  std::string NextChildName();
  Constraints GetChildConstraints() const;
  void AddChild(std::unique_ptr<AnyValue>&& child);
  std::vector<std::unique_ptr<AnyValue>> MoveChildValues();

private:
  const AnyValue* m_src;
  std::size_t m_index;
  std::vector<std::string> m_child_names;
  Constraints m_constraints;
  std::vector<std::unique_ptr<AnyValue>> m_children;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ANYVALUE_COPY_NODE_H_
