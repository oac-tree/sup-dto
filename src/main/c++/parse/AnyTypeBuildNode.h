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

#ifndef _SUP_AnyTypeBuildNode_h_
#define _SUP_AnyTypeBuildNode_h_

#include "IAnyBuildNode.h"
#include "AnyType.h"

#include <memory>
#include <utility>
#include <vector>

namespace sup
{
namespace dto
{
class MemberTypeArrayBuildNode;

class AnyTypeBuildNode : public IAnyBuildNode
{
public:
  AnyTypeBuildNode(IAnyBuildNode* parent);
  ~AnyTypeBuildNode();

  bool Int32(int32 i) override;
  bool Uint32(uint32 u) override;
  bool Int64(int64 i) override;
  bool Uint64(uint64 u) override;
  bool String(const std::string& str) override;
  bool Member(const std::string& str) override;

  IAnyBuildNode* GetStructureNode() override;
  IAnyBuildNode* GetArrayNode() override;
  bool PopStructureNode() override;
  bool PopArrayNode() override;

  AnyType MoveAnyType() const;

private:
  bool IsComplexType() const;
  AnyType MoveStructuredType() const;
  AnyType MoveArrayType() const;
  AnyType MoveSimpleType() const;
  std::unique_ptr<AnyTypeBuildNode> element_node;
  std::unique_ptr<MemberTypeArrayBuildNode> member_array_node;
  std::string current_member_name;
  bool struct_type;  // true if structure
  bool array_type;  // true if array
  std::string type_name;
  std::size_t number_elements;
  std::vector<std::pair<std::string, AnyType>> member_types;
  AnyType element_type;
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_AnyTypeBuildNode_h_
