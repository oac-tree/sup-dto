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

#include "binary_serializer.h"

#include <sup/dto/serialize/binary_tokens.h>
#include <sup/dto/serialize/scalar_to_bytes.h>

#include <sup/dto/anyvalue.h>

namespace sup
{
namespace dto
{

BinarySerializer::BinarySerializer()
  : representation{}
{}
BinarySerializer::~BinarySerializer() = default;

std::vector<uint8> BinarySerializer::GetRepresentation() const
{
  return representation;
}

void BinarySerializer::EmptyProlog(const AnyValue*)
{
  representation.push_back(EMPTY_TOKEN);
}

void BinarySerializer::EmptyEpilog(const AnyValue*)
{}

void BinarySerializer::StructProlog(const AnyValue*)
{
  representation.push_back(START_STRUCT_TOKEN);
}

void BinarySerializer::StructMemberSeparator()
{}

void BinarySerializer::StructEpilog(const AnyValue*)
{
  representation.push_back(END_STRUCT_TOKEN);
}

void BinarySerializer::MemberProlog(const AnyValue*, const std::string& member_name)
{
  AppendString(member_name);
}

void BinarySerializer::MemberEpilog(const AnyValue*, const std::string&)
{}

void BinarySerializer::ArrayProlog(const AnyValue*)
{
  representation.push_back(START_ARRAY_TOKEN);
}

void BinarySerializer::ArrayElementSeparator()
{}

void BinarySerializer::ArrayEpilog(const AnyValue*)
{
  representation.push_back(END_ARRAY_TOKEN);
}

void BinarySerializer::ScalarProlog(const AnyValue* anyvalue)
{
  auto byte_val = ScalarToBytes(*anyvalue);
  representation.insert(representation.end(), byte_val.begin(), byte_val.end());
}

void BinarySerializer::ScalarEpilog(const AnyValue*)
{}

void BinarySerializer::AppendString(const std::string& str)
{
  representation.push_back(STRING_TOKEN);
  auto str_size = str.size();
  if (str_size < 0x80)
  {
    auto size_byte = static_cast<sup::dto::uint8>(str_size);
    representation.push_back(size_byte);
  }
  else
  {
    representation.push_back(0x80);
    auto size_t_size = sizeof(str_size);
    std::vector<uint8> tmp(size_t_size);
    std::memcpy(tmp.data(), &str_size, size_t_size);
  }
  representation.insert(representation.end(), std::begin(str), std::end(str));
}

}  // namespace dto

}  // namespace sup
