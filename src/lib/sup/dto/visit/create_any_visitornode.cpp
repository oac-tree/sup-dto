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
 * Copyright (c) : 2010-2026 ITER Organization,
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

#include "create_any_visitornode.h"

#include <sup/dto/visit/create_any_visitornode_t.h>

namespace sup
{
namespace dto
{

std::unique_ptr<IAnyVisitorNode<AnyType>> CreateVisitorNode(AnyType* anytype)
{
  return CreateVisitorNodeT<AnyType>(anytype);
}

std::unique_ptr<IAnyVisitorNode<AnyValue>> CreateVisitorNode(AnyValue* anyvalue)
{
  return CreateVisitorNodeT<AnyValue>(anyvalue);
}

std::unique_ptr<IAnyVisitorNode<const AnyType>> CreateVisitorNode(const AnyType* anytype)
{
  return CreateVisitorNodeT<const AnyType>(anytype);
}

std::unique_ptr<IAnyVisitorNode<const AnyValue>> CreateVisitorNode(const AnyValue* anyvalue)
{
  return CreateVisitorNodeT<const AnyValue>(anyvalue);
}

}  // namespace dto

}  // namespace sup
