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

#include "binary_value_parser.h"

#include <sup/dto/low_level/binary_parser_functions.h>

#include <sup/dto/anyvalue.h>
#include <sup/dto/anyvalue_helper.h>

namespace sup
{
namespace dto
{

BinaryValueParser::BinaryValueParser(ByteIterator& it, ByteIterator end)
  : IAnyVisitor<AnyValue>{}
  , m_it{it}
  , m_end{end}
{}

BinaryValueParser::~BinaryValueParser() = default;

bool BinaryValueParser::IsFinished() const
{
  return m_it == m_end;
}

void BinaryValueParser::EmptyProlog(AnyValue*)
{}

void BinaryValueParser::EmptyEpilog(AnyValue*)
{}

void BinaryValueParser::StructProlog(AnyValue*)
{}

void BinaryValueParser::StructMemberSeparator()
{}

void BinaryValueParser::StructEpilog(AnyValue*)
{}

void BinaryValueParser::MemberProlog(AnyValue*, const std::string&)
{}

void BinaryValueParser::MemberEpilog(AnyValue*, const std::string&)
{}

void BinaryValueParser::ArrayProlog(AnyValue*)
{}

void BinaryValueParser::ArrayElementSeparator()
{}

void BinaryValueParser::ArrayEpilog(AnyValue*)
{}

void BinaryValueParser::ScalarProlog(AnyValue* anyvalue)
{
  static const auto parser_functions = CreateScalarParserFunctionArray();
  auto& parse_func = parser_functions[static_cast<size_t>(anyvalue->GetTypeCode())];
  parse_func(*anyvalue, m_it, m_end);
}

void BinaryValueParser::ScalarEpilog(AnyValue*)
{}

}  // namespace dto

}  // namespace sup
