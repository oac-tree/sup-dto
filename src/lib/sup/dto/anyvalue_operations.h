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

#ifndef SUP_DTO_ANYVALUE_OPERATIONS_H_
#define SUP_DTO_ANYVALUE_OPERATIONS_H_

#include <sup/dto/anyvalue.h>

namespace sup
{
namespace dto
{

enum class CompareResult : sup::dto::uint32
{
  Less,
  Greater,
  Equivalent,
  Unordered
};

/**
 * @brief Scalar comparison function.
 *
 * @details This comparison function will only provide meaningful results, i.e. not 'Unordered' when
 * comparing scalar types with underlying numeric types (scalar types excluding 'empty', 'bool',
 * 'char8' and 'string').
 * Furthermore, if one of the types is floating point, the comparison will use the largest floating
 * point type among the given types as the common type ('float64' if there is one, 'float32'
 * otherwise).
 * Integral comparisons are only supported between types that are both signed or both unsigned. In
 * these cases, the widest signed or unsigned integral type is used ('int64' or 'uint64').
 * For all comparisons that are not supported (for example 'string', structures, signed with
 * unsigned, etc.), the function returns 'Unordered'.
*/
CompareResult Compare(const AnyValue& lhs, const AnyValue& rhs);

/**
 * @brief Increment the underlying scalar value if possible.
 *
 * @details For numeric types (integers and floating point types), the underlying value will be
 * incremented by 1. Integral types will wrap around (max value becomes min value).
 * The following types are not supported and will cause the function to return 'false':
 * 'empty', 'bool', 'char8', 'string', 'struct' and 'array'.
*/
bool Increment(AnyValue& value);

/**
 * @brief Decrement the underlying scalar value if possible.
 *
 * @details For numeric types (integers and floating point types), the underlying value will be
 * decremented by 1. Integral types will wrap around (min value becomes max value).
 * The following types are not supported and will cause the function to return 'false':
 * 'empty', 'bool', 'char8', 'string', 'struct' and 'array'.
*/
bool Decrement(AnyValue& value);

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ANYVALUE_OPERATIONS_H_
