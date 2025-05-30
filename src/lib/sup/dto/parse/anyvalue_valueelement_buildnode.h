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

#ifndef SUP_DTO_ANYVALUE_VALUEELEMENT_BUILDNODE_H_
#define SUP_DTO_ANYVALUE_VALUEELEMENT_BUILDNODE_H_

#include <sup/dto/parse/i_any_buildnode.h>

#include <sup/dto/anyvalue.h>

#include <memory>

namespace sup
{
namespace dto
{
class AnyValueBuildNode;

class AnyValueValueElementBuildNode : public IAnyBuildNode
{
public:
  AnyValueValueElementBuildNode(const AnyTypeRegistry* anytype_registry, IAnyBuildNode* parent,
                                AnyValue& anyvalue);
  ~AnyValueValueElementBuildNode() override;

  AnyValueValueElementBuildNode(const AnyValueValueElementBuildNode& other) = delete;
  AnyValueValueElementBuildNode(AnyValueValueElementBuildNode&& other) = delete;
  AnyValueValueElementBuildNode& operator=(const AnyValueValueElementBuildNode& other) = delete;
  AnyValueValueElementBuildNode& operator=(AnyValueValueElementBuildNode&& other) = delete;

  bool Null() override;
  bool Bool(boolean b) override;
  bool Int32(int32 i) override;
  bool Uint32(uint32 u) override;
  bool Int64(int64 i) override;
  bool Uint64(uint64 u) override;
  bool Double(float64 d) override;
  bool String(const std::string& str) override;
  bool Member(const std::string& str) override;

  IAnyBuildNode* GetStructureNode() override;
  IAnyBuildNode* GetArrayNode() override;
  bool PopStructureNode() override;
  bool PopArrayNode() override;

private:
  std::unique_ptr<AnyValueBuildNode> m_value_node;
  std::unique_ptr<IAnyBuildNode> m_array_node;
  std::string m_member_name;
  AnyValue& m_anyvalue;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ANYVALUE_VALUEELEMENT_BUILDNODE_H_
