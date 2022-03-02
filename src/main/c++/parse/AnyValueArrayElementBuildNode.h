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
 * @file AnyValueArrayElementBuildNode.h
 * @brief Header file for the AnyValueArrayElementBuildNode class.
 * @date 02/03/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the AnyValueArrayElementBuildNode class.
 */

#ifndef _SUP_AnyValueArrayElementBuildNode_h_
#define _SUP_AnyValueArrayElementBuildNode_h_

#include "IAnyBuildNode.h"
#include "AnyValue.h"

#include <memory>

namespace sup
{
namespace dto
{
class AnyTypeBuildNode;
class AnyValueBuildNode;

class AnyValueArrayElementBuildNode : public IAnyBuildNode
{
public:
  AnyValueArrayElementBuildNode(IAnyBuildNode* parent, AnyValue& anyvalue);
  ~AnyValueArrayElementBuildNode();

  bool String(const std::string& str) override;
  bool Member(const std::string& str) override;

  IAnyBuildNode* GetStructureNode() override;
  bool PopStructureNode() override;

  AnyType MoveAnyType() const;
  AnyValue MoveAnyValue() const;

private:
  std::unique_ptr<AnyTypeBuildNode> type_node;
  std::unique_ptr<AnyValueBuildNode> value_node;
  std::string member_name;
  bool encoding_ok;
  AnyType anytype;
  AnyValue& anyvalue;
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_AnyValueArrayElementBuildNode_h_
