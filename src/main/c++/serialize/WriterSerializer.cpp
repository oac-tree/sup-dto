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

#include "WriterSerializer.h"
#include "AnyValue.h"

namespace sup
{
namespace dto
{

WriterTypeSerializer::WriterTypeSerializer(IWriter* writer_)
  : writer{writer_}
{}
WriterTypeSerializer::~WriterTypeSerializer() = default;

void WriterTypeSerializer::ResetRepresentation()
{}

void WriterTypeSerializer::AddEmptyProlog(const AnyType* anytype)
{
  writer->StartObject();
  writer->Key("type");
  auto type_name = anytype->GetTypeName();
  writer->String(type_name);
}

void WriterTypeSerializer::AddEmptyEpilog(const AnyType*)
{
  writer->EndObject();
}

void WriterTypeSerializer::AddStructProlog(const AnyType* anytype)
{
  writer->StartObject();
  writer->Key("type");
  auto type_name = anytype->GetTypeName();
  writer->String(type_name);
  writer->Key("attributes");
  writer->StartArray();
}

void WriterTypeSerializer::AddStructMemberSeparator()
{}

void WriterTypeSerializer::AddStructEpilog(const AnyType*)
{
  writer->EndArray();
  writer->EndObject();
}

void WriterTypeSerializer::AddMemberProlog(const AnyType* anytype, const std::string& member_name)
{
  writer->StartObject();
  writer->Key(member_name);
}

void WriterTypeSerializer::AddMemberEpilog(const AnyType*, const std::string&)
{
  writer->EndObject();
}

void WriterTypeSerializer::AddArrayProlog(const AnyType* anytype)
{
  writer->StartObject();
  writer->Key("type");
  auto type_name = anytype->GetTypeName();
  writer->String(type_name);
  writer->Key("multiplicity");
  writer->Uint64(anytype->NumberOfElements());
  writer->Key("element");
}

void WriterTypeSerializer::AddArrayElementSeparator()
{}

void WriterTypeSerializer::AddArrayEpilog(const AnyType*)
{
  writer->EndObject();
}

void WriterTypeSerializer::AddScalarProlog(const AnyType* anytype)
{
  writer->StartObject();
  writer->Key("type");
  auto type_name = anytype->GetTypeName();
  writer->String(type_name);
}

void WriterTypeSerializer::AddScalarEpilog(const AnyType*)
{
  writer->EndObject();
}

WriterValueSerializer::WriterValueSerializer(IWriter* writer_)
  : writer{writer_}
{}
WriterValueSerializer::~WriterValueSerializer() = default;

void WriterValueSerializer::ResetRepresentation()
{}

void WriterValueSerializer::AddEmptyProlog(const AnyValue*)
{}

void WriterValueSerializer::AddEmptyEpilog(const AnyValue*)
{}

void WriterValueSerializer::AddStructProlog(const AnyValue*)
{}

void WriterValueSerializer::AddStructMemberSeparator()
{}

void WriterValueSerializer::AddStructEpilog(const AnyValue*)
{}

void WriterValueSerializer::AddMemberProlog(const AnyValue*, const std::string&)
{}

void WriterValueSerializer::AddMemberEpilog(const AnyValue*, const std::string&)
{}

void WriterValueSerializer::AddArrayProlog(const AnyValue*)
{}

void WriterValueSerializer::AddArrayElementSeparator()
{}

void WriterValueSerializer::AddArrayEpilog(const AnyValue*)
{}

void WriterValueSerializer::AddScalarProlog(const AnyValue* anyvalue)
{}

void WriterValueSerializer::AddScalarEpilog(const AnyValue*)
{}

}  // namespace dto

}  // namespace sup
