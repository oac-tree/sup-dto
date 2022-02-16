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

#include "AnyTypeSerializeNode.h"
#include "EmptyTypeSerializeNode.h"
#include "StructTypeSerializeNode.h"
#include "ArrayTypeSerializeNode.h"
#include "ScalarTypeSerializeNode.h"

namespace sup
{
namespace dto
{

IAnyTypeSerializeNode::IAnyTypeSerializeNode(const AnyType* anytype_)
  : anytype{anytype_}
{}

IAnyTypeSerializeNode::~IAnyTypeSerializeNode() = default;

const AnyType* IAnyTypeSerializeNode::GetAnyType() const
{
  return anytype;
}

AnyTypeSerializeNode::AnyTypeSerializeNode(std::unique_ptr<IAnyTypeSerializeNode> node_)
  : node{std::move(node_)}
{}

AnyTypeSerializeNode::~AnyTypeSerializeNode() = default;

AnyTypeSerializeNode::AnyTypeSerializeNode(AnyTypeSerializeNode&& other)
  : node{std::move(other.node)}
{}

AnyTypeSerializeNode& AnyTypeSerializeNode::operator=(AnyTypeSerializeNode&& other)
{
  if (this != &other)
  {
    AnyTypeSerializeNode moved{std::move(other)};
    std::swap(this->node, moved.node);
  }
  return *this;
}

AnyTypeSerializeNode AnyTypeSerializeNode::NextChild()
{
  return node->NextChild();
}

bool AnyTypeSerializeNode::IsValid() const
{
  return static_cast<bool>(node);
}

void AnyTypeSerializeNode::AddProlog(IAnyTypeSerializer& serializer) const
{
  return node->AddProlog(serializer);
}

void AnyTypeSerializeNode::AddSeparator(IAnyTypeSerializer& serializer) const
{
  return node->AddSeparator(serializer);
}

void AnyTypeSerializeNode::AddEpilog(IAnyTypeSerializer& serializer) const
{
  return node->AddEpilog(serializer);
}

std::unique_ptr<IAnyTypeSerializeNode> CreateSerializeNode(const AnyType* anytype)
{
  std::unique_ptr<IAnyTypeSerializeNode> result;
  switch (anytype->GetTypeCode())
  {
  case TypeCode::Empty:
    result.reset(new EmptyTypeSerializeNode(anytype));
    break;
  case TypeCode::Struct:
    result.reset(new StructTypeSerializeNode(anytype));
    break;
  case TypeCode::Array:
    result.reset(new ArrayTypeSerializeNode(anytype));
    break;
  default:
    result.reset(new ScalarTypeSerializeNode(anytype));
    break;
  }
  return result;
}

AnyTypeSerializeNode CreateRootNode(const AnyType* anytype)
{
  return CreateSerializeNode(anytype);
}

}  // namespace dto

}  // namespace sup
