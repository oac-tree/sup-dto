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
 * @file SerializeT.h
 * @brief Header file for the Serialize function template.
 * @date 17/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the Serialize function template.
 */

#ifndef _SUP_SerializeT_h_
#define _SUP_SerializeT_h_

#include "AnySerializeStack.h"
#include "CreateAnySerializeNodeT.h"
#include "IAnySerializer.h"

namespace sup
{
namespace dto
{

template <typename T>
void Serialize(const T& any, IAnySerializer<T>& serializer)
{
  AnySerializeStack<T> node_stack;
  auto node = CreateRootNodeT(&any);
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

#endif  // _SUP_SerializeT_h_
