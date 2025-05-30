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

#ifndef SUP_DTO_ARRAYVALUE_BUILDNODE_H_
#define SUP_DTO_ARRAYVALUE_BUILDNODE_H_

#include <sup/dto/parse/i_any_buildnode.h>

#include <sup/dto/anyvalue.h>

#include <memory>

namespace sup
{
namespace dto
{
class AnyValueBuildNode;

class ArrayValueBuildNode : public IAnyBuildNode
{
public:
  ArrayValueBuildNode(const AnyTypeRegistry* anytype_registry, IAnyBuildNode* parent,
                      AnyValue& anyvalue);
  ~ArrayValueBuildNode() override;

  ArrayValueBuildNode(const ArrayValueBuildNode& other) = delete;
  ArrayValueBuildNode(ArrayValueBuildNode&& other) = delete;
  ArrayValueBuildNode& operator=(const ArrayValueBuildNode& other) = delete;
  ArrayValueBuildNode& operator=(ArrayValueBuildNode&& other) = delete;

  bool Bool(boolean b) override;
  bool Int32(int32 i) override;
  bool Uint32(uint32 u) override;
  bool Int64(int64 i) override;
  bool Uint64(uint64 u) override;
  bool Double(float64 d) override;
  bool String(const std::string& str) override;

  IAnyBuildNode* GetStructureNode() override;
  IAnyBuildNode* GetArrayNode() override;
  bool PopStructureNode() override;
  bool PopArrayNode() override;

private:
  template <typename T> bool TryAssign(T val);
  std::unique_ptr<AnyValueBuildNode> m_value_node;
  std::unique_ptr<IAnyBuildNode> m_array_node;
  std::size_t m_current_index;
  std::size_t m_size;
  AnyValue& m_anyvalue;
  AnyType m_element_type;
};

std::unique_ptr<IAnyBuildNode> CreateArrayBuildNode(
  const AnyTypeRegistry* anytype_registry, IAnyBuildNode* parent, AnyValue& anyvalue);

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ARRAYVALUE_BUILDNODE_H_
