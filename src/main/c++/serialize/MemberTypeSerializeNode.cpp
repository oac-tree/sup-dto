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

#include "MemberTypeSerializeNode.h"
#include "IAnySerializer.h"

namespace sup
{
namespace dto
{

MemberTypeSerializeNode::MemberTypeSerializeNode(const AnyType* anytype,
                                                 const std::string& member_name_)
  : IAnyTypeSerializeNode{anytype}
  , member_name{member_name_}
  , child_returned{false}
{}

MemberTypeSerializeNode::~MemberTypeSerializeNode() = default;

std::unique_ptr<IAnyTypeSerializeNode> MemberTypeSerializeNode::NextChild()
{
  if (child_returned)
  {
    return {};
  }
  child_returned = true;
  return CreateSerializeNode(GetValue());
}

void MemberTypeSerializeNode::AddProlog(IAnyTypeSerializer& serializer) const
{
  serializer.AddMemberProlog(GetValue(), member_name);
}

void MemberTypeSerializeNode::AddSeparator(IAnyTypeSerializer&) const
{}

void MemberTypeSerializeNode::AddEpilog(IAnyTypeSerializer& serializer) const
{
  serializer.AddMemberEpilog(GetValue(), member_name);
}

}  // namespace dto

}  // namespace sup
