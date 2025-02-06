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

#include <sup/dto/anyvalue/anyvalue_compare_node.h>
#include <sup/dto/anyvalue/anyvalue_copy_node.h>
#include <sup/dto/anyvalue/array_value_data.h>
#include <sup/dto/anyvalue/empty_value_data.h>
#include <sup/dto/anyvalue/node_utils.h>
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

// Split a possibly nested value path into the first component and the rest:
std::pair<std::string, std::string> SplitAnyValueFieldnameInHeadTail(const std::string& fieldname);

std::pair<std::string, std::string> SplitAnyValueFieldnameOnArrayCharacter(
  const std::string& fieldname, std::size_t pos);

std::pair<std::string, std::string> SplitAnyValueFieldnameOnStructCharacter(
  const std::string& fieldname, std::size_t pos);

bool CheckAnyValueComponentFieldname(const std::string& fieldname);

bool CheckIndexString(const std::string& index_string);
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
  for (auto& [mem_name, mem_value] : members)
  {
    AnyValue copy{mem_value};
    struct_data->AddMember(mem_name, std::move(copy));
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
  : AnyValue{}
{
  std::deque<AnyValueCopyNode> queue;
  AnyValueCopyNode root_node{std::addressof(other), other.NumberOfChildren(), Constraints::kNone};
  queue.push_back(std::move(root_node));
  while (true)
  {
    auto& last_node = queue.back();
    auto next_child_idx = last_node.NextIndex();
    if (next_child_idx == kInvalidIndex)
    {
      auto node_value = last_node.GetSource()->CloneFromChildren(last_node.MoveChildValues(),
                                                                 last_node.GetConstraints());
      queue.pop_back();
      if (queue.empty())
      {
        std::swap(m_data, node_value->m_data);
        break;
      }
      queue.back().AddChild(std::move(node_value));
    }
    else
    {
      auto next_child = last_node.GetSource()->GetChildValue(next_child_idx);
      auto child_constraints = last_node.GetChildConstraints();
      AnyValueCopyNode child_node{next_child, next_child->NumberOfChildren(), child_constraints};
      queue.push_back(std::move(child_node));
    }
  }
}

AnyValue::AnyValue(AnyValue&& other) noexcept
  : AnyValue{}
{
  if (IsLockedTypeConstraint(other.m_data->GetConstraints()))
  {
    AnyValue copy{other};
    std::swap(m_data, copy.m_data);
  }
  else
  {
    std::swap(m_data, other.m_data);
  }
}

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
      AnyValue copy{other};
      std::swap(m_data, copy.m_data);
    }
  }
  return *this;
}

