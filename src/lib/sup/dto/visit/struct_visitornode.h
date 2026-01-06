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

#ifndef SUP_DTO_STRUCT_VISITORNODE_H_
#define SUP_DTO_STRUCT_VISITORNODE_H_

#include <sup/dto/visit/any_visitornode.h>
#include <sup/dto/visit/member_visitornode.h>

namespace sup
{
namespace dto
{
/**
 * @brief Templated visitor node for structured types.
 */
template <typename T>
class StructVisitorNode : public IAnyVisitorNode<T>
{
public:
  explicit StructVisitorNode(T* any);
  ~StructVisitorNode() override;

  StructVisitorNode(const StructVisitorNode& other) = delete;
  StructVisitorNode(StructVisitorNode&& other) = delete;
  StructVisitorNode& operator=(const StructVisitorNode& other) = delete;
  StructVisitorNode& operator=(StructVisitorNode&& other) = delete;

  std::unique_ptr<IAnyVisitorNode<T>> NextChild() override;

  void AddProlog(IAnyVisitor<T>& visitor) const override;
  void AddSeparator(IAnyVisitor<T>& visitor) const override;
  void AddEpilog(IAnyVisitor<T>& visitor) const override;

private:
  std::size_t m_next_index;
  std::vector<std::string> m_member_names;
};

template <typename T>
StructVisitorNode<T>::StructVisitorNode(T* any)
  : IAnyVisitorNode<T>{any}
  , m_next_index{0}
  , m_member_names{any->MemberNames()}
{}

template <typename T>
StructVisitorNode<T>::~StructVisitorNode() = default;

template <typename T>
std::unique_ptr<IAnyVisitorNode<T>> StructVisitorNode<T>::NextChild()
{
  if (m_next_index >= m_member_names.size())
  {
    return {};
  }
  T* member = GetIndexedChild(this->GetValue(), m_next_index);
  const auto& member_name = m_member_names[m_next_index];
  ++m_next_index;
  return std::make_unique<MemberVisitorNode<T>>(member, member_name);
}

template <typename T>
void StructVisitorNode<T>::AddProlog(IAnyVisitor<T>& visitor) const
{
  visitor.StructProlog(this->GetValue());
}

template <typename T>
void StructVisitorNode<T>::AddSeparator(IAnyVisitor<T>& visitor) const
{
  visitor.StructMemberSeparator();
}

template <typename T>
void StructVisitorNode<T>::AddEpilog(IAnyVisitor<T>& visitor) const
{
  visitor.StructEpilog(this->GetValue());
}

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_STRUCT_VISITORNODE_H_
