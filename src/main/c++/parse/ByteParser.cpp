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

#include "ByteParser.h"
#include "AnyValue.h"
#include "ScalarFromBytes.h"

#include <functional>
#include <map>

namespace sup
{
namespace dto
{

ByteParser::ByteParser(const uint8* bytes_, std::size_t total_size_)
  : bytes{bytes_}
  , total_size{total_size_}
  , current_position{0}
{}

ByteParser::~ByteParser() = default;

void ByteParser::EmptyProlog(AnyValue*)
{}

void ByteParser::EmptyEpilog(AnyValue*)
{}

void ByteParser::StructProlog(AnyValue*)
{}

void ByteParser::StructMemberSeparator()
{}

void ByteParser::StructEpilog(AnyValue*)
{}

void ByteParser::MemberProlog(AnyValue*, const std::string&)
{}

void ByteParser::MemberEpilog(AnyValue*, const std::string&)
{}

void ByteParser::ArrayProlog(AnyValue*)
{}

void ByteParser::ArrayElementSeparator()
{}

void ByteParser::ArrayEpilog(AnyValue*)
{}

void ByteParser::ScalarProlog(AnyValue* anyvalue)
{
  static std::map<TypeCode, std::function<std::size_t(AnyValue&, const uint8*, std::size_t,
                                                      std::size_t)>> assign_map {
    {TypeCode::Bool, AssignBytes<boolean> },
    {TypeCode::Char8, AssignBytes<char8> },
    {TypeCode::Int8, AssignBytes<int8> },
    {TypeCode::UInt8, AssignBytes<uint8> },
    {TypeCode::Int16, AssignBytes<int16> },
    {TypeCode::UInt16, AssignBytes<uint16> },
    {TypeCode::Int32, AssignBytes<int32> },
    {TypeCode::UInt32, AssignBytes<uint32> },
    {TypeCode::Int64, AssignBytes<int64> },
    {TypeCode::UInt64, AssignBytes<uint64> },
    {TypeCode::Float32, AssignBytes<float32> },
    {TypeCode::Float64, AssignBytes<float64> },
    {TypeCode::String, AssignBytes<std::string> }
  };
  auto it = assign_map.find(anyvalue->GetTypeCode());
  if (it == assign_map.end())
  {
    throw ParseException("ByteParser: unknown scalar type code");
  }
  current_position = it->second(*anyvalue, bytes, total_size, current_position);
}

void ByteParser::ScalarEpilog(AnyValue*)
{}

}  // namespace dto

}  // namespace sup
