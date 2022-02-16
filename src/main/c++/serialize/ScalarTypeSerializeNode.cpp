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

#include "ScalarTypeSerializeNode.h"
#include "IAnyTypeSerializer.h"

namespace sup
{
namespace dto
{

ScalarTypeSerializeNode::ScalarTypeSerializeNode(const AnyType* anytype)
  : IAnyTypeSerializeNode{anytype}
{}

ScalarTypeSerializeNode::~ScalarTypeSerializeNode() = default;

std::unique_ptr<IAnyTypeSerializeNode> ScalarTypeSerializeNode::NextChild()
{
  return {};
}

void ScalarTypeSerializeNode::AddProlog(IAnyTypeSerializer& serializer) const
{
  serializer.AddScalarProlog(GetAnyType());
}

void ScalarTypeSerializeNode::AddSeparator(IAnyTypeSerializer&) const
{}

void ScalarTypeSerializeNode::AddEpilog(IAnyTypeSerializer& serializer) const
{
  serializer.AddScalarEpilog(GetAnyType());
}

}  // namespace dto

}  // namespace sup
