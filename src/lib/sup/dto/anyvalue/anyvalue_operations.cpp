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

#include <sup/dto/anyvalue_operations.h>
#include "anyvalue_operations_utils.h"

#include <sup/dto/anytype.h>

#include <map>

namespace
{

}  // unnamed namespace

namespace sup
{
namespace dto
{
CompareResult Compare(const AnyValue& lhs, const AnyValue& rhs)
{
  const auto t_1 = lhs.GetTypeCode();
  const auto t_2 = rhs.GetTypeCode();
  const auto p_1 = utils::PromoteIntegralCode(t_1);
  const auto p_2 = utils::PromoteIntegralCode(t_2);
  if (utils::AreMixedIntegerTypes(p_1, p_2))
  {
    return utils::CompareMixedIntegers(lhs, rhs, p_1 == TypeCode::Int64);
  }
  const auto common_type = utils::CommonTypeCode(p_1, p_2);
  return utils::GetCompareFunction(common_type)(lhs, rhs);
}

bool Increment(AnyValue& value)
{
  return utils::GetIncrementFunction(value.GetTypeCode())(value);
}

bool Decrement(AnyValue& value)
{
  return utils::GetDecrementFunction(value.GetTypeCode())(value);
}

}  // namespace dto

}  // namespace sup
