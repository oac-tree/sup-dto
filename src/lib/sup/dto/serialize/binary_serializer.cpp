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
 * Copyright (c) : 2010-2023 ITER Organization,
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

#include <sup/dto/serialize/binary_serialization_functions.h>
#include <sup/dto/serialize/binary_tokens.h>

#include <sup/dto/anyvalue.h>

namespace sup
{
namespace dto
{

BinaryValueSerializer::BinaryValueSerializer(std::vector<uint8>& representation)
  : m_representation{representation}
{}
BinaryValueSerializer::~BinaryValueSerializer() = default;

void BinaryValueSerializer::EmptyProlog(const AnyValue*)
{
  m_representation.push_back(EMPTY_TOKEN);
}

void BinaryValueSerializer::EmptyEpilog(const AnyValue*)
{}

void BinaryValueSerializer::StructProlog(const AnyValue* value)
{
  m_representation.push_back(START_STRUCT_TOKEN);
  AppendBinaryString(m_representation, value->GetTypeName());
}

void BinaryValueSerializer::StructMemberSeparator()
{}

void BinaryValueSerializer::StructEpilog(const AnyValue*)
{
  m_representation.push_back(END_STRUCT_TOKEN);
}

void BinaryValueSerializer::MemberProlog(const AnyValue*, const std::string& member_name)
{
  AppendBinaryString(m_representation, member_name);
}

void BinaryValueSerializer::MemberEpilog(const AnyValue*, const std::string&)
{}

void BinaryValueSerializer::ArrayProlog(const AnyValue* value)
{
  m_representation.push_back(START_ARRAY_TOKEN);
  AppendBinaryString(m_representation, value->GetTypeName());
}

void BinaryValueSerializer::ArrayElementSeparator()
{}

void BinaryValueSerializer::ArrayEpilog(const AnyValue*)
{
  m_representation.push_back(END_ARRAY_TOKEN);
}

void BinaryValueSerializer::ScalarProlog(const AnyValue* anyvalue)
{
  AppendBinaryScalar(m_representation, *anyvalue);
}

void BinaryValueSerializer::ScalarEpilog(const AnyValue*)
{}

}  // namespace dto

}  // namespace sup
