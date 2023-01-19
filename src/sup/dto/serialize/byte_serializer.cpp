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

#include "byte_serializer.h"

#include <sup/dto/serialize/scalar_to_bytes.h>

#include <sup/dto/anyvalue.h>

namespace sup
{
namespace dto
{

ByteSerializer::ByteSerializer()
  : representation{}
{}
ByteSerializer::~ByteSerializer() = default;

std::vector<uint8> ByteSerializer::GetRepresentation() const
{
  return representation;
}

void ByteSerializer::EmptyProlog(const AnyValue*)
{}

void ByteSerializer::EmptyEpilog(const AnyValue*)
{}

void ByteSerializer::StructProlog(const AnyValue*)
{}

void ByteSerializer::StructMemberSeparator()
{}

void ByteSerializer::StructEpilog(const AnyValue*)
{}

void ByteSerializer::MemberProlog(const AnyValue*, const std::string&)
{}

void ByteSerializer::MemberEpilog(const AnyValue*, const std::string&)
{}

void ByteSerializer::ArrayProlog(const AnyValue*)
{}

void ByteSerializer::ArrayElementSeparator()
{}

void ByteSerializer::ArrayEpilog(const AnyValue*)
{}

void ByteSerializer::ScalarProlog(const AnyValue* anyvalue)
{
  auto byte_val = ScalarToBytes(*anyvalue);
  representation.insert(representation.end(), byte_val.begin(), byte_val.end());
}

void ByteSerializer::ScalarEpilog(const AnyValue*)
{}

}  // namespace dto

}  // namespace sup
