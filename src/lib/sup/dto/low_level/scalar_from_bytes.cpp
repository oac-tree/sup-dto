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

#include "scalar_from_bytes.h"

#include "arithmetic_from_bytes_t.h"

#include <sup/dto/anyvalue_exceptions.h>

#include <map>

namespace
{
using namespace sup::dto;

template <typename T>
std::size_t AssignFromHostOrderT(AnyValue& anyvalue, const uint8* bytes, std::size_t size,
                                 std::size_t position)
{
  if ((position + sizeof(T)) > size)
  {
    throw ParseException("Trying to parse beyond size of byte array");
  }
  auto begin_it = bytes + position;
  auto val = ParseFromHostOrderT<T>(begin_it, bytes + position + sizeof(T));
  anyvalue = val;
  return position + sizeof(T);
}

template <>
std::size_t AssignFromHostOrderT<std::string>(AnyValue& anyvalue, const uint8* bytes,
                                              std::size_t size, std::size_t position)
{
  auto end_position = position + kStringMaxLength;
  if (end_position > size)
  {
    throw ParseException("Trying to parse beyond size of byte array");
  }
  auto null_pos = std::find(&bytes[position], &bytes[end_position], '\0');
  if (null_pos == &bytes[end_position])
  {
    throw ParseException("C-type string is not null-terminated");
  }
  std::string val = reinterpret_cast<const char*>(&bytes[position]);
  anyvalue = val;
  return end_position;
}

template <typename T>
std::size_t AssignFromLittleEndianOrderT(AnyValue& anyvalue, const uint8* bytes, std::size_t size,
                                         std::size_t position)
{
  if ((position + sizeof(T)) > size)
  {
    throw ParseException("Trying to parse beyond size of byte array");
  }
  auto begin_it = bytes + position;
  auto val = ParseFromLittleEndianOrderT<T>(begin_it, bytes + position + sizeof(T));
  anyvalue = val;
  return position + sizeof(T);
}

template <typename T>
std::size_t AssignFromNetworkOrderT(AnyValue& anyvalue, const uint8* bytes, std::size_t size,
                                    std::size_t position)
{
  if ((position + sizeof(T)) > size)
  {
    throw ParseException("Trying to parse beyond size of byte array");
  }
  auto begin_it = bytes + position;
  auto val = ParseFromNetworkOrderT<T>(begin_it, bytes + position + sizeof(T));
  anyvalue = val;
  return position + sizeof(T);
}

const std::map<TypeCode, std::function<std::size_t(AnyValue&, const uint8*, std::size_t,
                                                   std::size_t)>>&
GetFromHostOrderMap()
{
  static const std::map<TypeCode, std::function<std::size_t(AnyValue&, const uint8*, std::size_t,
                                                            std::size_t)>> map {
    {TypeCode::Bool, AssignFromHostOrderT<boolean> },
    {TypeCode::Char8, AssignFromHostOrderT<char8> },
    {TypeCode::Int8, AssignFromHostOrderT<int8> },
    {TypeCode::UInt8, AssignFromHostOrderT<uint8> },
    {TypeCode::Int16, AssignFromHostOrderT<int16> },
    {TypeCode::UInt16, AssignFromHostOrderT<uint16> },
    {TypeCode::Int32, AssignFromHostOrderT<int32> },
    {TypeCode::UInt32, AssignFromHostOrderT<uint32> },
    {TypeCode::Int64, AssignFromHostOrderT<int64> },
    {TypeCode::UInt64, AssignFromHostOrderT<uint64> },
    {TypeCode::Float32, AssignFromHostOrderT<float32> },
    {TypeCode::Float64, AssignFromHostOrderT<float64> },
    {TypeCode::String, AssignFromHostOrderT<std::string> }
  };
  return map;
}

const std::map<TypeCode, std::function<std::size_t(AnyValue&, const uint8*, std::size_t,
                                                   std::size_t)>>&
GetFromLittleEndianOrderMap()
{
  static const std::map<TypeCode, std::function<std::size_t(AnyValue&, const uint8*, std::size_t,
                                                            std::size_t)>> map {
    {TypeCode::Bool, AssignFromLittleEndianOrderT<boolean> },
    {TypeCode::Char8, AssignFromLittleEndianOrderT<char8> },
    {TypeCode::Int8, AssignFromLittleEndianOrderT<int8> },
    {TypeCode::UInt8, AssignFromLittleEndianOrderT<uint8> },
    {TypeCode::Int16, AssignFromLittleEndianOrderT<int16> },
    {TypeCode::UInt16, AssignFromLittleEndianOrderT<uint16> },
    {TypeCode::Int32, AssignFromLittleEndianOrderT<int32> },
    {TypeCode::UInt32, AssignFromLittleEndianOrderT<uint32> },
    {TypeCode::Int64, AssignFromLittleEndianOrderT<int64> },
    {TypeCode::UInt64, AssignFromLittleEndianOrderT<uint64> },
    {TypeCode::Float32, AssignFromLittleEndianOrderT<float32> },
    {TypeCode::Float64, AssignFromLittleEndianOrderT<float64> },
    {TypeCode::String, AssignFromHostOrderT<std::string> }
  };
  return map;
}

const std::map<TypeCode, std::function<std::size_t(AnyValue&, const uint8*, std::size_t,
                                                   std::size_t)>>&
GetFromNetworkOrderMap()
{
  static const std::map<TypeCode, std::function<std::size_t(AnyValue&, const uint8*, std::size_t,
                                                            std::size_t)>> map {
    {TypeCode::Bool, AssignFromNetworkOrderT<boolean> },
    {TypeCode::Char8, AssignFromNetworkOrderT<char8> },
    {TypeCode::Int8, AssignFromNetworkOrderT<int8> },
    {TypeCode::UInt8, AssignFromNetworkOrderT<uint8> },
    {TypeCode::Int16, AssignFromNetworkOrderT<int16> },
    {TypeCode::UInt16, AssignFromNetworkOrderT<uint16> },
    {TypeCode::Int32, AssignFromNetworkOrderT<int32> },
    {TypeCode::UInt32, AssignFromNetworkOrderT<uint32> },
    {TypeCode::Int64, AssignFromNetworkOrderT<int64> },
    {TypeCode::UInt64, AssignFromNetworkOrderT<uint64> },
    {TypeCode::Float32, AssignFromNetworkOrderT<float32> },
    {TypeCode::Float64, AssignFromNetworkOrderT<float64> },
    {TypeCode::String, AssignFromHostOrderT<std::string> }
  };
  return map;
}

}  // unnamed namespace

