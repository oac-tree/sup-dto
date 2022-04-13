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

#ifndef _SUP_VisitT_h_
#define _SUP_VisitT_h_

#include "AnyVisitorStack.h"
#include "CreateAnyVisitorNodeT.h"
#include "IAnyVisitor.h"

namespace sup
{
namespace dto
{

template <typename T>
void Visit(T& any, IAnyVisitor<T>& serializer)
{
  AnyVisitorStack<T> node_stack;
  auto node = CreateRootNodeT<T>(&any);
  node_stack.Push(std::move(node), serializer);
  while (!node_stack.empty())
  {
    auto& top = node_stack.Top();
    auto next_child = top.NextChild();
    if (next_child.IsValid())
    {
      node_stack.Push(std::move(next_child), serializer);
    }
    else
    {
      node_stack.Pop(serializer);
    }
  }
}

}  // namespace dto

}  // namespace sup

#endif  // _SUP_VisitT_h_
