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

#include "array_value_data.h"

#include <sup/dto/anyvalue_exceptions.h>

#include <stdexcept>
#include <utility>

namespace sup
{
namespace dto
{

ArrayValueData::ArrayValueData(std::size_t size, const AnyType& elem_type,
                               const std::string& name, value_flags::Constraints constraints)
  : m_elem_type{elem_type}
  , m_name{name}
  , m_elements{}
  , m_constraints{constraints}
{
  if (m_elem_type == EmptyType)
  {
    throw InvalidOperationException("Empty type is not allowed as element type");
  }
  for (std::size_t i = 0; i < size; ++i)
  {
    std::unique_ptr<IValueData> data{CreateValueData(m_elem_type, value_flags::kLockedType)};
    m_elements.push_back(MakeAnyValue(std::move(data)));
  }
}

ArrayValueData::~ArrayValueData() = default;

ArrayValueData* ArrayValueData::Clone(value_flags::Constraints constraints) const
{
  auto result = std::unique_ptr<ArrayValueData>(
      new ArrayValueData(NumberOfElements(), m_elem_type, m_name, constraints));
  for (std::size_t i = 0; i < NumberOfElements(); ++i)
  {
    result->operator[](i) = *m_elements[i];
  }
  return result.release();
}

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

value_flags::Constraints ArrayValueData::GetConstraints() const
{
  return m_constraints;
}

void ArrayValueData::AddElement(const AnyValue& value)
{
  std::unique_ptr<IValueData> data{CreateValueData(m_elem_type, value_flags::kLockedType)};
  data->Assign(value);
  m_elements.push_back(MakeAnyValue(std::move(data)));
}

std::size_t ArrayValueData::NumberOfElements() const
{
  return m_elements.size();
}

void ArrayValueData::Assign(const AnyValue& value)
{
  if (value.GetTypeCode() != TypeCode::Array)
  {
    IValueData::Assign(value);
  }
  if (NumberOfElements() == 0)
  {
    for (std::size_t i = 0; i < value.NumberOfElements(); ++i)
    {
      std::unique_ptr<IValueData> data{CreateValueData(m_elem_type, value_flags::kLockedType)};
      m_elements.push_back(MakeAnyValue(std::move(data)));
    }
  }
  if (value.NumberOfElements() != NumberOfElements())
  {
    throw InvalidConversionException("Can't convert between array values with different length "
                                     "unless target has zero size");
  }
  for (std::size_t idx = 0; idx < NumberOfElements(); ++idx)
  {
    *m_elements[idx] = value[idx];
  }
}

bool ArrayValueData::HasField(const std::string& fieldname) const
{
  std::pair<std::size_t, std::string> idx_remainder;
  try
  {
    idx_remainder = StripValueIndex(fieldname);
  }
  catch(const InvalidOperationException&)
  {
    return false;
  }
  if (idx_remainder.first >= NumberOfElements())
  {
    return false;
  }
  if (idx_remainder.second.empty())
  {
    return true;
  }
  return m_elements[idx_remainder.first]->HasField(idx_remainder.second);
}

AnyValue& ArrayValueData::operator[](const std::string& fieldname)
{
  auto idx_remainder = StripValueIndex(fieldname);
  auto& element = this->operator[](idx_remainder.first);
  if (idx_remainder.second.empty())
  {
    return element;
  }
  return element[idx_remainder.second];
}

AnyValue& ArrayValueData::operator[](std::size_t idx)
{
  if (idx >= NumberOfElements())
  {
    throw InvalidOperationException("Index operator argument out of bounds");
  }
  return *m_elements[idx];
}

bool ArrayValueData::Equals(const AnyValue& other) const
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
  for (std::size_t idx = 0; idx < NumberOfElements(); ++idx)
  {
    if (other[idx] != *m_elements[idx])
    {
      return false;
    }
  }
  return true;
}

std::pair<std::size_t, std::string> StripValueIndex(const std::string& fieldname)
{
  if (fieldname.empty() || fieldname.substr(0, 1) != "[")
  {
    throw InvalidOperationException("Index operator argument for array value should start with [");
  }
  auto remainder = fieldname.substr(1);
  std::size_t idx = 0;
  std::size_t pos;
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
  if (remainder.empty() || remainder.substr(0, 1) != "]")
  {
    throw InvalidOperationException("Index operator argument for array value should be integer in "
                                 "square brackets");
  }
  remainder = remainder.substr(1);
  if (!remainder.empty() && remainder.substr(0, 1) == ".")
  {
    return { idx, remainder.substr(1) };
  }
  return { idx, remainder };
}

ArrayValueData* CreateArrayValueData(const AnyType& anytype, value_flags::Constraints constraints)
{
  auto result = std::unique_ptr<ArrayValueData>(
    new ArrayValueData(anytype.NumberOfElements(), anytype.ElementType(), anytype.GetTypeName(),
                       constraints));
  return result.release();
}

}  // namespace dto

}  // namespace sup