namespace sup
{
namespace dto
{
std::size_t AssignFromHostOrder(AnyValue& anyvalue, const uint8* bytes, std::size_t size,
                                std::size_t position)
{
  static const auto& assign_map = GetFromHostOrderMap();
  const auto it = assign_map.find(anyvalue.GetTypeCode());
  if (it == assign_map.end())
  {
    throw ParseException("AssignFromHostOrder: unknown scalar type code");
  }
  return it->second(anyvalue, bytes, size, position);
}

std::size_t AssignFromLittleEndianOrder(AnyValue& anyvalue, const uint8* bytes, std::size_t size,
                                        std::size_t position)
{
  static const auto& assign_map = IsLittleEndian() ? GetFromHostOrderMap()
                                                   : GetFromLittleEndianOrderMap();
  const auto it = assign_map.find(anyvalue.GetTypeCode());
  if (it == assign_map.end())
  {
    throw ParseException("AssignFromLittleEndianOrder: unknown scalar type code");
  }
  return it->second(anyvalue, bytes, size, position);
}

std::size_t AssignFromNetworkOrder(AnyValue& anyvalue, const uint8* bytes, std::size_t size,
                                   std::size_t position)
{
  static const auto& assign_map = IsLittleEndian() ? GetFromNetworkOrderMap()
                                                   : GetFromHostOrderMap();
  const auto it = assign_map.find(anyvalue.GetTypeCode());
  if (it == assign_map.end())
  {
    throw ParseException("AssignFromNetworkOrder: unknown scalar type code");
  }
  return it->second(anyvalue, bytes, size, position);
}

}  // namespace dto

}  // namespace sup
