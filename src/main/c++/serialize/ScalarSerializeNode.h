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
 * @file ScalarSerializeNode.h
 * @brief Header file for the ScalarSerializeNode class template.
 * @date 16/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the ScalarSerializeNode class template.
 */

#ifndef _SUP_ScalarSerializeNode_h_
#define _SUP_ScalarSerializeNode_h_

#include "AnyVisitorNode.h"

namespace sup
{
namespace dto
{
/**
 * @brief Templated serialization node for scalar types.
 */
template <typename T>
class ScalarSerializeNode : public IAnyVisitorNode<T>
{
public:
  ScalarSerializeNode(T* any);
  ~ScalarSerializeNode() override;

  std::unique_ptr<IAnyVisitorNode<T>> NextChild() override;

  void AddProlog(IAnyVisitor<T>& serializer) const override;
  void AddSeparator(IAnyVisitor<T>& serializer) const override;
  void AddEpilog(IAnyVisitor<T>& serializer) const override;
};

template <typename T>
ScalarSerializeNode<T>::ScalarSerializeNode(T* any)
  : IAnyVisitorNode<T>{any}
{}

template <typename T>
ScalarSerializeNode<T>::~ScalarSerializeNode() = default;

template <typename T>
std::unique_ptr<IAnyVisitorNode<T>> ScalarSerializeNode<T>::NextChild()
{
  return {};
}

template <typename T>
void ScalarSerializeNode<T>::AddProlog(IAnyVisitor<T>& serializer) const
{
  serializer.ScalarProlog(this->GetValue());
}

template <typename T>
void ScalarSerializeNode<T>::AddSeparator(IAnyVisitor<T>&) const
{}

template <typename T>
void ScalarSerializeNode<T>::AddEpilog(IAnyVisitor<T>& serializer) const
{
  serializer.ScalarEpilog(this->GetValue());
}

}  // namespace dto

}  // namespace sup

#endif  // _SUP_ScalarSerializeNode_h_
