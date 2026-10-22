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

#ifndef SUP_DTO_TYPE_CODE_HELPER_H_
#define SUP_DTO_TYPE_CODE_HELPER_H_

#include <sup/dto/anytype.h>

#include <string>

namespace sup
{
namespace dto
{

/**
 * @brief Compile-time mapping from a scalar C++ type to its TypeCode, as TypeToCode<T>::code.
 *
 * Defined for the scalar types only (boolean, char8, int8 ... uint64, float32, float64 and
 * std::string); using any other type is a compile error.
 */
template <typename T>
struct TypeToCode;

template <>
struct TypeToCode<boolean>
{
  static constexpr TypeCode code = TypeCode::Bool;
};

template <>
struct TypeToCode<char8>
{
  static constexpr TypeCode code = TypeCode::Char8;
};

template <>
struct TypeToCode<int8>
{
  static constexpr TypeCode code = TypeCode::Int8;
};

template <>
struct TypeToCode<uint8>
{
  static constexpr TypeCode code = TypeCode::UInt8;
};

template <>
struct TypeToCode<int16>
{
  static constexpr TypeCode code = TypeCode::Int16;
};

template <>
struct TypeToCode<uint16>
{
  static constexpr TypeCode code = TypeCode::UInt16;
};

template <>
struct TypeToCode<int32>
{
  static constexpr TypeCode code = TypeCode::Int32;
};

template <>
struct TypeToCode<uint32>
{
  static constexpr TypeCode code = TypeCode::UInt32;
};

template <>
struct TypeToCode<int64>
{
  static constexpr TypeCode code = TypeCode::Int64;
};

template <>
struct TypeToCode<uint64>
{
  static constexpr TypeCode code = TypeCode::UInt64;
};

template <>
struct TypeToCode<float32>
{
  static constexpr TypeCode code = TypeCode::Float32;
};

template <>
struct TypeToCode<float64>
{
  static constexpr TypeCode code = TypeCode::Float64;
};

template <>
struct TypeToCode<std::string>
{
  static constexpr TypeCode code = TypeCode::String;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_TYPE_CODE_HELPER_H_
