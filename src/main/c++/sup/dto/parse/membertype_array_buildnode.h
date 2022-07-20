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

#ifndef _SUP_MemberTypeArrayBuildNode_h_
#define _SUP_MemberTypeArrayBuildNode_h_

#include <sup/dto/parse/i_any_buildnode.h>
#include <sup/dto/anytype.h>

#include <memory>
#include <utility>
#include <vector>

namespace sup
{
namespace dto
{
class MemberTypeBuildNode;

class MemberTypeArrayBuildNode : public IAnyBuildNode
{
public:
  MemberTypeArrayBuildNode(const AnyTypeRegistry* anytype_registry, IAnyBuildNode* parent);
  ~MemberTypeArrayBuildNode();

  IAnyBuildNode* GetStructureNode() override;
  bool PopStructureNode() override;

  std::vector<std::pair<std::string, AnyType>> MoveMemberTypes();

private:
  std::unique_ptr<MemberTypeBuildNode> member_node;
  std::vector<std::pair<std::string, AnyType>> member_types;
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_MemberTypeArrayBuildNode_h_
