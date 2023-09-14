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

#ifndef SUP_DTO_WRITER_SERIALIZER_H_
#define SUP_DTO_WRITER_SERIALIZER_H_

#include <sup/dto/serialize/i_writer.h>

#include <sup/dto/i_any_visitor.h>

#include <memory>

namespace sup
{
namespace dto
{
class AnyType;
class AnyValue;
class JSONRepresentation;

/**
 * @brief Serialization for AnyType, using an IWriter service.
 */
class WriterTypeSerializer : public IAnyVisitor<const AnyType>
{
public:
  explicit WriterTypeSerializer(IWriter* writer);
  ~WriterTypeSerializer() override;

  WriterTypeSerializer(const WriterTypeSerializer& other) = delete;
  WriterTypeSerializer(WriterTypeSerializer&& other) = delete;
  WriterTypeSerializer& operator=(const WriterTypeSerializer& other) = delete;
  WriterTypeSerializer& operator=(WriterTypeSerializer&& other) = delete;

  void EmptyProlog(const AnyType* anytype) override;
  void EmptyEpilog(const AnyType*) override;

  void StructProlog(const AnyType* anytype) override;
  void StructMemberSeparator() override;
  void StructEpilog(const AnyType*) override;

  void MemberProlog(const AnyType*, const std::string& member_name) override;
  void MemberEpilog(const AnyType*, const std::string&) override;

  void ArrayProlog(const AnyType* anytype) override;
  void ArrayElementSeparator() override;
  void ArrayEpilog(const AnyType*) override;

  void ScalarProlog(const AnyType* anytype) override;
  void ScalarEpilog(const AnyType*) override;

private:
  IWriter* m_writer;
};


/**
 * @brief Serialization for AnyValue, using an IWriter service.
 */
class WriterValueSerializer : public IAnyVisitor<const AnyValue>
{
public:
  explicit WriterValueSerializer(IWriter* writer);
  ~WriterValueSerializer() override;

  WriterValueSerializer(const WriterValueSerializer& other) = delete;
  WriterValueSerializer(WriterValueSerializer&& other) = delete;
  WriterValueSerializer& operator=(const WriterValueSerializer& other) = delete;
  WriterValueSerializer& operator=(WriterValueSerializer&& other) = delete;

  void EmptyProlog(const AnyValue*) override;
  void EmptyEpilog(const AnyValue*) override;

  void StructProlog(const AnyValue*) override;
  void StructMemberSeparator() override;
  void StructEpilog(const AnyValue*) override;

  void MemberProlog(const AnyValue*, const std::string& member_name) override;
  void MemberEpilog(const AnyValue*, const std::string&) override;

  void ArrayProlog(const AnyValue*) override;
  void ArrayElementSeparator() override;
  void ArrayEpilog(const AnyValue*) override;

  void ScalarProlog(const AnyValue* anyvalue) override;
  void ScalarEpilog(const AnyValue*) override;

private:
  IWriter* m_writer;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_WRITER_SERIALIZER_H_
