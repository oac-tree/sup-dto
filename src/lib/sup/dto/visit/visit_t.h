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
 * Copyright (c) : 2010-2023 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#ifndef SUP_DTO_VISIT_T_H_
#define SUP_DTO_VISIT_T_H_

#include <sup/dto/visit/any_visitorstack.h>
#include <sup/dto/visit/create_any_visitornode_t.h>

#include <sup/dto/i_any_visitor.h>

namespace sup
{
namespace dto
{

/**
 * @brief The Visit function will visit each node of an AnyType/AnyValue and call the appropriate
 * visitor methods while passing the node's value.
 *
 * @note Although this function is designed to change the underlying AnyType/AnyValue, it's
 * implementation expects that the structure is not changed. This means that only changes in leaf
 * values are allowed, i.e. scalar values for AnyValue, and scalar types for AnyType.
*/
template <typename T>
void Visit(T& any, IAnyVisitor<T>& visitor)
{
  AnyVisitorStack<T> node_stack;
  auto node = CreateRootNodeT<T>(&any);
  node_stack.Push(std::move(node), visitor);
  while (!node_stack.empty())
  {
    auto& top = node_stack.Top();
    auto next_child = top.NextChild();
    if (next_child.IsValid())
    {
      node_stack.Push(std::move(next_child), visitor);
    }
    else
    {
      node_stack.Pop(visitor);
    }
  }
}

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_VISIT_T_H_
