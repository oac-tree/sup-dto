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

/**
 * @file ArrayVisitorNode.h
 * @brief Header file for the ArrayVisitorNode class template.
 * @date 16/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the ArrayVisitorNode class template.
 */

#ifndef _SUP_ArrayVisitorNode_h_
#define _SUP_ArrayVisitorNode_h_

#include "AnyVisitorNode.h"
#include "CreateAnyVisitorNode.h"

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
  ArrayVisitorNode(T* any);
  ~ArrayVisitorNode() override;

  std::unique_ptr<IAnyVisitorNode<T>> NextChild() override;

  void AddProlog(IAnyVisitor<T>& serializer) const override;
  void AddSeparator(IAnyVisitor<T>& serializer) const override;
  void AddEpilog(IAnyVisitor<T>& serializer) const override;

private:
  std::size_t next_index;
};

template <typename T>
ArrayVisitorNode<T>::ArrayVisitorNode(T* any)
  : IAnyVisitorNode<T>{any}
  , next_index{0}
{}

template <typename T>
ArrayVisitorNode<T>::~ArrayVisitorNode() = default;

template <typename T>
std::unique_ptr<IAnyVisitorNode<T>> ArrayVisitorNode<T>::NextChild()
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
std::unique_ptr<IAnyVisitorNode<AnyType>> ArrayVisitorNode<AnyType>::NextChild();

template <>
std::unique_ptr<IAnyVisitorNode<const AnyType>> ArrayVisitorNode<const AnyType>::NextChild();

template <typename T>
void ArrayVisitorNode<T>::AddProlog(IAnyVisitor<T>& serializer) const
{
  serializer.ArrayProlog(this->GetValue());
}

template <typename T>
void ArrayVisitorNode<T>::AddSeparator(IAnyVisitor<T>& serializer) const
{
  serializer.ArrayElementSeparator();
}

template <typename T>
void ArrayVisitorNode<T>::AddEpilog(IAnyVisitor<T>& serializer) const
{
  serializer.ArrayEpilog(this->GetValue());
}

}  // namespace dto

}  // namespace sup

#endif  // _SUP_ArrayVisitorNode_h_
