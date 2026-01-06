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

#ifndef SUP_DTO_ANY_VISITORSTACK_H_
#define SUP_DTO_ANY_VISITORSTACK_H_

#include <sup/dto/visit/any_visitornode.h>

#include <stack>

namespace sup
{
namespace dto
{

/**
 * @brief Templated node stack for visiting an AnyType/AnyValue tree.
 *
 * @details This stack handles visitor calls on push/pop.
 */
template <typename T>
class AnyVisitorStack
{
public:
  AnyVisitorStack();
  ~AnyVisitorStack() = default;

  AnyVisitorStack(const AnyVisitorStack& other) = delete;
  AnyVisitorStack(AnyVisitorStack&& other) = delete;
  AnyVisitorStack& operator=(const AnyVisitorStack& other) = delete;
  AnyVisitorStack& operator=(AnyVisitorStack&& other) = delete;

  bool empty() const;

  AnyVisitorNode<T>& Top();

  void Push(AnyVisitorNode<T>&& node, IAnyVisitor<T>& visitor);
  void Pop(IAnyVisitor<T>& visitor);

private:
  std::stack<AnyVisitorNode<T>> m_node_stack;
  bool m_add_separator;
};

template <typename T>
AnyVisitorStack<T>::AnyVisitorStack()
  : m_node_stack{}
  , m_add_separator{false}
{}

template <typename T>
bool AnyVisitorStack<T>::empty() const
{
  return m_node_stack.empty();
}

template <typename T>
AnyVisitorNode<T>& AnyVisitorStack<T>::Top()
{
  return m_node_stack.top();
}

template <typename T>
void AnyVisitorStack<T>::Push(AnyVisitorNode<T>&& node, IAnyVisitor<T>& visitor)
{
  if (m_add_separator)
  {
    Top().AddSeparator(visitor);
    m_add_separator = false;
  }
  node.AddProlog(visitor);
  m_node_stack.push(std::move(node));
}

template <typename T>
void AnyVisitorStack<T>::Pop(IAnyVisitor<T>& visitor)
{
  Top().AddEpilog(visitor);
  m_node_stack.pop();
  m_add_separator = true;
}

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ANY_VISITORSTACK_H_
