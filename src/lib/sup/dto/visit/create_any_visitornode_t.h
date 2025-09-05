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
 * Copyright (c) : 2010-2025 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 * SPDX-License-Identifier: MIT
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file LICENSE located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#ifndef SUP_DTO_CREATE_ANY_VISITORNODE_T_H_
#define SUP_DTO_CREATE_ANY_VISITORNODE_T_H_

#include <sup/dto/visit/array_visitornode.h>
#include <sup/dto/visit/empty_visitornode.h>
#include <sup/dto/visit/scalar_visitornode.h>
#include <sup/dto/visit/struct_visitornode.h>

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
    result = std::make_unique<EmptyVisitorNode<T>>(any);
    break;
  case TypeCode::Struct:
    result = std::make_unique<StructVisitorNode<T>>(any);
    break;
  case TypeCode::Array:
    result = std::make_unique<ArrayVisitorNode<T>>(any);
    break;
  default:
    result = std::make_unique<ScalarVisitorNode<T>>(any);
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
    return AnyVisitorNode<T>{CreateVisitorNodeT<T>(any)};
}

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_CREATE_ANY_VISITORNODE_T_H_
