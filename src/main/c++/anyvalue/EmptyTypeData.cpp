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

#include "EmptyTypeData.h"

#include <stdexcept>

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

AnyType& EmptyTypeData::operator[](std::string fieldname)
{
  throw std::out_of_range("Index operator not supported for empty type");
}

const AnyType& EmptyTypeData::operator[](std::string fieldname) const
{
  throw std::out_of_range("Index operator not supported for empty type");
}

}  // namespace dto

}  // namespace sup
