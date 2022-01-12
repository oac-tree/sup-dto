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
 * Copyright (c) : 2010-2021 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include "AnyValue.h"

#include "EmptyValueData.h"

namespace sup
{
namespace dto
{

AnyValue::AnyValue()
  : data{new EmptyValueData{}}
{}

AnyValue::AnyValue(const AnyValue& other)
  : data{other.data->Clone()}
{}

AnyValue& AnyValue::operator=(const AnyValue& other)
{
  if (this != &other)
  {
    data.reset(other.data->Clone());
  }
  return *this;
}

AnyValue::AnyValue(AnyValue&& other)
  : data{other.data.release()}
{
  other.data.reset(new EmptyValueData());
}

AnyValue& AnyValue::operator=(AnyValue&& other)
{
  if (this != &other)
  {
    data.reset(other.data.release());
    other.data.reset(new EmptyValueData());
  }
  return *this;
}

AnyValue::~AnyValue() = default;

TypeCode AnyValue::GetTypeCode() const
{
  return data->GetTypeCode();
}

AnyType AnyValue::GetType() const
{
  return data->GetType();
}

std::string AnyValue::GetTypeName() const
{
  return data->GetTypeName();
}

AnyValue& AnyValue::operator[](std::string fieldname)
{
  return (*data)[fieldname];
}

const AnyValue& AnyValue::operator[](std::string fieldname) const
{
  return (*data)[fieldname];
}

bool AnyValue::operator==(const AnyValue& other) const
{
  return data->Equals(other.data.get());
}

bool AnyValue::operator!=(const AnyValue& other) const
{
  return !(this->operator==(other));
}

template <>
boolean AnyValue::As<boolean>() const
{
  return data->AsBoolean();
}

template <>
int8 AnyValue::As<int8>() const
{
  return data->AsSignedInteger8();
}

template <>
uint8 AnyValue::As<uint8>() const
{
  return data->AsUnsignedInteger8();
}

bool IsEmptyValue(const AnyValue& anyvalue)
{
  return IsEmptyTypeCode(anyvalue.GetTypeCode());
}

bool IsStructValue(const AnyValue& anyvalue)
{
  return IsStructTypeCode(anyvalue.GetTypeCode());
}

bool IsArrayValue(const AnyValue& anyvalue)
{
  return IsArrayTypeCode(anyvalue.GetTypeCode());
}

bool IsScalarValue(const AnyValue& anyvalue)
{
  return IsScalarTypeCode(anyvalue.GetTypeCode());
}

}  // namespace dto

}  // namespace sup
