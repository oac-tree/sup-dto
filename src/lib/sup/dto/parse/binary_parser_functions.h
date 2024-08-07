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

#ifndef SUP_DTO_BINARY_PARSER_FUNCTIONS_H_
#define SUP_DTO_BINARY_PARSER_FUNCTIONS_H_

#include <sup/dto/parse/binary_parser.h>
#include <sup/dto/serialize/append_scalar_t.h>

namespace sup
{
namespace dto
{

sup::dto::uint8 FetchToken(ByteIterator& it);

template <typename T>
T ParseBinaryScalarT(ByteIterator& it, ByteIterator end)
{
  if (static_cast<std::size_t>(std::distance(it, end)) < sizeof(T))
  {
    throw ParseException("End of byte stream encountered during scalar value parsing");
  }
  UnsignedRepresentationType<sizeof(T)> u_val = 0;
  for (sup::dto::uint8 i = 0; i < sizeof(T); ++i)
  {
    UnsignedRepresentationType<sizeof(T)> u_tmp = *it++;
    u_tmp <<= (kBitsPerByte*i);
    u_val += u_tmp;
  }
  T result = T{};
  (void)std::memcpy(std::addressof(result), &u_val, sizeof(T));
  return result;
}

std::string ParseBinaryString(ByteIterator& it, ByteIterator end);

sup::dto::uint64 ParseSize(ByteIterator& it, ByteIterator end);

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_BINARY_PARSER_FUNCTIONS_H_
