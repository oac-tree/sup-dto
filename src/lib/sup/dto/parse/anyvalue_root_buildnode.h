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

#ifndef SUP_DTO_ANYVALUE_ROOT_BUILDNODE_H_
#define SUP_DTO_ANYVALUE_ROOT_BUILDNODE_H_

#include <sup/dto/parse/i_any_buildnode.h>
#include <sup/dto/anyvalue.h>

#include <memory>

namespace sup
{
namespace dto
{
class AnyValueArrayBuildNode;

class AnyValueRootBuildNode : public IAnyBuildNode
{
public:
  AnyValueRootBuildNode(const AnyTypeRegistry* anytype_registry, IAnyBuildNode* parent);
  explicit AnyValueRootBuildNode(const AnyTypeRegistry* anytype_registry);

  ~AnyValueRootBuildNode() override;

  AnyValueRootBuildNode(const AnyValueRootBuildNode& other) = delete;
  AnyValueRootBuildNode(AnyValueRootBuildNode&& other) = delete;
  AnyValueRootBuildNode& operator=(const AnyValueRootBuildNode& other) = delete;
  AnyValueRootBuildNode& operator=(AnyValueRootBuildNode&& other) = delete;


  IAnyBuildNode* GetArrayNode() override;
  bool PopArrayNode() override;

  AnyValue MoveAnyValue();

private:
  std::unique_ptr<AnyValueArrayBuildNode> m_array_node;
  AnyValue m_anyvalue;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ANYVALUE_ROOT_BUILDNODE_H_
