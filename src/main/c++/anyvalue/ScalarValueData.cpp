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

#include "ScalarValueData.h"

#include "AnyValueExceptions.h"

namespace sup
{
namespace dto
{

ScalarValueData::ScalarValueData(TypeCode type_code_)
  : type_code{type_code_}
{}

ScalarValueData::~ScalarValueData() = default;

ScalarValueData* ScalarValueData::Clone() const
{
  return new ScalarValueData(type_code);
}

TypeCode ScalarValueData::GetTypeCode() const
{
  return type_code;
}

AnyType ScalarValueData::GetType() const
{
  return AnyType(type_code);
}

AnyValue& ScalarValueData::operator[](const std::string& fieldname)
{
  throw KeyNotAllowedException("Index operator not supported for scalar values");
}

const AnyValue& ScalarValueData::operator[](const std::string& fieldname) const
{
  throw KeyNotAllowedException("Index operator not supported for scalar values");
}

bool ScalarValueData::Equals(const IValueData* other) const
{
  return other->GetTypeCode() == GetTypeCode();
}

}  // namespace dto

}  // namespace sup
