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

#include "ScalarTypeData.h"

#include "AnyValueExceptions.h"

namespace sup
{
namespace dto
{

ScalarTypeData::ScalarTypeData(TypeCode type_code_)
  : type_code{type_code_}
{}

ScalarTypeData::~ScalarTypeData() = default;

ScalarTypeData* ScalarTypeData::Clone() const
{
  return new ScalarTypeData(type_code);
}

TypeCode ScalarTypeData::GetTypeCode() const
{
  return type_code;
}

AnyType& ScalarTypeData::operator[](const std::string& fieldname)
{
  throw KeyNotAllowedException("Index operator not supported for scalar types");
}

const AnyType& ScalarTypeData::operator[](const std::string& fieldname) const
{
  throw KeyNotAllowedException("Index operator not supported for scalar types");
}

bool ScalarTypeData::Equals(const ITypeData* other) const
{
  return other->GetTypeCode() == GetTypeCode();
}

ScalarTypeData* CreateScalarData(TypeCode type_code)
{
  if (!IsScalarTypeCode(type_code))
  {
    throw KeyNotAllowedException("Not a known scalar type code");
  }
  return new ScalarTypeData(type_code);
}

}  // namespace dto

}  // namespace sup
