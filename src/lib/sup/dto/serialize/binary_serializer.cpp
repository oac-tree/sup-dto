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

BinarySerializer::BinarySerializer(std::vector<uint8>& representation)
  : m_representation{representation}
{}
BinarySerializer::~BinarySerializer() = default;

void BinarySerializer::EmptyProlog(const AnyValue*)
{
  m_representation.push_back(EMPTY_TOKEN);
}

void BinarySerializer::EmptyEpilog(const AnyValue*)
{}

void BinarySerializer::StructProlog(const AnyValue* value)
{
  m_representation.push_back(START_STRUCT_TOKEN);
  AppendBinaryString(m_representation, value->GetTypeName());
}

void BinarySerializer::StructMemberSeparator()
{}

void BinarySerializer::StructEpilog(const AnyValue*)
{
  m_representation.push_back(END_STRUCT_TOKEN);
}

void BinarySerializer::MemberProlog(const AnyValue*, const std::string& member_name)
{
  AppendBinaryString(m_representation, member_name);
}

void BinarySerializer::MemberEpilog(const AnyValue*, const std::string&)
{}

void BinarySerializer::ArrayProlog(const AnyValue* value)
{
  m_representation.push_back(START_ARRAY_TOKEN);
  AppendBinaryString(m_representation, value->GetTypeName());
}

void BinarySerializer::ArrayElementSeparator()
{}

void BinarySerializer::ArrayEpilog(const AnyValue*)
{
  m_representation.push_back(END_ARRAY_TOKEN);
}

void BinarySerializer::ScalarProlog(const AnyValue* anyvalue)
{
  AppendBinaryScalar(m_representation, *anyvalue);
}

void BinarySerializer::ScalarEpilog(const AnyValue*)
{}

}  // namespace dto

}  // namespace sup
