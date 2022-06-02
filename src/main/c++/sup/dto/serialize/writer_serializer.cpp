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

#include "writer_serializer.h"
#include <sup/dto/anyvalue.h>
#include "serialization_constants.h"

namespace sup
{
namespace dto
{

WriterTypeSerializer::WriterTypeSerializer(IWriter* writer_)
  : writer{writer_}
{}
WriterTypeSerializer::~WriterTypeSerializer() = default;

void WriterTypeSerializer::EmptyProlog(const AnyType* anytype)
{
  writer->StartStructure();
  writer->Member(serialization::TYPE_KEY);
  auto type_name = anytype->GetTypeName();
  writer->String(type_name);
}

void WriterTypeSerializer::EmptyEpilog(const AnyType*)
{
  writer->EndStructure();
}

void WriterTypeSerializer::StructProlog(const AnyType* anytype)
{
  writer->StartStructure();
  writer->Member(serialization::TYPE_KEY);
  auto type_name = anytype->GetTypeName();
  writer->String(type_name);
  writer->Member(serialization::ATTRIBUTES_KEY);
  writer->StartArray();
}

void WriterTypeSerializer::StructMemberSeparator()
{}

void WriterTypeSerializer::StructEpilog(const AnyType*)
{
  writer->EndArray();
  writer->EndStructure();
}

void WriterTypeSerializer::MemberProlog(const AnyType* anytype, const std::string& member_name)
{
  writer->StartStructure();
  writer->Member(member_name);
}

void WriterTypeSerializer::MemberEpilog(const AnyType*, const std::string&)
{
  writer->EndStructure();
}

void WriterTypeSerializer::ArrayProlog(const AnyType* anytype)
{
  writer->StartStructure();
  writer->Member(serialization::TYPE_KEY);
  auto type_name = anytype->GetTypeName();
  writer->String(type_name);
  writer->Member(serialization::MULTIPLICITY_KEY);
  writer->Uint64(anytype->NumberOfElements());
  writer->Member(serialization::ELEMENT_KEY);
}

void WriterTypeSerializer::ArrayElementSeparator()
{}

void WriterTypeSerializer::ArrayEpilog(const AnyType*)
{
  writer->EndStructure();
}

void WriterTypeSerializer::UnboundedArrayProlog(const AnyType* anytype)
{
  writer->StartStructure();
  writer->Member(serialization::TYPE_KEY);
  auto type_name = anytype->GetTypeName();
  writer->String(type_name);
  writer->Member(serialization::ELEMENT_KEY);
}

void WriterTypeSerializer::UnboundedArrayEpilog(const AnyType*)
{
  writer->EndStructure();
}

void WriterTypeSerializer::ScalarProlog(const AnyType* anytype)
{
  writer->StartStructure();
  writer->Member(serialization::TYPE_KEY);
  auto type_name = anytype->GetTypeName();
  writer->String(type_name);
}

void WriterTypeSerializer::ScalarEpilog(const AnyType*)
{
  writer->EndStructure();
}

/**************************************/

WriterValueSerializer::WriterValueSerializer(IWriter* writer_)
  : writer{writer_}
{}
WriterValueSerializer::~WriterValueSerializer() = default;

void WriterValueSerializer::EmptyProlog(const AnyValue*)
{
  writer->Null();
}

void WriterValueSerializer::EmptyEpilog(const AnyValue*)
{}

void WriterValueSerializer::StructProlog(const AnyValue*)
{
  writer->StartStructure();
}

void WriterValueSerializer::StructMemberSeparator()
{}

void WriterValueSerializer::StructEpilog(const AnyValue*)
{
  writer->EndStructure();
}

void WriterValueSerializer::MemberProlog(const AnyValue*, const std::string& member_name)
{
  writer->Member(member_name);
}

void WriterValueSerializer::MemberEpilog(const AnyValue*, const std::string&)
{}

void WriterValueSerializer::ArrayProlog(const AnyValue*)
{
  writer->StartArray();
}

void WriterValueSerializer::ArrayElementSeparator()
{}

void WriterValueSerializer::ArrayEpilog(const AnyValue*)
{
  writer->EndArray();
}

void WriterValueSerializer::UnboundedArrayProlog(const AnyValue*)
{
  writer->StartArray();
}

void WriterValueSerializer::UnboundedArrayEpilog(const AnyValue*)
{
  writer->EndArray();
}

void WriterValueSerializer::ScalarProlog(const AnyValue* anyvalue)
{
  WriteScalarValue(*anyvalue, writer);
}

void WriterValueSerializer::ScalarEpilog(const AnyValue*)
{}

}  // namespace dto

}  // namespace sup
