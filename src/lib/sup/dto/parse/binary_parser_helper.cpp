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

#include "binary_parser_helper.h"

#include <sup/dto/serialize/binary_tokens.h>

namespace sup
{
namespace dto
{

BinaryParserHelper::BinaryParserHelper()
  : m_composer{}
  , m_parse_states{}
{}

bool BinaryParserHelper::HandleToken(ByteIterator& it, const ByteIterator& end)
{
  auto token = FetchToken(it);
  auto handler_func = GetHandlerMemberFunction(token);
  if (!handler_func)
  {
    std::string error = "BinaryParserHelper::HandleToken(): encountered unknown token: " +
      std::to_string(token);
    throw ParseException(error);
  }
  return handler_func(*this, it, end);
}

AnyValue BinaryParserHelper::MoveAnyValue()
{
  return m_composer.MoveAnyValue();
}

std::array<BinaryParserHelper::HandlerMemberFunction, 0x100>
BinaryParserHelper::CreateHandlerMemberFunctionArray()
{
  std::array<BinaryParserHelper::HandlerMemberFunction, 0x100> result;
  result[EMPTY_TOKEN] = &BinaryParserHelper::HandleEmpty;
  result[BOOL_TOKEN] =
    &BinaryParserHelper::HandleScalar<sup::dto::boolean, &AnyValueComposer::Bool>;
  result[CHAR8_TOKEN] =
    &BinaryParserHelper::HandleScalar<sup::dto::char8, &AnyValueComposer::Char8>;
  result[INT8_TOKEN] =
    &BinaryParserHelper::HandleScalar<sup::dto::int8, &AnyValueComposer::Int8>;
  result[UINT8_TOKEN] =
    &BinaryParserHelper::HandleScalar<sup::dto::uint8, &AnyValueComposer::UInt8>;
  result[INT16_TOKEN] =
    &BinaryParserHelper::HandleScalar<sup::dto::int16, &AnyValueComposer::Int16>;
  result[UINT16_TOKEN] =
    &BinaryParserHelper::HandleScalar<sup::dto::uint16, &AnyValueComposer::UInt16>;
  result[INT32_TOKEN] =
    &BinaryParserHelper::HandleScalar<sup::dto::int32, &AnyValueComposer::Int32>;
  result[UINT32_TOKEN] =
    &BinaryParserHelper::HandleScalar<sup::dto::uint32, &AnyValueComposer::UInt32>;
  result[INT64_TOKEN] =
    &BinaryParserHelper::HandleScalar<sup::dto::int64, &AnyValueComposer::Int64>;
  result[UINT64_TOKEN] =
    &BinaryParserHelper::HandleScalar<sup::dto::uint64, &AnyValueComposer::UInt64>;
  result[FLOAT32_TOKEN] =
    &BinaryParserHelper::HandleScalar<sup::dto::float32, &AnyValueComposer::Float32>;
  result[FLOAT64_TOKEN] =
    &BinaryParserHelper::HandleScalar<sup::dto::float64, &AnyValueComposer::Float64>;
  result[STRING_TOKEN] = &BinaryParserHelper::HandleString;
  result[START_STRUCT_TOKEN] = &BinaryParserHelper::HandleStartStruct;
  result[END_STRUCT_TOKEN] = &BinaryParserHelper::HandleEndStruct;
  result[START_ARRAY_TOKEN] = &BinaryParserHelper::HandleStartArray;
  result[END_ARRAY_TOKEN] = &BinaryParserHelper::HandleEndArray;
  return result;
}

BinaryParserHelper::HandlerMemberFunction
BinaryParserHelper::GetHandlerMemberFunction(sup::dto::uint8 token)
{
  static auto functions = CreateHandlerMemberFunctionArray();
  return functions[token];
}

void BinaryParserHelper::PushState()
{
  if (m_parse_states.empty())
  {
    return;
  }
  auto current_state = m_parse_states.top();
  // Only arrays need to be handled here, structures do this during the field name parsing.
  if (current_state == kInArray)
  {
    m_parse_states.push(kInArrayElement);
  }
}

bool BinaryParserHelper::PopState()
{
  if (m_parse_states.empty())
  {
    return false;
  }
  auto current_state = m_parse_states.top();
  if (current_state == kInStructElement)
  {
    m_composer.EndField();
    m_parse_states.pop();
    return true;
  }
  if (current_state == kInArrayElement)
  {
    m_composer.EndArrayElement();
    m_parse_states.pop();
    return true;
  }
  return false;
}

bool BinaryParserHelper::HandleEmpty(ByteIterator& it, const ByteIterator& end)
{
  (void)it;
  (void)end;
  PushState();
  m_composer.Empty();
  return PopState();
}

// HandleString is not intented to be called during parsing of struct/array typenames
bool BinaryParserHelper::HandleString(ByteIterator& it, const ByteIterator& end)
{
  auto str = ParseBinaryString(it, end);
  auto current_state = m_parse_states.top();
  if (current_state == kInStruct)
  {
    m_composer.StartField(str);
    m_parse_states.push(kInStructElement);
    return true;
  }
  PushState();
  m_composer.String(str);
  return PopState();
}

bool BinaryParserHelper::HandleStartStruct(ByteIterator& it, const ByteIterator& end)
{
  if (it == end || FetchToken(it) != STRING_TOKEN)
  {
    return false;
  }
  auto str = ParseBinaryString(it, end);
  PushState();
  m_composer.StartStruct(str);
  m_parse_states.push(kInStruct);
  return true;
}

bool BinaryParserHelper::HandleEndStruct(ByteIterator& it, const ByteIterator& end)
{
  (void)it;
  (void)end;
  if (m_parse_states.top() != kInStruct)
  {
    return false;
  }
  m_composer.EndStruct();
  m_parse_states.pop();
  return PopState();
}

bool BinaryParserHelper::HandleStartArray(ByteIterator& it, const ByteIterator& end)
{
  if (it == end || FetchToken(it) != STRING_TOKEN)
  {
    return false;
  }
  auto str = ParseBinaryString(it, end);
  PushState();
  m_composer.StartArray(str);
  m_parse_states.push(kInArray);
  return true;
}

bool BinaryParserHelper::HandleEndArray(ByteIterator& it, const ByteIterator& end)
{
  (void)it;
  (void)end;
  if (m_parse_states.top() != kInArray)
  {
    return false;
  }
  m_composer.EndArray();
  m_parse_states.pop();
  return PopState();
}

sup::dto::uint8 FetchToken(ByteIterator& it)
{
  return *it++;
}

}  // namespace dto

}  // namespace sup
