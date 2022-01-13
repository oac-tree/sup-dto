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
 * Copyright (c) : 2010-2022 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

/**
 * @file ScalarConversion.h
 * @brief Header file for ScalarConversion templates.
 * @date 12/01/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the ScalarConversion templates.
 */

#ifndef _SUP_ScalarConversion_h_
#define _SUP_ScalarConversion_h_

#include "BasicScalarTypes.h"

#include "AnyValueExceptions.h"

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
      !std::is_same<std::remove_cv_t<T>, bool>::value;
};

template <typename T>
struct IsSignedInteger
{
  static constexpr bool value = IsStrictlyInteger<T>::value && std::is_signed<T>::value;
};

template <typename T>
struct IsUnsignedInteger
{
  static constexpr bool value = IsStrictlyInteger<T>::value && !std::is_signed<T>::value;
};

// Conversion between signed integer types
template <typename To, typename From,
  std::enable_if_t<IsSignedInteger<To>::value && IsSignedInteger<From>::value, bool> = true>
To ConvertScalar(const From& value)
{
  if (value < std::numeric_limits<To>::min() || value > std::numeric_limits<To>::max())
  {
    throw InvalidConversionException("Source value doesn't fit in destination type");
  }
  return static_cast<To>(value);
}

// Conversion between unsigned integer types
template <typename To, typename From,
  std::enable_if_t<IsUnsignedInteger<To>::value && IsUnsignedInteger<From>::value, bool> = true>
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
  std::enable_if_t<IsUnsignedInteger<To>::value && IsSignedInteger<From>::value, bool> = true>
To ConvertScalar(const From& value)
{
  if (value < 0 || value > std::numeric_limits<To>::max())
  {
    throw InvalidConversionException("Source value doesn't fit in destination type");
  }
  return static_cast<To>(value);
}

// Conversion from unsigned to signed integer types
template <typename To, typename From,
  std::enable_if_t<IsSignedInteger<To>::value && IsUnsignedInteger<From>::value, bool> = true>
To ConvertScalar(const From& value)
{
  if (value > std::numeric_limits<To>::max())
  {
    throw InvalidConversionException("Source value doesn't fit in destination type");
  }
  return static_cast<To>(value);
}

// Conversion from any integer type to boolean type
template <typename To, typename From,
  std::enable_if_t<std::is_same<std::remove_cv_t<To>, bool>::value &&
    std::is_integral<From>::value, bool> = true>
To ConvertScalar(const From& value)
{
  return value;
}

// Conversion from boolean type to strict integer type (to avoid duplicate declaration)
template <typename To, typename From,
  std::enable_if_t<IsStrictlyInteger<To>::value &&
    std::is_same<std::remove_cv_t<From>, bool>::value, bool> = true>
To ConvertScalar(const From& value)
{
  return value;
}

}  // namespace dto

}  // namespace sup

#endif  // _SUP_ScalarConversion_h_
