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

#include "binary_parser_functions.h"

#include "arithmetic_from_bytes_t.h"

#include <sup/dto/serialize/binary_tokens.h>

#include <sup/dto/anyvalue_exceptions.h>

namespace
{
using sup::dto::AnyValue;
using sup::dto::ByteIterator;

template <typename T>
void AssignBinaryScalarFromLittleEndianOrderT(AnyValue& anyvalue, ByteIterator& it, ByteIterator end)
{
  anyvalue.ConvertFrom(AnyValue{sup::dto::ParseFromLittleEndianOrderT<T>(it, end)});
}

template <typename T>
void AssignBinaryScalarFromHostOrderT(AnyValue& anyvalue, ByteIterator& it, ByteIterator end)
{
  anyvalue.ConvertFrom(AnyValue{sup::dto::ParseFromHostOrderT<T>(it, end)});
}

using ScalarParserFunction = std::function<void(AnyValue&, ByteIterator&, ByteIterator)>;

template <typename T>
ScalarParserFunction GetScalarParserFunction()
{
  return IsLittleEndian() ? AssignBinaryScalarFromHostOrderT<T>
                          : AssignBinaryScalarFromLittleEndianOrderT<T>;
}

void AssignBinaryString(AnyValue& anyvalue, ByteIterator& it, ByteIterator end)
{
  anyvalue.ConvertFrom(sup::dto::ParseBinaryString(it, end));
}

void InvalidAssignFunction(AnyValue&, ByteIterator&, ByteIterator);

const sup::dto::uint32 kMaxScalarCode = 13u;

std::array<ScalarParserFunction, kMaxScalarCode + 1> CreateScalarParserFunctionArray();

}  // unnamed namespace

namespace sup
{
namespace dto
{

sup::dto::uint8 FetchToken(ByteIterator& it)
{
  return *it++;
}

std::string ParseBinaryString(ByteIterator& it, ByteIterator end)
{
  const auto str_size = ParseSize(it, end);
  if (static_cast<std::size_t>(std::distance(it, end)) < str_size)
  {
    throw ParseException("End of byte stream encountered during string value parsing");
  }
  std::string result;
  result.reserve(str_size);
  for (sup::dto::uint64 i = 0u; i < str_size; ++i)
  {
    const auto u = *it++;
    char c = '\0';
    (void)std::memcpy(&c, &u, 1u);
    result.push_back(c);
  }
  return result;
}

sup::dto::uint64 ParseSize(ByteIterator& it, ByteIterator end)
{
  if (it == end)
  {
    throw ParseException("End of byte stream encountered during size parsing");
  }
  const auto token = *it++;
  if (token < SHORT_SIZE_LIMIT)
  {
    return token;
  }
  // No test is done to check that the current token is LONG_SIZE_TOKEN, since the
  // current value of the limit is 0xFF.
  return ParseFromLittleEndianOrderT<sup::dto::uint64>(it, end);
}

void ParseBinaryScalar(AnyValue& anyvalue, ByteIterator& it, ByteIterator end)
{
  static const auto parser_functions = CreateScalarParserFunctionArray();
  auto& parse_func = parser_functions[static_cast<size_t>(anyvalue.GetTypeCode())];
  parse_func(anyvalue, it, end);
}

}  // namespace dto

}  // namespace sup

namespace
{
using sup::dto::AnyValue;
using sup::dto::ByteIterator;
using sup::dto::TypeCode;
using sup::dto::uint32;

void InvalidAssignFunction(AnyValue&, ByteIterator&, ByteIterator)
{
  const std::string error = "BinaryValueParser::ScalarProlog() called on an empty AnyValue";
  throw sup::dto::ParseException(error);
}

std::array<ScalarParserFunction, kMaxScalarCode + 1> CreateScalarParserFunctionArray()
{
  std::array<ScalarParserFunction, kMaxScalarCode + 1> result;
  result.at(static_cast<uint32>(TypeCode::Empty)) = InvalidAssignFunction;
  result.at(static_cast<uint32>(TypeCode::Bool)) = GetScalarParserFunction<sup::dto::boolean>();
  result.at(static_cast<uint32>(TypeCode::Char8)) = GetScalarParserFunction<sup::dto::char8>();
  result.at(static_cast<uint32>(TypeCode::Int8)) = GetScalarParserFunction<sup::dto::int8>();
  result.at(static_cast<uint32>(TypeCode::UInt8)) = GetScalarParserFunction<sup::dto::uint8>();
  result.at(static_cast<uint32>(TypeCode::Int16)) = GetScalarParserFunction<sup::dto::int16>();
  result.at(static_cast<uint32>(TypeCode::UInt16)) = GetScalarParserFunction<sup::dto::uint16>();
  result.at(static_cast<uint32>(TypeCode::Int32)) = GetScalarParserFunction<sup::dto::int32>();
  result.at(static_cast<uint32>(TypeCode::UInt32)) = GetScalarParserFunction<sup::dto::uint32>();
  result.at(static_cast<uint32>(TypeCode::Int64)) = GetScalarParserFunction<sup::dto::int64>();
  result.at(static_cast<uint32>(TypeCode::UInt64)) = GetScalarParserFunction<sup::dto::uint64>();
  result.at(static_cast<uint32>(TypeCode::Float32)) = GetScalarParserFunction<sup::dto::float32>();
  result.at(static_cast<uint32>(TypeCode::Float64)) = GetScalarParserFunction<sup::dto::float64>();
  result.at(static_cast<uint32>(TypeCode::String)) = AssignBinaryString;
  return result;
}

}  // unnamed namespace
