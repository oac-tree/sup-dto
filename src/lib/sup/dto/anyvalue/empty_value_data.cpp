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

#include "empty_value_data.h"

#include <sup/dto/anyvalue/empty_type_data.h>

#include <sup/dto/anyvalue_exceptions.h>

namespace sup
{
namespace dto
{

EmptyValueData::EmptyValueData(value_flags::Constraints constraints)
  : m_constraints{constraints}
{}

EmptyValueData::~EmptyValueData() = default;

EmptyValueData* EmptyValueData::Clone() const
{
  return new EmptyValueData(m_constraints);
}

TypeCode EmptyValueData::GetTypeCode() const
{
  return TypeCode::Empty;
}

AnyType EmptyValueData::GetType() const
{
  return AnyType{};
}

value_flags::Constraints EmptyValueData::GetConstraints() const
{
  return m_constraints;
}

bool EmptyValueData::Equals(const AnyValue& other) const
{
  return other.GetTypeCode() == TypeCode::Empty;
}

IValueData* CreateDefaultValueData()
{
  return new EmptyValueData{value_flags::kNone};
}

}  // namespace dto

}  // namespace sup
