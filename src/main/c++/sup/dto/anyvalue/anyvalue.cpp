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

#include <sup/dto/anyvalue.h>

#include <sup/dto/anyvalue/array_value_data.h>
#include <sup/dto/anyvalue/empty_value_data.h>
#include <sup/dto/anyvalue/scalar_value_data_t.h>
#include <sup/dto/anyvalue/struct_value_data.h>
#include <sup/dto/anyvalue/unbounded_array_value_data.h>

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

AnyValue::AnyValue(const std::string& val)
  : data{new ScalarValueDataT<std::string>(val)}
{}

AnyValue::AnyValue(const char* val)
  : data{new ScalarValueDataT<std::string>(val)}
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

AnyValue::AnyValue(std::size_t size, const AnyType& elem_type, const std::string& name)
  : data{new EmptyValueData{}}
{
  auto array_data = std::unique_ptr<ArrayValueData>(new ArrayValueData(size, elem_type, name));
  data = std::move(array_data);
}

AnyValue::AnyValue(AnyType::UnboundedArrayTag tag, const AnyType& elem_type,
                   const std::string& name)
  : data{new EmptyValueData{}}
{
  (void)tag;
  auto array_data = std::unique_ptr<UnboundedArrayValueData>(
    new UnboundedArrayValueData(elem_type, name));
  data = std::move(array_data);
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

AnyValue& AnyValue::Append(const AnyValue& value)
{
  data->Append(value);
  return *this;
}

std::size_t AnyValue::NumberOfElements() const
{
  return data->NumberOfElements();
}

AnyValue& AnyValue::operator[](const std::string& fieldname)
{
  return (*data)[fieldname];
}

const AnyValue& AnyValue::operator[](const std::string& fieldname) const
{
  return (*data)[fieldname];
}

AnyValue& AnyValue::operator[](std::size_t idx)
{
  return (*data)[idx];
}

const AnyValue& AnyValue::operator[](std::size_t idx) const
{
  return (*data)[idx];
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

template <>
std::string AnyValue::As<std::string>() const
{
  return data->AsString();
}

AnyValue EmptyStruct(const std::string& type_name)
{
  return AnyValue(EmptyStructType(type_name));
}

AnyValue ArrayValue(std::initializer_list<AnyValue> elements, const std::string& type_name)
{
  if (elements.size() == 0)
  {
    throw InvalidOperationException("Cannot construct an array value from a list with length zero");
  }
  auto it = elements.begin();
  AnyValue result(elements.size(), it->GetType(), type_name);
  std::size_t idx = 0;
  for (; it != elements.end(); ++it, ++idx)
  {
    result[idx] = *it;
  }
  return result;
}

AnyValue UnboundedArrayValue(std::initializer_list<AnyValue> elements, const std::string& type_name)
{
  if (elements.size() == 0)
  {
    throw InvalidOperationException("Cannot construct an array value from a list with length zero");
  }
  auto it = elements.begin();
  AnyValue result(AnyType::unbounded_array_tag, it->GetType(), type_name);
  for (; it != elements.end(); ++it)
  {
    result.Append(*it);
  }
  return result;
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

bool IsUnboundedArrayValue(const AnyValue& anyvalue)
{
  return IsUnboundedArrayTypeCode(anyvalue.GetTypeCode());
}

bool IsScalarValue(const AnyValue& anyvalue)
{
  return IsScalarTypeCode(anyvalue.GetTypeCode());
}

}  // namespace dto

}  // namespace sup
