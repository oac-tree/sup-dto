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

#include "empty_value_data.h"
#include "i_value_data.h"

#include <sup/dto/anyvalue/empty_type_data.h>

#include <sup/dto/anyvalue_exceptions.h>

namespace sup
{
namespace dto
{

EmptyValueData::EmptyValueData(Constraints constraints)
  : m_constraints{constraints}
{}

EmptyValueData::~EmptyValueData() = default;

std::unique_ptr<IValueData> EmptyValueData::Clone(Constraints constraints) const
{
  return std::unique_ptr<IValueData>{new EmptyValueData(constraints)};
}

TypeCode EmptyValueData::GetTypeCode() const
{
  return TypeCode::Empty;
}

AnyType EmptyValueData::GetType() const
{
  return AnyType{};
}

Constraints EmptyValueData::GetConstraints() const
{
  return m_constraints;
}

void EmptyValueData::ConvertFrom(const AnyValue& value)
{
  if (!IsEmptyValue(value))
  {
    return IValueData::ConvertFrom(value);
  }
}

bool EmptyValueData::Equals(const AnyValue& other) const
{
  return other.GetTypeCode() == TypeCode::Empty;
}

std::unique_ptr<IValueData> CreateDefaultValueData()
{
  return std::unique_ptr<IValueData>{new EmptyValueData{Constraints::kNone}};
}

}  // namespace dto

}  // namespace sup
