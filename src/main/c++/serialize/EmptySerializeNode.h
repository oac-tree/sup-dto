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
 * @file EmptySerializeNode.h
 * @brief Header file for the EmptySerializeNode class template.
 * @date 16/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the EmptySerializeNode class template.
 */

#ifndef _SUP_EmptySerializeNode_h_
#define _SUP_EmptySerializeNode_h_

#include "AnySerializeNode.h"

#include <string>

namespace sup
{
namespace dto
{
/**
 * @brief Templated serialization node for the empty type.
 */
template <typename T>
class EmptySerializeNode : public IAnySerializeNode<T>
{
public:
  EmptySerializeNode(const T* any);
  ~EmptySerializeNode() override;

  std::unique_ptr<IAnySerializeNode<T>> NextChild() override;

  void AddProlog(IAnyVisitor<const T>& serializer) const override;
  void AddSeparator(IAnyVisitor<const T>& serializer) const override;
  void AddEpilog(IAnyVisitor<const T>& serializer) const override;
};

template <typename T>
EmptySerializeNode<T>::EmptySerializeNode(const T* any)
  : IAnySerializeNode<T>{any}
{}

template <typename T>
EmptySerializeNode<T>::~EmptySerializeNode() = default;

template <typename T>
std::unique_ptr<IAnySerializeNode<T>> EmptySerializeNode<T>::NextChild()
{
  return {};
}

template <typename T>
void EmptySerializeNode<T>::AddProlog(IAnyVisitor<const T>& serializer) const
{
  serializer.EmptyProlog(this->GetValue());
}

template <typename T>
void EmptySerializeNode<T>::AddSeparator(IAnyVisitor<const T>&) const
{}

template <typename T>
void EmptySerializeNode<T>::AddEpilog(IAnyVisitor<const T>& serializer) const
{
  serializer.EmptyEpilog(this->GetValue());
}

}  // namespace dto

}  // namespace sup

#endif  // _SUP_EmptySerializeNode_h_
