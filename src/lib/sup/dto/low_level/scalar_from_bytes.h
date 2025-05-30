/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : SUP - DTO
 *
 * Description   : Unit test code
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

#ifndef SUP_DTO_SCALAR_FROM_BYTES_H_
#define SUP_DTO_SCALAR_FROM_BYTES_H_

#include "binary_parser_functions.h"

#include <sup/dto/anyvalue.h>

#include <algorithm>

namespace sup
{
namespace dto
{

template <typename T>
std::size_t AssignBytes(AnyValue& anyvalue, const uint8* bytes, std::size_t size,
                        std::size_t position)
{
  if ((position + sizeof(T)) > size)
  {
    throw ParseException("Trying to parse beyond size of byte array");
  }
  std::vector<uint8> byte_vector(bytes + position, bytes + position + sizeof(T));
  auto begin_it = byte_vector.cbegin();
  auto val = ParseBinaryScalarT<T>(begin_it, byte_vector.cend());
  anyvalue = val;
  return position + sizeof(T);
}

template <>
std::size_t AssignBytes<std::string>(AnyValue& anyvalue, const uint8* bytes, std::size_t size,
                                     std::size_t position)
{
  auto end_position = position + kStringMaxLength;
  if (end_position > size)
  {
    throw ParseException("Trying to parse beyond size of byte array");
  }
  auto null_pos = std::find(&bytes[position], &bytes[end_position], '\0');
  if (null_pos == &bytes[end_position])
  {
    throw ParseException("C-type string is not null-terminated");
  }
  std::string val = reinterpret_cast<const char*>(&bytes[position]);
  anyvalue = val;
  return end_position;
}

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_SCALAR_FROM_BYTES_H_
