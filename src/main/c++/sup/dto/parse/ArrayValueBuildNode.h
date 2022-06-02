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

#ifndef _SUP_ArrayValueBuildNode_h_
#define _SUP_ArrayValueBuildNode_h_

#include "IAnyBuildNode.h"
#include "sup/dto/anyvalue.h"

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
  ~ArrayValueBuildNode();

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

  AnyValue MoveAnyValue() const;

private:
  std::unique_ptr<AnyValueBuildNode> value_node;
  std::unique_ptr<IAnyBuildNode> array_node;
  std::size_t current_index;
  std::size_t size;
  AnyValue& anyvalue;
};

std::unique_ptr<IAnyBuildNode> CreateArrayBuildNode(
  const AnyTypeRegistry* anytype_registry, IAnyBuildNode* parent, AnyValue& anyvalue);

}  // namespace dto

}  // namespace sup

#endif  // _SUP_ArrayValueBuildNode_h_
