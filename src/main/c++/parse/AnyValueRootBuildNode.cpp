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

#include "AnyValueRootBuildNode.h"

#include "AnyValueArrayBuildNode.h"
#include "AnyValueExceptions.h"

namespace sup
{
namespace dto
{

AnyValueRootBuildNode::AnyValueRootBuildNode(IAnyBuildNode* parent)
  : IAnyBuildNode{parent}
  , array_node{}
  , anyvalue{}
{}

AnyValueRootBuildNode::~AnyValueRootBuildNode() = default;

IAnyBuildNode* AnyValueRootBuildNode::GetArrayNode()
{
  if (array_node)
  {
    throw InvalidOperationException(
        "AnyValueRootBuildNode::GetArrayNode must be called with empty child node");
  }
  array_node.reset(new AnyValueArrayBuildNode(this));
  return array_node.get();
}

bool AnyValueRootBuildNode::PopArrayNode()
{
  if (!array_node)
  {
    throw InvalidOperationException(
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
