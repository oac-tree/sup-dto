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

#ifndef _SUP_UnboundedArrayVisitorNode_h_
#define _SUP_UnboundedArrayVisitorNode_h_

#include "AnyVisitorNode.h"
#include "CreateAnyVisitorNode.h"

namespace sup
{
namespace dto
{
/**
 * @brief Templated visitor node for unbounded arrays.
 */
template <typename T>
class UnboundedArrayVisitorNode : public IAnyVisitorNode<T>
{
public:
  UnboundedArrayVisitorNode(T* any);
  ~UnboundedArrayVisitorNode() override;

  std::unique_ptr<IAnyVisitorNode<T>> NextChild() override;

  void AddProlog(IAnyVisitor<T>& visitor) const override;
  void AddSeparator(IAnyVisitor<T>& visitor) const override;
  void AddEpilog(IAnyVisitor<T>& visitor) const override;

private:
  std::size_t next_index;
};

template <typename T>
UnboundedArrayVisitorNode<T>::UnboundedArrayVisitorNode(T* any)
  : IAnyVisitorNode<T>{any}
  , next_index{0}
{}

template <typename T>
UnboundedArrayVisitorNode<T>::~UnboundedArrayVisitorNode() = default;

template <typename T>
std::unique_ptr<IAnyVisitorNode<T>> UnboundedArrayVisitorNode<T>::NextChild()
{
  if (next_index >= this->GetValue()->NumberOfElements())
  {
    return {};
  }
  T *element = &this->GetValue()->operator[](next_index);
  ++next_index;
  return CreateVisitorNode(element);
}

template <>
std::unique_ptr<IAnyVisitorNode<AnyType>> UnboundedArrayVisitorNode<AnyType>::NextChild();

template <>
std::unique_ptr<IAnyVisitorNode<const AnyType>> UnboundedArrayVisitorNode<const AnyType>::NextChild();

template <typename T>
void UnboundedArrayVisitorNode<T>::AddProlog(IAnyVisitor<T>& visitor) const
{
  visitor.UnboundedArrayProlog(this->GetValue());
}

template <typename T>
void UnboundedArrayVisitorNode<T>::AddSeparator(IAnyVisitor<T>& visitor) const
{
  visitor.ArrayElementSeparator();
}

template <typename T>
void UnboundedArrayVisitorNode<T>::AddEpilog(IAnyVisitor<T>& visitor) const
{
  visitor.UnboundedArrayEpilog(this->GetValue());
}

}  // namespace dto

}  // namespace sup

#endif  // _SUP_UnboundedArrayVisitorNode_h_
