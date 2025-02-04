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

#include "array_value_data.h"
#include "i_value_data.h"

#include <sup/dto/anyvalue_exceptions.h>

#include <stdexcept>
#include <utility>

namespace
{
std::size_t ParseValueIndex(const std::string& fieldname);
}  // unnamed namespace

namespace sup
{
namespace dto
{

ArrayValueData::ArrayValueData(std::size_t size, const AnyType& elem_type,
                               const std::string& name, Constraints constraints)
  : m_elem_type{elem_type}
  , m_name{name}
  , m_elements{}
  , m_constraints{constraints}
{
  if (m_elem_type == EmptyType)
  {
    throw InvalidOperationException("Empty type is not allowed as element type");
  }
  for (std::size_t i = 0u; i < size; ++i)
  {
    auto data = CreateValueData(m_elem_type, Constraints::kLockedType);
    m_elements.push_back(MakeAnyValue(std::move(data)));
  }
}

ArrayValueData::~ArrayValueData() = default;

TypeCode ArrayValueData::GetTypeCode() const
{
  return TypeCode::Array;
}

std::string ArrayValueData::GetTypeName() const
{
  return m_name;
}

AnyType ArrayValueData::GetType() const
{
  return AnyType(NumberOfElements(), m_elem_type, m_name);
}

Constraints ArrayValueData::GetConstraints() const
{
  return m_constraints;
}

void ArrayValueData::AddElement(const AnyValue& value)
{
  if (IsLockedTypeConstraint(m_constraints))
  {
    throw InvalidOperationException("Cannot add element to array whose type is locked");
  }
  auto data = CreateValueData(m_elem_type, Constraints::kLockedType);
  data->ConvertFrom(value);
  m_elements.push_back(MakeAnyValue(std::move(data)));
}

std::size_t ArrayValueData::NumberOfElements() const
{
  return m_elements.size();
}

void ArrayValueData::ConvertFrom(const AnyValue& value)
{
  if (value.GetTypeCode() != TypeCode::Array)
  {
    IValueData::ConvertFrom(value);
  }
  if (value.NumberOfElements() != NumberOfElements())
  {
    throw InvalidConversionException("Can't convert between array values with different length "
                                     "unless target has zero size");
  }
  for (std::size_t idx = 0u; idx < NumberOfElements(); ++idx)
  {
    UnsafeConversion(*m_elements[idx], value[idx]);
  }
}

AnyValue& ArrayValueData::operator[](std::size_t idx)
{
  if (idx >= NumberOfElements())
  {
    throw InvalidOperationException("Index operator argument out of bounds");
  }
  return *m_elements[idx];
}

bool ArrayValueData::HasChild(const std::string& child_name) const
{
  std::size_t idx{0};
  try
  {
    idx = ParseValueIndex(child_name);
  }
  catch(const InvalidOperationException&)
  {
    return false;
  }
  if (idx >= NumberOfElements())
  {
    return false;
  }
  return true;
}

std::vector<std::string> ArrayValueData::ChildNames() const
{
  std::vector<std::string> result;
  for (std::size_t idx = 0; idx < NumberOfElements(); ++idx)
  {
    std::string idx_str = "[" + std::to_string(idx) + "]";
    result.push_back(std::move(idx_str));
  }
  return result;
}

AnyValue* ArrayValueData::GetChildValue(const std::string& child_name)
{
  auto idx = ParseValueIndex(child_name);
  if (idx >= NumberOfElements())
  {
    throw InvalidOperationException("Index operator argument out of bounds");
  }
  return m_elements[idx].get();
}

std::unique_ptr<IValueData> ArrayValueData::CloneFromChildren(
  std::vector<std::unique_ptr<AnyValue>>&& children, Constraints constraints) const
{
  auto n_elements = NumberOfElements();
  if (children.size() != n_elements)
  {
    const std::string error =
      "StructValueData::CloneFromChildren(): Trying to clone array value with wrong number of "
      "child values";
    throw InvalidOperationException(error);
  }
  auto result = std::unique_ptr<ArrayValueData>{
    new ArrayValueData{m_elem_type, GetTypeName(), constraints}};
  for (auto& child : children)
  {
    result->m_elements.push_back(std::move(child));
  }
  return result;
}

bool ArrayValueData::ShallowEquals(const AnyValue& other) const
{
  if (!IsArrayValue(other))
  {
    return false;
  }
  if (other.GetTypeName() != GetTypeName())
  {
    return false;
  }
  if (other.NumberOfElements() != NumberOfElements())
  {
    return false;
  }
  return true;
}

ArrayValueData::ArrayValueData(const AnyType& elem_type, const std::string& name,
                               Constraints constraints)
  : m_elem_type{elem_type}
  , m_name{name}
  , m_elements{}
  , m_constraints{constraints}
{}

std::pair<std::size_t, std::string> StripValueIndex(const std::string& fieldname)
{
  if ((fieldname.empty()) || (fieldname.substr(0u, 1u) != "["))
  {
    throw InvalidOperationException("Index operator argument for array value should start with [");
  }
  auto remainder = fieldname.substr(1u);
  std::size_t idx = 0u;
  std::size_t pos = 0u;
  try
  {
    idx = std::stoul(remainder, &pos);
  }
  catch(const std::invalid_argument&)
  {
    throw InvalidOperationException("Index operator argument cannot be parsed to an unsigned integer");
  }
  catch(const std::out_of_range&)
  {
    throw InvalidOperationException("Index operator argument cannot be parsed to an unsigned integer");
  }
  remainder = remainder.substr(pos);
  if ((remainder.empty()) || (remainder.substr(0u, 1u) != "]"))
  {
    throw InvalidOperationException("Index operator argument for array value should be integer in "
                                 "square brackets");
  }
  remainder = remainder.substr(1u);
  if ((!remainder.empty()) && (remainder.substr(0u, 1u) == "."))
  {
    return { idx, remainder.substr(1u) };
  }
  return { idx, remainder };
}

std::unique_ptr<IValueData> CreateArrayValueData(const AnyType& anytype,
                                                 Constraints constraints)
{
  return std::make_unique<ArrayValueData>(anytype.NumberOfElements(), anytype.ElementType(),
                                          anytype.GetTypeName(), constraints);
}

}  // namespace dto

}  // namespace sup

namespace
{
using namespace sup::dto;
std::size_t ParseValueIndex(const std::string& fieldname)
{
  const std::string error = "ParseValueIndex(): could not parse \"" + fieldname + "\"";
  auto total_size = fieldname.size();
  if (total_size < 2)
  {
    throw InvalidOperationException(error);
  }
  if (fieldname[0] != '[' || fieldname[total_size - 1] != ']')
  {
    throw InvalidOperationException(error);
  }
  auto index_str = fieldname.substr(1, total_size - 2);
  std::size_t idx{0};
  std::size_t pos{0};
  try
  {
    idx = std::stoul(index_str, &pos);
  }
  catch(const std::logic_error&)
  {
    throw InvalidOperationException(error);
  }
  if (pos != index_str.size())
  {
    throw InvalidOperationException(error);
  }
  return idx;
}

}  // unnamed namespace

