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

#include "JSONSerializer.h"
#include "AnyValue.h"

#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

namespace sup
{
namespace dto
{

class JSONRepresentation
{
public:
  JSONRepresentation();
  ~JSONRepresentation();

  rapidjson::Writer<rapidjson::StringBuffer>& Writer();

  std::string GetString() const;

private:
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer;
};

JSONSerializer::JSONSerializer() = default;

JSONSerializer::~JSONSerializer() = default;

bool JSONSerializer::SerializeAnyType(const AnyType& anytype, IJSONWriter* writer)
{
  // construct IAnySerializer<AnyType> from the writer and call serialize
  return true;
}

bool JSONSerializer::SerializeAnyValue(const AnyValue& anyvalue, IJSONWriter* writer)
{
  // serialize type first
  // construct IAnySerializer<AnyValue> from the writer and call serialize
  return true;
}

JSONTypeSerializer::JSONTypeSerializer()
  : representation{new JSONRepresentation()}
{}
JSONTypeSerializer::~JSONTypeSerializer() = default;

void JSONTypeSerializer::ResetRepresentation()
{
  representation.reset(new JSONRepresentation());
}

std::string JSONTypeSerializer::GetRepresentation() const
{
  if (representation->Writer().IsComplete())
  {
    return representation->GetString();
  }
  return {};
}

void JSONTypeSerializer::AddEmptyProlog(const AnyType* anytype)
{
  representation->Writer().StartObject();
  representation->Writer().Key("type");
  auto type_name = anytype->GetTypeName();
  representation->Writer().String(type_name.c_str(), type_name.size());
}

void JSONTypeSerializer::AddEmptyEpilog(const AnyType*)
{
  representation->Writer().EndObject();
}

void JSONTypeSerializer::AddStructProlog(const AnyType* anytype)
{
  representation->Writer().StartObject();
  representation->Writer().Key("type");
  auto type_name = anytype->GetTypeName();
  representation->Writer().String(type_name.c_str(), type_name.size());
  representation->Writer().Key("attributes");
  representation->Writer().StartArray();
}

void JSONTypeSerializer::AddStructMemberSeparator()
{}

void JSONTypeSerializer::AddStructEpilog(const AnyType*)
{
  representation->Writer().EndArray();
  representation->Writer().EndObject();
}

void JSONTypeSerializer::AddMemberProlog(const AnyType* anytype, const std::string& member_name)
{
  representation->Writer().StartObject();
  representation->Writer().Key(member_name.c_str());
}

void JSONTypeSerializer::AddMemberEpilog(const AnyType*, const std::string&)
{
  representation->Writer().EndObject();
}

void JSONTypeSerializer::AddArrayProlog(const AnyType* anytype)
{
  representation->Writer().StartObject();
  representation->Writer().Key("type");
  auto type_name = anytype->GetTypeName();
  representation->Writer().String(type_name.c_str(), type_name.size());
  representation->Writer().Key("multiplicity");
  representation->Writer().Uint64(anytype->NumberOfElements());
  representation->Writer().Key("element");
}

void JSONTypeSerializer::AddArrayElementSeparator()
{}

void JSONTypeSerializer::AddArrayEpilog(const AnyType*)
{
  representation->Writer().EndObject();
}

void JSONTypeSerializer::AddScalarProlog(const AnyType* anytype)
{
  representation->Writer().StartObject();
  representation->Writer().Key("type");
  auto type_name = anytype->GetTypeName();
  representation->Writer().String(type_name.c_str(), type_name.size());
}

void JSONTypeSerializer::AddScalarEpilog(const AnyType*)
{
  representation->Writer().EndObject();
}

JSONValueSerializer::JSONValueSerializer()
  : representation{}
{}
JSONValueSerializer::~JSONValueSerializer() = default;

void JSONValueSerializer::ResetRepresentation()
{}

std::string JSONValueSerializer::GetRepresentation() const
{
  return {};
}

void JSONValueSerializer::AddEmptyProlog(const AnyValue*)
{}

void JSONValueSerializer::AddEmptyEpilog(const AnyValue*)
{}

void JSONValueSerializer::AddStructProlog(const AnyValue*)
{}

void JSONValueSerializer::AddStructMemberSeparator()
{}

void JSONValueSerializer::AddStructEpilog(const AnyValue*)
{}

void JSONValueSerializer::AddMemberProlog(const AnyValue*, const std::string&)
{}

void JSONValueSerializer::AddMemberEpilog(const AnyValue*, const std::string&)
{}

void JSONValueSerializer::AddArrayProlog(const AnyValue*)
{}

void JSONValueSerializer::AddArrayElementSeparator()
{}

void JSONValueSerializer::AddArrayEpilog(const AnyValue*)
{}

void JSONValueSerializer::AddScalarProlog(const AnyValue* anyvalue)
{}

void JSONValueSerializer::AddScalarEpilog(const AnyValue*)
{}

JSONRepresentation::JSONRepresentation()
  : buffer{}
  , writer{buffer}
{}

JSONRepresentation::~JSONRepresentation() = default;

rapidjson::Writer<rapidjson::StringBuffer>& JSONRepresentation::Writer()
{
  return writer;
}

std::string JSONRepresentation::GetString() const
{
  return buffer.GetString();
}

}  // namespace dto

}  // namespace sup
