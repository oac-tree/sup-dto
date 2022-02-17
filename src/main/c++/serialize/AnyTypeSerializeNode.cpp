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
