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

#include "StructTypeSerializeNode.h"
#include "MemberTypeSerializeNode.h"
#include "IAnySerializer.h"

namespace sup
{
namespace dto
{

StructTypeSerializeNode::StructTypeSerializeNode(const AnyType* anytype)
  : IAnyTypeSerializeNode{anytype}
  , next_index{0}
{}

StructTypeSerializeNode::~StructTypeSerializeNode() = default;

std::unique_ptr<IAnyTypeSerializeNode> StructTypeSerializeNode::NextChild()
{
  auto member_names = GetValue()->MemberNames();
  if (next_index >= member_names.size())
  {
    return {};
  }
  auto member_name = member_names[next_index];
  ++next_index;
  const AnyType *member_type = &GetValue()->operator[](member_name);
  std::unique_ptr<IAnyTypeSerializeNode> result{
      new MemberTypeSerializeNode(member_type, member_name)};
  return result;
}

void StructTypeSerializeNode::AddProlog(IAnySerializer<AnyType>& serializer) const
{
  serializer.AddStructProlog(GetValue());
}

void StructTypeSerializeNode::AddSeparator(IAnySerializer<AnyType>& serializer) const
{
  serializer.AddStructMemberSeparator();
}

void StructTypeSerializeNode::AddEpilog(IAnySerializer<AnyType>& serializer) const
{
  serializer.AddStructEpilog(GetValue());
}

}  // namespace dto

}  // namespace sup
