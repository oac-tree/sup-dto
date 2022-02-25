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

void SimpleAnyTypeSerializer::AddEmptyProlog(const AnyType* anytype)
{
  representation += "E(";
}

void SimpleAnyTypeSerializer::AddEmptyEpilog(const AnyType* anytype)
{
  representation += ")E";
}


void SimpleAnyTypeSerializer::AddStructProlog(const AnyType* anytype)
{
  representation += "S{";
}

void SimpleAnyTypeSerializer::AddStructMemberSeparator()
{
  representation += ",";
}

void SimpleAnyTypeSerializer::AddStructEpilog(const AnyType* anytype)
{
  representation += "}S";
}


void SimpleAnyTypeSerializer::AddMemberProlog(const AnyType* anytype, const std::string& member_name)
{
  std::string prolog = "M(" + member_name + ":";
  representation += prolog;
}

void SimpleAnyTypeSerializer::AddMemberEpilog(const AnyType* anytype, const std::string& member_name)
{
  representation += ")M";
}


void SimpleAnyTypeSerializer::AddArrayProlog(const AnyType* anytype)
{
  std::string prolog = "A[" + std::to_string(anytype->NumberOfElements()) + "|";
  representation += prolog;
}

void SimpleAnyTypeSerializer::AddArrayElementSeparator()
{
  representation += ",";
}

void SimpleAnyTypeSerializer::AddArrayEpilog(const AnyType* anytype)
{
  representation += "]A";
}


void SimpleAnyTypeSerializer::AddScalarProlog(const AnyType* anytype)
{
  representation += anytype->GetTypeName();
}

void SimpleAnyTypeSerializer::AddScalarEpilog(const AnyType*)
{}

SimpleAnyValueSerializer::SimpleAnyValueSerializer()
  : representation{}
{}
SimpleAnyValueSerializer::~SimpleAnyValueSerializer() = default;

std::string SimpleAnyValueSerializer::GetRepresentation() const
{
  return representation;
}

void SimpleAnyValueSerializer::AddEmptyProlog(const AnyValue* anyvalue)
{
  representation += "E(";
}

void SimpleAnyValueSerializer::AddEmptyEpilog(const AnyValue* anyvalue)
{
  representation += ")E";
}


void SimpleAnyValueSerializer::AddStructProlog(const AnyValue* anyvalue)
{
  representation += "S{";
}

void SimpleAnyValueSerializer::AddStructMemberSeparator()
{
  representation += ",";
}

void SimpleAnyValueSerializer::AddStructEpilog(const AnyValue* anyvalue)
{
  representation += "}S";
}


void SimpleAnyValueSerializer::AddMemberProlog(const AnyValue* anyvalue, const std::string& member_name)
{
  std::string prolog = "M(" + member_name + ":";
  representation += prolog;
}

void SimpleAnyValueSerializer::AddMemberEpilog(const AnyValue* anyvalue, const std::string& member_name)
{
  representation += ")M";
}


void SimpleAnyValueSerializer::AddArrayProlog(const AnyValue* anyvalue)
{
  std::string prolog = "A[" + std::to_string(anyvalue->NumberOfElements()) + "|";
  representation += prolog;
}

void SimpleAnyValueSerializer::AddArrayElementSeparator()
{
  representation += ",";
}

void SimpleAnyValueSerializer::AddArrayEpilog(const AnyValue* anyvalue)
{
  representation += "]A";
}


void SimpleAnyValueSerializer::AddScalarProlog(const AnyValue* anyvalue)
{
  representation += anyvalue->GetTypeName();
}

void SimpleAnyValueSerializer::AddScalarEpilog(const AnyValue*)
{}

}  // namespace dto

}  // namespace sup
