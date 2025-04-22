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
 * SPDX-License-Identifier: MIT
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file LICENSE located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include "i_value_data.h"

#include <sup/dto/anyvalue/array_value_data.h>
#include <sup/dto/anyvalue/empty_value_data.h>
#include <sup/dto/anyvalue/i_type_data.h>
#include <sup/dto/anyvalue/scalar_value_data_base.h>
#include <sup/dto/anyvalue/struct_value_data.h>

#include <sup/dto/anyvalue_exceptions.h>

namespace sup
{
namespace dto
{

IValueData::~IValueData() = default;

bool IValueData::IsScalar() const
{
  return false;
}

void IValueData::AddMember(const std::string&, std::unique_ptr<AnyValue>&&)
{
  throw InvalidOperationException("Add member only supported for structured types");
}

std::vector<std::string> IValueData::MemberNames() const
{
  return {};
}

std::size_t IValueData::NumberOfMembers() const
{
  return 0u;
}

void IValueData::AddElement(std::unique_ptr<AnyValue>&&)
{
  throw InvalidOperationException("Add element only supported for array types");
}

std::size_t IValueData::NumberOfElements() const
{
  return 0u;
}

AnyType IValueData::ElementType() const
{
  throw InvalidOperationException("Element type only supported for array types");
}

boolean IValueData::AsBoolean() const
{
  throw InvalidConversionException("Conversion to boolean not supported for this type");
}

char8 IValueData::AsCharacter8() const
{
  throw InvalidConversionException("Conversion to char8 not supported for this type");
}

int8 IValueData::AsSignedInteger8() const
{
  throw InvalidConversionException("Conversion to int8 not supported for this type");
}

uint8 IValueData::AsUnsignedInteger8() const
{
  throw InvalidConversionException("Conversion to uint8 not supported for this type");
}

int16 IValueData::AsSignedInteger16() const
{
  throw InvalidConversionException("Conversion to int16 not supported for this type");
}

uint16 IValueData::AsUnsignedInteger16() const
{
  throw InvalidConversionException("Conversion to uint16 not supported for this type");
}

int32 IValueData::AsSignedInteger32() const
{
  throw InvalidConversionException("Conversion to int32 not supported for this type");
}

uint32 IValueData::AsUnsignedInteger32() const
{
  throw InvalidConversionException("Conversion to uint32 not supported for this type");
}

int64 IValueData::AsSignedInteger64() const
{
  throw InvalidConversionException("Conversion to int64 not supported for this type");
}

uint64 IValueData::AsUnsignedInteger64() const
{
  throw InvalidConversionException("Conversion to uint64 not supported for this type");
}

float32 IValueData::AsFloat32() const
{
  throw InvalidConversionException("Conversion to float32 not supported for this type");
}

float64 IValueData::AsFloat64() const
{
  throw InvalidConversionException("Conversion to float64 not supported for this type");
}

std::string IValueData::AsString() const
{
  throw InvalidConversionException("Conversion to string not supported for this type");
}

AnyValue& IValueData::operator[](std::size_t )
{
  throw InvalidOperationException("Member access operator with unsigned index not supported");
}

std::size_t IValueData::NumberOfChildren() const
{
  return 0u;
}

bool IValueData::HasChild(const std::string&) const
{
  return false;
}

AnyValue* IValueData::GetChildValue(const std::string&)
{
  throw InvalidOperationException("This value does not support members or elements");
}

AnyValue* IValueData::GetChildValue(std::size_t)
{
  throw InvalidOperationException("This value does not support members or elements");
}

bool IValueData::ScalarEquals(const IValueData*) const
{
  return false;
}

void IValueData::ShallowConvertFrom(const AnyValue&)
{
  throw InvalidConversionException("Cannot convert from incompatible AnyValue");
}

bool IsLockedTypeConstraint(Constraints constraints)
{
  return constraints == Constraints::kLockedType;
}

}  // namespace dto

}  // namespace sup
