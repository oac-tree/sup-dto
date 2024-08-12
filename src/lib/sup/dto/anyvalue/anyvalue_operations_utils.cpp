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

#include "anyvalue_operations_utils.h"

#include <map>

namespace
{
using namespace sup::dto;
CompareResult Invert(CompareResult result);

/**
 * Templated comparison assumes both AnyValues can be cast to T and that there is a total order
 * for values of type T. Unsupported types will use the function UnsupportedCompare below.
*/
template <typename T>
CompareResult CompareT(const AnyValue& lhs, const AnyValue& rhs)
{
  auto left = lhs.As<T>();
  auto right = rhs.As<T>();
  if (left < right)
  {
    return CompareResult::Less;
  }
  if (left > right)
  {
    return CompareResult::Greater;
  }
  return CompareResult::Equivalent;
}

CompareResult UnsupportedCompare(const AnyValue&, const AnyValue&)
{
  return CompareResult::Unordered;
}

/**
 * Templated increment will be instantiated only for the supported types: 'uint64', 'float64'
 * and 'float32'. Unsupported types will use the function UnsupportedIncrement below.
*/
template <typename S, typename U>
bool IncrementT(AnyValue& value)
{
  auto temp = static_cast<U>(value.As<S>());
  ++temp;
  value = static_cast<S>(temp);
  return true;
}

bool UnsupportedIncrement(AnyValue&)
{
  return false;
}

/**
 * Templated decrement will be instantiated only for the supported promotion types U: 'uint64',
 * 'float64' and 'float32'. Unsupported types will use the function UnsupportedDecrement below.
*/
template <typename S, typename U>
bool DecrementT(AnyValue& value)
{
  auto temp = static_cast<U>(value.As<S>());
  --temp;
  value = static_cast<S>(temp);
  return true;
}

bool UnsupportedDecrement(AnyValue&)
{
  return false;
}

}  // unnamed namespace

namespace sup
{
namespace dto
{
namespace utils
{

TypeCode PromoteIntegralCode(TypeCode t)
{
  static const std::map<TypeCode, TypeCode> promotion_map {
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
  if ((t_1 == TypeCode::Empty) || (t_2 == TypeCode::Empty))
  {
    return TypeCode::Empty;
  }
  if ((t_1 == TypeCode::Float64) || (t_2 == TypeCode::Float64))
  {
    return TypeCode::Float64;
  }
  if ((t_1 == TypeCode::Float32) || (t_2 == TypeCode::Float32))
  {
    return TypeCode::Float32;
  }
  return (t_1 == t_2) ? t_1 : TypeCode::Empty;
}

CompareFunction GetCompareFunction(TypeCode type_code)
{
  const std::map<TypeCode, CompareFunction> compare_map = {
    { TypeCode::Empty, &UnsupportedCompare },
    { TypeCode::Int64, &CompareT<int64> },
    { TypeCode::UInt64, &CompareT<uint64> },
    { TypeCode::Float32, &CompareT<float32> },
    { TypeCode::Float64, &CompareT<float64> }
  };
  return compare_map.at(type_code);
}

bool AreMixedIntegerTypes(TypeCode p_1, TypeCode p_2)
{
  return (((p_1 == TypeCode::Int64) && (p_2 == TypeCode::UInt64)) ||
          ((p_1 == TypeCode::UInt64) && (p_2 == TypeCode::Int64)));
}

CompareResult CompareMixedIntegers(const AnyValue& lhs, const AnyValue& rhs, bool left_is_signed)
{
  if (!left_is_signed)
  {
    return Invert(CompareMixedIntegers(rhs, lhs, true));
  }
  auto left = lhs.As<int64>();
  if (left < 0)
  {
    return CompareResult::Less;
  }
  return CompareT<uint64>(lhs, rhs);
}

UnaryOperatorFunction GetIncrementFunction(TypeCode type_code)
{
  const std::map<TypeCode, UnaryOperatorFunction> increment_map = {
    { TypeCode::Empty, &UnsupportedIncrement },
    { TypeCode::Bool, &UnsupportedIncrement },
    { TypeCode::Char8, &UnsupportedIncrement },
    { TypeCode::Int8, &IncrementT<int8, uint64> },
    { TypeCode::UInt8, &IncrementT<uint8, uint64> },
    { TypeCode::Int16, &IncrementT<int16, uint64> },
    { TypeCode::UInt16, &IncrementT<uint16, uint64> },
    { TypeCode::Int32, &IncrementT<int32, uint64> },
    { TypeCode::UInt32, &IncrementT<uint32, uint64> },
    { TypeCode::Int64, &IncrementT<int64, uint64> },
    { TypeCode::UInt64, &IncrementT<uint64, uint64> },
    { TypeCode::Float32, &IncrementT<float32, float32> },
    { TypeCode::Float64, &IncrementT<float64, float64> },
    { TypeCode::String, &UnsupportedIncrement },
    { TypeCode::Struct, &UnsupportedIncrement },
    { TypeCode::Array, &UnsupportedIncrement }
  };
  return increment_map.at(type_code);
}

UnaryOperatorFunction GetDecrementFunction(TypeCode type_code)
{
  const std::map<TypeCode, UnaryOperatorFunction> decrement_map = {
    { TypeCode::Empty, &UnsupportedDecrement },
    { TypeCode::Bool, &UnsupportedDecrement },
    { TypeCode::Char8, &UnsupportedDecrement },
    { TypeCode::Int8, &DecrementT<int8, uint64> },
    { TypeCode::UInt8, &DecrementT<uint8, uint64> },
    { TypeCode::Int16, &DecrementT<int16, uint64> },
    { TypeCode::UInt16, &DecrementT<uint16, uint64> },
    { TypeCode::Int32, &DecrementT<int32, uint64> },
    { TypeCode::UInt32, &DecrementT<uint32, uint64> },
    { TypeCode::Int64, &DecrementT<int64, uint64> },
    { TypeCode::UInt64, &DecrementT<uint64, uint64> },
    { TypeCode::Float32, &DecrementT<float32, float32> },
    { TypeCode::Float64, &DecrementT<float64, float64> },
    { TypeCode::String, &UnsupportedDecrement },
    { TypeCode::Struct, &UnsupportedDecrement },
    { TypeCode::Array, &UnsupportedDecrement }
  };
  return decrement_map.at(type_code);
}

}  // namespace utils

}  // namespace dto

}  // namespace sup

namespace
{
CompareResult Invert(CompareResult result)
{
  switch (result)
  {
  case CompareResult::Less:
    return CompareResult::Greater;
  case CompareResult::Greater:
    return CompareResult::Less;
  default:
    break;
  }
  return result;
}
}  // unnamed namespace

