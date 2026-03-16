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
std::vector<uint8> ScalarToHostOrderT(const AnyValue& anyvalue)
{
  T val = anyvalue.As<T>();
  return ToHostOrderT(val);
}

template <>
std::vector<uint8> ScalarToHostOrderT<std::string>(const AnyValue& anyvalue)
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

template <typename T>
std::vector<uint8> ScalarToNetworkOrderT(const AnyValue& anyvalue)
{
  T val = anyvalue.As<T>();
  return ToNetworkOrder(val);
}

}  // namespace

namespace sup
{
namespace dto
{

std::vector<uint8> ScalarToHostOrder(const AnyValue& anyvalue)
{
  static const std::map<TypeCode, std::function<std::vector<uint8>(const AnyValue&)>> conversion_map {
    {TypeCode::Bool, ScalarToHostOrderT<boolean> },
    {TypeCode::Char8, ScalarToHostOrderT<char8> },
    {TypeCode::Int8, ScalarToHostOrderT<int8> },
    {TypeCode::UInt8, ScalarToHostOrderT<uint8> },
    {TypeCode::Int16, ScalarToHostOrderT<int16> },
    {TypeCode::UInt16, ScalarToHostOrderT<uint16> },
    {TypeCode::Int32, ScalarToHostOrderT<int32> },
    {TypeCode::UInt32, ScalarToHostOrderT<uint32> },
    {TypeCode::Int64, ScalarToHostOrderT<int64> },
    {TypeCode::UInt64, ScalarToHostOrderT<uint64> },
    {TypeCode::Float32, ScalarToHostOrderT<float32> },
    {TypeCode::Float64, ScalarToHostOrderT<float64> },
    {TypeCode::String, ScalarToHostOrderT<std::string> }
  };
  const auto it = conversion_map.find(anyvalue.GetTypeCode());
  if (it == conversion_map.end())
  {
    throw SerializeException("Not a known scalar type code");
  }
  return it->second(anyvalue);
}

std::vector<uint8> ScalarToNetwokOrder(const AnyValue& anyvalue)
{
  static const std::map<TypeCode, std::function<std::vector<uint8>(const AnyValue&)>> conversion_map {
    {TypeCode::Bool, ScalarToNetworkOrderT<boolean> },
    {TypeCode::Char8, ScalarToNetworkOrderT<char8> },
    {TypeCode::Int8, ScalarToNetworkOrderT<int8> },
    {TypeCode::UInt8, ScalarToNetworkOrderT<uint8> },
    {TypeCode::Int16, ScalarToNetworkOrderT<int16> },
    {TypeCode::UInt16, ScalarToNetworkOrderT<uint16> },
    {TypeCode::Int32, ScalarToNetworkOrderT<int32> },
    {TypeCode::UInt32, ScalarToNetworkOrderT<uint32> },
    {TypeCode::Int64, ScalarToNetworkOrderT<int64> },
    {TypeCode::UInt64, ScalarToNetworkOrderT<uint64> },
    {TypeCode::Float32, ScalarToNetworkOrderT<float32> },
    {TypeCode::Float64, ScalarToNetworkOrderT<float64> },
    {TypeCode::String, ScalarToHostOrderT<std::string> }
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
