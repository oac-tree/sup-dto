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
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#ifndef SUP_DTO_MEMBERTYPE_BUILDNODE_H_
#define SUP_DTO_MEMBERTYPE_BUILDNODE_H_

#include <sup/dto/parse/i_any_buildnode.h>

#include <sup/dto/anytype.h>

#include <memory>
#include <utility>

namespace sup
{
namespace dto
{
class AnyTypeBuildNode;

class MemberTypeBuildNode : public IAnyBuildNode
{
public:
  MemberTypeBuildNode(const AnyTypeRegistry* anytype_registry, IAnyBuildNode* parent);
  ~MemberTypeBuildNode() override;

  MemberTypeBuildNode(const MemberTypeBuildNode& other) = delete;
  MemberTypeBuildNode(MemberTypeBuildNode&& other) = delete;
  MemberTypeBuildNode& operator=(const MemberTypeBuildNode& other) = delete;
  MemberTypeBuildNode& operator=(MemberTypeBuildNode&& other) = delete;

  bool Member(const std::string& str) override;

  IAnyBuildNode* GetStructureNode() override;
  bool PopStructureNode() override;

  std::pair<std::string, AnyType> MoveMemberType();

private:
  std::unique_ptr<AnyTypeBuildNode> m_type_node;
  std::string m_member_name;
  std::pair<std::string, AnyType> m_member_type;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_MEMBERTYPE_BUILDNODE_H_
