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
 * Copyright (c) : 2010-2025 ITER Organization,
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

#ifndef SUP_DTO_BINARY_TYPE_PARSER_HELPER_H_
#define SUP_DTO_BINARY_TYPE_PARSER_HELPER_H_

#include <sup/dto/parse/binary_parser.h>
#include <sup/dto/low_level/binary_parser_functions.h>

#include <sup/dto/anytype_composer.h>

#include <array>
#include <stack>

namespace sup
{
namespace dto
{

class BinaryTypeParserHelper
{
public:
  BinaryTypeParserHelper();
  ~BinaryTypeParserHelper() = default;

  BinaryTypeParserHelper(const BinaryTypeParserHelper& other) = delete;
  BinaryTypeParserHelper(BinaryTypeParserHelper&& other) = delete;
  BinaryTypeParserHelper& operator=(const BinaryTypeParserHelper& other) = delete;
  BinaryTypeParserHelper& operator=(BinaryTypeParserHelper&& other) = delete;

  bool HandleToken(ByteIterator& it, ByteIterator end);

  AnyType MoveAnyType();

private:
  using HandlerMemberFunction =
    std::function<bool(BinaryTypeParserHelper&, ByteIterator&, ByteIterator)>;
  static std::array<HandlerMemberFunction, 0x100> CreateHandlerMemberFunctionArray();
  static HandlerMemberFunction GetHandlerMemberFunction(sup::dto::uint8 token);

  AnyTypeComposer m_composer;
  std::stack<ParseState> m_parse_states;

  ParseState GetCurrentState() const;

  void PushState();
  bool PopState();

  template <void (AnyTypeComposer::*mem_fun)() >
  bool HandleScalar(ByteIterator&, ByteIterator);

  bool HandleString(ByteIterator& it, ByteIterator end);
  bool HandleStartStruct(ByteIterator& it, ByteIterator end);
  bool HandleEndStruct(ByteIterator&, ByteIterator);
  bool HandleStartArray(ByteIterator& it, ByteIterator end);
  bool HandleEndArray(ByteIterator&, ByteIterator);
};

template <void (AnyTypeComposer::*mem_fun)() >
bool BinaryTypeParserHelper::HandleScalar(ByteIterator&, ByteIterator)
{
  PushState();
  (m_composer.*mem_fun)();
  return PopState();
}

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_BINARY_TYPE_PARSER_HELPER_H_
