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

#include "ctype_serializer.h"

#include <sup/dto/low_level/scalar_to_bytes.h>

#include <sup/dto/anyvalue.h>

namespace sup
{
namespace dto
{

CTypeSerializer::CTypeSerializer()
  : m_representation{}
{}
CTypeSerializer::~CTypeSerializer() = default;

std::vector<uint8> CTypeSerializer::GetRepresentation() const
{
  return m_representation;
}

void CTypeSerializer::EmptyProlog(const AnyValue*)
{}

void CTypeSerializer::EmptyEpilog(const AnyValue*)
{}

void CTypeSerializer::StructProlog(const AnyValue*)
{}

void CTypeSerializer::StructMemberSeparator()
{}

void CTypeSerializer::StructEpilog(const AnyValue*)
{}

void CTypeSerializer::MemberProlog(const AnyValue*, const std::string&)
{}

void CTypeSerializer::MemberEpilog(const AnyValue*, const std::string&)
{}

void CTypeSerializer::ArrayProlog(const AnyValue*)
{}

void CTypeSerializer::ArrayElementSeparator()
{}

void CTypeSerializer::ArrayEpilog(const AnyValue*)
{}

void CTypeSerializer::ScalarProlog(const AnyValue* anyvalue)
{
  auto byte_val = ScalarToBytes(*anyvalue);
  (void)m_representation.insert(m_representation.cend(), byte_val.begin(), byte_val.end());
}

void CTypeSerializer::ScalarEpilog(const AnyValue*)
{}

}  // namespace dto

}  // namespace sup
