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

#include "IValueData.h"

#include "AnyValueExceptions.h"
#include "ITypeData.h"
#include "ScalarValueDataBase.h"

namespace sup
{
namespace dto
{

IValueData::~IValueData() = default;

std::string IValueData::GetTypeName() const
{
  return TypeCodeToString(GetTypeCode());
}

void IValueData::AddMember(const std::string&, const AnyValue&)
{
  throw InvalidOperationException("Add member only supported for structured types");
}

bool IValueData::HasMember(const std::string&) const
{
  return false;
}

std::vector<std::string> IValueData::MemberNames() const
{
  return {};
}

std::size_t IValueData::NumberOfMembers() const
{
  return 0;
}

void IValueData::Assign(const AnyValue&)
{
  throw InvalidConversionException("Cannot assign incompatible AnyValue");
}

boolean IValueData::AsBoolean() const
{
  throw InvalidConversionException("Conversion to boolean not supported for this type");
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

IValueData* CreateValueData(const AnyType& anytype)
{
  // TODO: add creation of structures
  return CreateScalarValueData(anytype.GetTypeCode());
}

}  // namespace dto

}  // namespace sup
