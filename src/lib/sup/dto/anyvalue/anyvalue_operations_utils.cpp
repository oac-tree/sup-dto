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

#include "anyvalue_operations_utils.h"

#include <map>

namespace sup
{
namespace dto
{
namespace utils
{

TypeCode PromoteIntegralCode(TypeCode t)
{
  static const std::map<TypeCode, TypeCode> promotion_map = {
    { TypeCode::Empty, TypeCode::Empty },
    { TypeCode::Bool, TypeCode::Empty },
    { TypeCode::Char8, TypeCode::Empty },
    { TypeCode::Int8, TypeCode::Int64 },
    { TypeCode::UInt8, TypeCode::UInt64 },
    { TypeCode::Int16, TypeCode::Int64 },
    { TypeCode::UInt16, TypeCode::UInt64 },
    { TypeCode::Int32, TypeCode::Int64 },
    { TypeCode::UInt32, TypeCode::UInt64 },
    { TypeCode::Int64, TypeCode::Int64 },
    { TypeCode::UInt64, TypeCode::UInt64 },
    { TypeCode::Float32, TypeCode::Float32 },
    { TypeCode::Float64, TypeCode::Float64 },
    { TypeCode::String, TypeCode::Empty },
    { TypeCode::Struct, TypeCode::Empty },
    { TypeCode::Array, TypeCode::Empty }
  };
  return promotion_map.at(t);
}

// Not a very performant implementation. Will be refactored when this poses an issue.
TypeCode CommonTypeCode(TypeCode t_1, TypeCode t_2)
{
  if (t_1 == TypeCode::Empty || t_2 == TypeCode::Empty)
  {
    return TypeCode::Empty;
  }
  if (t_1 == TypeCode::Float64 || t_2 == TypeCode::Float64)
  {
    return TypeCode::Float64;
  }
  if (t_1 == TypeCode::Float32 || t_2 == TypeCode::Float32)
  {
    return TypeCode::Float32;
  }
  return t_1 == t_2 ? t_1 : TypeCode::Empty;
}

}  // namespace utils

}  // namespace dto

}  // namespace sup
