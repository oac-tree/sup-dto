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

/**
 * @file AnyValueArrayBuildNode.h
 * @brief Header file for the AnyValueArrayBuildNode class.
 * @date 02/03/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the AnyValueArrayBuildNode class.
 */

#ifndef _SUP_AnyValueArrayBuildNode_h_
#define _SUP_AnyValueArrayBuildNode_h_

#include "IAnyBuildNode.h"
#include "AnyValue.h"

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
  AnyValueArrayBuildNode(IAnyBuildNode* parent);
  ~AnyValueArrayBuildNode();

  IAnyBuildNode* GetStructureNode() override;
  bool PopStructureNode() override;

  AnyValue MoveAnyValue() const;

private:
  std::unique_ptr<AnyValueEncodingElementBuildNode> encoding_node;
  std::unique_ptr<AnyValueTypeElementBuildNode> type_node;
  std::unique_ptr<AnyValueValueElementBuildNode> value_node;
  unsigned processed_nodes;
  AnyValue anyvalue;
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_AnyValueArrayBuildNode_h_
