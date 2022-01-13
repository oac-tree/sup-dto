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

// Conversion between strictly integer types
template <typename To, typename From,
  std::enable_if_t<IsStrictlyInteger<To>::value && IsStrictlyInteger<From>::value, bool> = true>
To ConvertScalar(const From& value)
{
  if (value < std::numeric_limits<To>::min() || value > std::numeric_limits<To>::max())
  {
    throw InvalidConversionException("Source value doesn't fit in destination type");
  }
  return value;
}

// Conversion from any integer type to boolean type
template <typename To, typename From,
  std::enable_if_t<std::is_same<std::remove_cv_t<To>, bool>::value &&
    std::is_integral<From>::value, bool> = true>
To ConvertScalar(const From& value)
{
  return value;
}

// Conversion from boolean type to integer type
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
