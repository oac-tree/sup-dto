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
#include "StructValueData.h"

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

AnyValue::AnyValue(char8 val)
  : data{new ScalarValueDataT<char8>(val)}
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

AnyValue::AnyValue(float32 val)
  : data{new ScalarValueDataT<float32>(val)}
{}

AnyValue::AnyValue(float64 val)
  : data{new ScalarValueDataT<float64>(val)}
{}

AnyValue::AnyValue(const AnyType& anytype)
  : data{CreateValueData(anytype)}
{}

AnyValue::AnyValue(const AnyType& anytype, const AnyValue& anyvalue)
  : data{CreateValueData(anytype)}
{
  data->Assign(anyvalue);
}

AnyValue::AnyValue(std::initializer_list<std::pair<std::string, AnyValue>> members,
                   const std::string& type_name)
  : data{new EmptyValueData{}}
{
  auto struct_data = std::unique_ptr<StructValueData>(new StructValueData(type_name));
  for (auto& member : members)
  {
    struct_data->AddMember(member.first, member.second);
  }
  data = std::move(struct_data);
}

AnyValue::AnyValue(const AnyValue& other)
  : data{other.data->Clone()}
{}

AnyValue& AnyValue::operator=(const AnyValue& other)
{
  if (this == &other)
  {
    return *this;
  }
  if (!IsEmptyValue(*this))
  {
    data->Assign(other);
  }
  else
  {
    data.reset(other.data->Clone());
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
  if (this == &other)
  {
    return *this;
  }
  if (GetType() == other.GetType() || IsEmptyValue(*this))
  {
    data.reset(other.data.release());
    other.data.reset(new EmptyValueData());
  }
  else
  {
    // Fallback to copy
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

AnyValue& AnyValue::AddMember(const std::string& name, const AnyValue& value)
{
  data->AddMember(name, value);
  return *this;
}

bool AnyValue::HasMember(const std::string& name) const
{
  return data->HasMember(name);
}

std::vector<std::string> AnyValue::MemberNames() const
{
  return data->MemberNames();
}

std::size_t AnyValue::NumberOfMembers() const
{
  return data->NumberOfMembers();
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
  return data->Equals(other);
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
char8 AnyValue::As<char8>() const
{
  return data->AsCharacter8();
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

template <>
float32 AnyValue::As<float32>() const
{
  return data->AsFloat32();
}

template <>
float64 AnyValue::As<float64>() const
{
  return data->AsFloat64();
}

AnyValue EmptyStructValue(const std::string& type_name)
{
  return AnyValue(EmptyStructType(type_name));
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
