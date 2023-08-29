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

#include "empty_type_data.h"

#include <sup/dto/anyvalue_exceptions.h>

namespace sup
{
namespace dto
{

EmptyTypeData::EmptyTypeData() = default;

EmptyTypeData::~EmptyTypeData() = default;

EmptyTypeData* EmptyTypeData::Clone() const
{
  return new EmptyTypeData();
}

TypeCode EmptyTypeData::GetTypeCode() const
{
  return TypeCode::Empty;
}

std::string EmptyTypeData::GetTypeName() const
{
  return kEmptyTypeName;
}

bool EmptyTypeData::Equals(const AnyType& other) const
{
  return other.GetTypeCode() == TypeCode::Empty;
}

}  // namespace dto

}  // namespace sup
