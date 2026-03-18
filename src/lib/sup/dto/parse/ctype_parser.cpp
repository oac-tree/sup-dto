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
 * Copyright (c) : 2010-2026 ITER Organization,
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

#include "ctype_parser.h"

#include <sup/dto/low_level/scalar_from_bytes.h>

#include <sup/dto/anyvalue.h>

namespace sup
{
namespace dto
{

CTypeParser::CTypeParser(const uint8* bytes, std::size_t total_size, ByteOrder byte_order)
  : IAnyVisitor<AnyValue>{}
  , m_bytes{bytes}
  , m_total_size{total_size}
  , m_current_position{0}
  , m_byte_order{byte_order}
{}

CTypeParser::~CTypeParser() = default;

bool CTypeParser::IsFinished() const
{
  return m_current_position == m_total_size;
}

void CTypeParser::EmptyProlog(AnyValue*)
{}

void CTypeParser::EmptyEpilog(AnyValue*)
{}

void CTypeParser::StructProlog(AnyValue*)
{}

void CTypeParser::StructMemberSeparator()
{}

void CTypeParser::StructEpilog(AnyValue*)
{}

void CTypeParser::MemberProlog(AnyValue*, const std::string&)
{}

void CTypeParser::MemberEpilog(AnyValue*, const std::string&)
{}

void CTypeParser::ArrayProlog(AnyValue*)
{}

void CTypeParser::ArrayElementSeparator()
{}

void CTypeParser::ArrayEpilog(AnyValue*)
{}

void CTypeParser::ScalarProlog(AnyValue* anyvalue)
{
  m_current_position = (m_byte_order == ByteOrder::Host)
    ? AssignFromHostOrder(*anyvalue, m_bytes, m_total_size, m_current_position)
    : AssignFromNetworkOrder(*anyvalue, m_bytes, m_total_size, m_current_position);
}

void CTypeParser::ScalarEpilog(AnyValue*)
{}

}  // namespace dto

}  // namespace sup
