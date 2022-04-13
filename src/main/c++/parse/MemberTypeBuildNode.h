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

#ifndef _SUP_MemberTypeBuildNode_h_
#define _SUP_MemberTypeBuildNode_h_

#include "IAnyBuildNode.h"
#include "AnyType.h"

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
  MemberTypeBuildNode(IAnyBuildNode* parent);
  ~MemberTypeBuildNode();

  bool Member(const std::string& str) override;

  IAnyBuildNode* GetStructureNode() override;
  bool PopStructureNode() override;

  std::pair<std::string, AnyType> MoveMemberType();

private:
  std::unique_ptr<AnyTypeBuildNode> type_node;
  std::string member_name;
  std::pair<std::string, AnyType> member_type;
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_MemberTypeBuildNode_h_
