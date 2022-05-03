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

#ifndef _SUP_AnyValueValueElementBuildNode_h_
#define _SUP_AnyValueValueElementBuildNode_h_

#include "IAnyBuildNode.h"
#include "AnyValue.h"

#include <memory>

namespace sup
{
namespace dto
{
class AnyValueBuildNode;
class ArrayValueBuildNode;

class AnyValueValueElementBuildNode : public IAnyBuildNode
{
public:
  AnyValueValueElementBuildNode(const AnyTypeRegistry* anytype_registry, IAnyBuildNode* parent,
                                AnyValue& anyvalue);
  ~AnyValueValueElementBuildNode();

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
  std::unique_ptr<AnyValueBuildNode> value_node;
  std::unique_ptr<ArrayValueBuildNode> array_node;
  std::string member_name;
  AnyValue& anyvalue;
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_AnyValueValueElementBuildNode_h_
