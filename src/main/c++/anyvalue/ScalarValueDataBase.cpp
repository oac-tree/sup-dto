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

#include <functional>
#include <map>
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

template <typename T>
ScalarValueDataBase* ScalarValueConstructor()
{
    return new ScalarValueDataT<T>{};
}

ScalarValueDataBase* CreateScalarValueData(TypeCode type_code)
{
  static const std::map<TypeCode, std::function<ScalarValueDataBase*()>> constructor_map{
    {TypeCode::Bool, ScalarValueConstructor<boolean> },
    {TypeCode::Char8, ScalarValueConstructor<char8> },
    {TypeCode::Int8, ScalarValueConstructor<int8> },
    {TypeCode::UInt8, ScalarValueConstructor<uint8> },
    {TypeCode::Int16, ScalarValueConstructor<int16> },
    {TypeCode::UInt16, ScalarValueConstructor<uint16> },
    {TypeCode::Int32, ScalarValueConstructor<int32> },
    {TypeCode::UInt32, ScalarValueConstructor<uint32> },
    {TypeCode::Int64, ScalarValueConstructor<int64> },
    {TypeCode::UInt64, ScalarValueConstructor<uint64> },
    {TypeCode::Float32, ScalarValueConstructor<float32> },
    {TypeCode::Float64, ScalarValueConstructor<float64> }
  };
  auto it = constructor_map.find(type_code);
  if (it == constructor_map.end())
  {
    throw KeyNotAllowedException("Not a known scalar type code");
  }
  return it->second();
}

}  // namespace dto

}  // namespace sup
