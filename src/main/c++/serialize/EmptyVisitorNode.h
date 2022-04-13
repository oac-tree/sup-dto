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
 * @file EmptyVisitorNode.h
 * @brief Header file for the EmptyVisitorNode class template.
 * @date 16/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the EmptyVisitorNode class template.
 */

#ifndef _SUP_EmptyVisitorNode_h_
#define _SUP_EmptyVisitorNode_h_

#include "AnyVisitorNode.h"

#include <string>

namespace sup
{
namespace dto
{
/**
 * @brief Templated visitor node for the empty types/values.
 */
template <typename T>
class EmptyVisitorNode : public IAnyVisitorNode<T>
{
public:
  EmptyVisitorNode(T* any);
  ~EmptyVisitorNode() override;

  std::unique_ptr<IAnyVisitorNode<T>> NextChild() override;

  void AddProlog(IAnyVisitor<T>& serializer) const override;
  void AddSeparator(IAnyVisitor<T>& serializer) const override;
  void AddEpilog(IAnyVisitor<T>& serializer) const override;
};

template <typename T>
EmptyVisitorNode<T>::EmptyVisitorNode(T* any)
  : IAnyVisitorNode<T>{any}
{}

template <typename T>
EmptyVisitorNode<T>::~EmptyVisitorNode() = default;

template <typename T>
std::unique_ptr<IAnyVisitorNode<T>> EmptyVisitorNode<T>::NextChild()
{
  return {};
}

template <typename T>
void EmptyVisitorNode<T>::AddProlog(IAnyVisitor<T>& serializer) const
{
  serializer.EmptyProlog(this->GetValue());
}

template <typename T>
void EmptyVisitorNode<T>::AddSeparator(IAnyVisitor<T>&) const
{}

template <typename T>
void EmptyVisitorNode<T>::AddEpilog(IAnyVisitor<T>& serializer) const
{
  serializer.EmptyEpilog(this->GetValue());
}

}  // namespace dto

}  // namespace sup

#endif  // _SUP_EmptyVisitorNode_h_
