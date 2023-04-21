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

#include <sup/dto/anytype.h>

#include <map>

namespace
{
/**
 * Templated comparison assumes both AnyValues can be cast to T and that there is a total order
 * for values of type T, unless T is void (see specialization).
*/
template <typename T>
sup::dto::CompareResult CompareT(const sup::dto::AnyValue& lhs, const sup::dto::AnyValue& rhs)
{
  auto left = lhs.As<T>();
  auto right = rhs.As<T>();
  if (left < right)
  {
    return sup::dto::CompareResult::Less;
  }
  if (left > right)
  {
    return sup::dto::CompareResult::Greater;
  }
  return sup::dto::CompareResult::Equivalent;
}

template <>
sup::dto::CompareResult CompareT<void>(const sup::dto::AnyValue& lhs, const sup::dto::AnyValue& rhs)
{
  (void)lhs;
  (void)rhs;
  return sup::dto::CompareResult::Unordered;
}

using CompareFunction = sup::dto::CompareResult(*)(const sup::dto::AnyValue&,
                                                   const sup::dto::AnyValue&);
const std::map<sup::dto::TypeCode, CompareFunction> compare_map = {
  { sup::dto::TypeCode::Empty, CompareT<void> },
  { sup::dto::TypeCode::Int64, CompareT<sup::dto::int64> },
  { sup::dto::TypeCode::UInt64, CompareT<sup::dto::uint64> },
  { sup::dto::TypeCode::Float32, CompareT<sup::dto::float32> },
  { sup::dto::TypeCode::Float64, CompareT<sup::dto::float64> }
};
}  // unnamed namespace

namespace sup
{
namespace dto
{
CompareResult Compare(const AnyValue& lhs, const AnyValue& rhs)
{
  auto t_1 = lhs.GetTypeCode();
  auto t_2 = rhs.GetTypeCode();
  auto p_1 = PromoteIntegralCode(t_1);
  auto p_2 = PromoteIntegralCode(t_2);
  auto common_type = CommonTypeCode(p_1, p_2);
  return compare_map.at(common_type)(lhs, rhs);
}

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

}  // namespace dto

}  // namespace sup
