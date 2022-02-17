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
#include "IAnySerializer.h"

namespace sup
{
namespace dto
{

ArrayTypeSerializeNode::ArrayTypeSerializeNode(const AnyType* anytype)
  : IAnyTypeSerializeNode{anytype}
  , child_returned{false}
{}

ArrayTypeSerializeNode::~ArrayTypeSerializeNode() = default;

std::unique_ptr<IAnyTypeSerializeNode> ArrayTypeSerializeNode::NextChild()
{
  if (child_returned)
  {
    return {};
  }
  const AnyType *element_type = &GetValue()->operator[]("[]");
  child_returned = true;
  return CreateSerializeNode(element_type);
}

void ArrayTypeSerializeNode::AddProlog(IAnySerializer<AnyType>& serializer) const
{
  serializer.AddArrayProlog(GetValue());
}

void ArrayTypeSerializeNode::AddSeparator(IAnySerializer<AnyType>& serializer) const
{
  serializer.AddArrayElementSeparator();
}

void ArrayTypeSerializeNode::AddEpilog(IAnySerializer<AnyType>& serializer) const
{
  serializer.AddArrayEpilog(GetValue());
}

}  // namespace dto

}  // namespace sup
