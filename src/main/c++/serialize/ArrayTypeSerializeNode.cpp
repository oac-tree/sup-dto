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

#include "ArrayTypeSerializeNode.h"
#include "IAnyTypeSerializer.h"

namespace sup
{
namespace dto
{

ArrayTypeSerializeNode::ArrayTypeSerializeNode(const AnyType* anytype)
  : IAnyTypeSerializeNode{anytype}
  , next_index{0}
{}

ArrayTypeSerializeNode::~ArrayTypeSerializeNode() = default;

std::unique_ptr<IAnyTypeSerializeNode> ArrayTypeSerializeNode::NextChild()
{
  if (next_index >= GetAnyType()->NumberOfElements())
  {
    return {};
  }
  const AnyType *element_type = &GetAnyType()->operator[]("[]");
  ++next_index;
  return CreateSerializeNode(element_type);
}

void ArrayTypeSerializeNode::AddProlog(IAnyTypeSerializer& serializer) const
{
  serializer.AddArrayProlog(GetAnyType());
}

void ArrayTypeSerializeNode::AddSeparator(IAnyTypeSerializer& serializer) const
{
  serializer.AddArrayElementSeparator();
}

void ArrayTypeSerializeNode::AddEpilog(IAnyTypeSerializer& serializer) const
{
  serializer.AddArrayEpilog(GetAnyType());
}

}  // namespace dto

}  // namespace sup
