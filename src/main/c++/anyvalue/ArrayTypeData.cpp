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

#include "ArrayTypeData.h"

#include "AnyValueExceptions.h"

namespace sup
{
namespace dto
{

static std::string StripIndex(const std::string& fieldname);

ArrayTypeData::ArrayTypeData(std::size_t size_, const AnyType& elem_type_, const std::string& name_)
  : size{size_}
  , elem_type{elem_type_}
  , name{name_}
{}

ArrayTypeData::~ArrayTypeData() = default;

ArrayTypeData* ArrayTypeData::Clone() const
{
  auto result = std::unique_ptr<ArrayTypeData>(new ArrayTypeData(size, elem_type, name));
  return result.release();
}

TypeCode ArrayTypeData::GetTypeCode() const
{
  return TypeCode::Array;
}

std::string ArrayTypeData::GetTypeName() const
{
  return name;
}

AnyType ArrayTypeData::ElementType() const
{
  return elem_type;
}

std::size_t ArrayTypeData::NumberOfElements() const
{
  return size;
}

AnyType& ArrayTypeData::operator[](const std::string& fieldname)
{
  auto remainder = StripIndex(fieldname);
  if (remainder.empty())
  {
    return elem_type;
  }
  return elem_type[remainder];
}

bool ArrayTypeData::Equals(const AnyType& other) const
{
  if (other.GetTypeCode() != TypeCode::Array)
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
  return other.ElementType() == ElementType();
}

static std::string StripIndex(const std::string& fieldname)
{
  if (fieldname.substr(0, 2) != "[]")
  {
    throw KeyNotAllowedException("Index operator argument for array type should start with []");
  }
  std::string result = fieldname.substr(2);
  if (result.size() > 0 && result[0] == '.')
  {
    result = result.substr(1);
  }
  return result;
}

}  // namespace dto

}  // namespace sup
