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

#ifndef SUP_DTO_BYTE_PARSER_H_
#define SUP_DTO_BYTE_PARSER_H_

#include <sup/dto/basic_scalar_types.h>
#include <sup/dto/i_any_visitor.h>

namespace sup
{
namespace dto
{
class AnyValue;

class CTypeParser : public IAnyVisitor<AnyValue>
{
public:
  CTypeParser(const uint8* bytes, std::size_t total_size);
  ~CTypeParser() override;

  CTypeParser(const CTypeParser& other) = delete;
  CTypeParser(CTypeParser&& other) = delete;
  CTypeParser& operator=(const CTypeParser& other) = delete;
  CTypeParser& operator=(CTypeParser&& other) = delete;

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

private:
  const uint8* m_bytes;
  std::size_t m_total_size;
  std::size_t m_current_position;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_BYTE_PARSER_H_
