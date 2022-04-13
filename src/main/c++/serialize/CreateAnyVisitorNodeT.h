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

#ifndef _SUP_CreateAnyVisitorNodeT_h_
#define _SUP_CreateAnyVisitorNodeT_h_

#include "EmptySerializeNode.h"
#include "StructSerializeNode.h"
#include "ArraySerializeNode.h"
#include "ScalarSerializeNode.h"

#include <memory>

namespace sup
{
namespace dto
{

/**
 * @brief Function template for creating an IAnyVisitorNode from an AnyType/AnyValue pointer.
 */
template <typename T>
std::unique_ptr<IAnyVisitorNode<T>> CreateVisitorNodeT(T* any)
{
  std::unique_ptr<IAnyVisitorNode<T>> result;
  switch (any->GetTypeCode())
  {
  case TypeCode::Empty:
    result.reset(new EmptySerializeNode<T>(any));
    break;
  case TypeCode::Struct:
    result.reset(new StructSerializeNode<T>(any));
    break;
  case TypeCode::Array:
    result.reset(new ArraySerializeNode<T>(any));
    break;
  default:
    result.reset(new ScalarSerializeNode<T>(any));
    break;
  }
  return result;
}

/**
 * @brief Function template for creating an AnyVisitorNode from an AnyType/AnyValue pointer.
 */
template <typename T>
AnyVisitorNode<T> CreateRootNodeT(T* any)
{
    return CreateVisitorNodeT<T>(any);
}


}  // namespace dto

}  // namespace sup

#endif  // _SUP_CreateAnyVisitorNodeT_h_
