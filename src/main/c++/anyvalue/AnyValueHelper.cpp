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

#include "AnyValueHelper.h"
#include "AnyValue.h"
#include "ByteSerializer.h"
#include "JSONWriter.h"
#include "SerializeT.h"
#include "WriterSerializer.h"

namespace sup
{
namespace dto
{

void SerializeAnyValue(const AnyValue& anyvalue, IAnySerializer<AnyValue>& serializer)
{
  return Serialize(anyvalue, serializer);
}

std::vector<uint8> ToBytes(const AnyValue& anyvalue)
{
  ByteSerializer serializer;
  SerializeAnyValue(anyvalue, serializer);
  return serializer.GetRepresentation();
}

std::string ToJSONString(const AnyValue& anyvalue)
{
  // TODO: serialize type first
  JSONStringWriter writer;
  WriterValueSerializer serializer(&writer);
  SerializeAnyValue(anyvalue, serializer);
  return writer.GetRepresentation();
}

}  // namespace dto

}  // namespace sup
