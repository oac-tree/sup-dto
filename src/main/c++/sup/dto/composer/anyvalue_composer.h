/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : SUP - DTO
 *
 * Description   : Data transfer objects for SUP
 *
 * Author        : Gennady Pospelov (IO)
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

#ifndef SUP_DTO_COMPOSER_ANYVALUE_COMPOSER_H_
#define SUP_DTO_COMPOSER_ANYVALUE_COMPOSER_H_

#include <sup/dto/basic_scalar_types.h>

#include <memory>
#include <string>

namespace sup
{
namespace dto
{

class AnyValue;

//! Builds AnyValue in step-wise manner by calling methods to add fields and structs.

class AnyValueComposer
{
public:
  AnyValueComposer();
  ~AnyValueComposer();

  sup::dto::AnyValue MoveAnyValue() const;

  void Bool(::sup::dto::boolean value);
  void Int8(::sup::dto::int8 value);
  void UInt8(::sup::dto::uint8 value);
  void Int16(::sup::dto::int16 value);
  void UInt16(::sup::dto::uint16 value);
  void Int32(::sup::dto::int32 value);
  void UInt32(::sup::dto::uint32 value);
  void Int64(::sup::dto::int64 value);
  void UInt64(::sup::dto::uint64 value);
  void Float32(::sup::dto::float32 value);
  void Float64(::sup::dto::float64 value);
  void String(const std::string& value);

  void AddValue(const sup::dto::AnyValue& anyvalue);

  void StartStruct(const std::string& struct_name = {});

  void EndStruct();

  void StartField(const std::string& field_name);

  void EndField();

  void AddMember(const std::string& name, sup::dto::AnyValue anyvalue);

  void StartArray(const std::string& array_name = {});

  void StartArrayElement();

  void EndArrayElement();

  void AddArrayElement(const sup::dto::AnyValue& anyvalue);

  void EndArray();

  int GetStackSize() const;

private:
  struct AnyValueComposerImpl;
  std::unique_ptr<AnyValueComposerImpl> p_impl;
};

}  // namespace dto
}  // namespace sup

#endif  // SUP_DTO_COMPOSER_ANYVALUE_COMPOSER_H_
