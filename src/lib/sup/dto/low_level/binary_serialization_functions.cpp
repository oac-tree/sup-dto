/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : SUP - DTO
 *
 * Description   : Unit test code
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

#include "binary_serialization_functions.h"
#include "arithmetic_to_bytes_t.h"

#include <sup/dto/serialize/binary_tokens.h>

#include <sup/dto/anyvalue.h>

#include <map>

namespace
{
using namespace sup::dto;
template <typename T>
void AppendScalarAnyValueT(std::vector<uint8>& representation, const AnyValue& anyvalue)
{
  T val = anyvalue.As<T>();
  AppendScalarBytesT(representation, val);
}

void AppendBinaryStringAnyValue(std::vector<uint8>& representation, const AnyValue& anyvalue)
{
  const std::string str = anyvalue.As<std::string>();
  AppendBinaryStringValue(representation, str);
}
}  // namespace

namespace sup
{
namespace dto
{

void AppendScalarToken(std::vector<uint8>& representation, const TypeCode& type_code)
{
  static const std::map<TypeCode, sup::dto::uint8> token_map {
    {TypeCode::Bool, BOOL_TOKEN },
    {TypeCode::Char8, CHAR8_TOKEN },
    {TypeCode::Int8, INT8_TOKEN },
    {TypeCode::UInt8, UINT8_TOKEN },
    {TypeCode::Int16, INT16_TOKEN },
    {TypeCode::UInt16, UINT16_TOKEN },
    {TypeCode::Int32, INT32_TOKEN },
    {TypeCode::UInt32, UINT32_TOKEN },
    {TypeCode::Int64, INT64_TOKEN },
    {TypeCode::UInt64, UINT64_TOKEN },
    {TypeCode::Float32, FLOAT32_TOKEN },
    {TypeCode::Float64, FLOAT64_TOKEN },
    {TypeCode::String, STRING_TOKEN }
  };
  const auto it = token_map.find(type_code);
  if (it == token_map.end())
  {
    throw SerializeException("Not a known scalar type code");
  }
  representation.push_back(it->second);
}

void AppendSize(std::vector<sup::dto::uint8>& representation, sup::dto::uint64 size)
{
  if (size < SHORT_SIZE_LIMIT)
  {
    representation.push_back(static_cast<sup::dto::uint8>(size));
  }
  else
  {
    representation.push_back(LONG_SIZE_TOKEN);
    AppendScalarBytesT(representation, size);
  }
}

void AppendBinaryScalar(std::vector<uint8>& representation, const AnyValue& anyvalue)
{
  using AppendFunction = std::function<void(std::vector<uint8>&, const AnyValue&)>;
  static const std::map<TypeCode, AppendFunction> function_map {
    {TypeCode::Bool, AppendScalarAnyValueT<boolean> },
    {TypeCode::Char8, AppendScalarAnyValueT<char8> },
    {TypeCode::Int8, AppendScalarAnyValueT<int8> },
    {TypeCode::UInt8, AppendScalarAnyValueT<uint8> },
    {TypeCode::Int16, AppendScalarAnyValueT<int16> },
    {TypeCode::UInt16, AppendScalarAnyValueT<uint16> },
    {TypeCode::Int32, AppendScalarAnyValueT<int32> },
    {TypeCode::UInt32, AppendScalarAnyValueT<uint32> },
    {TypeCode::Int64, AppendScalarAnyValueT<int64> },
    {TypeCode::UInt64, AppendScalarAnyValueT<uint64> },
    {TypeCode::Float32, AppendScalarAnyValueT<float32> },
    {TypeCode::Float64, AppendScalarAnyValueT<float64> },
    {TypeCode::String, AppendBinaryStringAnyValue }
  };
  const auto it = function_map.find(anyvalue.GetTypeCode());
  if (it == function_map.end())
  {
    throw SerializeException("Not a known scalar type code");
  }
  return it->second(representation, anyvalue);
}

void AppendBinaryString(std::vector<uint8>& representation, const std::string& str)
{
  representation.push_back(STRING_TOKEN);
  AppendBinaryStringValue(representation, str);
}

void AppendBinaryStringValue(std::vector<uint8>& representation, const std::string& str)
{
  const auto str_size = str.size();
  AppendSize(representation, str_size);
  (void)representation.insert(representation.cend(), std::begin(str), std::end(str));
}

}  // namespace dto

}  // namespace sup
