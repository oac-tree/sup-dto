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
#include "SerializationConstants.h"

namespace sup
{
namespace dto
{

WriterTypeSerializer::WriterTypeSerializer(IWriter* writer_)
  : writer{writer_}
{}
WriterTypeSerializer::~WriterTypeSerializer() = default;

void WriterTypeSerializer::AddEmptyProlog(const AnyType* anytype)
{
  writer->StartStructure();
  writer->Member(serialization::TYPE_KEY);
  auto type_name = anytype->GetTypeName();
  writer->String(type_name);
}

void WriterTypeSerializer::AddEmptyEpilog(const AnyType*)
{
  writer->EndStructure();
}

void WriterTypeSerializer::AddStructProlog(const AnyType* anytype)
{
  writer->StartStructure();
  writer->Member(serialization::TYPE_KEY);
  auto type_name = anytype->GetTypeName();
  writer->String(type_name);
  writer->Member(serialization::ATTRIBUTES_KEY);
  writer->StartArray();
}

void WriterTypeSerializer::AddStructMemberSeparator()
{}

void WriterTypeSerializer::AddStructEpilog(const AnyType*)
{
  writer->EndArray();
  writer->EndStructure();
}

void WriterTypeSerializer::AddMemberProlog(const AnyType* anytype, const std::string& member_name)
{
  writer->StartStructure();
  writer->Member(member_name);
}

void WriterTypeSerializer::AddMemberEpilog(const AnyType*, const std::string&)
{
  writer->EndStructure();
}

void WriterTypeSerializer::AddArrayProlog(const AnyType* anytype)
{
  writer->StartStructure();
  writer->Member(serialization::TYPE_KEY);
  auto type_name = anytype->GetTypeName();
  writer->String(type_name);
  writer->Member(serialization::MULTIPLICITY_KEY);
  writer->Uint64(anytype->NumberOfElements());
  writer->Member(serialization::ELEMENT_KEY);
}

void WriterTypeSerializer::AddArrayElementSeparator()
{}

void WriterTypeSerializer::AddArrayEpilog(const AnyType*)
{
  writer->EndStructure();
}

void WriterTypeSerializer::AddScalarProlog(const AnyType* anytype)
{
  writer->StartStructure();
  writer->Member(serialization::TYPE_KEY);
  auto type_name = anytype->GetTypeName();
  writer->String(type_name);
}

void WriterTypeSerializer::AddScalarEpilog(const AnyType*)
{
  writer->EndStructure();
}

/**************************************/

WriterValueSerializer::WriterValueSerializer(IWriter* writer_)
  : writer{writer_}
{}
WriterValueSerializer::~WriterValueSerializer() = default;

void WriterValueSerializer::AddEmptyProlog(const AnyValue*)
{
  writer->Null();
}

void WriterValueSerializer::AddEmptyEpilog(const AnyValue*)
{}

void WriterValueSerializer::AddStructProlog(const AnyValue*)
{
  writer->StartStructure();
}

void WriterValueSerializer::AddStructMemberSeparator()
{}

void WriterValueSerializer::AddStructEpilog(const AnyValue*)
{
  writer->EndStructure();
}

void WriterValueSerializer::AddMemberProlog(const AnyValue*, const std::string& member_name)
{
  writer->Member(member_name);
}

void WriterValueSerializer::AddMemberEpilog(const AnyValue*, const std::string&)
{}

void WriterValueSerializer::AddArrayProlog(const AnyValue*)
{
  writer->StartArray();
}

void WriterValueSerializer::AddArrayElementSeparator()
{}

void WriterValueSerializer::AddArrayEpilog(const AnyValue*)
{
  writer->EndArray();
}

void WriterValueSerializer::AddScalarProlog(const AnyValue* anyvalue)
{
  WriteScalarValue(*anyvalue, writer);
}

void WriterValueSerializer::AddScalarEpilog(const AnyValue*)
{}

}  // namespace dto

}  // namespace sup
