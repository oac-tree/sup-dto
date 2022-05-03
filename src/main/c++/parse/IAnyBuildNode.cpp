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

#include "IAnyBuildNode.h"

#include "AnyValueExceptions.h"

namespace sup
{
namespace dto
{

IAnyBuildNode::IAnyBuildNode(const AnyTypeRegistry* anytype_registry_, IAnyBuildNode* parent_)
  : anytype_registry{anytype_registry_}
  , parent{parent_}
{
  if (anytype_registry == nullptr)
  {
    throw InvalidOperationException("IAnyBuildNode cannot be constructed from nullptr to "
                                    "AnyTypeRegistry");
  }
}

IAnyBuildNode::~IAnyBuildNode() = default;

const AnyTypeRegistry* IAnyBuildNode::TypeRegistry() const
{
  return anytype_registry;
}

IAnyBuildNode* IAnyBuildNode::Parent() const
{
  return parent;
}

bool IAnyBuildNode::Null()
{
  throw ParseException("Parser called unsupported operation for this node (Null)");
}

bool IAnyBuildNode::Bool(boolean)
{
  throw ParseException("Parser called unsupported operation for this node (Bool)");
}

bool IAnyBuildNode::Int32(int32)
{
  throw ParseException("Parser called unsupported operation for this node (Int32)");
}

bool IAnyBuildNode::Uint32(uint32)
{
  throw ParseException("Parser called unsupported operation for this node (Uint32)");
}

bool IAnyBuildNode::Int64(int64)
{
  throw ParseException("Parser called unsupported operation for this node (Int64)");
}

bool IAnyBuildNode::Uint64(uint64)
{
  throw ParseException("Parser called unsupported operation for this node (Uint64)");
}

bool IAnyBuildNode::Double(float64)
{
  throw ParseException("Parser called unsupported operation for this node (Double)");
}

bool IAnyBuildNode::String(const std::string&)
{
  throw ParseException("Parser called unsupported operation for this node (String)");
}

bool IAnyBuildNode::Member(const std::string&)
{
  throw ParseException("Parser called unsupported operation for this node (Member)");
}

IAnyBuildNode* IAnyBuildNode::GetStructureNode()
{
  throw ParseException(
      "Parser called unsupported operation for this node (GetStructureNode)");
}

IAnyBuildNode* IAnyBuildNode::GetArrayNode()
{
  throw ParseException(
      "Parser called unsupported operation for this node (GetArrayNode)");
}

bool IAnyBuildNode::PopStructureNode()
{
  throw ParseException(
      "Parser called unsupported operation for this node (PopStructureNode)");
}

bool IAnyBuildNode::PopArrayNode()
{
  throw ParseException(
      "Parser called unsupported operation for this node (PopArrayNode)");
}

}  // namespace dto

}  // namespace sup
