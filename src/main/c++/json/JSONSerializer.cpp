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

namespace sup
{
namespace dto
{

class JSONRepresentation
{
public:
  JSONRepresentation() = default;
  ~JSONRepresentation() = default;
};

JSONTypeSerializer::JSONTypeSerializer()
  : representation{}
{}
JSONTypeSerializer::~JSONTypeSerializer() = default;

void JSONTypeSerializer::ResetRepresentation()
{}

std::string JSONTypeSerializer::GetRepresentation() const
{
  return {};
}

void JSONTypeSerializer::AddEmptyProlog(const AnyType* anytype)
{
}

void JSONTypeSerializer::AddEmptyEpilog(const AnyType* anytype)
{
}

void JSONTypeSerializer::AddStructProlog(const AnyType* anytype)
{
}

void JSONTypeSerializer::AddStructMemberSeparator()
{
}

void JSONTypeSerializer::AddStructEpilog(const AnyType* anytype)
{
}

void JSONTypeSerializer::AddMemberProlog(const AnyType* anytype, const std::string& member_name)
{
}

void JSONTypeSerializer::AddMemberEpilog(const AnyType* anytype, const std::string& member_name)
{
}

void JSONTypeSerializer::AddArrayProlog(const AnyType* anytype)
{
}

void JSONTypeSerializer::AddArrayElementSeparator()
{
}

void JSONTypeSerializer::AddArrayEpilog(const AnyType* anytype)
{
}

void JSONTypeSerializer::AddScalarProlog(const AnyType* anytype)
{
}

void JSONTypeSerializer::AddScalarEpilog(const AnyType*)
{}

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

}  // namespace dto

}  // namespace sup
