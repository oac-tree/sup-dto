/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : SUP - DTO
 *
 * Description   : Unit test code
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

#include "anytype_root_buildnode.h"

#include "anytype_buildnode.h"
#include "sup/dto/anyvalue_exceptions.h"

namespace sup
{
namespace dto
{

AnyTypeRootBuildNode::AnyTypeRootBuildNode(const AnyTypeRegistry* anytype_registry,
                                           IAnyBuildNode* parent)
  : IAnyBuildNode(anytype_registry, parent)
  , type_node{}
  , anytype{}
{}

AnyTypeRootBuildNode::~AnyTypeRootBuildNode() = default;

IAnyBuildNode* AnyTypeRootBuildNode::GetStructureNode()
{
  if (type_node)
  {
    throw ParseException(
        "AnyTypeRootBuildNode::GetStructureNode must be called with empty child node");
  }
  type_node.reset(new AnyTypeBuildNode(GetTypeRegistry(), this));
  return type_node.get();
}

bool AnyTypeRootBuildNode::PopStructureNode()
{
  if (!type_node)
  {
    throw ParseException(
        "AnyTypeRootBuildNode::PopStructureNode must be called with a non-empty child node");
  }
  anytype = type_node->MoveAnyType();
  type_node.reset();
  return true;
}

AnyType AnyTypeRootBuildNode::MoveAnyType() const
{
  return std::move(anytype);
}

}  // namespace dto

}  // namespace sup
