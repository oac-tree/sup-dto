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

#ifndef _SUP_WriterSerializer_h_
#define _SUP_WriterSerializer_h_

#include "IAnyVisitor.h"
#include "IWriter.h"

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
  WriterTypeSerializer(IWriter* writer);
  ~WriterTypeSerializer() override;

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
  IWriter* writer;
};


/**
 * @brief Serialization for AnyValue, using an IWriter service.
 */
class WriterValueSerializer : public IAnyVisitor<const AnyValue>
{
public:
  WriterValueSerializer(IWriter* writer);
  ~WriterValueSerializer() override;

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
  IWriter* writer;
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_WriterSerializer_h_
