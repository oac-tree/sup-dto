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

#include "empty_type_data.h"

#include <sup/dto/anyvalue_exceptions.h>

namespace sup
{
namespace dto
{

EmptyTypeData::EmptyTypeData() = default;

EmptyTypeData::~EmptyTypeData() = default;

TypeCode EmptyTypeData::GetTypeCode() const
{
  return TypeCode::Empty;
}

std::string EmptyTypeData::GetTypeName() const
{
  return kEmptyTypeName;
}

std::unique_ptr<ITypeData> EmptyTypeData::CloneFromChildren(
  std::vector<std::unique_ptr<AnyType>>&&) const
{
  return std::make_unique<EmptyTypeData>();
}

bool EmptyTypeData::ShallowEquals(const AnyType& other) const
{
  return IsEmptyType(other);
}

std::unique_ptr<ITypeData> CreateDefaultTypeData()
{
  return std::make_unique<EmptyTypeData>();
}

}  // namespace dto

}  // namespace sup
