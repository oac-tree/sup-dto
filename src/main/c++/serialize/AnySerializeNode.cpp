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

#include "AnySerializeNode.h"
#include "EmptySerializeNode.h"
#include "StructSerializeNode.h"
#include "ArraySerializeNode.h"
#include "ScalarSerializeNode.h"

namespace sup
{
namespace dto
{

std::unique_ptr<IAnySerializeNode<AnyType>> CreateSerializeNode(const AnyType* any)
{
  std::unique_ptr<IAnySerializeNode<AnyType>> result;
  switch (any->GetTypeCode())
  {
  case TypeCode::Empty:
    result.reset(new EmptySerializeNode<AnyType>(any));
    break;
  case TypeCode::Struct:
    result.reset(new StructSerializeNode<AnyType>(any));
    break;
  case TypeCode::Array:
    result.reset(new ArraySerializeNode<AnyType>(any));
    break;
  default:
    result.reset(new ScalarSerializeNode<AnyType>(any));
    break;
  }
  return result;
}

AnySerializeNode<AnyType> CreateRootNode(const AnyType* anytype)
{
  return CreateSerializeNode(anytype);
}

}  // namespace dto

}  // namespace sup
