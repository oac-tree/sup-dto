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

#ifndef SUP_DTO_MEMBER_VISITORNODE_H_
#define SUP_DTO_MEMBER_VISITORNODE_H_

#include <sup/dto/visit/any_visitornode.h>
#include <sup/dto/visit/create_any_visitornode.h>

#include <string>

namespace sup
{
namespace dto
{
/**
 * @brief Templated visitor node for members of structured types.
 */
template <typename T>
class MemberVisitorNode : public IAnyVisitorNode<T>
{
public:
  MemberVisitorNode(T* any, const std::string& member_name);
  ~MemberVisitorNode() override;

  MemberVisitorNode(const MemberVisitorNode& other) = delete;
  MemberVisitorNode(MemberVisitorNode&& other) = delete;
  MemberVisitorNode& operator=(const MemberVisitorNode& other) = delete;
  MemberVisitorNode& operator=(MemberVisitorNode&& other) = delete;

  std::unique_ptr<IAnyVisitorNode<T>> NextChild() override;

  void AddProlog(IAnyVisitor<T>& visitor) const override;
  void AddSeparator(IAnyVisitor<T>& visitor) const override;
  void AddEpilog(IAnyVisitor<T>& visitor) const override;

private:
  std::string m_member_name;
  bool m_child_returned;
};

template <typename T>
MemberVisitorNode<T>::MemberVisitorNode(T* any, const std::string& member_name)
  : IAnyVisitorNode<T>{any}
  , m_member_name{member_name}
  , m_child_returned{false}
{}

template <typename T>
MemberVisitorNode<T>::~MemberVisitorNode() = default;

template <typename T>
std::unique_ptr<IAnyVisitorNode<T>> MemberVisitorNode<T>::NextChild()
{
  if (m_child_returned)
  {
    return {};
  }
  m_child_returned = true;
  return CreateVisitorNode(this->GetValue());
}

template <typename T>
void MemberVisitorNode<T>::AddProlog(IAnyVisitor<T>& visitor) const
{
  visitor.MemberProlog(this->GetValue(), m_member_name);
}

template <typename T>
void MemberVisitorNode<T>::AddSeparator(IAnyVisitor<T>&) const
{}

template <typename T>
void MemberVisitorNode<T>::AddEpilog(IAnyVisitor<T>& visitor) const
{
  visitor.MemberEpilog(this->GetValue(), m_member_name);
}

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_MEMBER_VISITORNODE_H_
