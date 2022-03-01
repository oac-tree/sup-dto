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
 * @file MemberTypeArrayBuildNode.h
 * @brief Header file for the MemberTypeArrayBuildNode class.
 * @date 01/03/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the MemberTypeArrayBuildNode class.
 */

#ifndef _SUP_MemberTypeArrayBuildNode_h_
#define _SUP_MemberTypeArrayBuildNode_h_

#include "IAnyBuildNode.h"
#include "AnyType.h"

#include <memory>

namespace sup
{
namespace dto
{
class MemberTypeArrayBuildNode : public IAnyBuildNode
{
public:
  MemberTypeArrayBuildNode(IAnyBuildNode* parent);
  ~MemberTypeArrayBuildNode();

  IAnyBuildNode* GetStructureNode() override;
  bool PopStructureNode() override;

private:
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_MemberTypeArrayBuildNode_h_
