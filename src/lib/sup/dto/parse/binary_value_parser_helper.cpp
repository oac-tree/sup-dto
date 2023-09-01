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

#include "binary_value_parser_helper.h"

#include <sup/dto/serialize/binary_tokens.h>

namespace sup
{
namespace dto
{

BinaryValueParserHelper::BinaryValueParserHelper()
  : m_composer{}
  , m_parse_states{}
{}

bool BinaryValueParserHelper::HandleToken(ByteIterator& it, const ByteIterator& end)
{
  auto token = FetchToken(it);
  auto handler_func = GetHandlerMemberFunction(token);
  if (!handler_func)
  {
    std::string error = "BinaryValueParserHelper::HandleToken(): encountered unknown token: " +
      std::to_string(token);
    throw ParseException(error);
  }
  return handler_func(*this, it, end);
}

AnyValue BinaryValueParserHelper::MoveAnyValue()
{
  if (GetCurrentState() != ParseState::kNone)
  {
    std::string error = "BinaryValueParserHelper::MoveAnyValue(): parsing was not complete";
    throw ParseException(error);
  }
  return m_composer.MoveAnyValue();
}

std::array<BinaryValueParserHelper::HandlerMemberFunction, 0x100>
BinaryValueParserHelper::CreateHandlerMemberFunctionArray()
{
  std::array<BinaryValueParserHelper::HandlerMemberFunction, 0x100> result;
  result[EMPTY_TOKEN] = &BinaryValueParserHelper::HandleEmpty;
  result[BOOL_TOKEN] =
    &BinaryValueParserHelper::HandleScalar<sup::dto::boolean, &AnyValueComposer::Bool>;
  result[CHAR8_TOKEN] =
    &BinaryValueParserHelper::HandleScalar<sup::dto::char8, &AnyValueComposer::Char8>;
  result[INT8_TOKEN] =
    &BinaryValueParserHelper::HandleScalar<sup::dto::int8, &AnyValueComposer::Int8>;
  result[UINT8_TOKEN] =
    &BinaryValueParserHelper::HandleScalar<sup::dto::uint8, &AnyValueComposer::UInt8>;
  result[INT16_TOKEN] =
    &BinaryValueParserHelper::HandleScalar<sup::dto::int16, &AnyValueComposer::Int16>;
  result[UINT16_TOKEN] =
    &BinaryValueParserHelper::HandleScalar<sup::dto::uint16, &AnyValueComposer::UInt16>;
  result[INT32_TOKEN] =
    &BinaryValueParserHelper::HandleScalar<sup::dto::int32, &AnyValueComposer::Int32>;
  result[UINT32_TOKEN] =
    &BinaryValueParserHelper::HandleScalar<sup::dto::uint32, &AnyValueComposer::UInt32>;
  result[INT64_TOKEN] =
    &BinaryValueParserHelper::HandleScalar<sup::dto::int64, &AnyValueComposer::Int64>;
  result[UINT64_TOKEN] =
    &BinaryValueParserHelper::HandleScalar<sup::dto::uint64, &AnyValueComposer::UInt64>;
  result[FLOAT32_TOKEN] =
    &BinaryValueParserHelper::HandleScalar<sup::dto::float32, &AnyValueComposer::Float32>;
  result[FLOAT64_TOKEN] =
    &BinaryValueParserHelper::HandleScalar<sup::dto::float64, &AnyValueComposer::Float64>;
  result[STRING_TOKEN] = &BinaryValueParserHelper::HandleString;
  result[START_STRUCT_TOKEN] = &BinaryValueParserHelper::HandleStartStruct;
  result[END_STRUCT_TOKEN] = &BinaryValueParserHelper::HandleEndStruct;
  result[START_ARRAY_TOKEN] = &BinaryValueParserHelper::HandleStartArray;
  result[END_ARRAY_TOKEN] = &BinaryValueParserHelper::HandleEndArray;
  return result;
}

BinaryValueParserHelper::HandlerMemberFunction
BinaryValueParserHelper::GetHandlerMemberFunction(sup::dto::uint8 token)
{
  static auto functions = CreateHandlerMemberFunctionArray();
  return functions[token];
}

ParseState BinaryValueParserHelper::GetCurrentState() const
{
  if (m_parse_states.empty())
  {
    return ParseState::kNone;
  }
  return m_parse_states.top();
}

void BinaryValueParserHelper::PushState()
{
  auto current_state = GetCurrentState();
  // Only arrays need to be handled here, structures do this during the field name parsing.
  if (current_state == ParseState::kInArray)
  {
    m_composer.StartArrayElement();
    m_parse_states.push(ParseState::kInArrayElement);
  }
}

bool BinaryValueParserHelper::PopState()
{
  auto current_state = GetCurrentState();
  if (current_state == ParseState::kNone)
  {
    return false;
  }
  if (current_state == ParseState::kInStructElement)
  {
    m_composer.EndField();
    m_parse_states.pop();
    return true;
  }
  if (current_state == ParseState::kInArrayElement)
  {
    m_composer.EndArrayElement();
    m_parse_states.pop();
    return true;
  }
  return false;
}

bool BinaryValueParserHelper::HandleEmpty(ByteIterator& it, const ByteIterator& end)
{
  (void)it;
  (void)end;
  PushState();
  m_composer.Empty();
  return PopState();
}

// HandleString is not intented to be called during parsing of struct/array typenames
bool BinaryValueParserHelper::HandleString(ByteIterator& it, const ByteIterator& end)
{
  auto str = ParseBinaryString(it, end);
  auto current_state = GetCurrentState();
  if (current_state == ParseState::kInStruct)
  {
    m_composer.StartField(str);
    m_parse_states.push(ParseState::kInStructElement);
    return true;
  }
  PushState();
  m_composer.String(str);
  return PopState();
}

bool BinaryValueParserHelper::HandleStartStruct(ByteIterator& it, const ByteIterator& end)
{
  if (it == end || FetchToken(it) != STRING_TOKEN)
  {
    return false;
  }
  auto str = ParseBinaryString(it, end);
  PushState();
  m_composer.StartStruct(str);
  m_parse_states.push(ParseState::kInStruct);
  return true;
}

bool BinaryValueParserHelper::HandleEndStruct(ByteIterator& it, const ByteIterator& end)
{
  (void)it;
  (void)end;
  if (GetCurrentState() != ParseState::kInStruct)
  {
    return false;
  }
  m_composer.EndStruct();
  m_parse_states.pop();
  return PopState();
}

bool BinaryValueParserHelper::HandleStartArray(ByteIterator& it, const ByteIterator& end)
{
  if (it == end || FetchToken(it) != STRING_TOKEN)
  {
    return false;
  }
  auto str = ParseBinaryString(it, end);
  PushState();
  m_composer.StartArray(str);
  m_parse_states.push(ParseState::kInArray);
  return true;
}

bool BinaryValueParserHelper::HandleEndArray(ByteIterator& it, const ByteIterator& end)
{
  (void)it;
  (void)end;
  if (GetCurrentState() != ParseState::kInArray)
  {
    return false;
  }
  m_composer.EndArray();
  m_parse_states.pop();
  return PopState();
}

}  // namespace dto

}  // namespace sup
