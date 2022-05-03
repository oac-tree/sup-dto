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

#include "UnboundedArrayTypeData.h"

#include "AnyValueExceptions.h"

namespace sup
{
namespace dto
{

static std::string StripIndex(const std::string& fieldname);

UnboundedArrayTypeData::UnboundedArrayTypeData(const AnyType& elem_type_, const std::string& name_)
  : elem_type{elem_type_}
  , name{name_}
{
  if (elem_type == EmptyType)
  {
    throw InvalidOperationException("Empty type is not allowed as element type");
  }
}

UnboundedArrayTypeData::~UnboundedArrayTypeData() = default;

UnboundedArrayTypeData* UnboundedArrayTypeData::Clone() const
{
  auto result = std::unique_ptr<UnboundedArrayTypeData>(
      new UnboundedArrayTypeData(elem_type, name));
  return result.release();
}

TypeCode UnboundedArrayTypeData::GetTypeCode() const
{
  return TypeCode::UnboundedArray;
}

std::string UnboundedArrayTypeData::GetTypeName() const
{
  return name;
}

AnyType UnboundedArrayTypeData::ElementType() const
{
  return elem_type;
}

AnyType& UnboundedArrayTypeData::operator[](const std::string& fieldname)
{
  auto remainder = StripIndex(fieldname);
  if (remainder.empty())
  {
    return elem_type;
  }
  return elem_type[remainder];
}

bool UnboundedArrayTypeData::Equals(const AnyType& other) const
{
  if (other.GetTypeCode() != TypeCode::UnboundedArray)
  {
    return false;
  }
  if (other.GetTypeName() != GetTypeName())
  {
    return false;
  }
  return other.ElementType() == ElementType();
}

static std::string StripIndex(const std::string& fieldname)
{
  if (fieldname.substr(0, 2) != "[]")
  {
    throw InvalidOperationException("Index operator argument for array type should start with []");
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
