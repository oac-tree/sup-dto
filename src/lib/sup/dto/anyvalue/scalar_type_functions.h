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
 * Copyright (c) : 2010-2025 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#ifndef SUP_DTO_SCALAR_TYPE_FUNCTIONS_H_
#define SUP_DTO_SCALAR_TYPE_FUNCTIONS_H_

#include <sup/dto/anyvalue/i_value_data.h>

namespace sup
{
namespace dto
{

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

template <typename T>
struct TypeToConversionFunc;

template <>
struct TypeToConversionFunc<boolean>
{
  static constexpr boolean (IValueData::* MemFunc)() const = &IValueData::AsBoolean;
};

template <>
struct TypeToConversionFunc<char8>
{
  static constexpr char8 (IValueData::* MemFunc)() const = &IValueData::AsCharacter8;
};

template <>
struct TypeToConversionFunc<int8>
{
  static constexpr int8 (IValueData::* MemFunc)() const = &IValueData::AsSignedInteger8;
};

template <>
struct TypeToConversionFunc<uint8>
{
  static constexpr uint8 (IValueData::* MemFunc)() const = &IValueData::AsUnsignedInteger8;
};

template <>
struct TypeToConversionFunc<int16>
{
  static constexpr int16 (IValueData::* MemFunc)() const = &IValueData::AsSignedInteger16;
};

template <>
struct TypeToConversionFunc<uint16>
{
  static constexpr uint16 (IValueData::* MemFunc)() const = &IValueData::AsUnsignedInteger16;
};

template <>
struct TypeToConversionFunc<int32>
{
  static constexpr int32 (IValueData::* MemFunc)() const = &IValueData::AsSignedInteger32;
};

template <>
struct TypeToConversionFunc<uint32>
{
  static constexpr uint32 (IValueData::* MemFunc)() const = &IValueData::AsUnsignedInteger32;
};

template <>
struct TypeToConversionFunc<int64>
{
  static constexpr int64 (IValueData::* MemFunc)() const = &IValueData::AsSignedInteger64;
};

template <>
struct TypeToConversionFunc<uint64>
{
  static constexpr uint64 (IValueData::* MemFunc)() const = &IValueData::AsUnsignedInteger64;
};

template <>
struct TypeToConversionFunc<float32>
{
  static constexpr float32 (IValueData::* MemFunc)() const = &IValueData::AsFloat32;
};

template <>
struct TypeToConversionFunc<float64>
{
  static constexpr float64 (IValueData::* MemFunc)() const = &IValueData::AsFloat64;
};

template <>
struct TypeToConversionFunc<std::string>
{
  static constexpr std::string (IValueData::* MemFunc)() const = &IValueData::AsString;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_SCALAR_TYPE_FUNCTIONS_H_
