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
#include <sup/dto/parse/byteparser.h>
#include <sup/dto/serialize/byte_serializer.h>
#include <sup/dto/visit/visit_t.h>

namespace sup
{
namespace dto
{
template <typename T>
IValueData* CreateUnconstrainedScalarData(const T& val)
{
  return new ScalarValueDataT<T>(val, value_flags::kNone);
}

AnyValue::AnyValue()
  : m_data{CreateDefaultValueData()}
{}

AnyValue::AnyValue(const AnyType& anytype)
  : m_data{CreateValueData(anytype, value_flags::kNone)}
{}

AnyValue::AnyValue(boolean val)
  : m_data{CreateUnconstrainedScalarData(val)}
{}

AnyValue::AnyValue(char8 val)
  : m_data{CreateUnconstrainedScalarData(val)}
{}

AnyValue::AnyValue(int8 val)
  : m_data{CreateUnconstrainedScalarData(val)}
{}

AnyValue::AnyValue(uint8 val)
  : m_data{CreateUnconstrainedScalarData(val)}
{}

AnyValue::AnyValue(int16 val)
  : m_data{CreateUnconstrainedScalarData(val)}
{}

AnyValue::AnyValue(uint16 val)
  : m_data{CreateUnconstrainedScalarData(val)}
{}

AnyValue::AnyValue(int32 val)
  : m_data{CreateUnconstrainedScalarData(val)}
{}

AnyValue::AnyValue(uint32 val)
  : m_data{CreateUnconstrainedScalarData(val)}
{}

AnyValue::AnyValue(int64 val)
  : m_data{CreateUnconstrainedScalarData(val)}
{}

AnyValue::AnyValue(uint64 val)
  : m_data{CreateUnconstrainedScalarData(val)}
{}

AnyValue::AnyValue(float32 val)
  : m_data{CreateUnconstrainedScalarData(val)}
{}

AnyValue::AnyValue(float64 val)
  : m_data{CreateUnconstrainedScalarData(val)}
{}

AnyValue::AnyValue(const std::string& val)
  : m_data{CreateUnconstrainedScalarData(val)}
{}

AnyValue::AnyValue(const char* val)
  : m_data{CreateUnconstrainedScalarData<std::string>(val)}
{}

AnyValue::AnyValue(const AnyType& anytype, const AnyValue& anyvalue)
  : m_data{CreateValueData(anytype, value_flags::kNone)}
{
  m_data->Assign(anyvalue);
}

AnyValue::AnyValue(std::initializer_list<std::pair<std::string, AnyValue>> members,
                   const std::string& type_name)
  : m_data{CreateDefaultValueData()}
{
  auto struct_data =
    std::unique_ptr<StructValueData>(new StructValueData(type_name, value_flags::kNone));
  for (auto& member : members)
  {
    struct_data->AddMember(member.first, member.second);
  }
  m_data = std::move(struct_data);
}

AnyValue::AnyValue(std::size_t size, const AnyType& elem_type, const std::string& name)
  : m_data{CreateDefaultValueData()}
{
  auto array_data =
    std::unique_ptr<IValueData>(new ArrayValueData(size, elem_type, name, value_flags::kNone));
  m_data = std::move(array_data);
}

AnyValue::AnyValue(const AnyValue& other)
  : m_data{other.m_data->Clone(value_flags::kNone)}
{}

AnyValue::AnyValue(AnyValue&& other)
  : m_data{StealOrClone(std::move(other.m_data))}
{}

AnyValue& AnyValue::operator=(const AnyValue& other)
{
  if (IsLockedTypeConstraint(m_data->GetConstraints()))
  {
    m_data->Assign(other);
    return *this;
  }
  std::unique_ptr<IValueData> tmp{other.m_data->Clone(value_flags::kNone)};
  std::swap(m_data, tmp);
  return *this;
}

AnyValue& AnyValue::operator=(AnyValue&& other)
{
  if (IsLockedTypeConstraint(m_data->GetConstraints()))
  {
    m_data->Assign(other);
    return *this;
  }
  if (IsLockedTypeConstraint(other.m_data->GetConstraints()))
  {
    std::unique_ptr<IValueData> tmp{other.m_data->Clone(value_flags::kNone)};
    std::swap(m_data, tmp);
  }
  else
  {
    std::swap(m_data, other.m_data);
  }
  return *this;
}

void AnyValue::ConvertFrom(const AnyValue& other)
{
  std::unique_ptr<IValueData> tmp{CreateValueData(GetType(), m_data->GetConstraints())};
  tmp->Assign(other);
  std::swap(m_data, tmp);
}

AnyValue::~AnyValue() = default;

TypeCode AnyValue::GetTypeCode() const
{
  return m_data->GetTypeCode();
}

AnyType AnyValue::GetType() const
{
  return m_data->GetType();
}

std::string AnyValue::GetTypeName() const
{
  return m_data->GetTypeName();
}

AnyValue& AnyValue::AddMember(const std::string& name, const AnyValue& value)
{
  m_data->AddMember(name, value);
  return *this;
}

std::vector<std::string> AnyValue::MemberNames() const
{
  return m_data->MemberNames();
}

std::size_t AnyValue::NumberOfMembers() const
{
  return m_data->NumberOfMembers();
}

AnyValue& AnyValue::AddElement(const AnyValue& value)
{
  m_data->AddElement(value);
  return *this;
}

std::size_t AnyValue::NumberOfElements() const
{
  return m_data->NumberOfElements();
}

template <>
AnyValue AnyValue::As<AnyValue>() const
{
  return *this;
}

template <>
boolean AnyValue::As<boolean>() const
{
  return m_data->AsBoolean();
}

template <>
char8 AnyValue::As<char8>() const
{
  return m_data->AsCharacter8();
}

template <>
int8 AnyValue::As<int8>() const
{
  return m_data->AsSignedInteger8();
}

template <>
uint8 AnyValue::As<uint8>() const
{
  return m_data->AsUnsignedInteger8();
}

template <>
int16 AnyValue::As<int16>() const
{
  return m_data->AsSignedInteger16();
}

template <>
uint16 AnyValue::As<uint16>() const
{
  return m_data->AsUnsignedInteger16();
}

template <>
int32 AnyValue::As<int32>() const
{
  return m_data->AsSignedInteger32();
}

template <>
uint32 AnyValue::As<uint32>() const
{
  return m_data->AsUnsignedInteger32();
}

template <>
int64 AnyValue::As<int64>() const
{
  return m_data->AsSignedInteger64();
}

template <>
uint64 AnyValue::As<uint64>() const
{
  return m_data->AsUnsignedInteger64();
}

template <>
float32 AnyValue::As<float32>() const
{
  return m_data->AsFloat32();
}

template <>
float64 AnyValue::As<float64>() const
{
  return m_data->AsFloat64();
}

template <>
std::string AnyValue::As<std::string>() const
{
  return m_data->AsString();
}

bool AnyValue::HasField(const std::string& fieldname) const
{
  return m_data->HasField(fieldname);
}

AnyValue& AnyValue::operator[](const std::string& fieldname)
{
  return (*m_data)[fieldname];
}

const AnyValue& AnyValue::operator[](const std::string& fieldname) const
{
  return (*m_data)[fieldname];
}

AnyValue& AnyValue::operator[](std::size_t idx)
{
  return (*m_data)[idx];
}

const AnyValue& AnyValue::operator[](std::size_t idx) const
{
  return (*m_data)[idx];
}

bool AnyValue::operator==(const AnyValue& other) const
{
  if (m_data->IsScalar())
  {
    // Enforce symmetry of scalar comparison when conversions are involved
    return m_data->Equals(other) && other.m_data->Equals(*this);
  }
  return m_data->Equals(other);
}

bool AnyValue::operator!=(const AnyValue& other) const
{
  return !(this->operator==(other));
}

AnyValue::AnyValue(std::unique_ptr<IValueData>&& data)
  : m_data{std::move(data)}
{}

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

std::vector<uint8> ToBytes(const AnyValue& anyvalue)
{
  ByteSerializer serializer;
  Visit(anyvalue, serializer);
  return serializer.GetRepresentation();
}

void FromBytes(AnyValue& anyvalue, const uint8* bytes, std::size_t total_size)
{
  ByteParser byte_parser(bytes, total_size);
  Visit(anyvalue, byte_parser);
  if (!byte_parser.IsFinished())
  {
    throw ParseException("FromBytes ended before parsing all input bytes");
  }
}

}  // namespace dto

}  // namespace sup
