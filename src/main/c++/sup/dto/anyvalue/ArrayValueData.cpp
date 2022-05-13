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

#include "ArrayValueData.h"

#include "sup/dto/AnyValueExceptions.h"

#include <stdexcept>
#include <utility>

namespace sup
{
namespace dto
{

ArrayValueData::ArrayValueData(std::size_t size_, const AnyType& elem_type_, const std::string& name_)
  : elem_type{elem_type_}
  , name{name_}
  , elements(size_, AnyValue{elem_type_})
{
  if (elem_type == EmptyType)
  {
    throw InvalidOperationException("Empty type is not allowed as element type");
  }
}

ArrayValueData::~ArrayValueData() = default;

ArrayValueData* ArrayValueData::Clone() const
{
  auto result = std::unique_ptr<ArrayValueData>(
      new ArrayValueData(NumberOfElements(), elem_type, name));
  result->elements = elements;
  return result.release();
}

TypeCode ArrayValueData::GetTypeCode() const
{
  return TypeCode::Array;
}

std::string ArrayValueData::GetTypeName() const
{
  return name;
}

AnyType ArrayValueData::GetType() const
{
  return AnyType(NumberOfElements(), elem_type, name);
}

std::size_t ArrayValueData::NumberOfElements() const
{
  return elements.size();
}

void ArrayValueData::Assign(const AnyValue& value)
{
  if (value.GetTypeCode() != TypeCode::Array)
  {
    IValueData::Assign(value);
  }
  if (value.NumberOfElements() != NumberOfElements())
  {
    throw InvalidConversionException("Can't convert between array values with different length");
  }
  for (std::size_t idx = 0; idx < NumberOfElements(); ++idx)
  {
    elements[idx] = value[idx];
  }
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
  return elements[idx];
}

bool ArrayValueData::Equals(const AnyValue& other) const
{
  if (other.GetType() != GetType())
  {
    return false;
  }
  for (std::size_t idx = 0; idx < NumberOfElements(); ++idx)
  {
    if (other[idx] != elements[idx])
    {
      return false;
    }
  }
  return true;
}

std::pair<std::size_t, std::string> StripValueIndex(const std::string& fieldname)
{
  if (fieldname.substr(0, 1) != "[")
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
  if (remainder.substr(pos, 1) != "]")
  {
    throw InvalidOperationException("Index operator argument for array value should be integer in "
                                 "square brackets");
  }
  if (remainder.substr(pos + 1, 1) == ".")
  {
    ++pos;
  }
  return { idx, remainder.substr(pos + 1) };
}

ArrayValueData* CreateArrayValueData(const AnyType& anytype)
{
  auto result = std::unique_ptr<ArrayValueData>(
    new ArrayValueData(anytype.NumberOfElements(), anytype.ElementType(), anytype.GetTypeName()));
  return result.release();
}

}  // namespace dto

}  // namespace sup
