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

#include "AnyTypeHelper.h"
#include "AnyTypeSerializeStack.h"

namespace sup
{
namespace dto
{

// TODO: implement in terms of a templated stack
template <typename T>
void Serialize(const T& any, IAnySerializer<T>& serializer);

void SerializeAnyType(const AnyType& anytype, IAnySerializer<AnyType>& serializer)
{
  AnyTypeSerializeStack node_stack;
  auto node = CreateRootNode(&anytype);
  node_stack.push(std::move(node), serializer);
  while (!node_stack.empty())
  {
    auto& top = node_stack.top();
    auto next_child = top.NextChild();
    if (next_child.IsValid())
    {
      node_stack.push(std::move(next_child), serializer);
    }
    else
    {
      node_stack.pop(serializer);
    }
  }
}

}  // namespace dto

}  // namespace sup
