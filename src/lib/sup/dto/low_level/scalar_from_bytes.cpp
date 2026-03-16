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

#include <map>

namespace sup
{
namespace dto
{
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

std::size_t AssignFromHostOrder(AnyValue& anyvalue, const uint8* bytes, std::size_t size,
                                std::size_t position)
{
  static const std::map<TypeCode, std::function<std::size_t(AnyValue&, const uint8*, std::size_t,
                                                            std::size_t)>> assign_map {
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
  const auto it = assign_map.find(anyvalue.GetTypeCode());
  if (it == assign_map.end())
  {
    throw ParseException("AssignFromHostOrder: unknown scalar type code");
  }
  return it->second(anyvalue, bytes, size, position);
}

}  // namespace dto

}  // namespace sup
