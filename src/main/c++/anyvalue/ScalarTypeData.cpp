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

#include <map>

namespace sup
{
namespace dto
{

static std::string ScalarTypeCodeToString(TypeCode type_code);

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

std::string ScalarTypeData::GetTypeName() const
{
  return ScalarTypeCodeToString(type_code);
}

AnyType& ScalarTypeData::operator[](const std::string& fieldname)
{
  throw KeyNotAllowedException("Index operator not supported for scalar types");
}

bool ScalarTypeData::Equals(const AnyType& other) const
{
  return other.GetTypeCode() == GetTypeCode();
}

ScalarTypeData* CreateScalarData(TypeCode type_code)
{
  if (!IsScalarTypeCode(type_code))
  {
    throw KeyNotAllowedException("Not a known scalar type code");
  }
  return new ScalarTypeData(type_code);
}

static std::string ScalarTypeCodeToString(TypeCode type_code)
{
  static const std::map<TypeCode, std::string> type_map({
    { TypeCode::Bool, BOOLEAN_TYPE_NAME },
    { TypeCode::Char8, CHAR8_TYPE_NAME },
    { TypeCode::Int8, INT8_TYPE_NAME },
    { TypeCode::UInt8, UINT8_TYPE_NAME },
    { TypeCode::Int16, INT16_TYPE_NAME },
    { TypeCode::UInt16, UINT16_TYPE_NAME },
    { TypeCode::Int32, INT32_TYPE_NAME },
    { TypeCode::UInt32, UINT32_TYPE_NAME },
    { TypeCode::Int64, INT64_TYPE_NAME },
    { TypeCode::UInt64, UINT64_TYPE_NAME },
    { TypeCode::Float32, FLOAT32_TYPE_NAME },
    { TypeCode::Float64, FLOAT64_TYPE_NAME }
  });
  auto it = type_map.find(type_code);
  return it->second;
}

}  // namespace dto

}  // namespace sup
