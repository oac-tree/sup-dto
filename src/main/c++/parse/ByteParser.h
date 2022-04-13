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

#ifndef _SUP_ByteParser_h_
#define _SUP_ByteParser_h_

#include "IAnyVisitor.h"
#include "BasicScalarTypes.h"

namespace sup
{
namespace dto
{
class AnyValue;

class ByteParser : public IAnyVisitor<AnyValue>
{
public:
  ByteParser(const uint8* bytes, std::size_t total_size);
  ~ByteParser() override;

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
  const uint8* bytes;
  std::size_t total_size;
  std::size_t current_position;
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_ByteParser_h_
