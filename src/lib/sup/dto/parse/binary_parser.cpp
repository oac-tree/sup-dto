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

#include "binary_parser.h"

#include <sup/dto/anyvalue_composer.h>

#include <stack>

namespace
{
using namespace sup::dto;

sup::dto::uint8 FetchToken(ByteIterator& it);

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
}

namespace sup
{
namespace dto
{

AnyValue ParseAnyValue(ByteIterator& it, const ByteIterator& end)
{
  BinaryParserHelper helper;
  while (it != end)
  {
    if (!helper.HandleToken(it, end))
    {
      break;
    }
  }
  // Make sure the helper has correctly finished (e.g. stack empty)
  return helper.MoveAnyValue();
}

}  // namespace dto

}  // namespace sup

namespace
{
using namespace sup::dto;

sup::dto::uint8 FetchToken(ByteIterator& it)
{
  auto token = *it;
  ++it;
  return token;
}

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

}
