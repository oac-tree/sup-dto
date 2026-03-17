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
#include <sup/dto/anyvalue_exceptions.h>

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
std::vector<uint8> ScalarToLittleEndianOrderT(const AnyValue& anyvalue)
{
  T val = anyvalue.As<T>();
  return ToLittleEndianOrderT(val);
}

template <typename T>
std::vector<uint8> ScalarToNetworkOrderT(const AnyValue& anyvalue)
{
  T val = anyvalue.As<T>();
  return ToNetworkOrder(val);
}

const std::map<TypeCode, std::function<std::vector<uint8>(const AnyValue&)>>&
GetToHostOrderMap()
{
  static const std::map<TypeCode, std::function<std::vector<uint8>(const AnyValue&)>> map {
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
  return map;
}

const std::map<TypeCode, std::function<std::vector<uint8>(const AnyValue&)>>&
GetToLittleEndianOrderMap()
{
  static const std::map<TypeCode, std::function<std::vector<uint8>(const AnyValue&)>> map {
    {TypeCode::Bool, ScalarToLittleEndianOrderT<boolean> },
    {TypeCode::Char8, ScalarToLittleEndianOrderT<char8> },
    {TypeCode::Int8, ScalarToLittleEndianOrderT<int8> },
    {TypeCode::UInt8, ScalarToLittleEndianOrderT<uint8> },
    {TypeCode::Int16, ScalarToLittleEndianOrderT<int16> },
    {TypeCode::UInt16, ScalarToLittleEndianOrderT<uint16> },
    {TypeCode::Int32, ScalarToLittleEndianOrderT<int32> },
    {TypeCode::UInt32, ScalarToLittleEndianOrderT<uint32> },
    {TypeCode::Int64, ScalarToLittleEndianOrderT<int64> },
    {TypeCode::UInt64, ScalarToLittleEndianOrderT<uint64> },
    {TypeCode::Float32, ScalarToLittleEndianOrderT<float32> },
    {TypeCode::Float64, ScalarToLittleEndianOrderT<float64> },
    {TypeCode::String, ScalarToHostOrderT<std::string> }
  };
  return map;
}

const std::map<TypeCode, std::function<std::vector<uint8>(const AnyValue&)>>&
GetToNetworkOrderMap()
{
  static const std::map<TypeCode, std::function<std::vector<uint8>(const AnyValue&)>> map {
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
  return map;
}

}  // unnamed namespace

namespace sup
{
namespace dto
{

std::vector<uint8> ScalarToHostOrder(const AnyValue& anyvalue)
{
  static const auto& conversion_map = GetToHostOrderMap();
  const auto it = conversion_map.find(anyvalue.GetTypeCode());
  if (it == conversion_map.end())
  {
    throw SerializeException("Not a known scalar type code");
  }
  return it->second(anyvalue);
}

std::vector<uint8> ScalarToLittleEndianOrder(const AnyValue& anyvalue)
{
  static const auto& conversion_map = IsLittleEndian() ? GetToHostOrderMap()
                                                       : GetToLittleEndianOrderMap();
  const auto it = conversion_map.find(anyvalue.GetTypeCode());
  if (it == conversion_map.end())
  {
    throw SerializeException("Not a known scalar type code");
  }
  return it->second(anyvalue);
}

std::vector<uint8> ScalarToNetwokOrder(const AnyValue& anyvalue)
{
  static const auto& conversion_map = IsLittleEndian() ? GetToNetworkOrderMap()
                                                       : GetToHostOrderMap();
  const auto it = conversion_map.find(anyvalue.GetTypeCode());
  if (it == conversion_map.end())
  {
    throw SerializeException("Not a known scalar type code");
  }
  return it->second(anyvalue);
}

}  // namespace dto

}  // namespace sup
