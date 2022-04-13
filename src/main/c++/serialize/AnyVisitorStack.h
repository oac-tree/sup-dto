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

#ifndef _SUP_AnyVisitorStack_h_
#define _SUP_AnyVisitorStack_h_

#include "AnyVisitorNode.h"

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
class AnyVisitorStack
{
public:
  AnyVisitorStack();
  ~AnyVisitorStack() = default;

  bool empty() const;

  AnyVisitorNode<T>& Top();

  void Push(AnyVisitorNode<T>&& node, IAnyVisitor<T>& serializer);
  void Pop(IAnyVisitor<T>& serializer);

private:
  std::stack<AnyVisitorNode<T>> node_stack;
  bool add_separator;
};

template <typename T>
AnyVisitorStack<T>::AnyVisitorStack()
  : node_stack{}
  , add_separator{false}
{}

template <typename T>
bool AnyVisitorStack<T>::empty() const
{
  return node_stack.empty();
}

template <typename T>
AnyVisitorNode<T>& AnyVisitorStack<T>::Top()
{
  return node_stack.top();
}

template <typename T>
void AnyVisitorStack<T>::Push(AnyVisitorNode<T>&& node, IAnyVisitor<T>& serializer)
{
  if (add_separator)
  {
    Top().AddSeparator(serializer);
    add_separator = false;
  }
  node.AddProlog(serializer);
  node_stack.push(std::move(node));
}

template <typename T>
void AnyVisitorStack<T>::Pop(IAnyVisitor<T>& serializer)
{
  Top().AddEpilog(serializer);
  node_stack.pop();
  add_separator = true;
}

}  // namespace dto

}  // namespace sup

#endif  // _SUP_AnyVisitorStack_h_
