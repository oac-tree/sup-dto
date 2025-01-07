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
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include "i_writer.h"

#include <sup/dto/anyvalue.h>

#include <functional>
#include <map>

namespace
{
using namespace sup::dto;
template <typename T, bool (IWriter::*member_func)(T)>
bool WriteScalarValueT(const AnyValue& anyvalue, IWriter* writer)
{
  T val = anyvalue.As<T>();
  return (writer->*member_func)(val);
}

bool WriteScalarString(const AnyValue& anyvalue, IWriter* writer)
{
  const std::string str = anyvalue.As<std::string>();
  return writer->String(str);
}
}  // namespace

namespace sup
{
namespace dto
{

IWriter::~IWriter() = default;

bool WriteScalarValue(const AnyValue& anyvalue, IWriter* writer)
{
  static const std::map<TypeCode, std::function<bool(const AnyValue&, IWriter*)>> conversion_map {
    {TypeCode::Bool, WriteScalarValueT<boolean, &IWriter::Bool> },
    {TypeCode::Char8, WriteScalarValueT<char8, &IWriter::Char> },
    {TypeCode::Int8, WriteScalarValueT<int8, &IWriter::Int8> },
    {TypeCode::UInt8, WriteScalarValueT<uint8, &IWriter::Uint8> },
    {TypeCode::Int16, WriteScalarValueT<int16, &IWriter::Int16> },
    {TypeCode::UInt16, WriteScalarValueT<uint16, &IWriter::Uint16> },
    {TypeCode::Int32, WriteScalarValueT<int32, &IWriter::Int32> },
    {TypeCode::UInt32, WriteScalarValueT<uint32, &IWriter::Uint32> },
    {TypeCode::Int64, WriteScalarValueT<int64, &IWriter::Int64> },
    {TypeCode::UInt64, WriteScalarValueT<uint64, &IWriter::Uint64> },
    {TypeCode::Float32, WriteScalarValueT<float32, &IWriter::Float> },
    {TypeCode::Float64, WriteScalarValueT<float64, &IWriter::Double> },
    {TypeCode::String, WriteScalarString }
  };
  const auto it = conversion_map.find(anyvalue.GetTypeCode());
  if (it == conversion_map.end())
  {
    throw SerializeException("Not a known scalar type code");
  }
  return it->second(anyvalue, writer);
}

}  // namespace dto

}  // namespace sup
