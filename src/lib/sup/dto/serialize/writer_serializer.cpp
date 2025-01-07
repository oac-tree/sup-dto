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
 * Copyright (c) : 2010-2025 ITER Organization,
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

#include <sup/dto/parse/serialization_constants.h>

#include <sup/dto/anyvalue.h>

namespace sup
{
namespace dto
{

WriterTypeSerializer::WriterTypeSerializer(IWriter* writer)
  : m_writer{writer}
{}
WriterTypeSerializer::~WriterTypeSerializer() = default;

void WriterTypeSerializer::EmptyProlog(const AnyType* anytype)
{
  (void)m_writer->StartStructure();
  (void)m_writer->Member(serialization::TYPE_KEY);
  const auto type_name = anytype->GetTypeName();
  (void)m_writer->String(type_name);
}

void WriterTypeSerializer::EmptyEpilog(const AnyType*)
{
  (void)m_writer->EndStructure();
}

void WriterTypeSerializer::StructProlog(const AnyType* anytype)
{
  (void)m_writer->StartStructure();
  (void)m_writer->Member(serialization::TYPE_KEY);
  const auto type_name = anytype->GetTypeName();
  (void)m_writer->String(type_name);
  (void)m_writer->Member(serialization::ATTRIBUTES_KEY);
  (void)m_writer->StartArray();
}

void WriterTypeSerializer::StructMemberSeparator()
{}

void WriterTypeSerializer::StructEpilog(const AnyType*)
{
  (void)m_writer->EndArray();
  (void)m_writer->EndStructure();
}

void WriterTypeSerializer::MemberProlog(const AnyType*, const std::string& member_name)
{
  (void)m_writer->StartStructure();
  (void)m_writer->Member(member_name);
}

void WriterTypeSerializer::MemberEpilog(const AnyType*, const std::string&)
{
  (void)m_writer->EndStructure();
}

void WriterTypeSerializer::ArrayProlog(const AnyType* anytype)
{
  (void)m_writer->StartStructure();
  (void)m_writer->Member(serialization::TYPE_KEY);
  const auto type_name = anytype->GetTypeName();
  (void)m_writer->String(type_name);
  if (anytype->NumberOfElements() > 0)
  {
    (void)m_writer->Member(serialization::MULTIPLICITY_KEY);
    (void)m_writer->Uint64(anytype->NumberOfElements());
  }
  (void)m_writer->Member(serialization::ELEMENT_KEY);
}

void WriterTypeSerializer::ArrayElementSeparator()
{}

void WriterTypeSerializer::ArrayEpilog(const AnyType*)
{
  (void)m_writer->EndStructure();
}

void WriterTypeSerializer::ScalarProlog(const AnyType* anytype)
{
  (void)m_writer->StartStructure();
  (void)m_writer->Member(serialization::TYPE_KEY);
  const auto type_name = anytype->GetTypeName();
  (void)m_writer->String(type_name);
}

void WriterTypeSerializer::ScalarEpilog(const AnyType*)
{
  (void)m_writer->EndStructure();
}

/**************************************/

WriterValueSerializer::WriterValueSerializer(IWriter* writer)
  : m_writer{writer}
{}
WriterValueSerializer::~WriterValueSerializer() = default;

void WriterValueSerializer::EmptyProlog(const AnyValue*)
{
  (void)m_writer->Null();
}

void WriterValueSerializer::EmptyEpilog(const AnyValue*)
{}

void WriterValueSerializer::StructProlog(const AnyValue*)
{
  (void)m_writer->StartStructure();
}

void WriterValueSerializer::StructMemberSeparator()
{}

void WriterValueSerializer::StructEpilog(const AnyValue*)
{
  (void)m_writer->EndStructure();
}

void WriterValueSerializer::MemberProlog(const AnyValue*, const std::string& member_name)
{
  (void)m_writer->Member(member_name);
}

void WriterValueSerializer::MemberEpilog(const AnyValue*, const std::string&)
{}

void WriterValueSerializer::ArrayProlog(const AnyValue*)
{
  (void)m_writer->StartArray();
}

void WriterValueSerializer::ArrayElementSeparator()
{}

void WriterValueSerializer::ArrayEpilog(const AnyValue*)
{
  (void)m_writer->EndArray();
}

void WriterValueSerializer::ScalarProlog(const AnyValue* anyvalue)
{
  (void)WriteScalarValue(*anyvalue, m_writer);
}

void WriterValueSerializer::ScalarEpilog(const AnyValue*)
{}

}  // namespace dto

}  // namespace sup
