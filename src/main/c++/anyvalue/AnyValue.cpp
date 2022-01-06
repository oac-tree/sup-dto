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

}  // namespace dto

}  // namespace sup
