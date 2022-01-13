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
 * Copyright (c) : 2010-2021 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include "AnyValue.h"

#include "EmptyValueData.h"
#include "ScalarValueDataT.h"

namespace sup
{
namespace dto
{

AnyValue::AnyValue()
  : data{new EmptyValueData{}}
{}

AnyValue::AnyValue(boolean val)
  : data{new ScalarValueDataT<boolean>(val)}
{}

AnyValue::AnyValue(int8 val)
  : data{new ScalarValueDataT<int8>(val)}
{}

AnyValue::AnyValue(uint8 val)
  : data{new ScalarValueDataT<uint8>(val)}
{}

AnyValue::AnyValue(int16 val)
  : data{new ScalarValueDataT<int16>(val)}
{}

AnyValue::AnyValue(uint16 val)
  : data{new ScalarValueDataT<uint16>(val)}
{}

AnyValue::AnyValue(int32 val)
  : data{new ScalarValueDataT<int32>(val)}
{}

AnyValue::AnyValue(uint32 val)
  : data{new ScalarValueDataT<uint32>(val)}
{}

AnyValue::AnyValue(int64 val)
  : data{new ScalarValueDataT<int64>(val)}
{}

AnyValue::AnyValue(uint64 val)
  : data{new ScalarValueDataT<uint64>(val)}
{}

AnyValue::AnyValue(const AnyType& anytype)
  : data{CreateValueData(anytype)}
{}

AnyValue::AnyValue(const AnyType& anytype, const AnyValue& anyvalue)
  : data{CreateValueData(anytype)}
{
  data->Assign(anyvalue);
}

AnyValue::AnyValue(const AnyValue& other)
  : data{other.data->Clone()}
{}

AnyValue& AnyValue::operator=(const AnyValue& other)
{
  if (this != &other)
  {
    data->Assign(other);
  }
  return *this;
}

AnyValue::AnyValue(AnyValue&& other)
  : data{other.data.release()}
{
  other.data.reset(new EmptyValueData());
}

AnyValue& AnyValue::operator=(AnyValue&& other)
{
  // Same as copy assignment
  if (this != &other)
  {
    data->Assign(other);
  }
  return *this;
}

AnyValue::~AnyValue() = default;

TypeCode AnyValue::GetTypeCode() const
{
  return data->GetTypeCode();
}

AnyType AnyValue::GetType() const
{
  return data->GetType();
}

std::string AnyValue::GetTypeName() const
{
  return data->GetTypeName();
}

AnyValue& AnyValue::operator[](std::string fieldname)
{
  return (*data)[fieldname];
}

const AnyValue& AnyValue::operator[](std::string fieldname) const
{
  return (*data)[fieldname];
}

bool AnyValue::operator==(const AnyValue& other) const
{
  return data->Equals(other.data.get());
}

bool AnyValue::operator!=(const AnyValue& other) const
{
  return !(this->operator==(other));
}

template <>
AnyValue AnyValue::As<AnyValue>() const
{
  return *this;
}

template <>
boolean AnyValue::As<boolean>() const
{
  return data->AsBoolean();
}

template <>
int8 AnyValue::As<int8>() const
{
  return data->AsSignedInteger8();
}

template <>
uint8 AnyValue::As<uint8>() const
{
  return data->AsUnsignedInteger8();
}

template <>
int16 AnyValue::As<int16>() const
{
  return data->AsSignedInteger16();
}

template <>
uint16 AnyValue::As<uint16>() const
{
  return data->AsUnsignedInteger16();
}

template <>
int32 AnyValue::As<int32>() const
{
  return data->AsSignedInteger32();
}

template <>
uint32 AnyValue::As<uint32>() const
{
  return data->AsUnsignedInteger32();
}

template <>
int64 AnyValue::As<int64>() const
{
  return data->AsSignedInteger64();
}

template <>
uint64 AnyValue::As<uint64>() const
{
  return data->AsUnsignedInteger64();
}

bool IsEmptyValue(const AnyValue& anyvalue)
{
  return IsEmptyTypeCode(anyvalue.GetTypeCode());
}

bool IsStructValue(const AnyValue& anyvalue)
{
  return IsStructTypeCode(anyvalue.GetTypeCode());
}

bool IsArrayValue(const AnyValue& anyvalue)
{
  return IsArrayTypeCode(anyvalue.GetTypeCode());
}

bool IsScalarValue(const AnyValue& anyvalue)
{
  return IsScalarTypeCode(anyvalue.GetTypeCode());
}

}  // namespace dto

}  // namespace sup
