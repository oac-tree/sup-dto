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

#ifndef SUP_DTO_SCALAR_CONVERSION_H_
#define SUP_DTO_SCALAR_CONVERSION_H_

#include <sup/dto/basic_scalar_types.h>
#include <sup/dto/anyvalue_exceptions.h>

#include <limits>
#include <type_traits>

namespace sup
{
namespace dto
{

template <typename T>
struct IsStrictlyInteger
{
  static constexpr bool value = std::is_integral<T>::value &&
      !std::is_same<typename std::remove_cv<T>::type, bool>::value;
};

template <typename T>
constexpr bool IsStrictlyInteger<T>::value;

template <typename T>
struct IsStrictlyArithmetic
{
  static constexpr bool value = std::is_arithmetic<T>::value &&
      !std::is_same<typename std::remove_cv<T>::type, bool>::value;
};

template <typename T>
constexpr bool IsStrictlyArithmetic<T>::value;

template <typename T>
struct IsSignedInteger
{
  static constexpr bool value = IsStrictlyInteger<T>::value && std::is_signed<T>::value;
};

template <typename T>
constexpr bool IsSignedInteger<T>::value;

template <typename T>
struct IsUnsignedInteger
{
  static constexpr bool value = IsStrictlyInteger<T>::value && !std::is_signed<T>::value;
};

template <typename T>
constexpr bool IsUnsignedInteger<T>::value;

// Conversion between signed integer types
template <typename To, typename From,
  typename std::enable_if<IsSignedInteger<To>::value &&
                          IsSignedInteger<From>::value, bool>::type = true>
To ConvertScalar(const From& value)
{
  if ((value < std::numeric_limits<To>::min()) || (value > std::numeric_limits<To>::max()))
  {
    throw InvalidConversionException("Source value doesn't fit in destination type");
  }
  return static_cast<To>(value);
}

// Conversion between unsigned integer types
template <typename To, typename From,
  typename std::enable_if<IsUnsignedInteger<To>::value &&
                          IsUnsignedInteger<From>::value, bool>::type = true>
To ConvertScalar(const From& value)
{
  if (value > std::numeric_limits<To>::max())
  {
    throw InvalidConversionException("Source value doesn't fit in destination type");
  }
  return static_cast<To>(value);
}

// Conversion from signed to unsigned integer types
template <typename To, typename From,
  typename std::enable_if<IsUnsignedInteger<To>::value &&
                          IsSignedInteger<From>::value, bool>::type = true>
To ConvertScalar(const From& value)
{
  if ((value < 0) ||
      (static_cast<typename std::make_unsigned<From>::type>(value) > std::numeric_limits<To>::max()))
  {
    throw InvalidConversionException("Source value doesn't fit in destination type");
  }
  return static_cast<To>(value);
}

// Conversion from unsigned to signed integer types
template <typename To, typename From,
  typename std::enable_if<IsSignedInteger<To>::value &&
                          IsUnsignedInteger<From>::value, bool>::type = true>
To ConvertScalar(const From& value)
{
  if (value > static_cast<typename std::make_unsigned<To>::type>(std::numeric_limits<To>::max()))
  {
    throw InvalidConversionException("Source value doesn't fit in destination type");
  }
  return static_cast<To>(value);
}

// Conversion from any arithmetic type to boolean type
template <typename To, typename From,
  typename std::enable_if<std::is_same<typename std::remove_cv<To>::type, bool>::value &&
    std::is_arithmetic<From>::value, bool>::type = true>
To ConvertScalar(const From& value)
{
  return static_cast<To>(value);
}

// Conversion from boolean type to strict arithmetic type (to avoid duplicate declaration)
template <typename To, typename From,
  typename std::enable_if<IsStrictlyArithmetic<To>::value &&
    std::is_same<typename std::remove_cv<From>::type, bool>::value, bool>::type = true>
To ConvertScalar(const From& value)
{
  return static_cast<To>(value);
}

// Conversion from strict integer type to floating type
template <typename To, typename From,
  typename std::enable_if<std::is_floating_point<To>::value &&
    IsStrictlyInteger<From>::value, bool>::type = true>
To ConvertScalar(const From& value)
{
  return static_cast<To>(value);
}

// Conversion from floating type to strictly arithmetic type
template <typename To, typename From,
  typename std::enable_if<IsStrictlyArithmetic<To>::value &&
    std::is_floating_point<From>::value, bool>::type = true>
To ConvertScalar(const From& value)
{
  if ((value < static_cast<To>(std::numeric_limits<To>::lowest())) ||
      (value > static_cast<To>(std::numeric_limits<To>::max())))
  {
    throw InvalidConversionException("Source value doesn't fit in destination type");
  }
  return static_cast<To>(value);
}

// Conversion from any arithmetic type to string type
template <typename To, typename From,
  typename std::enable_if<std::is_same<typename std::remove_cv<To>::type, std::string>::value &&
    std::is_arithmetic<From>::value, bool>::type = true>
To ConvertScalar(const From&)
{
  throw InvalidConversionException("Cannot convert arithmetic types to string");
}

// Conversion from string type to any arithmetic type
template <typename To, typename From,
  typename std::enable_if<std::is_arithmetic<To>::value &&
    std::is_same<typename std::remove_cv<From>::type, std::string>::value, bool>::type = true>
To ConvertScalar(const From&)
{
  throw InvalidConversionException("Cannot convert string to arithmetic types");
}

// Conversion between string types
template <typename To, typename From,
  typename std::enable_if<std::is_same<typename std::remove_cv<To>::type, std::string>::value &&
    std::is_same<typename std::remove_cv<From>::type, std::string>::value, bool>::type = true>
To ConvertScalar(const From& value)
{
  return value;
}

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_SCALAR_CONVERSION_H_
