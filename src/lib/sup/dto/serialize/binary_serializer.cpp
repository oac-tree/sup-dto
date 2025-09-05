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
 * SPDX-License-Identifier: MIT
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file LICENSE located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include "binary_serializer.h"

#include <sup/dto/low_level/binary_serialization_functions.h>
#include <sup/dto/serialize/binary_tokens.h>

#include <sup/dto/anyvalue.h>

namespace sup
{
namespace dto
{
BinaryTypeSerializer::BinaryTypeSerializer(std::vector<uint8>& representation)
  : IAnyVisitor<const AnyType>{}
  , m_representation{representation}
{}
BinaryTypeSerializer::~BinaryTypeSerializer() = default;

void BinaryTypeSerializer::EmptyProlog(const AnyType*)
{
  m_representation.push_back(EMPTY_TOKEN);
}

void BinaryTypeSerializer::EmptyEpilog(const AnyType*)
{}

void BinaryTypeSerializer::StructProlog(const AnyType* anytype)
{
  m_representation.push_back(START_STRUCT_TOKEN);
  AppendBinaryString(m_representation, anytype->GetTypeName());
}

void BinaryTypeSerializer::StructMemberSeparator()
{}

void BinaryTypeSerializer::StructEpilog(const AnyType*)
{
  m_representation.push_back(END_STRUCT_TOKEN);
}

void BinaryTypeSerializer::MemberProlog(const AnyType*, const std::string& member_name)
{
  AppendBinaryString(m_representation, member_name);
}

void BinaryTypeSerializer::MemberEpilog(const AnyType*, const std::string&)
{}

void BinaryTypeSerializer::ArrayProlog(const AnyType* anytype)
{
  m_representation.push_back(START_ARRAY_TOKEN);
  AppendBinaryString(m_representation, anytype->GetTypeName());
  AppendSize(m_representation, anytype->NumberOfElements());
}

void BinaryTypeSerializer::ArrayElementSeparator()
{}

void BinaryTypeSerializer::ArrayEpilog(const AnyType*)
{
  m_representation.push_back(END_ARRAY_TOKEN);
}

void BinaryTypeSerializer::ScalarProlog(const AnyType* anytype)
{
  AppendScalarToken(m_representation, anytype->GetTypeCode());
}

void BinaryTypeSerializer::ScalarEpilog(const AnyType*)
{}

BinaryValueSerializer::BinaryValueSerializer(std::vector<uint8>& representation)
  : IAnyVisitor<const AnyValue>{}
  , m_representation{representation}
{}
BinaryValueSerializer::~BinaryValueSerializer() = default;

void BinaryValueSerializer::EmptyProlog(const AnyValue*)
{}

void BinaryValueSerializer::EmptyEpilog(const AnyValue*)
{}

void BinaryValueSerializer::StructProlog(const AnyValue*)
{}

void BinaryValueSerializer::StructMemberSeparator()
{}

void BinaryValueSerializer::StructEpilog(const AnyValue*)
{}

void BinaryValueSerializer::MemberProlog(const AnyValue*, const std::string&)
{}

void BinaryValueSerializer::MemberEpilog(const AnyValue*, const std::string&)
{}

void BinaryValueSerializer::ArrayProlog(const AnyValue*)
{}

void BinaryValueSerializer::ArrayElementSeparator()
{}

void BinaryValueSerializer::ArrayEpilog(const AnyValue*)
{}

void BinaryValueSerializer::ScalarProlog(const AnyValue* anyvalue)
{
  AppendBinaryScalar(m_representation, *anyvalue);
}

void BinaryValueSerializer::ScalarEpilog(const AnyValue*)
{}

}  // namespace dto

}  // namespace sup
