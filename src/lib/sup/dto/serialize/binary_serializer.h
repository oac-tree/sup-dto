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

#ifndef SUP_DTO_BINARY_SERIALIZER_H_
#define SUP_DTO_BINARY_SERIALIZER_H_

#include <sup/dto/basic_scalar_types.h>
#include <sup/dto/i_any_visitor.h>

#include <vector>

namespace sup
{
namespace dto
{
class AnyType;
class AnyValue;

class BinaryTypeSerializer : public IAnyVisitor<const AnyType>
{
public:
  explicit BinaryTypeSerializer(std::vector<uint8>& representation);
  ~BinaryTypeSerializer() override;

  BinaryTypeSerializer(const BinaryTypeSerializer& other) = delete;
  BinaryTypeSerializer(BinaryTypeSerializer&& other) = delete;
  BinaryTypeSerializer& operator=(const BinaryTypeSerializer& other) = delete;
  BinaryTypeSerializer& operator=(BinaryTypeSerializer&& other) = delete;

  void EmptyProlog(const AnyType* anytype) override;
  void EmptyEpilog(const AnyType* anytype) override;

  void StructProlog(const AnyType* anytype) override;
  void StructMemberSeparator() override;
  void StructEpilog(const AnyType* anytype) override;

  void MemberProlog(const AnyType* anytype, const std::string& member_name) override;
  void MemberEpilog(const AnyType* anytype, const std::string& member_name) override;

  void ArrayProlog(const AnyType* anytype) override;
  void ArrayElementSeparator() override;
  void ArrayEpilog(const AnyType* anytype) override;

  void ScalarProlog(const AnyType* anytype) override;
  void ScalarEpilog(const AnyType* anytype) override;

private:
  std::vector<uint8>& m_representation;
};

class BinaryValueSerializer : public IAnyVisitor<const AnyValue>
{
public:
  explicit BinaryValueSerializer(std::vector<uint8>& representation);
  ~BinaryValueSerializer() override;

  BinaryValueSerializer(const BinaryValueSerializer& other) = delete;
  BinaryValueSerializer(BinaryValueSerializer&& other) = delete;
  BinaryValueSerializer& operator=(const BinaryValueSerializer& other) = delete;
  BinaryValueSerializer& operator=(BinaryValueSerializer&& other) = delete;

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
  std::vector<uint8>& m_representation;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_BINARY_SERIALIZER_H_
