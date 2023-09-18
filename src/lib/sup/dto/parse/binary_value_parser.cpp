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

#include <functional>
#include <map>

namespace
{
using sup::dto::AnyValue;
using sup::dto::ByteIterator;

template <typename T>
void AssignBinaryScalarT(AnyValue& anyvalue, ByteIterator& it, const ByteIterator& end)
{
  anyvalue = sup::dto::ParseBinaryScalarT<T>(it, end);
}

void AssignBinaryString(AnyValue& anyvalue, ByteIterator& it, const ByteIterator& end)
{
  anyvalue = sup::dto::ParseBinaryString(it, end);
}
}  // unnamed namespace

namespace sup
{
namespace dto
{

BinaryValueParser::BinaryValueParser(ByteIterator& it, const ByteIterator& end)
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
  using ScalarParserFunction = std::function<void(AnyValue&, ByteIterator&, const ByteIterator&)>;
  static const std::map<TypeCode, ScalarParserFunction> assign_map {
    {TypeCode::Bool, AssignBinaryScalarT<boolean> },
    {TypeCode::Char8, AssignBinaryScalarT<char8> },
    {TypeCode::Int8, AssignBinaryScalarT<int8> },
    {TypeCode::UInt8, AssignBinaryScalarT<uint8> },
    {TypeCode::Int16, AssignBinaryScalarT<int16> },
    {TypeCode::UInt16, AssignBinaryScalarT<uint16> },
    {TypeCode::Int32, AssignBinaryScalarT<int32> },
    {TypeCode::UInt32, AssignBinaryScalarT<uint32> },
    {TypeCode::Int64, AssignBinaryScalarT<int64> },
    {TypeCode::UInt64, AssignBinaryScalarT<uint64> },
    {TypeCode::Float32, AssignBinaryScalarT<float32> },
    {TypeCode::Float64, AssignBinaryScalarT<float64> },
    {TypeCode::String, AssignBinaryString }
  };
  const auto it = assign_map.find(anyvalue->GetTypeCode());
  if (it == assign_map.end())
  {
    throw ParseException("BinaryValueParser: unknown scalar type code");
  }
  it->second(*anyvalue, m_it, m_end);
}

void BinaryValueParser::ScalarEpilog(AnyValue*)
{}

}  // namespace dto

}  // namespace sup
