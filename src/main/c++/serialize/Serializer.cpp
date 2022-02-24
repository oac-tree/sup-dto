/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : SUP - DTO
 *
 * Description   : Unit test code
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

#include "Serializer.h"
#include "AnyValue.h"
#include "SerializeT.h"
#include "WriterSerializer.h"

namespace sup
{
namespace dto
{

Serializer::Serializer() = default;

Serializer::~Serializer() = default;

bool Serializer::SerializeAnyType(const AnyType& anytype, IWriter* writer)
{
  WriterTypeSerializer serializer(writer);
  Serialize(anytype, serializer);
  return true;
}

bool Serializer::SerializeAnyValue(const AnyValue& anyvalue, IWriter* writer)
{
  WriterValueSerializer serializer(writer);
  Serialize(anyvalue, serializer);
  return true;
}

}  // namespace dto

}  // namespace sup
