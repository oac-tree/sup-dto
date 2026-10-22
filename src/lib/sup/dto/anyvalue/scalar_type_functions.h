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

#ifndef SUP_DTO_SCALAR_TYPE_FUNCTIONS_H_
#define SUP_DTO_SCALAR_TYPE_FUNCTIONS_H_

#include <sup/dto/anyvalue/i_value_data.h>
#include <sup/dto/type_code_helper.h>

namespace sup
{
namespace dto
{

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
