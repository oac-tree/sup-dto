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

std::unique_ptr<IValueData> EmptyValueData::CloneFromChildren(
  std::vector<std::unique_ptr<AnyValue>>&& children, Constraints constraints) const
{
  if (!children.empty())
  {
    const std::string error =
      "EmptyValueData::CloneFromChildren(): Trying to clone empty value with child values";
    throw InvalidOperationException(error);
  }
  return std::make_unique<EmptyValueData>(constraints);
}

bool EmptyValueData::ShallowEquals(const IValueData* other) const
{
  return IsEmptyTypeCode(other->GetTypeCode());
}

std::unique_ptr<IValueData> CreateDefaultValueData()
{
  return std::make_unique<EmptyValueData>(Constraints::kNone);
}

void EmptyValueData::ShallowConvertFrom(const AnyValue& value)
{
  if (!IsEmptyValue(value))
  {
    return IValueData::ShallowConvertFrom(value);
  }
}

}  // namespace dto

}  // namespace sup
