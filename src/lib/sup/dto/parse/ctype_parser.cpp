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

#include "ctype_parser.h"

#include <sup/dto/parse/scalar_from_bytes.h>

#include <sup/dto/anyvalue.h>

#include <functional>
#include <map>

namespace sup
{
namespace dto
{

CTypeParser::CTypeParser(const uint8* bytes_, std::size_t total_size_)
  : bytes{bytes_}
  , total_size{total_size_}
  , current_position{0}
{}

CTypeParser::~CTypeParser() = default;

bool CTypeParser::IsFinished() const
{
  return current_position == total_size;
}

void CTypeParser::EmptyProlog(AnyValue*)
{}

void CTypeParser::EmptyEpilog(AnyValue*)
{}

void CTypeParser::StructProlog(AnyValue*)
{}

void CTypeParser::StructMemberSeparator()
{}

void CTypeParser::StructEpilog(AnyValue*)
{}

void CTypeParser::MemberProlog(AnyValue*, const std::string&)
{}

void CTypeParser::MemberEpilog(AnyValue*, const std::string&)
{}

void CTypeParser::ArrayProlog(AnyValue*)
{}

void CTypeParser::ArrayElementSeparator()
{}

void CTypeParser::ArrayEpilog(AnyValue*)
{}

void CTypeParser::ScalarProlog(AnyValue* anyvalue)
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
    throw ParseException("CTypeParser: unknown scalar type code");
  }
  current_position = it->second(*anyvalue, bytes, total_size, current_position);
}

void CTypeParser::ScalarEpilog(AnyValue*)
{}

}  // namespace dto

}  // namespace sup
