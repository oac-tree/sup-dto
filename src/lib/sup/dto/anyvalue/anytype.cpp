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
 * Copyright (c) : 2010-2023 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include <sup/dto/anytype.h>

#include <sup/dto/anyvalue/array_type_data.h>
#include <sup/dto/anyvalue/empty_type_data.h>
#include <sup/dto/anyvalue/scalar_type_data.h>
#include <sup/dto/anyvalue/struct_type_data.h>

#include <unordered_set>

namespace sup
{
namespace dto
{

namespace
{
std::unordered_set<TypeCode> ScalarTypes();
}  // unnamed namespace

AnyType::AnyType() noexcept
  : AnyType{new EmptyTypeData()}
{}

AnyType::AnyType(TypeCode type_code)
  : AnyType{CreateScalarData(type_code)}
{}

AnyType::AnyType(std::initializer_list<std::pair<std::string, AnyType>> members,
                 const std::string& name)
  : AnyType{}
{
  auto struct_data = std::unique_ptr<StructTypeData>(new StructTypeData(name));
  for (const std::pair<std::basic_string<char>, AnyType>& member : members)
  {
    struct_data->AddMember(member.first, member.second);
  }
  m_data = std::move(struct_data);
}

AnyType::AnyType(std::initializer_list<std::pair<std::string, AnyType>> members)
  : AnyType{members, {}}
{}

AnyType::AnyType(std::size_t size, const AnyType& elem_type, const std::string& name)
  : AnyType{}
{
  auto array_data = std::unique_ptr<ITypeData>(new ArrayTypeData(size, elem_type, name));
  std::swap(m_data, array_data);
}

AnyType::AnyType(std::size_t size, const AnyType& elem_type)
  : AnyType{size, elem_type, {}}
{}

AnyType::AnyType(const AnyType& other)
  : AnyType{other.m_data->Clone()}
{}

AnyType::AnyType(AnyType&& other) noexcept
  : AnyType{}
{
  std::swap(m_data, other.m_data);
}

AnyType& AnyType::operator=(const AnyType& other) &
{
  if (other.m_data != this->m_data)
  {
    auto copy = AnyType(other);
    std::swap(m_data, copy.m_data);
  }
  return *this;
}

AnyType& AnyType::operator=(AnyType&& other) & noexcept
{
  std::swap(m_data, other.m_data);
  return *this;
}

AnyType::~AnyType() = default;

TypeCode AnyType::GetTypeCode() const
{
  return m_data->GetTypeCode();
}

std::string AnyType::GetTypeName() const
{
  return m_data->GetTypeName();
}

AnyType& AnyType::AddMember(const std::string& name, const AnyType& type) &
{
  m_data->AddMember(name, type);
  return *this;
}

const AnyType& AnyType::AddMember(const std::string& name, const AnyType& type) const &
{
  m_data->AddMember(name, type);
  return *this;
}

std::vector<std::string> AnyType::MemberNames() const
{
  return m_data->MemberNames();
}

std::size_t AnyType::NumberOfMembers() const
{
  return m_data->NumberOfMembers();
}

AnyType AnyType::ElementType() const
{
  return m_data->ElementType();
}

std::size_t AnyType::NumberOfElements() const
{
  return m_data->NumberOfElements();
}

bool AnyType::HasField(const std::string& fieldname) const
{
  return m_data->HasField(fieldname);
}

AnyType& AnyType::operator[](const std::string& fieldname)
{
  return (*m_data)[fieldname];
}

const AnyType& AnyType::operator[](const std::string& fieldname) const
{
  return (*m_data)[fieldname];
}

bool AnyType::operator==(const AnyType& other) const
{
  return m_data->Equals(other);
}

bool AnyType::operator!=(const AnyType& other) const
{
  return !(this->operator==(other));
}

AnyType::AnyType(ITypeData* data)
  : m_data{data}
{}

AnyType EmptyStructType(const std::string& name)
{
  return AnyType(std::initializer_list<std::pair<std::string, AnyType>>{}, name);
}

AnyType EmptyStructType()
{
  return EmptyStructType({});
}

bool IsEmptyTypeCode(TypeCode type_code)
{
  return type_code == TypeCode::Empty;
}

bool IsStructTypeCode(TypeCode type_code)
{
  return type_code == TypeCode::Struct;
}

bool IsArrayTypeCode(TypeCode type_code)
{
  return type_code == TypeCode::Array;
}

bool IsScalarTypeCode(TypeCode type_code)
{
  static const auto scalar_types = ScalarTypes();
  return scalar_types.count(type_code) == 1;
}

bool IsEmptyType(const AnyType& anytype)
{
  return IsEmptyTypeCode(anytype.GetTypeCode());
}

bool IsStructType(const AnyType& anytype)
{
  return IsStructTypeCode(anytype.GetTypeCode());
}

bool IsArrayType(const AnyType& anytype)
{
  return IsArrayTypeCode(anytype.GetTypeCode());
}

bool IsScalarType(const AnyType& anytype)
{
  return IsScalarTypeCode(anytype.GetTypeCode());
}

const std::vector<std::pair<TypeCode, std::string>>& ScalarTypeDefinitions()
{
  static const std::vector<std::pair<TypeCode, std::string>> scalar_type_definitions({
    { TypeCode::Bool, kBooleanTypeName },
    { TypeCode::Char8, kChar8TypeName },
    { TypeCode::Int8, kInt8TypeName },
    { TypeCode::UInt8, kUInt8TypeName },
    { TypeCode::Int16, kInt16TypeName },
    { TypeCode::UInt16, kUInt16TypeName },
    { TypeCode::Int32, kInt32TypeName },
    { TypeCode::UInt32, kUInt32TypeName },
    { TypeCode::Int64, kInt64TypeName },
    { TypeCode::UInt64, kUInt64TypeName },
    { TypeCode::Float32, kFloat32TypeName },
    { TypeCode::Float64, kFloat64TypeName },
    { TypeCode::String, kStringTypeName }
  });
  return scalar_type_definitions;
}

const AnyType EmptyType{};
const AnyType BooleanType{TypeCode::Bool};
const AnyType Character8Type{TypeCode::Char8};
const AnyType SignedInteger8Type{TypeCode::Int8};
const AnyType UnsignedInteger8Type{TypeCode::UInt8};
const AnyType SignedInteger16Type{TypeCode::Int16};
const AnyType UnsignedInteger16Type{TypeCode::UInt16};
const AnyType SignedInteger32Type{TypeCode::Int32};
const AnyType UnsignedInteger32Type{TypeCode::UInt32};
const AnyType SignedInteger64Type{TypeCode::Int64};
const AnyType UnsignedInteger64Type{TypeCode::UInt64};
const AnyType Float32Type{TypeCode::Float32};
const AnyType Float64Type{TypeCode::Float64};
const AnyType StringType{TypeCode::String};

namespace
{
std::unordered_set<TypeCode> ScalarTypes()
{
  std::unordered_set<TypeCode> result;
  for (const std::pair<TypeCode, std::string>& entry : ScalarTypeDefinitions())
  {
    (void)result.insert(entry.first);
  }
  return result;
}

}  // unnamed namespace

}  // namespace dto

}  // namespace sup
