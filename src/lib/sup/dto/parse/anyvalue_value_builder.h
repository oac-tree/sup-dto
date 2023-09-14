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

#ifndef SUP_DTO_ANYVALUE_VALUE_BUILDER_H_
#define SUP_DTO_ANYVALUE_VALUE_BUILDER_H_

#include <sup/dto/anytype_registry.h>
#include <sup/dto/anyvalue.h>
#include <sup/dto/basic_scalar_types.h>

#include <memory>

namespace sup
{
namespace dto
{
class AnyValueValueElementBuildNode;
class IAnyBuildNode;

class AnyValueValueBuilder
{
public:
  explicit AnyValueValueBuilder(const AnyType& anytype);
  ~AnyValueValueBuilder();

  AnyValueValueBuilder(const AnyValueValueBuilder& other) = delete;
  AnyValueValueBuilder(AnyValueValueBuilder&& other) = delete;
  AnyValueValueBuilder& operator=(const AnyValueValueBuilder& other) = delete;
  AnyValueValueBuilder& operator=(AnyValueValueBuilder&& other) = delete;

  AnyValue MoveAnyValue();

  bool Null();
  bool Bool(boolean b);
  bool Int(int32 i);
  bool Uint(uint32 u);
  bool Int64(int64 i);
  bool Uint64(uint64 u);
  bool Double(float64 d);
  bool RawNumber(const char* str, std::size_t length, bool copy);
  bool String(const char* str, std::size_t length, bool copy);
  bool StartObject();
  bool Key(const char* str, std::size_t length, bool copy);
  bool EndObject(std::size_t memberCount);
  bool StartArray();
  bool EndArray(std::size_t elementCount);

private:
  AnyValue m_value;
  AnyTypeRegistry m_registry;
  std::unique_ptr<AnyValueValueElementBuildNode> m_root;
  IAnyBuildNode* m_current;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ANYVALUE_VALUE_BUILDER_H_
