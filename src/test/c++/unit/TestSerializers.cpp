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

#include "TestSerializers.h"
#include "AnyType.h"
#include "AnyValue.h"

namespace sup
{
namespace dto
{

SimpleAnyTypeSerializer::SimpleAnyTypeSerializer()
  : representation{}
{}
SimpleAnyTypeSerializer::~SimpleAnyTypeSerializer() = default;

std::string SimpleAnyTypeSerializer::GetRepresentation() const
{
  return representation;
}

void SimpleAnyTypeSerializer::EmptyProlog(const AnyType* anytype)
{
  representation += "E(";
}

void SimpleAnyTypeSerializer::EmptyEpilog(const AnyType* anytype)
{
  representation += ")E";
}


void SimpleAnyTypeSerializer::StructProlog(const AnyType* anytype)
{
  representation += "S{";
}

void SimpleAnyTypeSerializer::StructMemberSeparator()
{
  representation += ",";
}

void SimpleAnyTypeSerializer::StructEpilog(const AnyType* anytype)
{
  representation += "}S";
}


void SimpleAnyTypeSerializer::MemberProlog(const AnyType* anytype, const std::string& member_name)
{
  std::string prolog = "M(" + member_name + ":";
  representation += prolog;
}

void SimpleAnyTypeSerializer::AddMemberEpilog(const AnyType* anytype, const std::string& member_name)
{
  representation += ")M";
}


void SimpleAnyTypeSerializer::ArrayProlog(const AnyType* anytype)
{
  std::string prolog = "A[" + std::to_string(anytype->NumberOfElements()) + "|";
  representation += prolog;
}

void SimpleAnyTypeSerializer::ArrayElementSeparator()
{
  representation += ",";
}

void SimpleAnyTypeSerializer::ArrayEpilog(const AnyType* anytype)
{
  representation += "]A";
}


void SimpleAnyTypeSerializer::ScalarProlog(const AnyType* anytype)
{
  representation += anytype->GetTypeName();
}

void SimpleAnyTypeSerializer::ScalarEpilog(const AnyType*)
{}

SimpleAnyValueSerializer::SimpleAnyValueSerializer()
  : representation{}
{}
SimpleAnyValueSerializer::~SimpleAnyValueSerializer() = default;

std::string SimpleAnyValueSerializer::GetRepresentation() const
{
  return representation;
}

void SimpleAnyValueSerializer::EmptyProlog(const AnyValue* anyvalue)
{
  representation += "E(";
}

void SimpleAnyValueSerializer::EmptyEpilog(const AnyValue* anyvalue)
{
  representation += ")E";
}


void SimpleAnyValueSerializer::StructProlog(const AnyValue* anyvalue)
{
  representation += "S{";
}

void SimpleAnyValueSerializer::StructMemberSeparator()
{
  representation += ",";
}

void SimpleAnyValueSerializer::StructEpilog(const AnyValue* anyvalue)
{
  representation += "}S";
}


void SimpleAnyValueSerializer::MemberProlog(const AnyValue* anyvalue, const std::string& member_name)
{
  std::string prolog = "M(" + member_name + ":";
  representation += prolog;
}

void SimpleAnyValueSerializer::AddMemberEpilog(const AnyValue* anyvalue, const std::string& member_name)
{
  representation += ")M";
}


void SimpleAnyValueSerializer::ArrayProlog(const AnyValue* anyvalue)
{
  std::string prolog = "A[" + std::to_string(anyvalue->NumberOfElements()) + "|";
  representation += prolog;
}

void SimpleAnyValueSerializer::ArrayElementSeparator()
{
  representation += ",";
}

void SimpleAnyValueSerializer::ArrayEpilog(const AnyValue* anyvalue)
{
  representation += "]A";
}


void SimpleAnyValueSerializer::ScalarProlog(const AnyValue* anyvalue)
{
  representation += anyvalue->GetTypeName();
}

void SimpleAnyValueSerializer::ScalarEpilog(const AnyValue*)
{}

}  // namespace dto

}  // namespace sup
