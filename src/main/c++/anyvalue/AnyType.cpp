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
 * Copyright (c) : 2010-2022 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include "AnyType.h"

#include "EmptyTypeData.h"
#include "ScalarTypeData.h"
#include "StructTypeData.h"

#include <unordered_set>

namespace sup
{
namespace dto
{

namespace
{
std::unordered_set<TypeCode> ScalarTypes();
}  // unnamed namespace

AnyType::AnyType()
  : data{new EmptyTypeData()}
{}

AnyType::AnyType(TypeCode type_code)
  : data{CreateScalarData(type_code)}
{}

AnyType::AnyType(std::initializer_list<std::pair<std::string, AnyType>> members,
                 const std::string& name)
  : data{new EmptyTypeData()}
{
  auto struct_data = std::unique_ptr<StructTypeData>(new StructTypeData(name));
  for (auto& member : members)
  {
    struct_data->AddMember(member.first, member.second);
  }
  data = std::move(struct_data);
}

AnyType::AnyType(const AnyType& other)
  : data{other.data->Clone()}
{}

AnyType& AnyType::operator=(const AnyType& other)
{
  if (this != &other)
  {
    data.reset(other.data->Clone());
  }
  return *this;
}

AnyType::AnyType(AnyType&& other)
  : data{other.data.release()}
{
  other.data.reset(new EmptyTypeData());
}

AnyType& AnyType::operator=(AnyType&& other)
{
  if (this != &other)
  {
    data.reset(other.data.release());
    other.data.reset(new EmptyTypeData());
  }
  return *this;
}

AnyType::~AnyType() = default;

TypeCode AnyType::GetTypeCode() const
{
  return data->GetTypeCode();
}

std::string AnyType::GetTypeName() const
{
  return data->GetTypeName();
}

void AnyType::AddMember(const std::string& name, const AnyType& type)
{
  return data->AddMember(name, type);
}

bool AnyType::HasMember(const std::string& name) const
{
  return data->HasMember(name);
}

std::vector<std::string> AnyType::MemberNames() const
{
  return data->MemberNames();
}

std::size_t AnyType::NumberOfMembers() const
{
  return data->NumberOfMembers();
}

AnyType& AnyType::operator[](std::string fieldname)
{
  return (*data)[fieldname];
}

const AnyType& AnyType::operator[](std::string fieldname) const
{
  return (*data)[fieldname];
}

bool AnyType::operator==(const AnyType& other) const
{
  return data->Equals(other);
}

bool AnyType::operator!=(const AnyType& other) const
{
  return !(this->operator==(other));
}

AnyType EmptyStructType(const std::string& name)
{
  return AnyType(std::initializer_list<std::pair<std::string, AnyType>>{}, name);
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
  static auto scalar_types = ScalarTypes();
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

const AnyType EmptyType{};
const AnyType Boolean{TypeCode::Bool};
const AnyType SignedInteger8{TypeCode::Int8};
const AnyType UnsignedInteger8{TypeCode::UInt8};
const AnyType SignedInteger16{TypeCode::Int16};
const AnyType UnsignedInteger16{TypeCode::UInt16};
const AnyType SignedInteger32{TypeCode::Int32};
const AnyType UnsignedInteger32{TypeCode::UInt32};
const AnyType SignedInteger64{TypeCode::Int64};
const AnyType UnsignedInteger64{TypeCode::UInt64};

namespace
{
std::unordered_set<TypeCode> ScalarTypes()
{
  std::unordered_set<TypeCode> result;
  result.insert({ TypeCode::Bool,
                  TypeCode::Int8, TypeCode::UInt8, TypeCode::Int16, TypeCode::UInt16,
                  TypeCode::Int32, TypeCode::UInt32, TypeCode::Int64, TypeCode::UInt64 });
  return result;
}
}  // unnamed namespace

}  // namespace dto

}  // namespace sup
