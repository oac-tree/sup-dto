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

#ifndef _SUP_ScalarVisitorNode_h_
#define _SUP_ScalarVisitorNode_h_

#include "AnyVisitorNode.h"

namespace sup
{
namespace dto
{
/**
 * @brief Templated visitor node for scalar types.
 */
template <typename T>
class ScalarVisitorNode : public IAnyVisitorNode<T>
{
public:
  ScalarVisitorNode(T* any);
  ~ScalarVisitorNode() override;

  std::unique_ptr<IAnyVisitorNode<T>> NextChild() override;

  void AddProlog(IAnyVisitor<T>& serializer) const override;
  void AddSeparator(IAnyVisitor<T>& serializer) const override;
  void AddEpilog(IAnyVisitor<T>& serializer) const override;
};

template <typename T>
ScalarVisitorNode<T>::ScalarVisitorNode(T* any)
  : IAnyVisitorNode<T>{any}
{}

template <typename T>
ScalarVisitorNode<T>::~ScalarVisitorNode() = default;

template <typename T>
std::unique_ptr<IAnyVisitorNode<T>> ScalarVisitorNode<T>::NextChild()
{
  return {};
}

template <typename T>
void ScalarVisitorNode<T>::AddProlog(IAnyVisitor<T>& serializer) const
{
  serializer.ScalarProlog(this->GetValue());
}

template <typename T>
void ScalarVisitorNode<T>::AddSeparator(IAnyVisitor<T>&) const
{}

template <typename T>
void ScalarVisitorNode<T>::AddEpilog(IAnyVisitor<T>& serializer) const
{
  serializer.ScalarEpilog(this->GetValue());
}

}  // namespace dto

}  // namespace sup

#endif  // _SUP_ScalarVisitorNode_h_
