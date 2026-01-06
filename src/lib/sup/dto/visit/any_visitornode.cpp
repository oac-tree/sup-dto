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

#include "any_visitornode.h"

#include <sup/dto/anytype.h>
#include <sup/dto/anyvalue.h>

namespace sup
{
namespace dto
{

AnyType* GetIndexedChild(AnyType* parent, std::size_t idx)
{
  return parent->GetChildType(idx);
}

const AnyType* GetIndexedChild(const AnyType* parent, std::size_t idx)
{
  return parent->GetChildType(idx);
}

AnyValue* GetIndexedChild(AnyValue* parent, std::size_t idx)
{
  return parent->GetChildValue(idx);
}

const AnyValue* GetIndexedChild(const AnyValue* parent, std::size_t idx)
{
  return parent->GetChildValue(idx);
}

}  // namespace dto

}  // namespace sup
