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

#ifndef SUP_DTO_ARITHMETIC_TO_BYTES_T_H_
#define SUP_DTO_ARITHMETIC_TO_BYTES_T_H_

#include <sup/dto/basic_scalar_types.h>

#include <cstring>
#include <vector>

namespace BitConstants
{
const sup::dto::uint32 kLSBMask = 0xFFu;
const sup::dto::uint32 kBitsPerByte = 8u;
}

namespace sup
{
namespace dto
{
template <sup::dto::uint64 Size>
struct UnsignedRepresentation
{};

template <>
struct UnsignedRepresentation<1u>
{
  using type = sup::dto::uint8;
};

template <>
struct UnsignedRepresentation<2u>
{
  using type = sup::dto::uint16;
};

template <>
struct UnsignedRepresentation<4u>
{
  using type = sup::dto::uint32;
};

template <>
struct UnsignedRepresentation<8u>
{
  using type = sup::dto::uint64;
};

template <sup::dto::uint64 Size>
using UnsignedRepresentationType = typename UnsignedRepresentation<Size>::type;

// Convert a basic arithmetic type to a vector of bytes in host byte order.
template <typename T, typename std::enable_if_t<std::is_arithmetic_v<T>, bool> = true>
std::vector<uint8> ToHostOrderT(const T& val)
{
  std::vector<uint8> result(sizeof(T), 0);
  (void)std::memcpy(result.data(), std::addressof(val), sizeof(T));
  return result;
}

// Convert a basic arithmetic type to a vector of bytes in network byte order.
// This implementation assumes that the same endianness is used for floating point values as
// for integral values.
template <typename T, typename std::enable_if_t<std::is_arithmetic_v<T>, bool> = true>
std::vector<uint8> ToNetworkOrder(const T& val)
{
  UnsignedRepresentationType<sizeof(T)> u_val{};
  (void)std::memcpy(&u_val, std::addressof(val), sizeof(T));
  std::vector<uint8> result(sizeof(T), 0);
  for (std::size_t i = 0; i < sizeof(T); ++i)
  {
    auto idx = sizeof(T) - i - 1;
    result[idx] = static_cast<uint8>(u_val & BitConstants::kLSBMask);
    u_val >>= BitConstants::kBitsPerByte;
  }
  return result;
}

// Append the binary representation of an arithmetic value to the provided byte stream.
template <typename T>
void AppendScalarBytesT(std::vector<uint8>& representation, const T& val)
{
  auto val_rep = ToHostOrderT(val);
  (void)representation.insert(representation.cend(), val_rep.cbegin(), val_rep.cend());
}

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ARITHMETIC_TO_BYTES_T_H_
