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
 * SPDX-License-Identifier: MIT
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file LICENSE located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include <sup/dto/anytype.h>

#include <sup/dto/anyvalue/anytype_compare_node.h>
#include <sup/dto/anyvalue/anytype_copy_node.h>
#include <sup/dto/anyvalue/anytype_from_anyvalue_node.h>
#include <sup/dto/anyvalue/array_type_data.h>
#include <sup/dto/anyvalue/empty_type_data.h>
#include <sup/dto/anyvalue/node_utils.h>
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

// Split a possibly nested type path into the first component and the rest:
std::pair<std::string, std::string> SplitAnyTypeFieldnameInHeadTail(const std::string& fieldname);

std::pair<std::string, std::string> SplitAnyTypeFieldnameOnArrayCharacter(
  const std::string& fieldname, std::size_t pos);

std::pair<std::string, std::string> SplitAnyTypeFieldnameOnStructCharacter(
  const std::string& fieldname, std::size_t pos);

bool CheckAnyTypeComponentFieldname(const std::string& fieldname);
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
    AnyType copy{memberType};
    struct_data->AddMember(memberName, std::move(copy));
  }
  m_data = std::move(struct_data);
}

AnyType::AnyType(std::initializer_list<std::pair<std::string, AnyType>> members)
  : AnyType{members, {}}
{}

AnyType::AnyType(std::size_t size, AnyType elem_type, const std::string& name)
  : AnyType{}
{
  std::unique_ptr<ITypeData> array_data =
    std::make_unique<ArrayTypeData>(size, std::move(elem_type), name);
  m_data = std::move(array_data);
}

AnyType::AnyType(std::size_t size, AnyType elem_type)
  : AnyType{size, std::move(elem_type), {}}
{}

AnyType::AnyType(const AnyValue& anyvalue)
  : AnyType{}
{
  std::deque<AnyTypeFromAnyValueNode> queue;
  (void)queue.emplace_back(std::addressof(anyvalue));
  while (true)
  {
    auto& last_node = queue.back();
    auto next_child_idx = last_node.NextIndex();
    if (next_child_idx == kInvalidIndex)
    {
      auto node_type = MakeAnyType(*last_node.GetSource(), last_node.MoveChildValues());
      queue.pop_back();
      if (queue.empty())
      {
        std::swap(m_data, node_type->m_data);
        break;
      }
      queue.back().AddChild(std::move(node_type));
    }
    else
    {
      auto next_child = last_node.GetSource()->GetChildValue(next_child_idx);
      (void)queue.emplace_back(next_child);
    }
  }
}

AnyType::AnyType(const AnyType& other)
  : AnyType{}
{
  std::deque<AnyTypeCopyNode> queue;
  (void)queue.emplace_back(std::addressof(other));
  while (true)
  {
    auto& last_node = queue.back();
    auto next_child_idx = last_node.NextIndex();
    if (next_child_idx == kInvalidIndex)
    {
      auto node_type = last_node.GetSource()->CloneFromChildren(last_node.MoveChildTypes());
      queue.pop_back();
      if (queue.empty())
      {
        std::swap(m_data, node_type->m_data);
        break;
      }
      queue.back().AddChild(std::move(node_type));
    }
    else
    {
      auto next_child = last_node.GetSource()->GetChildType(next_child_idx);
      (void)queue.emplace_back(next_child);
    }
  }
}

AnyType::AnyType(AnyType&& other) noexcept
  : AnyType{}
{
  std::swap(m_data, other.m_data);
}

