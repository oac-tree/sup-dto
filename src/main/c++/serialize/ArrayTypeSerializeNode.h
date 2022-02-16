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
 * @file ArrayTypeSerializeNode.h
 * @brief Header file for the ArrayTypeSerializeNode class.
 * @date 16/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the ArrayTypeSerializeNode class.
 */

#ifndef _SUP_ArrayTypeSerializeNode_h_
#define _SUP_ArrayTypeSerializeNode_h_

#include "AnyTypeSerializeNode.h"

namespace sup
{
namespace dto
{
/**
 * @brief Serialization node for structured types.
 */
class ArrayTypeSerializeNode : public IAnyTypeSerializeNode
{
public:
  ArrayTypeSerializeNode(const AnyType* anytype);
  ~ArrayTypeSerializeNode() override;

  std::unique_ptr<IAnyTypeSerializeNode> NextChild() override;

  void AddProlog(IAnyTypeSerializer& serializer) const override;
  void AddSeparator(IAnyTypeSerializer& serializer) const override;
  void AddEpilog(IAnyTypeSerializer& serializer) const override;

private:
  std::size_t next_index;
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_ArrayTypeSerializeNode_h_
