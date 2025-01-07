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

#include <sup/dto/anyvalue.h>

#include <sup/dto/anyvalue/array_value_data.h>
#include <sup/dto/anyvalue/empty_value_data.h>
#include <sup/dto/anyvalue/scalar_value_data_t.h>
#include <sup/dto/anyvalue/struct_value_data.h>
#include <sup/dto/parse/ctype_parser.h>
#include <sup/dto/serialize/ctype_serializer.h>
#include <sup/dto/visit/visit_t.h>

namespace
{
using namespace sup::dto;
template <typename T>
std::unique_ptr<IValueData> CreateUnconstrainedScalarData(const T& val)
{
  return std::make_unique<ScalarValueDataT<T>>(val, Constraints::kNone);
}
}  // namespace

namespace sup
{
namespace dto
{
AnyValue::AnyValue() noexcept
  : AnyValue{CreateDefaultValueData()}
{}

AnyValue::AnyValue(const AnyType& anytype)
  : AnyValue{CreateValueData(anytype, Constraints::kNone)}
{}

AnyValue::AnyValue(boolean val)
  : AnyValue{CreateUnconstrainedScalarData(val)}
{}

AnyValue::AnyValue(char8 val)
  : AnyValue{CreateUnconstrainedScalarData(val)}
{}

AnyValue::AnyValue(int8 val)
  : AnyValue{CreateUnconstrainedScalarData(val)}
{}

AnyValue::AnyValue(uint8 val)
  : AnyValue{CreateUnconstrainedScalarData(val)}
{}

AnyValue::AnyValue(int16 val)
  : AnyValue{CreateUnconstrainedScalarData(val)}
{}

AnyValue::AnyValue(uint16 val)
  : AnyValue{CreateUnconstrainedScalarData(val)}
{}

AnyValue::AnyValue(int32 val)
  : AnyValue{CreateUnconstrainedScalarData(val)}
{}

AnyValue::AnyValue(uint32 val)
  : AnyValue{CreateUnconstrainedScalarData(val)}
{}

AnyValue::AnyValue(int64 val)
  : AnyValue{CreateUnconstrainedScalarData(val)}
{}

AnyValue::AnyValue(uint64 val)
  : AnyValue{CreateUnconstrainedScalarData(val)}
{}

AnyValue::AnyValue(float32 val)
  : AnyValue{CreateUnconstrainedScalarData(val)}
{}

AnyValue::AnyValue(float64 val)
  : AnyValue{CreateUnconstrainedScalarData(val)}
{}

AnyValue::AnyValue(const std::string& val)
  : AnyValue{CreateUnconstrainedScalarData(val)}
{}

AnyValue::AnyValue(const char* val)
  : AnyValue{CreateUnconstrainedScalarData<std::string>(val)}
{}

AnyValue::AnyValue(const AnyType& anytype, const AnyValue& anyvalue)
  : AnyValue{CreateValueData(anytype, Constraints::kNone)}
{
  m_data->ConvertFrom(anyvalue);
}

AnyValue::AnyValue(std::initializer_list<std::pair<std::string, AnyValue>> members,
                   const std::string& type_name)
  : AnyValue{}
{
  auto struct_data = std::make_unique<StructValueData>(type_name, Constraints::kNone);
  for (auto& [memberName, memberValue] : members)
  {
    struct_data->AddMember(memberName, memberValue);
  }
  m_data = std::move(struct_data);
}

AnyValue::AnyValue(std::initializer_list<std::pair<std::string, AnyValue>> members)
  : AnyValue{members, {}}
{}

AnyValue::AnyValue(std::size_t size, const AnyType& elem_type, const std::string& name)
  : AnyValue{}
{
  auto array_data = std::make_unique<ArrayValueData>(size, elem_type, name, Constraints::kNone);
  m_data = std::move(array_data);
}

AnyValue::AnyValue(std::size_t size, const AnyType& elem_type)
  : AnyValue{size, elem_type, {}}
{}

AnyValue::AnyValue(const AnyValue& other)
  : AnyValue{other.m_data->Clone(Constraints::kNone)}
{}

AnyValue::AnyValue(AnyValue&& other) noexcept
  : AnyValue{StealOrClone(std::move(other.m_data))}
{}

AnyValue& AnyValue::operator=(const AnyValue& other) &
{
  if (this != std::addressof(other))
  {
    if (IsLockedTypeConstraint(m_data->GetConstraints()))
    {
      ConvertFrom(other);
    }
    else
    {
      auto tmp = other.m_data->Clone(Constraints::kNone);
      std::swap(m_data, tmp);
    }
  }
  return *this;
}

AnyValue& AnyValue::operator=(AnyValue&& other) &
{
  if (IsLockedTypeConstraint(m_data->GetConstraints()))
  {
    ConvertFrom(other);
    return *this;
  }
  if (IsLockedTypeConstraint(other.m_data->GetConstraints()))
  {
    auto tmp = other.m_data->Clone(Constraints::kNone);
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
  auto tmp = CreateValueData(GetType(), m_data->GetConstraints());
  tmp->ConvertFrom(other);
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

AnyValue& AnyValue::AddMember(const std::string& name, const AnyValue& value) &
{
  m_data->AddMember(name, value);
  return *this;
}

AnyValue&& AnyValue::AddMember(const std::string& name, const AnyValue& value) &&
{
  m_data->AddMember(name, value);
  return std::move(*this);
}

std::vector<std::string> AnyValue::MemberNames() const
{
  return m_data->MemberNames();
}

std::size_t AnyValue::NumberOfMembers() const
{
  return m_data->NumberOfMembers();
}

AnyValue& AnyValue::AddElement(const AnyValue& value) &
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
    return (m_data->Equals(other)) && (other.m_data->Equals(*this));
  }
  return m_data->Equals(other);
}

bool AnyValue::operator!=(const AnyValue& other) const
{
  return !(this->operator==(other));
}

void AnyValue::UnsafeConvertFrom(const AnyValue& other)
{
  m_data->ConvertFrom(other);
}

AnyValue::AnyValue(std::unique_ptr<IValueData>&& data)
  : m_data{std::move(data)}
{}

AnyValue EmptyStruct(const std::string& type_name)
{
  return AnyValue(EmptyStructType(type_name));
}

AnyValue EmptyStruct()
{
  return EmptyStruct({});
}

AnyValue ArrayValue(std::initializer_list<AnyValue> elements, const std::string& type_name)
{
  if (elements.size() == 0)
  {
    throw InvalidOperationException("Cannot construct an array value from a list with length zero");
  }
  auto result = AnyValue(elements.size(), elements.begin()->GetType(), type_name);
  std::size_t idx = 0u;
  for (const AnyValue& element : elements)
  {
    result[idx] = element;
    ++idx;
  }
  return result;
}

AnyValue ArrayValue(std::initializer_list<AnyValue> elements)
{
  return ArrayValue(elements, {});
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
  CTypeSerializer serializer;
  Visit(anyvalue, serializer);
  return serializer.GetRepresentation();
}

void FromBytes(AnyValue& anyvalue, const uint8* bytes, std::size_t total_size)
{
  CTypeParser byte_parser(bytes, total_size);
  Visit(anyvalue, byte_parser);
  if (!byte_parser.IsFinished())
  {
    throw ParseException("FromBytes ended before parsing all input bytes");
  }
}

}  // namespace dto

}  // namespace sup
