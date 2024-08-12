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

#include "scalar_value_data_base.h"

#include <sup/dto/anyvalue/scalar_value_data_t.h>

#include <sup/dto/anyvalue_exceptions.h>

#include <functional>
#include <map>

namespace
{
using namespace sup::dto;
template <typename T>
ScalarValueDataBase* ScalarValueConstructor(value_flags::Constraints constraints)
{
  return new ScalarValueDataT<T>{T{}, constraints};
}
}  // namespace

namespace sup
{
namespace dto
{

ScalarValueDataBase::ScalarValueDataBase(TypeCode type_code, value_flags::Constraints constraints)
  : m_type_code{type_code}
  , m_constraints{constraints}
{}

ScalarValueDataBase::~ScalarValueDataBase() = default;

TypeCode ScalarValueDataBase::GetTypeCode() const
{
  return m_type_code;
}

AnyType ScalarValueDataBase::GetType() const
{
  return AnyType(m_type_code);
}

bool ScalarValueDataBase::IsScalar() const
{
  return true;
}

value_flags::Constraints ScalarValueDataBase::GetConstraints() const
{
  return m_constraints;
}

ScalarValueDataBase* CreateScalarValueData(TypeCode type_code, value_flags::Constraints constraints)
{
  using ScalarValueDataConstructor = std::function<ScalarValueDataBase*(value_flags::Constraints)>;
  static const std::map<TypeCode, ScalarValueDataConstructor> constructor_map {
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
    {TypeCode::Float64, ScalarValueConstructor<float64> },
    {TypeCode::String, ScalarValueConstructor<std::string> }
  };
  const auto it = constructor_map.find(type_code);
  if (it == constructor_map.end())
  {
    throw InvalidOperationException("Not a known scalar type code");
  }
  return it->second(constraints);
}

}  // namespace dto

}  // namespace sup
