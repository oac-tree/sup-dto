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

#include "i_type_data.h"

#include <sup/dto/anyvalue_exceptions.h>

namespace sup
{
namespace dto
{

ITypeData::~ITypeData() = default;

bool ITypeData::IsScalar() const
{
  return false;
}

void ITypeData::AddMember(const std::string&, AnyType&&)
{
  throw InvalidOperationException("Add member only supported for structured types");
}

std::vector<std::string> ITypeData::MemberNames() const
{
  return {};
}

std::size_t ITypeData::NumberOfMembers() const
{
  return 0u;
}

AnyType ITypeData::ElementType() const
{
  throw InvalidOperationException("Element type only supported for array types");
}

std::size_t ITypeData::NumberOfElements() const
{
  return 0u;
}

std::size_t ITypeData::NumberOfChildren() const
{
  return 0u;
}

bool ITypeData::HasChild(const std::string&) const
{
  return false;
}

AnyType* ITypeData::GetChildType(const std::string&)
{
  throw InvalidOperationException("This type does not support members or elements");
}

AnyType* ITypeData::GetChildType(std::size_t)
{
  throw InvalidOperationException("This type does not support members or elements");
}

}  // namespace dto

}  // namespace sup
