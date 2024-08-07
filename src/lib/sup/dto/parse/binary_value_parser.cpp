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

#include "binary_value_parser.h"

#include <sup/dto/parse/binary_parser_functions.h>

#include <sup/dto/anyvalue.h>
#include <sup/dto/anyvalue_helper.h>
#include <sup/dto/anyvalue_exceptions.h>

#include <array>
#include <functional>

namespace
{
using sup::dto::AnyValue;
using sup::dto::ByteIterator;
using sup::dto::TypeCode;

template <typename T>
void AssignBinaryScalarT(AnyValue& anyvalue, ByteIterator& it, ByteIterator end)
{
  anyvalue.UnsafeConvertFrom(sup::dto::ParseBinaryScalarT<T>(it, end));
}

void AssignBinaryString(AnyValue& anyvalue, ByteIterator& it, ByteIterator end)
{
  anyvalue.UnsafeConvertFrom(sup::dto::ParseBinaryString(it, end));
}

using ScalarParserFunction = std::function<void(AnyValue&, ByteIterator&, ByteIterator)>;
const sup::dto::uint32 kMaxScalarCode = 13u;
std::array<ScalarParserFunction, kMaxScalarCode + 1> CreateScalarParserFunctionArray();
}  // unnamed namespace

namespace sup
{
namespace dto
{

BinaryValueParser::BinaryValueParser(ByteIterator& it, ByteIterator end)
  : m_it{it}
  , m_end{end}
{}

BinaryValueParser::~BinaryValueParser() = default;

bool BinaryValueParser::IsFinished() const
{
  return m_it == m_end;
}

void BinaryValueParser::EmptyProlog(AnyValue*)
{}

void BinaryValueParser::EmptyEpilog(AnyValue*)
{}

void BinaryValueParser::StructProlog(AnyValue*)
{}

void BinaryValueParser::StructMemberSeparator()
{}

void BinaryValueParser::StructEpilog(AnyValue*)
{}

void BinaryValueParser::MemberProlog(AnyValue*, const std::string&)
{}

void BinaryValueParser::MemberEpilog(AnyValue*, const std::string&)
{}

void BinaryValueParser::ArrayProlog(AnyValue*)
{}

void BinaryValueParser::ArrayElementSeparator()
{}

void BinaryValueParser::ArrayEpilog(AnyValue*)
{}

void BinaryValueParser::ScalarProlog(AnyValue* anyvalue)
{
  static const auto parser_functions = CreateScalarParserFunctionArray();
  auto& parse_func = parser_functions[static_cast<size_t>(anyvalue->GetTypeCode())];
  parse_func(*anyvalue, m_it, m_end);
}

void BinaryValueParser::ScalarEpilog(AnyValue*)
{}

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
  result.at(static_cast<uint32>(TypeCode::Bool)) = AssignBinaryScalarT<sup::dto::boolean>;
  result.at(static_cast<uint32>(TypeCode::Char8)) = AssignBinaryScalarT<sup::dto::char8>;
  result.at(static_cast<uint32>(TypeCode::Int8)) = AssignBinaryScalarT<sup::dto::int8>;
  result.at(static_cast<uint32>(TypeCode::UInt8)) = AssignBinaryScalarT<sup::dto::uint8>;
  result.at(static_cast<uint32>(TypeCode::Int16)) = AssignBinaryScalarT<sup::dto::int16>;
  result.at(static_cast<uint32>(TypeCode::UInt16)) = AssignBinaryScalarT<sup::dto::uint16>;
  result.at(static_cast<uint32>(TypeCode::Int32)) = AssignBinaryScalarT<sup::dto::int32>;
  result.at(static_cast<uint32>(TypeCode::UInt32)) = AssignBinaryScalarT<sup::dto::uint32>;
  result.at(static_cast<uint32>(TypeCode::Int64)) = AssignBinaryScalarT<sup::dto::int64>;
  result.at(static_cast<uint32>(TypeCode::UInt64)) = AssignBinaryScalarT<sup::dto::uint64>;
  result.at(static_cast<uint32>(TypeCode::Float32)) = AssignBinaryScalarT<sup::dto::float32>;
  result.at(static_cast<uint32>(TypeCode::Float64)) = AssignBinaryScalarT<sup::dto::float64>;
  result.at(static_cast<uint32>(TypeCode::String)) = AssignBinaryString;
  return result;
}
}  // unnamed namespace
