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

#include "AnyTypeSerializeStack.h"
#include "IAnySerializer.h"

namespace sup
{
namespace dto
{

AnyTypeSerializeStack::AnyTypeSerializeStack()
  : node_stack{}
  , add_separator{false}
{}

bool AnyTypeSerializeStack::empty() const
{
  return node_stack.empty();
}

AnyTypeSerializeNode& AnyTypeSerializeStack::top()
{
  return node_stack.top();
}

void AnyTypeSerializeStack::push(AnyTypeSerializeNode&& node, IAnyTypeSerializer& serializer)
{
  if (add_separator)
  {
    top().AddSeparator(serializer);
    add_separator = false;
  }
  node.AddProlog(serializer);
  node_stack.push(std::move(node));
}

void AnyTypeSerializeStack::pop(IAnyTypeSerializer& serializer)
{
  top().AddEpilog(serializer);
  node_stack.pop();
  add_separator = true;
}

}  // namespace dto

}  // namespace sup
