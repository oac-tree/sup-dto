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
#include "AnyTypeHelper.h"
#include "AnyValue.h"
#include "ByteSerializer.h"
#include "JSONWriter.h"
#include "SerializeT.h"
#include "WriterSerializer.h"

namespace sup
{
namespace dto
{
namespace
{
void ToJSONWriter(IWriter& writer, const AnyValue& anyvalue);
void AddEncodingInformation(IWriter& writer);
void AddDatatypeStart(IWriter& writer);
void AddValueStart(IWriter& writer);
}

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

std::string ValuesToJSONString(const AnyValue& anyvalue)
{
  auto writer = CreateJSONStringWriter();
  WriterValueSerializer serializer(writer.get());
  SerializeAnyValue(anyvalue, serializer);
  return writer->GetRepresentation();
}

std::string ToJSONString(const AnyValue& anyvalue)
{
  auto writer = CreateJSONStringWriter();
  ToJSONWriter(*writer, anyvalue);
  return writer->GetRepresentation();
}

std::string ToPrettyJSONString(const AnyValue& anyvalue)
{
  auto writer = CreatePrettyJSONStringWriter();
  ToJSONWriter(*writer, anyvalue);
  return writer->GetRepresentation();
}

namespace
{
void ToJSONWriter(IWriter& writer, const AnyValue& anyvalue)
{
  writer.StartStructure();
  AddEncodingInformation(writer);
  AddDatatypeStart(writer);
  WriterTypeSerializer type_serializer(&writer);
  SerializeAnyType(anyvalue.GetType(), type_serializer);
  AddValueStart(writer);
  WriterValueSerializer value_serializer(&writer);
  SerializeAnyValue(anyvalue, value_serializer);
  writer.EndStructure();
}

void AddEncodingInformation(IWriter& writer)
{
  writer.Member("encoding");
  writer.String("sup-dto/v1.0/JSON");
}

void AddDatatypeStart(IWriter& writer)
{
  writer.Member("datatype");
}

void AddValueStart(IWriter& writer)
{
  writer.Member("instance");
}
}

}  // namespace dto

}  // namespace sup
