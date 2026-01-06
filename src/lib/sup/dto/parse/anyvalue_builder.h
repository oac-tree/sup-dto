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
 * Copyright (c) : 2010-2026 ITER Organization,
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

#ifndef SUP_DTO_ANYVALUE_BUILDER_H_
#define SUP_DTO_ANYVALUE_BUILDER_H_

#include <sup/dto/anyvalue.h>
#include <sup/dto/basic_scalar_types.h>

#include <memory>

namespace sup
{
namespace dto
{
class AnyTypeRegistry;
class AnyValueRootBuildNode;
class IAnyBuildNode;

class AnyValueBuilder
{
public:
  explicit AnyValueBuilder(const AnyTypeRegistry* anytype_registry);
  ~AnyValueBuilder();

  AnyValueBuilder(const AnyValueBuilder& other) = delete;
  AnyValueBuilder(AnyValueBuilder&& other) = delete;
  AnyValueBuilder& operator=(const AnyValueBuilder& other) = delete;
  AnyValueBuilder& operator=(AnyValueBuilder&& other) = delete;

  AnyValue MoveAnyValue();

  bool Null();
  bool Bool(boolean b);
  bool Int(int32 i);
  bool Uint(uint32 u);
  bool Int64(int64 i);
  bool Uint64(uint64 u);
  bool Double(float64 d);
  bool RawNumber(const char* str, std::size_t length, bool);
  bool String(const char* str, std::size_t length, bool);
  bool StartObject();
  bool Key(const char* str, std::size_t length, bool);
  bool EndObject(std::size_t memberCount);
  bool StartArray();
  bool EndArray(std::size_t);

private:
  std::unique_ptr<AnyValueRootBuildNode> m_root;
  IAnyBuildNode* m_current;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ANYVALUE_BUILDER_H_
