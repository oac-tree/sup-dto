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
 * @file ArrayValueBuildNode.h
 * @brief Header file for the ArrayValueBuildNode class.
 * @date 02/03/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the ArrayValueBuildNode class.
 */

#ifndef _SUP_ArrayValueBuildNode_h_
#define _SUP_ArrayValueBuildNode_h_

#include "IAnyBuildNode.h"
#include "AnyValue.h"

#include <memory>

namespace sup
{
namespace dto
{
class ArrayValueBuildNode;

class ArrayValueBuildNode : public IAnyBuildNode
{
public:
  ArrayValueBuildNode(IAnyBuildNode* parent);
  ~ArrayValueBuildNode();

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

  AnyValue MoveAnyValue() const;

private:
  std::unique_ptr<ArrayValueBuildNode> value_node;
  std::unique_ptr<ArrayValueBuildNode> value_node;
  AnyValue anyvalue;
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_ArrayValueBuildNode_h_
