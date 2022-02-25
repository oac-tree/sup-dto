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

#include "CreateAnySerializeNode.h"
#include "CreateAnySerializeNodeT.h"

namespace sup
{
namespace dto
{

std::unique_ptr<IAnySerializeNode<AnyType>> CreateSerializeNode(const AnyType* anytype)
{
  return CreateSerializeNodeT(anytype);
}

std::unique_ptr<IAnySerializeNode<AnyValue>> CreateSerializeNode(const AnyValue* anyvalue)
{
  return CreateSerializeNodeT(anyvalue);
}

}  // namespace dto

}  // namespace sup
