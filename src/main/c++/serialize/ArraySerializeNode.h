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
 * @file ArraySerializeNode.h
 * @brief Header file for the ArraySerializeNode class template.
 * @date 16/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the ArraySerializeNode class template.
 */

#ifndef _SUP_ArraySerializeNode_h_
#define _SUP_ArraySerializeNode_h_

#include "AnyVisitorNode.h"
#include "CreateAnySerializeNode.h"

namespace sup
{
namespace dto
{
/**
 * @brief Templated serialization node for array types.
 */
template <typename T>
class ArraySerializeNode : public IAnyVisitorNode<const T>
{
public:
  ArraySerializeNode(const T* any);
  ~ArraySerializeNode() override;

  std::unique_ptr<IAnyVisitorNode<const T>> NextChild() override;

  void AddProlog(IAnyVisitor<const T>& serializer) const override;
  void AddSeparator(IAnyVisitor<const T>& serializer) const override;
  void AddEpilog(IAnyVisitor<const T>& serializer) const override;

private:
  std::size_t next_index;
};

template <typename T>
ArraySerializeNode<T>::ArraySerializeNode(const T* any)
  : IAnyVisitorNode<const T>{any}
  , next_index{0}
{}

template <typename T>
ArraySerializeNode<T>::~ArraySerializeNode() = default;

template <typename T>
std::unique_ptr<IAnyVisitorNode<const T>> ArraySerializeNode<T>::NextChild()
{
  if (next_index >= this->GetValue()->NumberOfElements())
  {
    return {};
  }
  const T *element = &this->GetValue()->operator[](next_index);
  ++next_index;
  return CreateSerializeNode(element);
}

template <>
std::unique_ptr<IAnyVisitorNode<const AnyType>> ArraySerializeNode<AnyType>::NextChild();

template <typename T>
void ArraySerializeNode<T>::AddProlog(IAnyVisitor<const T>& serializer) const
{
  serializer.ArrayProlog(this->GetValue());
}

template <typename T>
void ArraySerializeNode<T>::AddSeparator(IAnyVisitor<const T>& serializer) const
{
  serializer.ArrayElementSeparator();
}

template <typename T>
void ArraySerializeNode<T>::AddEpilog(IAnyVisitor<const T>& serializer) const
{
  serializer.ArrayEpilog(this->GetValue());
}

}  // namespace dto

}  // namespace sup

#endif  // _SUP_ArraySerializeNode_h_
