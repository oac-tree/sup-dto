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

#include "EmptyTypeSerializeNode.h"
#include "IAnyTypeSerializer.h"

namespace sup
{
namespace dto
{

EmptyTypeSerializeNode::EmptyTypeSerializeNode(const AnyType* anytype)
  : IAnyTypeSerializeNode{anytype}
{}

EmptyTypeSerializeNode::~EmptyTypeSerializeNode() = default;

std::unique_ptr<IAnyTypeSerializeNode> EmptyTypeSerializeNode::NextChild()
{
  return {};
}

void EmptyTypeSerializeNode::AddProlog(IAnyTypeSerializer& serializer) const
{
  serializer.AddEmptyProlog(GetAnyType());
}

void EmptyTypeSerializeNode::AddSeparator(IAnyTypeSerializer&) const
{}

void EmptyTypeSerializeNode::AddEpilog(IAnyTypeSerializer& serializer) const
{
  serializer.AddEmptyEpilog(GetAnyType());
}

}  // namespace dto

}  // namespace sup