AnyType& AnyType::operator=(const AnyType& other) &
{
  AnyType copy{other};
  std::swap(m_data, copy.m_data);
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

bool AnyType::IsScalar() const
{
  return m_data->IsScalar();
}

AnyType& AnyType::AddMember(const std::string& name, AnyType type) &
{
  m_data->AddMember(name, std::move(type));
  return *this;
}

AnyType&& AnyType::AddMember(const std::string& name, AnyType type) &&
{
  m_data->AddMember(name, std::move(type));
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
  // Only push nodes that already compare equal on a shallow level:
  if (!ShallowEquals(other))
  {
    return false;
  }
  std::deque<AnyTypeCompareNode> queue;
  (void)queue.emplace_back(this, std::addressof(other));
  while (!queue.empty())
  {
    auto& last_node = queue.back();
    if (last_node.m_index >= last_node.m_n_children)
    {
      queue.pop_back();
    }
    else
    {
      auto idx = last_node.m_index++;
      auto left_child = last_node.m_left->GetChildType(idx);
      auto right_child = last_node.m_right->GetChildType(idx);
      if (!left_child->ShallowEquals(*right_child))
      {
        return false;
      }
      (void)queue.emplace_back(left_child, right_child);
    }
  }
  return true;
}

bool AnyType::operator!=(const AnyType& other) const
{
  return !(this->operator==(other));
}

std::size_t AnyType::NumberOfChildren() const
{
  return m_data->NumberOfChildren();
}

AnyType* AnyType::GetChildType(std::size_t idx)
{
  return m_data->GetChildType(idx);
}

const AnyType* AnyType::GetChildType(std::size_t idx) const
{
  return m_data->GetChildType(idx);
}

std::unique_ptr<AnyType> AnyType::MakeAnyType(
  const AnyValue& anyvalue, std::vector<std::unique_ptr<AnyType>>&& children)
{
  if (IsScalarValue(anyvalue))
  {
    return MakeScalarAnyType(anyvalue);
  }
  if (IsStructValue(anyvalue))
  {
    return MakeStructAnyType(anyvalue, std::move(children));
  }
  if (IsArrayValue(anyvalue))
  {
    return MakeArrayAnyType(anyvalue);
  }
  return MakeEmptyAnyType();
}

std::unique_ptr<AnyType> AnyType::MakeStructAnyType(
  const AnyValue& anyvalue, std::vector<std::unique_ptr<AnyType>>&& children)
{
  const auto& type_name = anyvalue.GetTypeName();
  const auto member_names = anyvalue.MemberNames();
  auto struct_data = std::make_unique<StructTypeData>(type_name);
  for (std::size_t idx = 0; idx < member_names.size(); ++idx)
  {
    struct_data->AddMember(member_names[idx], std::move(*children[idx]));
  }
  std::unique_ptr<ITypeData> type_data = std::move(struct_data);
  return std::unique_ptr<AnyType>{new AnyType{std::move(type_data)}};
}

std::unique_ptr<AnyType> AnyType::MakeArrayAnyType(const AnyValue& anyvalue)
{
  const auto& type_name = anyvalue.GetTypeName();
  const size_t n_elems = anyvalue.NumberOfElements();
  auto array_data = std::make_unique<ArrayTypeData>(n_elems, anyvalue.ElementType(), type_name);
  std::unique_ptr<ITypeData> type_data = std::move(array_data);
  return std::unique_ptr<AnyType>{new AnyType{std::move(type_data)}};
}

std::unique_ptr<AnyType> AnyType::MakeScalarAnyType(const AnyValue& anyvalue)
{
  return std::unique_ptr<AnyType>{new AnyType{CreateScalarData(anyvalue.GetTypeCode())}};
}

std::unique_ptr<AnyType> AnyType::MakeEmptyAnyType()
{
  return std::make_unique<AnyType>();
}

AnyType::AnyType(std::unique_ptr<ITypeData>&& data)
  : m_data{std::move(data)}
{}

bool AnyType::HasChild(const std::string& child_name) const
{
  return m_data->HasChild(child_name);
}

const AnyType* AnyType::GetChildType(const std::string& child_name) const
{
  return m_data->GetChildType(child_name);
}

std::unique_ptr<AnyType> AnyType::CloneFromChildren(
  std::vector<std::unique_ptr<AnyType>>&& children) const
{
  return std::unique_ptr<AnyType>{new AnyType{m_data->CloneFromChildren(std::move(children))}};
}

bool AnyType::ShallowEquals(const AnyType& other) const
{
  return m_data->ShallowEquals(other);
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
  return anytype.IsScalar();
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

std::deque<std::string> SplitFieldname(const std::string& fieldname, HeadTailFunction func)
{
  std::deque<std::string> component_names;
  auto [head, tail] = func(fieldname);   // head is never empty
  component_names.push_back(head);
  while (!tail.empty())
  {
    auto [new_head, new_tail] = func(tail);
    component_names.push_back(new_head);
    tail = new_tail;
  }
  return component_names;
}

std::deque<std::string> SplitAnyTypeFieldname(const std::string& fieldname)
{
  return SplitFieldname(fieldname, SplitAnyTypeFieldnameInHeadTail);
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

std::pair<std::string, std::string> SplitAnyTypeFieldnameInHeadTail(const std::string& fieldname)
{
  if (fieldname.empty())
  {
    throw InvalidOperationException(
      "SplitAnyTypeFieldnameInHeadTail() called with empty fieldname");
  }
  auto pos = fieldname.find_first_of("].");
  if (pos == std::string::npos)
  {
    if (!CheckAnyTypeComponentFieldname(fieldname))
    {
        const std::string error =
          "SplitAnyTypeFieldnameInHeadTail(): could not parse fieldname \"" + fieldname + "\"";
        throw InvalidOperationException(error);
    }
    return { fieldname, "" };
  }
  if (fieldname[pos] == ']')
  {
    return SplitAnyTypeFieldnameOnArrayCharacter(fieldname, pos);
  }
  return SplitAnyTypeFieldnameOnStructCharacter(fieldname, pos);
}

std::pair<std::string, std::string> SplitAnyTypeFieldnameOnArrayCharacter(
  const std::string& fieldname, std::size_t pos)
{
  auto total_size = fieldname.size();
  std::string head{};
  std::string tail{};
  if (pos == 0 || fieldname[pos-1] != '[')
  {
    const std::string error =
      "SplitAnyTypeFieldnameInHeadTail(): could not parse fieldname \"" + fieldname + "\"";
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
  if (!CheckAnyTypeComponentFieldname(head))
  {
    const std::string error =
      "SplitAnyTypeFieldnameInHeadTail(): could not parse fieldname \"" + fieldname + "\"";
    throw InvalidOperationException(error);
  }
  return { head, tail };
}

std::pair<std::string, std::string> SplitAnyTypeFieldnameOnStructCharacter(
  const std::string& fieldname, std::size_t pos)
{
  auto total_size = fieldname.size();
  if (pos == 0 || pos + 1 == total_size)  // fieldname starts or ends with '.'
  {
    const std::string error =
      "SplitAnyTypeFieldnameInHeadTail(): could not parse fieldname \"" + fieldname + "\"";
    throw InvalidOperationException(error);
  }
  auto head = fieldname.substr(0, pos);
  auto tail = fieldname.substr(pos + 1);
  if (!CheckAnyTypeComponentFieldname(head))
  {
    const std::string error =
      "SplitAnyTypeFieldnameInHeadTail(): could not parse fieldname \"" + fieldname + "\"";
    throw InvalidOperationException(error);
  }
  return { head, tail };
}

bool CheckAnyTypeComponentFieldname(const std::string& fieldname)
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
