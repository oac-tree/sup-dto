/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : SUP - DTO
 *
 * Description   : Unit test code
 *
 * Author        : Walter Van Herck (IO)
 *
 * Copyright (c) : 2010-2025 ITER Organization,
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

#include "scalar_to_bytes.h"
#include "arithmetic_to_bytes_t.h"

#include <sup/dto/anyvalue.h>

#include <cstring>
#include <functional>
#include <map>

namespace
{
using namespace sup::dto;
template <typename T>
std::vector<uint8> ScalarToBytesT(const AnyValue& anyvalue)
{
  T val = anyvalue.As<T>();
  return ArithmeticToBytesT(val);
}

template <>
std::vector<uint8> ScalarToBytesT<std::string>(const AnyValue& anyvalue)
{
  auto str = anyvalue.As<std::string>();
  auto size = str.size();
  if ((size + 1) > kStringMaxLength)
  {
    throw SerializeException("Strings should not exceed max length for C-type casting");
  }
  std::vector<uint8> result(kStringMaxLength, 0);
  (void)std::memcpy(result.data(), str.data(), size);
  return result;
}
}  // namespace

namespace sup
{
namespace dto
{

std::vector<uint8> ScalarToBytes(const AnyValue& anyvalue)
{
  static const std::map<TypeCode, std::function<std::vector<uint8>(const AnyValue&)>> conversion_map {
    {TypeCode::Bool, ScalarToBytesT<boolean> },
    {TypeCode::Char8, ScalarToBytesT<char8> },
    {TypeCode::Int8, ScalarToBytesT<int8> },
    {TypeCode::UInt8, ScalarToBytesT<uint8> },
    {TypeCode::Int16, ScalarToBytesT<int16> },
    {TypeCode::UInt16, ScalarToBytesT<uint16> },
    {TypeCode::Int32, ScalarToBytesT<int32> },
    {TypeCode::UInt32, ScalarToBytesT<uint32> },
    {TypeCode::Int64, ScalarToBytesT<int64> },
    {TypeCode::UInt64, ScalarToBytesT<uint64> },
    {TypeCode::Float32, ScalarToBytesT<float32> },
    {TypeCode::Float64, ScalarToBytesT<float64> },
    {TypeCode::String, ScalarToBytesT<std::string> }
  };
  const auto it = conversion_map.find(anyvalue.GetTypeCode());
  if (it == conversion_map.end())
  {
    throw SerializeException("Not a known scalar type code");
  }
  return it->second(anyvalue);
}

}  // namespace dto

}  // namespace sup
