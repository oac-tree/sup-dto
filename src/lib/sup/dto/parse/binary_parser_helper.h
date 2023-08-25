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

#ifndef SUP_DTO_BINARY_PARSER_HELPER_H_
#define SUP_DTO_BINARY_PARSER_HELPER_H_

#include <sup/dto/parse/binary_parser.h>

#include <sup/dto/anyvalue_composer.h>

#include <stack>

namespace sup
{
namespace dto
{

enum ParseState
{
  kInStruct = 0,
  kInStructElement,
  kInArray,
  kInArrayElement
};

class BinaryParserHelper
{
public:
  BinaryParserHelper();
  ~BinaryParserHelper() = default;

  bool HandleToken(ByteIterator& it, const ByteIterator& end);

  AnyValue MoveAnyValue();
private:
  AnyValueComposer m_composer;
  std::stack<ParseState> m_parse_states;
};

sup::dto::uint8 FetchToken(ByteIterator& it);

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_BINARY_PARSER_HELPER_H_
