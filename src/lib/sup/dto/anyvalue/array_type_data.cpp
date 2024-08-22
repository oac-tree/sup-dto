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
 * Copyright (c) : 2010-2023 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include "array_type_data.h"

#include <sup/dto/anyvalue_exceptions.h>

namespace
{
const sup::dto::uint32 kBracketsSize = 2u;
}

namespace sup
{
namespace dto
{

ArrayTypeData::ArrayTypeData(std::size_t size, const AnyType& elem_type, const std::string& name)
  : m_size{size}
  , m_elem_type{elem_type}
  , m_name{name}
{}

ArrayTypeData::~ArrayTypeData() = default;

std::unique_ptr<ITypeData> ArrayTypeData::Clone() const
{
  return std::unique_ptr<ITypeData>(new ArrayTypeData(m_size, m_elem_type, m_name));
}

TypeCode ArrayTypeData::GetTypeCode() const
{
  return TypeCode::Array;
}

std::string ArrayTypeData::GetTypeName() const
{
  return m_name;
}

AnyType ArrayTypeData::ElementType() const
{
  return m_elem_type;
}

std::size_t ArrayTypeData::NumberOfElements() const
{
  return m_size;
}

bool ArrayTypeData::HasField(const std::string& fieldname) const
{
  std::string remainder;
  try
  {
    remainder = StripTypeIndex(fieldname);
  }
  catch(const InvalidOperationException&)
  {
    return false;
  }
  if (remainder.empty())
  {
    return true;
  }
  return m_elem_type.HasField(remainder);
}

AnyType& ArrayTypeData::operator[](const std::string& fieldname) &
{
  const auto remainder = StripTypeIndex(fieldname);
  if (remainder.empty())
  {
    return m_elem_type;
  }
  return m_elem_type[remainder];
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

std::string StripTypeIndex(const std::string& fieldname)
{
  if ((fieldname.size() < kBracketsSize) || (fieldname.substr(0u, kBracketsSize) != "[]"))
  {
    throw InvalidOperationException("Index operator argument for array type should start with []");
  }
  auto result = fieldname.substr(kBracketsSize);
  if (!result.empty() && (result[0u] == '.'))
  {
    result = result.substr(1u);
  }
  return result;
}

}  // namespace dto

}  // namespace sup
