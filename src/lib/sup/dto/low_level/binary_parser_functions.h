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
 * Copyright (c) : 2010-2026 ITER Organization,
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

#ifndef SUP_DTO_BINARY_PARSER_FUNCTIONS_H_
#define SUP_DTO_BINARY_PARSER_FUNCTIONS_H_

#include "arithmetic_to_bytes_t.h"

#include <sup/dto/parse/binary_parser.h>

namespace sup
{
namespace dto
{

sup::dto::uint8 FetchToken(ByteIterator& it);

template <typename T, typename InputIterator,
          typename std::enable_if_t<std::is_arithmetic_v<T>, bool> = true>
T ParseFromHostOrderT(InputIterator& it, InputIterator end)
{
  if (static_cast<std::size_t>(std::distance(it, end)) < sizeof(T))
  {
    throw ParseException("End of byte stream encountered during scalar value parsing");
  }
  const std::vector<uint8> bytes{it, it + sizeof(T)};
  it += sizeof(T);
  T result{};
  (void)std::memcpy(std::addressof(result), bytes.data(), sizeof(T));
  return result;
}

template <typename T, typename InputIterator,
          typename std::enable_if_t<std::is_arithmetic_v<T>, bool> = true>
T ParseFromNetworkOrderT(InputIterator& it, InputIterator end)
{
  if (static_cast<std::size_t>(std::distance(it, end)) < sizeof(T))
  {
    throw ParseException("End of byte stream encountered during scalar value parsing");
  }
  UnsignedRepresentationType<sizeof(T)> u_val = 0;
  for (std::size_t i = 0; i < sizeof(T); ++i)
  {
    u_val <<= (BitConstants::kBitsPerByte);
    u_val += *it++;
  }
  T result{};
  (void)std::memcpy(std::addressof(result), &u_val, sizeof(T));
  return result;
}

std::string ParseBinaryString(ByteIterator& it, ByteIterator end);

sup::dto::uint64 ParseSize(ByteIterator& it, ByteIterator end);

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_BINARY_PARSER_FUNCTIONS_H_
