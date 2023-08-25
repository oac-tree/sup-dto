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
  (void)end;
  auto token = FetchToken(it);
  (void)token;
  // take appropriate action, based on token and current parsing state
  return true;
}

AnyValue BinaryParserHelper::MoveAnyValue()
{
  return m_composer.MoveAnyValue();
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
