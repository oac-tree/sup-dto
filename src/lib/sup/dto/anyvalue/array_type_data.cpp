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
 * Copyright (c) : 2010-2026 ITER Organization,
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

#include "array_type_data.h"

#include <sup/dto/anyvalue_exceptions.h>

namespace
{
const std::string kArrayTypeChildName = "[]";  // fieldname of the only child
}

namespace sup
{
namespace dto
{

ArrayTypeData::ArrayTypeData(std::size_t size, AnyType&& elem_type, const std::string& name)
  : ITypeData{}
  , m_size{size}
  , m_elem_type{std::move(elem_type)}
  , m_name{name}
{}

ArrayTypeData::~ArrayTypeData() = default;

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

std::size_t ArrayTypeData::NumberOfChildren() const
{
  return 1u;
}

bool ArrayTypeData::HasChild(const std::string& child_name) const
{
  return child_name == kArrayTypeChildName;
}

AnyType* ArrayTypeData::GetChildType(const std::string& child_name)
{
  if (child_name != kArrayTypeChildName)
  {
    const std::string error =
      "ArrayTypeData::GetChildType() called with argument \"" + child_name +
      "\", while it only supports \"" + kArrayTypeChildName + "\"";
    throw InvalidOperationException(error);
  }
  return std::addressof(m_elem_type);
}

AnyType* ArrayTypeData::GetChildType(std::size_t idx)
{
  if (idx != 0)
  {
    const std::string error =
      "ArrayTypeData::GetChildType() called with non-zero index";
    throw InvalidOperationException(error);
  }
  return std::addressof(m_elem_type);
}

std::unique_ptr<ITypeData> ArrayTypeData::CloneFromChildren(
  std::vector<std::unique_ptr<AnyType>>&& children) const
{
  auto elem_typ = std::move(children[0]);
  return std::make_unique<ArrayTypeData>(m_size, std::move(*elem_typ), m_name);
}

bool ArrayTypeData::ShallowEquals(const AnyType& other) const
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
  return true;
}

}  // namespace dto

}  // namespace sup
