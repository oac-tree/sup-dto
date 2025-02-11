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

ArrayValueData::ArrayValueData(const AnyType& elem_type, const std::string& name,
                               Constraints constraints)
  : m_elem_type{elem_type}
  , m_name{name}
  , m_elements{}
  , m_constraints{constraints}
{
  if (m_elem_type == EmptyType)
  {
    throw InvalidOperationException("Empty type is not allowed as element type");
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

void ArrayValueData::AddElement(std::unique_ptr<AnyValue>&& value)
{
  m_elements.push_back(std::move(value));
}

std::size_t ArrayValueData::NumberOfElements() const
{
  return m_elements.size();
}

AnyValue& ArrayValueData::operator[](std::size_t idx)
{
  if (idx >= NumberOfElements())
  {
    throw InvalidOperationException("Index operator argument out of bounds");
  }
  return *m_elements[idx];
}

std::size_t ArrayValueData::NumberOfChildren() const
{
  return m_elements.size();
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

AnyValue* ArrayValueData::GetChildValue(const std::string& child_name)
{
  auto idx = ParseValueIndex(child_name);
  if (idx >= NumberOfElements())
  {
    throw InvalidOperationException("Index operator argument out of bounds");
  }
  return m_elements[idx].get();
}

AnyValue* ArrayValueData::GetChildValue(std::size_t idx)
{
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
  auto result = std::make_unique<ArrayValueData>(m_elem_type, GetTypeName(), constraints);
  for (auto& child : children)
  {
    result->m_elements.push_back(std::move(child));
  }
  return result;
}

bool ArrayValueData::ShallowEquals(const IValueData* other) const
{
  if (!IsArrayTypeCode(other->GetTypeCode()))
  {
    return false;
  }
  if (other->GetTypeName() != GetTypeName())
  {
    return false;
  }
  if (other->NumberOfElements() != NumberOfElements())
  {
    return false;
  }
  return true;
}

void ArrayValueData::ShallowConvertFrom(const AnyValue& value)
{
  if (value.GetTypeCode() != TypeCode::Array)
  {
    IValueData::ShallowConvertFrom(value);
  }
  if (value.NumberOfElements() != NumberOfElements())
  {
    throw InvalidConversionException("Can't convert between arrays of different length");
  }
}

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

