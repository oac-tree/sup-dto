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

#include "binary_type_parser_helper.h"

#include <sup/dto/serialize/binary_tokens.h>

namespace sup
{
namespace dto
{

BinaryTypeParserHelper::BinaryTypeParserHelper()
  : m_composer{}
  , m_parse_states{}
{}

bool BinaryTypeParserHelper::HandleToken(ByteIterator& it, ByteIterator end)
{
  auto token = FetchToken(it);
  const auto handler_func = GetHandlerMemberFunction(token);
  if (!handler_func)
  {
    const std::string error =
      "BinaryTypeParserHelper::HandleToken(): encountered unknown token: " + std::to_string(token);
    throw ParseException(error);
  }
  return handler_func(*this, it, end);
}

AnyType BinaryTypeParserHelper::MoveAnyType()
{
  if (GetCurrentState() != ParseState::kNone)
  {
    const std::string error = "BinaryTypeParserHelper::MoveAnyType(): parsing was not complete";
    throw ParseException(error);
  }
  return m_composer.MoveAnyType();
}

std::array<BinaryTypeParserHelper::HandlerMemberFunction, 0x100>
BinaryTypeParserHelper::CreateHandlerMemberFunctionArray()
{
  std::array<BinaryTypeParserHelper::HandlerMemberFunction, 0x100> result;
  result[EMPTY_TOKEN] =
    &BinaryTypeParserHelper::HandleScalar<&AnyTypeComposer::Empty>;
  result[BOOL_TOKEN] =
    &BinaryTypeParserHelper::HandleScalar<&AnyTypeComposer::Bool>;
  result[CHAR8_TOKEN] =
    &BinaryTypeParserHelper::HandleScalar<&AnyTypeComposer::Char8>;
  result[INT8_TOKEN] =
    &BinaryTypeParserHelper::HandleScalar<&AnyTypeComposer::Int8>;
  result[UINT8_TOKEN] =
    &BinaryTypeParserHelper::HandleScalar<&AnyTypeComposer::UInt8>;
  result[INT16_TOKEN] =
    &BinaryTypeParserHelper::HandleScalar<&AnyTypeComposer::Int16>;
  result[UINT16_TOKEN] =
    &BinaryTypeParserHelper::HandleScalar<&AnyTypeComposer::UInt16>;
  result[INT32_TOKEN] =
    &BinaryTypeParserHelper::HandleScalar<&AnyTypeComposer::Int32>;
  result[UINT32_TOKEN] =
    &BinaryTypeParserHelper::HandleScalar<&AnyTypeComposer::UInt32>;
  result[INT64_TOKEN] =
    &BinaryTypeParserHelper::HandleScalar<&AnyTypeComposer::Int64>;
  result[UINT64_TOKEN] =
    &BinaryTypeParserHelper::HandleScalar<&AnyTypeComposer::UInt64>;
  result[FLOAT32_TOKEN] =
    &BinaryTypeParserHelper::HandleScalar<&AnyTypeComposer::Float32>;
  result[FLOAT64_TOKEN] =
    &BinaryTypeParserHelper::HandleScalar<&AnyTypeComposer::Float64>;
  result[STRING_TOKEN] = &BinaryTypeParserHelper::HandleString;
  result[START_STRUCT_TOKEN] = &BinaryTypeParserHelper::HandleStartStruct;
  result[END_STRUCT_TOKEN] = &BinaryTypeParserHelper::HandleEndStruct;
  result[START_ARRAY_TOKEN] = &BinaryTypeParserHelper::HandleStartArray;
  result[END_ARRAY_TOKEN] = &BinaryTypeParserHelper::HandleEndArray;
  return result;
}

BinaryTypeParserHelper::HandlerMemberFunction
BinaryTypeParserHelper::GetHandlerMemberFunction(sup::dto::uint8 token)
{
  static const auto functions = CreateHandlerMemberFunctionArray();
  return functions[token];
}

ParseState BinaryTypeParserHelper::GetCurrentState() const
{
  if (m_parse_states.empty())
  {
    return ParseState::kNone;
  }
  return m_parse_states.top();
}

void BinaryTypeParserHelper::PushState()
{
  const auto current_state = GetCurrentState();
  // Only arrays need to be handled here, structures do this during the field name parsing.
  if (current_state == ParseState::kInArray)
  {
    m_composer.StartArrayElement();
    m_parse_states.push(ParseState::kInArrayElement);
  }
}

bool BinaryTypeParserHelper::PopState()
{
  const auto current_state = GetCurrentState();
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

// HandleString is not intented to be called during parsing of struct/array typenames
bool BinaryTypeParserHelper::HandleString(ByteIterator& it, ByteIterator end)
{
  const auto current_state = GetCurrentState();
  if (current_state == ParseState::kInStruct)
  {
    const auto str = ParseBinaryString(it, end);
    m_composer.StartField(str);
    m_parse_states.push(ParseState::kInStructElement);
    return true;
  }
  PushState();
  m_composer.String();
  return PopState();
}

bool BinaryTypeParserHelper::HandleStartStruct(ByteIterator& it, ByteIterator end)
{
  if ((it == end) || (FetchToken(it) != STRING_TOKEN))
  {
    return false;
  }
  const auto str = ParseBinaryString(it, end);
  PushState();
  m_composer.StartStruct(str);
  m_parse_states.push(ParseState::kInStruct);
  return true;
}

bool BinaryTypeParserHelper::HandleEndStruct(ByteIterator&, ByteIterator)
{
  if (GetCurrentState() != ParseState::kInStruct)
  {
    return false;
  }
  m_composer.EndStruct();
  m_parse_states.pop();
  return PopState();
}

bool BinaryTypeParserHelper::HandleStartArray(ByteIterator& it, ByteIterator end)
{
  if ((it == end) || (FetchToken(it) != STRING_TOKEN))
  {
    return false;
  }
  const auto str = ParseBinaryString(it, end);
  const auto size = ParseSize(it, end);
  PushState();
  m_composer.StartArray(str, size);
  m_parse_states.push(ParseState::kInArray);
  return true;
}

bool BinaryTypeParserHelper::HandleEndArray(ByteIterator&, ByteIterator)
{
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