AnyValue& AnyValue::operator=(AnyValue&& other) &
{
  if (IsLockedTypeConstraint(m_data->GetConstraints()))
  {
    ConvertFrom(other);
  }
  else if (IsLockedTypeConstraint(other.m_data->GetConstraints()))
  {
    AnyValue copy{other};
    std::swap(m_data, copy.m_data);
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

AnyValue& AnyValue::AddMember(const std::string& name, AnyValue value) &
{
  m_data->AddMember(name, std::move(value));
  return *this;
}

AnyValue&& AnyValue::AddMember(const std::string& name, AnyValue value) &&
{
  m_data->AddMember(name, std::move(value));
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
  std::deque<std::string> field_names;
  try
  {
    field_names = SplitAnyValueFieldname(fieldname);
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
    node = node->GetChildValue(child_name);
    field_names.pop_front();
  }
  return true;
}

AnyValue& AnyValue::operator[](const std::string& fieldname)
{
  return const_cast<AnyValue&>(const_cast<const AnyValue*>(this)->operator[](fieldname));
}

const AnyValue& AnyValue::operator[](const std::string& fieldname) const
{
  auto field_names = SplitAnyValueFieldname(fieldname);
  const auto* result = this;
  while (!field_names.empty())
  {
    result = result->GetChildValue(field_names.front());
    field_names.pop_front();
  }
  return *result;
}

AnyValue& AnyValue::operator[](std::size_t idx)
{
  return const_cast<AnyValue&>(const_cast<const AnyValue*>(this)->operator[](idx));
}

const AnyValue& AnyValue::operator[](std::size_t idx) const
{
  return (*m_data)[idx];
}

bool AnyValue::operator==(const AnyValue& other) const
{
  // Only push nodes that already compare equal on a shallow level:
  if (!ShallowEquals(other))
  {
    return false;
  }
  std::deque<AnyValueCompareNode> queue;
  AnyValueCompareNode root_node{this, std::addressof(other), NumberOfChildren()};
  queue.push_back(std::move(root_node));
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
      auto left_child = last_node.m_left->GetChildValue(idx);
      auto right_child = last_node.m_right->GetChildValue(idx);
      if (!left_child->ShallowEquals(*right_child))
      {
        return false;
      }
      AnyValueCompareNode child_node{left_child, right_child, left_child->NumberOfChildren()};
      queue.push_back(std::move(child_node));
    }
  }
  return true;
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

std::size_t AnyValue::NumberOfChildren() const
{
  return m_data->NumberOfChildren();
}

bool AnyValue::HasChild(const std::string& child_name) const
{
  return m_data->HasChild(child_name);
}

const AnyValue* AnyValue::GetChildValue(const std::string& child_name) const
{
  return m_data->GetChildValue(child_name);
}

const AnyValue* AnyValue::GetChildValue(std::size_t idx) const
{
  return m_data->GetChildValue(idx);
}

std::unique_ptr<AnyValue> AnyValue::CloneFromChildren(
  std::vector<std::unique_ptr<AnyValue>>&& children, Constraints constraints) const
{
  return std::unique_ptr<AnyValue>{
    new AnyValue{m_data->CloneFromChildren(std::move(children), constraints)}};
}

bool AnyValue::ShallowEquals(const AnyValue& other) const
{
  if (m_data->IsScalar())
  {
    // Enforce symmetry of scalar comparison when conversions are involved
    return (m_data->ShallowEquals(other)) && (other.m_data->ShallowEquals(*this));
  }
  return m_data->ShallowEquals(other);
}

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

std::deque<std::string> SplitAnyValueFieldname(const std::string& fieldname)
{
  return SplitFieldname(fieldname, SplitAnyValueFieldnameInHeadTail);
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

namespace
{
std::pair<std::string, std::string> SplitAnyValueFieldnameInHeadTail(const std::string& fieldname)
{
  if (fieldname.empty())
  {
    throw InvalidOperationException(
      "SplitAnyValueFieldnameInHeadTail() called with empty fieldname");
  }
  const std::string error =
    "SplitAnyValueFieldnameInHeadTail(): could not parse fieldname \"" + fieldname + "\"";
  auto pos = fieldname.find_first_of("[.");
  if (pos == std::string::npos)
  {
    if (!CheckAnyValueComponentFieldname(fieldname))
    {
      throw InvalidOperationException(error);
    }
    return { fieldname, "" };
  }
  if (fieldname[pos] == '[')
  {
    return SplitAnyValueFieldnameOnArrayCharacter(fieldname, pos);
  }
  return SplitAnyValueFieldnameOnStructCharacter(fieldname, pos);
}

std::pair<std::string, std::string> SplitAnyValueFieldnameOnArrayCharacter(
  const std::string& fieldname, std::size_t pos)
{
  const std::string error =
    "SplitAnyValueFieldnameInHeadTail(): could not parse fieldname \"" + fieldname + "\"";
  std::string head{};
  std::string tail{};
  if (pos == 0)
  {
    auto pos_end = fieldname.find(']', pos);
    if (pos_end == std::string::npos)
    {
      throw InvalidOperationException(error);
    }
    auto remainder_start = pos_end + 1;
    if (remainder_start < fieldname.size() && fieldname[remainder_start] == '.')
    {
      ++remainder_start;
    }
    head = fieldname.substr(0, pos_end + 1);
    tail = fieldname.substr(remainder_start);
  }
  else
  {
    head = fieldname.substr(0, pos);
    tail = fieldname.substr(pos);
  }
  if (!CheckAnyValueComponentFieldname(head))
  {
    throw InvalidOperationException(error);
  }
  return { head, tail };
}

std::pair<std::string, std::string> SplitAnyValueFieldnameOnStructCharacter(
  const std::string& fieldname, std::size_t pos)
{
  const std::string error =
    "SplitAnyValueFieldnameInHeadTail(): could not parse fieldname \"" + fieldname + "\"";
  auto total_size = fieldname.size();
  if (pos == 0 || pos + 1 == total_size)  // fieldname starts or ends with '.'
  {
    throw InvalidOperationException(error);
  }
  auto head = fieldname.substr(0, pos);
  auto tail = fieldname.substr(pos + 1);
  if (!CheckAnyValueComponentFieldname(head))
  {
    throw InvalidOperationException(error);
  }
  return { head, tail };
}

bool CheckAnyValueComponentFieldname(const std::string& fieldname)
{
  // A component fieldname is either "[x]" with x an integer or a non-empty string that doesn't
  // contain any of "[]."
  if (fieldname.empty())
  {
    return false;
  }
  auto total_size = fieldname.size();
  if (fieldname[0] == '[' && fieldname[total_size - 1] == ']')
  {
    return CheckIndexString(fieldname.substr(1, total_size - 2));
  }
  auto pos = fieldname.find_first_of("[].");
  return (pos == std::string::npos);
}

bool CheckIndexString(const std::string& index_string)
{
  std::size_t pos{0};
  try
  {
    (void)std::stoul(index_string, &pos);
  }
  catch(const std::logic_error&)
  {
    return false;
  }
  return pos == index_string.size();
}

}  // namespace
