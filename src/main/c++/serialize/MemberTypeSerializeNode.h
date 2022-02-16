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
 * @file MemberTypeSerializeNode.h
 * @brief Header file for the MemberTypeSerializeNode class.
 * @date 16/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the MemberTypeSerializeNode class.
 */

#ifndef _SUP_MemberTypeSerializeNode_h_
#define _SUP_MemberTypeSerializeNode_h_

#include "AnyTypeSerializeNode.h"

#include <string>

namespace sup
{
namespace dto
{
/**
 * @brief Serialization node for structured types.
 */
class MemberTypeSerializeNode : public IAnyTypeSerializeNode
{
public:
  MemberTypeSerializeNode(const AnyType* anytype, const std::string& member_name);
  ~MemberTypeSerializeNode() override;

  std::unique_ptr<IAnyTypeSerializeNode> NextChild() override;

  void AddProlog(IAnyTypeSerializer& serializer) const override;
  void AddSeparator(IAnyTypeSerializer& serializer) const override;
  void AddEpilog(IAnyTypeSerializer& serializer) const override;

private:
  std::string member_name;
  bool child_returned;
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_MemberTypeSerializeNode_h_
