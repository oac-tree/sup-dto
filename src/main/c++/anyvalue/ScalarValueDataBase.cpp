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

#include "ScalarValueDataBase.h"

#include "AnyValueExceptions.h"
#include "ScalarValueDataT.h"

#include <type_traits>

namespace sup
{
namespace dto
{

ScalarValueDataBase::ScalarValueDataBase(TypeCode type_code_)
  : type_code{type_code_}
{}

ScalarValueDataBase::~ScalarValueDataBase() = default;

TypeCode ScalarValueDataBase::GetTypeCode() const
{
  return type_code;
}

AnyType ScalarValueDataBase::GetType() const
{
  return AnyType(type_code);
}

AnyValue& ScalarValueDataBase::operator[](const std::string& fieldname)
{
  throw KeyNotAllowedException("Index operator not supported for scalar values");
}

const AnyValue& ScalarValueDataBase::operator[](const std::string& fieldname) const
{
  throw KeyNotAllowedException("Index operator not supported for scalar values");
}

bool ScalarValueDataBase::Equals(const IValueData* other) const
{
  return other->GetTypeCode() == GetTypeCode();
}

ScalarValueDataBase* CreateScalarValueData(TypeCode type_code)
{
  switch (type_code)
  {
    case TypeCode::Bool: return new ScalarValueDataT<boolean>();
    case TypeCode::Int8: return new ScalarValueDataT<int8>();
    case TypeCode::UInt8: return new ScalarValueDataT<uint8>();
    case TypeCode::Int16: return new ScalarValueDataT<int16>();
    case TypeCode::UInt16: return new ScalarValueDataT<uint16>();
    case TypeCode::Int32: return new ScalarValueDataT<int32>();
    case TypeCode::UInt32: return new ScalarValueDataT<uint32>();
    case TypeCode::Int64: return new ScalarValueDataT<int64>();
    case TypeCode::UInt64: return new ScalarValueDataT<uint64>();
  }
  throw KeyNotAllowedException("Not a known scalar type code");
}

}  // namespace dto

}  // namespace sup
