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

#include "AnyTypeNode.h"

namespace sup
{
namespace dto
{

AnyTypeDFSNode::AnyTypeDFSNode(const AnyType* anytype_)
  : anytype{anytype_}
{}

AnyTypeDFSNode::~AnyTypeDFSNode() = default;

const AnyType* AnyTypeDFSNode::GetAnyType() const
{
  return anytype;
}

}  // namespace dto

}  // namespace sup
