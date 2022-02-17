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

/**
 * @file CreateAnySerializeNode.h
 * @brief Header file for serialization node creation function templates.
 * @date 17/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the serialization node creation function
 * templates.
 */

#ifndef _SUP_CreateAnySerializeNode_h_
#define _SUP_CreateAnySerializeNode_h_

#include "EmptySerializeNode.h"
#include "StructSerializeNode.h"
#include "ArraySerializeNode.h"
#include "ScalarSerializeNode.h"
#include "AnyType.h"

#include <memory>

namespace sup
{
namespace dto
{

template <typename T>
std::unique_ptr<IAnySerializeNode<T>> CreateSerializeNode(const T* any)
{
  std::unique_ptr<IAnySerializeNode<T>> result;
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

template <typename T>
AnySerializeNode<T> CreateRootNode(const T* any)
{
    return CreateSerializeNode(any);
}


}  // namespace dto

}  // namespace sup

#endif  // _SUP_CreateAnySerializeNode_h_
