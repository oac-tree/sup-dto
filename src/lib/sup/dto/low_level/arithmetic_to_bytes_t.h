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
#include <array>

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

// Specialization for integers with sizeof(T) > 1
// The passed value is converted to an unsigned integral type and then serialized in little
// endian format (regardless of system endianness)
// The choice for little endian encoding is motivated by the fact that most common systems use this
// format, which would allow a more performant implementation (if required) on these systems.
template <typename T,
          typename std::enable_if<std::is_integral<T>::value && (sizeof(T) > 1), bool>::type = true>
std::vector<uint8> ArithmeticToBytesT(const T& val)
{
  auto u_val = static_cast<UnsignedRepresentationType<sizeof(T)>>(val);
  std::vector<uint8> result(sizeof(T), 0);
  for (std::size_t i = 0; i < sizeof(T); ++i)
  {
    result[i] = static_cast<uint8>(u_val & BitConstants::kLSBMask);
    u_val >>= BitConstants::kBitsPerByte;
  }
  return result;
}

// Specialization for integers with sizeof(T) == 1
template <typename T,
          typename std::enable_if<std::is_integral<T>::value && (sizeof(T) == 1), bool>::type = true>
std::vector<uint8> ArithmeticToBytesT(const T &val)
{
  auto u_val = static_cast<UnsignedRepresentationType<sizeof(T)>>(val);
  std::vector<uint8> result{};
  result.push_back(u_val);
  return result;
}

// Specialization for floating points
// This implementation assumes that the same endianness is used for floating point values as
// for integral values.
template <typename T, typename std::enable_if<std::is_floating_point<T>::value, bool>::type = true>
std::vector<uint8> ArithmeticToBytesT(const T& val)
{
  UnsignedRepresentationType<sizeof(T)> u_val{};
  (void)std::memcpy(&u_val, std::addressof(val), sizeof(T));
  std::vector<uint8> result(sizeof(T), 0);
  for (std::size_t i = 0; i < sizeof(T); ++i)
  {
    result[i] = static_cast<uint8>(u_val & BitConstants::kLSBMask);
    u_val >>= BitConstants::kBitsPerByte;
  }
  return result;
}

// Append the binary representation of an arithmetic value to the provided byte stream.
template <typename T>
void AppendScalarBytesT(std::vector<uint8>& representation, const T& val)
{
  auto val_rep = ArithmeticToBytesT(val);
  (void)representation.insert(representation.cend(), val_rep.cbegin(), val_rep.cend());
}

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ARITHMETIC_TO_BYTES_T_H_
