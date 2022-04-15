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

#include "ITypeData.h"

#include "AnyValueExceptions.h"

namespace sup
{
namespace dto
{

ITypeData::~ITypeData() = default;

void ITypeData::AddMember(const std::string&, const AnyType&)
{
  throw InvalidOperationException("Add member only supported for structured types");
}

bool ITypeData::HasMember(const std::string&) const
{
  return false;
}

std::vector<std::string> ITypeData::MemberNames() const
{
  return {};
}

std::size_t ITypeData::NumberOfMembers() const
{
  return 0;
}

AnyType ITypeData::ElementType() const
{
  throw InvalidOperationException("Element type only supported for array types");
}

std::size_t ITypeData::NumberOfElements() const
{
  return 0;
}

AnyType& ITypeData::operator[](const std::string& fieldname)
{
  throw InvalidOperationException("Index operator not supported for this type");
}

}  // namespace dto

}  // namespace sup
