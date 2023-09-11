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
 * Copyright (c) : 2010-2023 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include "i_type_data.h"

#include <sup/dto/anyvalue_exceptions.h>

namespace sup
{
namespace dto
{

ITypeData::~ITypeData() = default;

void ITypeData::AddMember(const std::string&, const AnyType&)
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

bool ITypeData::HasField(const std::string&) const
{
  return false;
}

AnyType& ITypeData::operator[](const std::string& fieldname)
{
  (void)fieldname;
  throw InvalidOperationException("Index operator not supported for this type");
}

}  // namespace dto

}  // namespace sup
