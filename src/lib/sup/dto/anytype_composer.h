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

#ifndef SUP_DTO_COMPOSER_ANYTYPE_COMPOSER_H_
#define SUP_DTO_COMPOSER_ANYTYPE_COMPOSER_H_

#include <sup/dto/basic_scalar_types.h>

#include <memory>
#include <string>

namespace sup
{
namespace dto
{

class AnyType;

//! Builds AnyType in step-wise manner by calling methods to add fields and structs.

class AnyTypeComposer
{
public:
  AnyTypeComposer();
  ~AnyTypeComposer();

  AnyTypeComposer(const AnyTypeComposer& other) = delete;
  AnyTypeComposer(AnyTypeComposer&& other) = delete;
  AnyTypeComposer& operator=(const AnyTypeComposer& other) = delete;
  AnyTypeComposer& operator=(AnyTypeComposer&& other) = delete;

  sup::dto::AnyType MoveAnyType();

  void Empty();
  void Bool();
  void Char8();
  void Int8();
  void UInt8();
  void Int16();
  void UInt16();
  void Int32();
  void UInt32();
  void Int64();
  void UInt64();
  void Float32();
  void Float64();
  void String();

  void StartStruct(const std::string& struct_name);
  void StartStruct();

  void EndStruct();

  void StartField(const std::string& field_name);

  void EndField();

  void StartArray(const std::string& array_name, sup::dto::uint64 array_size);

  void EndArray();

  void StartArrayElement();

  void EndArrayElement();

  sup::dto::uint64 GetStackSize() const;

private:
  struct AnyTypeComposerImpl;
  std::unique_ptr<AnyTypeComposerImpl> p_impl;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_COMPOSER_ANYTYPE_COMPOSER_H_
