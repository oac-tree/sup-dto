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

#include "binary_parser_functions.h"

#include <sup/dto/serialize/binary_tokens.h>

namespace sup
{
namespace dto
{

sup::dto::uint8 FetchToken(ByteIterator& it)
{
  return *it++;
}

std::string ParseBinaryString(ByteIterator& it, const ByteIterator& end)
{
  const auto str_size = ParseSize(it, end);
  if (static_cast<std::size_t>(std::distance(it, end)) < str_size)
  {
    throw ParseException("End of byte stream encountered during string value parsing");
  }
  std::string result;
  result.reserve(str_size);
  for (sup::dto::uint64 i = 0u; i < str_size; ++i)
  {
    const auto u = *it++;
    char c;
    std::memcpy(&c, &u, 1u);
    result.push_back(c);
  }
  return result;
}

sup::dto::uint64 ParseSize(ByteIterator& it, const ByteIterator& end)
{
  if (it == end)
  {
    throw ParseException("End of byte stream encountered during size parsing");
  }
  const auto token = *it++;
  if (token < SHORT_SIZE_LIMIT)
  {
    return token;
  }
  // No test is done to check that the current token is LONG_SIZE_TOKEN, since the
  // current value of the limit is 0xFF.
  return ParseBinaryScalarT<sup::dto::uint64>(it, end);
}

}  // namespace dto

}  // namespace sup
