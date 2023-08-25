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

#include "binary_serialization_functions.h"

#include <sup/dto/serialize/append_scalar_t.h>
#include <sup/dto/serialize/binary_tokens.h>

#include <sup/dto/anyvalue.h>

#include <map>

namespace sup
{
namespace dto
{

template <typename T, uint8 token>
void AppendScalarAnyValueT(std::vector<uint8>& representation, const AnyValue& anyvalue)
{
  representation.push_back(token);
  T val = anyvalue.As<T>();
  AppendScalarT(representation, val);
}

void AppendBinaryStringValue(std::vector<uint8>& representation, const AnyValue& anyvalue)
{
  std::string str = anyvalue.As<std::string>();
  AppendBinaryString(representation, str);
}

void AppendBinaryScalar(std::vector<uint8>& representation, const AnyValue& anyvalue)
{
  using AppendFunction = std::function<void(std::vector<uint8>&, const AnyValue&)>;
  static std::map<TypeCode, AppendFunction> function_map {
    {TypeCode::Bool, AppendScalarAnyValueT<boolean, BOOL_TOKEN> },
    {TypeCode::Char8, AppendScalarAnyValueT<char8, CHAR8_TOKEN> },
    {TypeCode::Int8, AppendScalarAnyValueT<int8, INT8_TOKEN> },
    {TypeCode::UInt8, AppendScalarAnyValueT<uint8, UINT8_TOKEN> },
    {TypeCode::Int16, AppendScalarAnyValueT<int16, INT16_TOKEN> },
    {TypeCode::UInt16, AppendScalarAnyValueT<uint16, UINT16_TOKEN> },
    {TypeCode::Int32, AppendScalarAnyValueT<int32, INT32_TOKEN> },
    {TypeCode::UInt32, AppendScalarAnyValueT<uint32, UINT32_TOKEN> },
    {TypeCode::Int64, AppendScalarAnyValueT<int64, INT64_TOKEN> },
    {TypeCode::UInt64, AppendScalarAnyValueT<uint64, UINT64_TOKEN> },
    {TypeCode::Float32, AppendScalarAnyValueT<float32, FLOAT32_TOKEN> },
    {TypeCode::Float64, AppendScalarAnyValueT<float64, FLOAT64_TOKEN> },
    {TypeCode::String, AppendBinaryStringValue }
  };
  auto it = function_map.find(anyvalue.GetTypeCode());
  if (it == function_map.end())
  {
    throw SerializeException("Not a known scalar type code");
  }
  return it->second(representation, anyvalue);
}

void AppendBinaryString(std::vector<uint8>& representation, const std::string& str)
{
  representation.push_back(STRING_TOKEN);
  auto str_size = str.size();
  if (str_size < SHORT_STRING_LENGTH_LIMIT)
  {
    auto size_byte = static_cast<sup::dto::uint8>(str_size);
    representation.push_back(size_byte);
  }
  else
  {
    representation.push_back(LONG_STRING_LENGTH_TOKEN);
    AppendScalarT(representation, str_size);
  }
  representation.insert(representation.end(), std::begin(str), std::end(str));
}

}  // namespace dto

}  // namespace sup
