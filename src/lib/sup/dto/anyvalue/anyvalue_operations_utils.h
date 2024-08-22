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
 * Copyright (c) : 2010-2024 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#ifndef SUP_DTO_ANYVALUE_OPERATIONS_UTILS_H_
#define SUP_DTO_ANYVALUE_OPERATIONS_UTILS_H_

#include <sup/dto/anytype.h>
#include <sup/dto/anyvalue.h>
#include <sup/dto/anyvalue_operations.h>

#include <map>

namespace sup
{
namespace dto
{
namespace utils
{

/**
 * @brief Promote typecodes.
 *
 * @details Unsupported types will all be mapped to TypeCode::Empty. Floating point types are not
 * promoted. Signed and unsigned integer types are mapped to TypeCode::Int64 and TypeCode::UInt64
 * respectively.
*/
TypeCode PromoteIntegralCode(TypeCode t);

/**
 * @brief Calculate common typecode for the two given typecodes.
 *
 * @details Unsupported types will all be mapped to TypeCode::Empty.
*/
TypeCode CommonTypeCode(TypeCode t_1, TypeCode t_2);

using CompareFunction = CompareResult(*)(const AnyValue&, const AnyValue&);

CompareFunction GetCompareFunction(TypeCode type_code);

bool AreMixedIntegerTypes(TypeCode p_1, TypeCode p_2);

CompareResult CompareMixedIntegers(const AnyValue& lhs, const AnyValue& rhs, bool left_is_signed);

using UnaryOperatorFunction = bool(*)(AnyValue&);

UnaryOperatorFunction GetIncrementFunction(TypeCode type_code);

UnaryOperatorFunction GetDecrementFunction(TypeCode type_code);

}  // namespace utils

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ANYVALUE_OPERATIONS_UTILS_H_
