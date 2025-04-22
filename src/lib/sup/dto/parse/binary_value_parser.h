/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : SUP - DTO
 *
 * Description   : Data transfer objects for SUP
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

#ifndef SUP_DTO_BINARY_VALUE_PARSER_H_
#define SUP_DTO_BINARY_VALUE_PARSER_H_

#include <sup/dto/parse/binary_parser.h>

#include <sup/dto/basic_scalar_types.h>
#include <sup/dto/i_any_visitor.h>

namespace sup
{
namespace dto
{
class AnyValue;

class BinaryValueParser : public IAnyVisitor<AnyValue>
{
public:
  BinaryValueParser(ByteIterator& it, ByteIterator end);
  ~BinaryValueParser() override;

  BinaryValueParser(const BinaryValueParser& other) = delete;
  BinaryValueParser(BinaryValueParser&& other) = delete;
  BinaryValueParser& operator=(const BinaryValueParser& other) = delete;
  BinaryValueParser& operator=(BinaryValueParser&& other) = delete;

  bool IsFinished() const;

  void EmptyProlog(AnyValue* anyvalue) override;
  void EmptyEpilog(AnyValue* anyvalue) override;

  void StructProlog(AnyValue* anyvalue) override;
  void StructMemberSeparator() override;
  void StructEpilog(AnyValue* anyvalue) override;

  void MemberProlog(AnyValue* anyvalue, const std::string& member_name) override;
  void MemberEpilog(AnyValue* anyvalue, const std::string& member_name) override;

  void ArrayProlog(AnyValue* anyvalue) override;
  void ArrayElementSeparator() override;
  void ArrayEpilog(AnyValue* anyvalue) override;

  void ScalarProlog(AnyValue* anyvalue) override;
  void ScalarEpilog(AnyValue* anyvalue) override;
  bool HandleToken();

private:
  ByteIterator& m_it;
  ByteIterator m_end;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_BINARY_VALUE_PARSER_H_
