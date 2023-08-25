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

namespace sup
{
namespace dto
{

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

}  // namespace dto

}  // namespace sup


