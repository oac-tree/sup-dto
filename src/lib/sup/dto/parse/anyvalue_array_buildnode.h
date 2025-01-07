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

#ifndef SUP_DTO_ANYVALUE_ARRAY_BUILDNODE_H_
#define SUP_DTO_ANYVALUE_ARRAY_BUILDNODE_H_

#include <sup/dto/parse/i_any_buildnode.h>

#include <sup/dto/anyvalue.h>

#include <memory>

namespace sup
{
namespace dto
{
class AnyValueEncodingElementBuildNode;
class AnyValueTypeElementBuildNode;
class AnyValueValueElementBuildNode;

class AnyValueArrayBuildNode : public IAnyBuildNode
{
public:
  AnyValueArrayBuildNode(const AnyTypeRegistry* anytype_registry, IAnyBuildNode* parent);
  ~AnyValueArrayBuildNode() override;

  AnyValueArrayBuildNode(const AnyValueArrayBuildNode& other) = delete;
  AnyValueArrayBuildNode(AnyValueArrayBuildNode&& other) = delete;
  AnyValueArrayBuildNode& operator=(const AnyValueArrayBuildNode& other) = delete;
  AnyValueArrayBuildNode& operator=(AnyValueArrayBuildNode&& other) = delete;


  IAnyBuildNode* GetStructureNode() override;
  bool PopStructureNode() override;

  AnyValue MoveAnyValue();

private:
  std::unique_ptr<AnyValueEncodingElementBuildNode> m_encoding_node;
  std::unique_ptr<AnyValueTypeElementBuildNode> m_type_node;
  std::unique_ptr<AnyValueValueElementBuildNode> m_value_node;
  sup::dto::uint64 m_processed_nodes;
  AnyValue m_anyvalue;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ANYVALUE_ARRAY_BUILDNODE_H_
