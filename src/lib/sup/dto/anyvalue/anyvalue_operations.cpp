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
  auto t_1 = lhs.GetTypeCode();
  auto t_2 = rhs.GetTypeCode();
  auto p_1 = utils::PromoteIntegralCode(t_1);
  auto p_2 = utils::PromoteIntegralCode(t_2);
  auto common_type = utils::CommonTypeCode(p_1, p_2);
  return utils::GetCompareFunction(common_type)(lhs, rhs);
}

}  // namespace dto

}  // namespace sup
