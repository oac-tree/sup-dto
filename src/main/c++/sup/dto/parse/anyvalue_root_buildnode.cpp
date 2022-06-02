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

#include "anyvalue_root_buildnode.h"

#include "anyvalue_array_buildnode.h"
#include "sup/dto/anyvalue_exceptions.h"

namespace sup
{
namespace dto
{

AnyValueRootBuildNode::AnyValueRootBuildNode(const AnyTypeRegistry* anytype_registry,
                                             IAnyBuildNode* parent)
  : IAnyBuildNode(anytype_registry, parent)
  , array_node{}
  , anyvalue{}
{}

AnyValueRootBuildNode::~AnyValueRootBuildNode() = default;

IAnyBuildNode* AnyValueRootBuildNode::GetArrayNode()
{
  if (array_node)
  {
    throw ParseException(
      "AnyValueRootBuildNode::GetArrayNode must be called with empty child node");
  }
  array_node.reset(new AnyValueArrayBuildNode(GetTypeRegistry(), this));
  return array_node.get();
}

bool AnyValueRootBuildNode::PopArrayNode()
{
  if (!array_node)
  {
    throw ParseException(
        "AnyValueRootBuildNode::PopArrayNode must be called with a non-empty child node");
  }
  anyvalue = array_node->MoveAnyValue();
  array_node.reset();
  return true;
}

AnyValue AnyValueRootBuildNode::MoveAnyValue() const
{
  return std::move(anyvalue);
}

}  // namespace dto

}  // namespace sup
