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
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#ifndef SUP_DTO_CTYPE_SERIALIZER_H_
#define SUP_DTO_CTYPE_SERIALIZER_H_

#include <sup/dto/basic_scalar_types.h>
#include <sup/dto/i_any_visitor.h>

#include <vector>

namespace sup
{
namespace dto
{
class AnyValue;

class CTypeSerializer : public IAnyVisitor<const AnyValue>
{
public:
  CTypeSerializer();
  ~CTypeSerializer() override;

  CTypeSerializer(const CTypeSerializer& other) = delete;
  CTypeSerializer(CTypeSerializer&& other) = delete;
  CTypeSerializer& operator=(const CTypeSerializer& other) = delete;
  CTypeSerializer& operator=(CTypeSerializer&& other) = delete;

  std::vector<uint8> GetRepresentation() const;

  void EmptyProlog(const AnyValue* anyvalue) override;
  void EmptyEpilog(const AnyValue* anyvalue) override;

  void StructProlog(const AnyValue* anyvalue) override;
  void StructMemberSeparator() override;
  void StructEpilog(const AnyValue* anyvalue) override;

  void MemberProlog(const AnyValue* anyvalue, const std::string& member_name) override;
  void MemberEpilog(const AnyValue* anyvalue, const std::string& member_name) override;

  void ArrayProlog(const AnyValue* anyvalue) override;
  void ArrayElementSeparator() override;
  void ArrayEpilog(const AnyValue* anyvalue) override;

  void ScalarProlog(const AnyValue* anyvalue) override;
  void ScalarEpilog(const AnyValue* anyvalue) override;

private:
  std::vector<uint8> m_representation;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_CTYPE_SERIALIZER_H_
