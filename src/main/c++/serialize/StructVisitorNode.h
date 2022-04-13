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
 * Copyright (c) : 2010-2022 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#ifndef _SUP_StructVisitorNode_h_
#define _SUP_StructVisitorNode_h_

#include "AnyVisitorNode.h"
#include "MemberVisitorNode.h"

namespace sup
{
namespace dto
{
/**
 * @brief Templated Serialization node for structured types.
 */
template <typename T>
class StructVisitorNode : public IAnyVisitorNode<T>
{
public:
  StructVisitorNode(T* any);
  ~StructVisitorNode() override;

  std::unique_ptr<IAnyVisitorNode<T>> NextChild() override;

  void AddProlog(IAnyVisitor<T>& serializer) const override;
  void AddSeparator(IAnyVisitor<T>& serializer) const override;
  void AddEpilog(IAnyVisitor<T>& serializer) const override;

private:
  std::size_t next_index;
};

template <typename T>
StructVisitorNode<T>::StructVisitorNode(T* any)
  : IAnyVisitorNode<T>{any}
  , next_index{0}
{}

template <typename T>
StructVisitorNode<T>::~StructVisitorNode() = default;

template <typename T>
std::unique_ptr<IAnyVisitorNode<T>> StructVisitorNode<T>::NextChild()
{
  auto member_names = this->GetValue()->MemberNames();
  if (next_index >= member_names.size())
  {
    return {};
  }
  auto member_name = member_names[next_index];
  ++next_index;
  T *member_type = &this->GetValue()->operator[](member_name);
  std::unique_ptr<IAnyVisitorNode<T>> result{
      new MemberVisitorNode<T>(member_type, member_name)};
  return result;
}

template <typename T>
void StructVisitorNode<T>::AddProlog(IAnyVisitor<T>& serializer) const
{
  serializer.StructProlog(this->GetValue());
}

template <typename T>
void StructVisitorNode<T>::AddSeparator(IAnyVisitor<T>& serializer) const
{
  serializer.StructMemberSeparator();
}

template <typename T>
void StructVisitorNode<T>::AddEpilog(IAnyVisitor<T>& serializer) const
{
  serializer.StructEpilog(this->GetValue());
}

}  // namespace dto

}  // namespace sup

#endif  // _SUP_StructVisitorNode_h_
