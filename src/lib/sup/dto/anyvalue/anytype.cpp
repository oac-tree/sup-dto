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

std::pair<std::string, std::string> SplitFieldnameInHeadTail(const std::string& fieldname);

std::pair<std::string, std::string> SplitFieldnameOnArrayCharacter(const std::string& fieldname,
                                                                   std::size_t pos);

std::pair<std::string, std::string> SplitFieldnameOnStructCharacter(const std::string& fieldname,
                                                                   std::size_t pos);

bool CheckComponentFieldname(const std::string& fieldname);
}  // unnamed namespace

AnyType::AnyType() noexcept
  : AnyType{CreateDefaultTypeData()}
{}

AnyType::AnyType(TypeCode type_code)
  : AnyType{CreateScalarData(type_code)}
{}

AnyType::AnyType(std::initializer_list<std::pair<std::string, AnyType>> members,
                 const std::string& name)
  : AnyType{}
{
  auto struct_data = std::make_unique<StructTypeData>(name);
  for (auto& [memberName, memberType] : members)
  {
    struct_data->AddMember(memberName, memberType);
  }
  m_data = std::move(struct_data);
}

AnyType::AnyType(std::initializer_list<std::pair<std::string, AnyType>> members)
  : AnyType{members, {}}
{}

AnyType::AnyType(std::size_t size, const AnyType& elem_type, const std::string& name)
  : AnyType{}
{
  std::unique_ptr<ITypeData> array_data = std::make_unique<ArrayTypeData>(size, elem_type, name);
  m_data = std::move(array_data);
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
  auto copy = AnyType(other);
  std::swap(m_data, copy.m_data);
  return *this;
}

AnyType& AnyType::operator=(AnyType&& other) & noexcept
{
  auto moved = std::move(other);
  std::swap(m_data, moved.m_data);
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

AnyType&& AnyType::AddMember(const std::string& name, const AnyType& type) &&
{
  m_data->AddMember(name, type);
  return std::move(*this);
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
  std::deque<std::string> field_names;
  try
  {
    field_names = SplitAnyTypeFieldname(fieldname);
  }
  catch(const MessageException&)
  {
    return false;
  }
  const auto* node = this;
  while (!field_names.empty())
  {
    auto child_name = field_names.front();
    if (!node->HasChild(child_name))
    {
      return false;
    }
    node = node->GetChildType(child_name);
    field_names.pop_front();
  }
  return true;
}

AnyType& AnyType::operator[](const std::string& fieldname)
{
  return const_cast<AnyType&>(const_cast<const AnyType*>(this)->operator[](fieldname));
}

const AnyType& AnyType::operator[](const std::string& fieldname) const
{
  auto field_names = SplitAnyTypeFieldname(fieldname);
  const auto* result = this;
  while (!field_names.empty())
  {
    result = result->GetChildType(field_names.front());
    field_names.pop_front();
  }
  return *result;
}

bool AnyType::operator==(const AnyType& other) const
{
  return m_data->Equals(other);
}

bool AnyType::operator!=(const AnyType& other) const
{
  return !(this->operator==(other));
}

AnyType::AnyType(std::unique_ptr<ITypeData>&& data)
  : m_data{std::move(data)}
{}

bool AnyType::HasChild(const std::string& child_name) const
{
  return m_data->HasChild(child_name);
}

std::vector<std::string> AnyType::ChildNames() const
{
  return m_data->ChildNames();
}

AnyType* AnyType::GetChildType(const std::string& child_name)
{
  return const_cast<AnyType*>(const_cast<const AnyType*>(this)->GetChildType(child_name));
}

const AnyType* AnyType::GetChildType(const std::string& child_name) const
{
  return m_data->GetChildType(child_name);
}

AnyType AnyType::CloneFromChildren(std::vector<AnyType>&& children) const
{
  auto type_data = m_data->CloneFromChildren(std::move(children));
  return AnyType{std::move(type_data)};
}

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

std::deque<std::string> SplitAnyTypeFieldname(const std::string& fieldname)
{
  std::deque<std::string> component_names;
  auto [head, tail] = SplitFieldnameInHeadTail(fieldname);   // head is never empty
  component_names.push_back(head);
  while (!tail.empty())
  {
    auto [new_head, new_tail] = SplitFieldnameInHeadTail(tail);
    component_names.push_back(new_head);
    tail = new_tail;
  }
  return component_names;
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
  for (auto& [type_code, _] : ScalarTypeDefinitions())
  {
    (void)result.insert(type_code);
  }
  return result;
}

std::pair<std::string, std::string> SplitFieldnameInHeadTail(const std::string& fieldname)
{
  if (fieldname.empty())
  {
    throw InvalidOperationException("SplitFieldnameInHeadTail() called with empty fieldname");
  }
  const std::string error =
    "SplitFieldnameInHeadTail(): could not parse fieldname \"" + fieldname + "\"";
  auto pos = fieldname.find_first_of("].");
  if (pos == std::string::npos)
  {
    if (!CheckComponentFieldname(fieldname))
    {
      throw InvalidOperationException(error);
    }
    return { fieldname, "" };
  }
  if (fieldname[pos] == ']')
  {
    return SplitFieldnameOnArrayCharacter(fieldname, pos);
  }
  return SplitFieldnameOnStructCharacter(fieldname, pos);
}

std::pair<std::string, std::string> SplitFieldnameOnArrayCharacter(const std::string& fieldname,
                                                                   std::size_t pos)
{
  const std::string error =
    "SplitFieldnameInHeadTail(): could not parse fieldname \"" + fieldname + "\"";
  auto total_size = fieldname.size();
  std::string head{};
  std::string tail{};
  if (pos == 0 || fieldname[pos-1] != '[')
  {
    throw InvalidOperationException(error);
  }
  if (pos == 1)  // fieldname starts with []
  {
    auto pos_remainder = pos + 1;
    if (pos_remainder < total_size && fieldname[pos_remainder] == '.')
    {
      ++pos_remainder;
    }
    head = "[]";
    tail = fieldname.substr(pos_remainder);
  }
  else
  {
    head = fieldname.substr(0, pos - 1);
    tail = fieldname.substr(pos - 1);
  }
  if (!CheckComponentFieldname(head))
  {
    throw InvalidOperationException(error);
  }
  return { head, tail };
}

std::pair<std::string, std::string> SplitFieldnameOnStructCharacter(const std::string& fieldname,
                                                                   std::size_t pos)
{
  const std::string error =
    "SplitFieldnameInHeadTail(): could not parse fieldname \"" + fieldname + "\"";
  auto total_size = fieldname.size();
  if (pos == 0 || pos + 1 == total_size)  // fieldname starts or ends with '.'
  {
    throw InvalidOperationException(error);
  }
  auto head = fieldname.substr(0, pos);
  auto tail = fieldname.substr(pos + 1);
  if (!CheckComponentFieldname(head))
  {
    throw InvalidOperationException(error);
  }
  return { head, tail };
}

bool CheckComponentFieldname(const std::string& fieldname)
{
  // A component fieldname is either "[]" or a non-empty string that doesn't contain any of "[]."
  if (fieldname.empty())
  {
    return false;
  }
  if (fieldname == "[]")
  {
    return true;
  }
  auto pos = fieldname.find_first_of("[].");
  return (pos == std::string::npos);
}

}  // unnamed namespace

}  // namespace dto

}  // namespace sup
