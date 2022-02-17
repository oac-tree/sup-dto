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
 * @file AnySerializeStack.h
 * @brief Header file for templated serialization stack.
 * @date 16/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the templated serialization stack.
 */

#ifndef _SUP_AnySerializeStack_h_
#define _SUP_AnySerializeStack_h_

#include "AnySerializeNode.h"

#include <stack>

namespace sup
{
namespace dto
{

/**
 * @brief Templated serialization node stack.
 *
 * @details This stack handles serialization calls on push/pop.
 */
template <typename T>
class AnySerializeStack
{
public:
  AnySerializeStack();
  ~AnySerializeStack() = default;

  bool empty() const;

  AnySerializeNode<T>& top();

  void push(AnySerializeNode<T>&& node, IAnySerializer<T>& serializer);
  void pop(IAnySerializer<T>& serializer);

private:
  std::stack<AnySerializeNode<T>> node_stack;
  bool add_separator;
};

template <typename T>
AnySerializeStack<T>::AnySerializeStack()
  : node_stack{}
  , add_separator{false}
{}

template <typename T>
bool AnySerializeStack<T>::empty() const
{
  return node_stack.empty();
}

template <typename T>
AnySerializeNode<T>& AnySerializeStack<T>::top()
{
  return node_stack.top();
}

template <typename T>
void AnySerializeStack<T>::push(AnySerializeNode<T>&& node, IAnySerializer<T>& serializer)
{
  if (add_separator)
  {
    top().AddSeparator(serializer);
    add_separator = false;
  }
  node.AddProlog(serializer);
  node_stack.push(std::move(node));
}

template <typename T>
void AnySerializeStack<T>::pop(IAnySerializer<T>& serializer)
{
  top().AddEpilog(serializer);
  node_stack.pop();
  add_separator = true;
}

}  // namespace dto

}  // namespace sup

#endif  // _SUP_AnySerializeStack_h_
