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

#include "ByteSerializer.h"
#include "AnyValue.h"
#include "ScalarToBytes.h"

namespace sup
{
namespace dto
{

ByteSerializer::ByteSerializer()
  : representation{}
{}
ByteSerializer::~ByteSerializer() = default;

void ByteSerializer::ResetRepresentation()
{
  representation.clear();
}

std::vector<uint8> ByteSerializer::GetRepresentation() const
{
  return representation;
}

void ByteSerializer::AddEmptyProlog(const AnyValue*)
{}

void ByteSerializer::AddEmptyEpilog(const AnyValue*)
{}

void ByteSerializer::AddStructProlog(const AnyValue*)
{}

void ByteSerializer::AddStructMemberSeparator()
{}

void ByteSerializer::AddStructEpilog(const AnyValue*)
{}

void ByteSerializer::AddMemberProlog(const AnyValue*, const std::string&)
{}

void ByteSerializer::AddMemberEpilog(const AnyValue*, const std::string&)
{}

void ByteSerializer::AddArrayProlog(const AnyValue*)
{}

void ByteSerializer::AddArrayElementSeparator()
{}

void ByteSerializer::AddArrayEpilog(const AnyValue*)
{}

void ByteSerializer::AddScalarProlog(const AnyValue* anyvalue)
{
  auto byte_val = ScalarToBytes(*anyvalue);
  representation.insert(representation.begin(), byte_val.begin(), byte_val.end());
}

void ByteSerializer::AddScalarEpilog(const AnyValue*)
{}

}  // namespace dto

}  // namespace sup
