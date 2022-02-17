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
 * @file StructTypeSerializeNode.h
 * @brief Header file for the StructTypeSerializeNode class.
 * @date 16/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the StructTypeSerializeNode class.
 */

#ifndef _SUP_StructTypeSerializeNode_h_
#define _SUP_StructTypeSerializeNode_h_

#include "AnyTypeSerializeNode.h"

namespace sup
{
namespace dto
{
/**
 * @brief Serialization node for structured types.
 */
class StructTypeSerializeNode : public IAnyTypeSerializeNode
{
public:
  StructTypeSerializeNode(const AnyType* anytype);
  ~StructTypeSerializeNode() override;

  std::unique_ptr<IAnyTypeSerializeNode> NextChild() override;

  void AddProlog(IAnySerializer<AnyType>& serializer) const override;
  void AddSeparator(IAnySerializer<AnyType>& serializer) const override;
  void AddEpilog(IAnySerializer<AnyType>& serializer) const override;

private:
  std::size_t next_index;
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_StructTypeSerializeNode_h_
