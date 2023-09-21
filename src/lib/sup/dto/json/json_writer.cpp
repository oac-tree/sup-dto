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

#include "json_writer.h"

#include <sup/dto/json/json_writer_t.h>
#include <sup/dto/parse/serialization_constants.h>
#include <sup/dto/serialize/writer_serializer.h>
#include <sup/dto/visit/visit_t.h>

#include <sup/dto/anytype.h>
#include <sup/dto/anyvalue.h>

namespace sup
{
namespace dto
{
namespace
{
std::unique_ptr<IWriter> CreateJSONWriter(std::ostream& out_stream);
std::unique_ptr<IWriter> CreatePrettyJSONWriter(std::ostream& out_stream);

void ToJSONWriter(IWriter& writer, const AnyValue& anyvalue);
void AddEncodingInformation(IWriter& writer);
void AddDatatypeStart(IWriter& writer);
void AddValueStart(IWriter& writer);
}


using JSONStringWriter = JSONStringWriterT<RapidJSONWriter>;
using PrettyJSONStringWriter = JSONStringWriterT<RapidJSONPrettyWriter>;

void JSONSerializeAnyType(std::ostream& json_stream, const AnyType& anytype, bool pretty)
{
  auto writer = pretty ? CreatePrettyJSONWriter(json_stream)
                       : CreateJSONWriter(json_stream);
  WriterTypeSerializer serializer(writer.get());
  Visit(anytype, serializer);
}

void JSONSerializeAnyType(std::ostream& json_stream, const AnyType& anytype)
{
  return JSONSerializeAnyType(json_stream, anytype, false);
}

void JSONSerializeAnyValue(std::ostream& json_stream, const AnyValue& anyvalue, bool pretty)
{
  auto writer = pretty ? CreatePrettyJSONWriter(json_stream)
                       : CreateJSONWriter(json_stream);
  ToJSONWriter(*writer, anyvalue);
}

void JSONSerializeAnyValue(std::ostream& json_stream, const AnyValue& anyvalue)
{
  return JSONSerializeAnyValue(json_stream, anyvalue, false);
}

void JSONSerializeAnyValueValues(std::ostream& json_stream, const AnyValue& anyvalue, bool pretty)
{
  auto writer = pretty ? CreatePrettyJSONWriter(json_stream)
                       : CreateJSONWriter(json_stream);
  WriterValueSerializer serializer(writer.get());
  Visit(anyvalue, serializer);
}

void JSONSerializeAnyValueValues(std::ostream& json_stream, const AnyValue& anyvalue)
{
  return JSONSerializeAnyValueValues(json_stream, anyvalue, false);
}

namespace
{
std::unique_ptr<IWriter> CreateJSONWriter(std::ostream& out_stream)
{
  return std::unique_ptr<IWriter>(new JSONStringWriter(out_stream));
}

std::unique_ptr<IWriter> CreatePrettyJSONWriter(std::ostream& out_stream)
{
  return std::unique_ptr<IWriter>(new PrettyJSONStringWriter(out_stream));
}

void ToJSONWriter(IWriter& writer, const AnyValue& anyvalue)
{
  writer.StartArray();
  AddEncodingInformation(writer);
  AddDatatypeStart(writer);
  WriterTypeSerializer type_serializer(&writer);
  Visit<const AnyType>(anyvalue.GetType(), type_serializer);
  writer.EndStructure();
  AddValueStart(writer);
  WriterValueSerializer value_serializer(&writer);
  Visit<const AnyValue>(anyvalue, value_serializer);
  writer.EndStructure();
  writer.EndArray();
}

void AddEncodingInformation(IWriter& writer)
{
  writer.StartStructure();
  writer.Member(serialization::ENCODING_KEY);
  writer.String(serialization::JSON_ENCODING_1_0);
  writer.EndStructure();
}

void AddDatatypeStart(IWriter& writer)
{
  writer.StartStructure();
  writer.Member(serialization::DATATYPE_KEY);
}

void AddValueStart(IWriter& writer)
{
  writer.StartStructure();
  writer.Member(serialization::INSTANCE_KEY);
}
}  // unnamed namespace

}  // namespace dto

}  // namespace sup
