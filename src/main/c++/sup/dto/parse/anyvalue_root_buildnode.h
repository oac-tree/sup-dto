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

#ifndef _SUP_AnyValueRootBuildNode_h_
#define _SUP_AnyValueRootBuildNode_h_

#include "i_any_buildnode.h"
#include "sup/dto/anyvalue.h"

#include <memory>

namespace sup
{
namespace dto
{
class AnyValueArrayBuildNode;

class AnyValueRootBuildNode : public IAnyBuildNode
{
public:
  AnyValueRootBuildNode(const AnyTypeRegistry* anytype_registry, IAnyBuildNode* parent = nullptr);
  ~AnyValueRootBuildNode();

  IAnyBuildNode* GetArrayNode() override;
  bool PopArrayNode() override;

  AnyValue MoveAnyValue() const;

private:
  std::unique_ptr<AnyValueArrayBuildNode> array_node;
  AnyValue anyvalue;
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_AnyValueRootBuildNode_h_
