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
#include "IAnySerializer.h"

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

void ScalarTypeSerializeNode::AddProlog(IAnySerializer<AnyType>& serializer) const
{
  serializer.AddScalarProlog(GetValue());
}

void ScalarTypeSerializeNode::AddSeparator(IAnySerializer<AnyType>&) const
{}

void ScalarTypeSerializeNode::AddEpilog(IAnySerializer<AnyType>& serializer) const
{
  serializer.AddScalarEpilog(GetValue());
}

}  // namespace dto

}  // namespace sup
