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

#include "UnboundedArrayValueData.h"

#include "ArrayValueData.h"
#include "AnyValueExceptions.h"

#include <utility>

namespace sup
{
namespace dto
{

UnboundedArrayValueData::UnboundedArrayValueData(const AnyType& elem_type_, const std::string& name_)
  : elem_type{elem_type_}
  , name{name_}
  , elements{}
{
  if (elem_type == EmptyType)
  {
    throw InvalidOperationException("Empty type is not allowed as element type");
  }
}

UnboundedArrayValueData::~UnboundedArrayValueData() = default;

UnboundedArrayValueData* UnboundedArrayValueData::Clone() const
{
  auto result = std::unique_ptr<UnboundedArrayValueData>(
    new UnboundedArrayValueData(elem_type, name));
  result->elements = elements;
  return result.release();
}

TypeCode UnboundedArrayValueData::GetTypeCode() const
{
  return TypeCode::UnboundedArray;
}

std::string UnboundedArrayValueData::GetTypeName() const
{
  return name;
}

AnyType UnboundedArrayValueData::GetType() const
{
  return AnyType(AnyType::unbounded_array_tag, elem_type, name);
}

void UnboundedArrayValueData::Append(const AnyValue& value)
{
  AnyValue copy{elem_type};
  copy = value;
  elements.push_back(std::move(copy));
}

std::size_t UnboundedArrayValueData::NumberOfElements() const
{
  return elements.size();
}

void UnboundedArrayValueData::Assign(const AnyValue& value)
{
  if (value.GetTypeCode() != TypeCode::UnboundedArray)
  {
    IValueData::Assign(value);
  }
  elements.clear();
  for (std::size_t idx = 0; idx < value.NumberOfElements(); ++idx)
  {
    AnyValue copy{elem_type};
    copy = value[idx];
    elements.push_back(std::move(copy));
  }
}

AnyValue& UnboundedArrayValueData::operator[](const std::string& fieldname)
{
  auto idx_remainder = StripValueIndex(fieldname);
  auto& element = this->operator[](idx_remainder.first);
  if (idx_remainder.second.empty())
  {
    return element;
  }
  return element[idx_remainder.second];
}

AnyValue& UnboundedArrayValueData::operator[](std::size_t idx)
{
  if (idx >= NumberOfElements())
  {
    throw InvalidOperationException("Index operator argument out of bounds");
  }
  return elements[idx];
}

bool UnboundedArrayValueData::Equals(const AnyValue& other) const
{
  if (other.GetType() != GetType())
  {
    return false;
  }
  if (other.NumberOfElements() != NumberOfElements())
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

UnboundedArrayValueData* CreateUnboundedArrayValueData(const AnyType& anytype)
{
  auto result = std::unique_ptr<UnboundedArrayValueData>(
    new UnboundedArrayValueData(anytype.ElementType(), anytype.GetTypeName()));
  return result.release();
}

}  // namespace dto

}  // namespace sup
