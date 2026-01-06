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

#ifndef SUP_DTO_ARRAY_VISITORNODE_H_
#define SUP_DTO_ARRAY_VISITORNODE_H_

#include <sup/dto/visit/any_visitornode.h>
#include <sup/dto/visit/create_any_visitornode.h>

namespace sup
{
namespace dto
{
/**
 * @brief Templated visitor node for arrays.
 */
template <typename T>
class ArrayVisitorNode : public IAnyVisitorNode<T>
{
public:
  explicit ArrayVisitorNode(T* any);
  ~ArrayVisitorNode() override;

  ArrayVisitorNode(const ArrayVisitorNode& other) = delete;
  ArrayVisitorNode(ArrayVisitorNode&& other) = delete;
  ArrayVisitorNode& operator=(const ArrayVisitorNode& other) = delete;
  ArrayVisitorNode& operator=(ArrayVisitorNode&& other) = delete;

  std::unique_ptr<IAnyVisitorNode<T>> NextChild() override;

  void AddProlog(IAnyVisitor<T>& visitor) const override;
  void AddSeparator(IAnyVisitor<T>& visitor) const override;
  void AddEpilog(IAnyVisitor<T>& visitor) const override;

private:
  std::size_t m_next_index;
};

template <typename T>
ArrayVisitorNode<T>::ArrayVisitorNode(T* any)
  : IAnyVisitorNode<T>{any}
  , m_next_index{0}
{}

template <typename T>
ArrayVisitorNode<T>::~ArrayVisitorNode() = default;

template <typename T>
std::unique_ptr<IAnyVisitorNode<T>> ArrayVisitorNode<T>::NextChild()
{
  if (m_next_index >= this->GetValue()->NumberOfElements())
  {
    return {};
  }
  T *element = &this->GetValue()->operator[](m_next_index);
  ++m_next_index;
  return CreateVisitorNode(element);
}

template <>
std::unique_ptr<IAnyVisitorNode<AnyType>> ArrayVisitorNode<AnyType>::NextChild();

template <>
std::unique_ptr<IAnyVisitorNode<const AnyType>> ArrayVisitorNode<const AnyType>::NextChild();

template <typename T>
void ArrayVisitorNode<T>::AddProlog(IAnyVisitor<T>& visitor) const
{
  visitor.ArrayProlog(this->GetValue());
}

template <typename T>
void ArrayVisitorNode<T>::AddSeparator(IAnyVisitor<T>& visitor) const
{
  visitor.ArrayElementSeparator();
}

template <typename T>
void ArrayVisitorNode<T>::AddEpilog(IAnyVisitor<T>& visitor) const
{
  visitor.ArrayEpilog(this->GetValue());
}

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ARRAY_VISITORNODE_H_
