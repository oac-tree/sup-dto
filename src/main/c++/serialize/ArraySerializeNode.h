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

#include "AnySerializeNode.h"
#include "CreateAnySerializeNode.h"

namespace sup
{
namespace dto
{
/**
 * @brief Templated serialization node for array types.
 */
template <typename T>
class ArraySerializeNode : public IAnySerializeNode<T>
{
public:
  ArraySerializeNode(const T* any);
  ~ArraySerializeNode() override;

  std::unique_ptr<IAnySerializeNode<T>> NextChild() override;

  void AddProlog(IAnySerializer<T>& serializer) const override;
  void AddSeparator(IAnySerializer<T>& serializer) const override;
  void AddEpilog(IAnySerializer<T>& serializer) const override;

private:
  bool child_returned;
};

template <typename T>
ArraySerializeNode<T>::ArraySerializeNode(const T* any)
  : IAnySerializeNode<T>{any}
  , child_returned{false}
{}

template <typename T>
ArraySerializeNode<T>::~ArraySerializeNode() = default;

template <typename T>
std::unique_ptr<IAnySerializeNode<T>> ArraySerializeNode<T>::NextChild()
{
  if (child_returned)
  {
    return {};
  }
  const T *element_type = &this->GetValue()->operator[]("[]");
  child_returned = true;
  return CreateSerializeNode(element_type);
}

template <typename T>
void ArraySerializeNode<T>::AddProlog(IAnySerializer<T>& serializer) const
{
  serializer.AddArrayProlog(this->GetValue());
}

template <typename T>
void ArraySerializeNode<T>::AddSeparator(IAnySerializer<T>& serializer) const
{
  serializer.AddArrayElementSeparator();
}

template <typename T>
void ArraySerializeNode<T>::AddEpilog(IAnySerializer<T>& serializer) const
{
  serializer.AddArrayEpilog(this->GetValue());
}

}  // namespace dto

}  // namespace sup

#endif  // _SUP_ArraySerializeNode_h_
