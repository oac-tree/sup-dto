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

#ifndef SUP_DTO_ANYVALUE_TYPEELEMENT_BUILDNODE_H_
#define SUP_DTO_ANYVALUE_TYPEELEMENT_BUILDNODE_H_

#include <sup/dto/parse/i_any_buildnode.h>

#include <sup/dto/anytype.h>

#include <memory>

namespace sup
{
namespace dto
{
class AnyTypeBuildNode;

class AnyValueTypeElementBuildNode : public IAnyBuildNode
{
public:
  AnyValueTypeElementBuildNode(const AnyTypeRegistry* anytype_registry, IAnyBuildNode* parent);
  ~AnyValueTypeElementBuildNode();

  AnyValueTypeElementBuildNode(const AnyValueTypeElementBuildNode& other) = delete;
  AnyValueTypeElementBuildNode(AnyValueTypeElementBuildNode&& other) = delete;
  AnyValueTypeElementBuildNode& operator=(const AnyValueTypeElementBuildNode& other) = delete;
  AnyValueTypeElementBuildNode& operator=(AnyValueTypeElementBuildNode&& other) = delete;


  bool Member(const std::string& str) override;

  IAnyBuildNode* GetStructureNode() override;
  bool PopStructureNode() override;

  AnyType MoveAnyType();

private:
  std::unique_ptr<AnyTypeBuildNode> m_type_node;
  std::string m_member_name;
  AnyType m_anytype;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ANYVALUE_TYPEELEMENT_BUILDNODE_H_
