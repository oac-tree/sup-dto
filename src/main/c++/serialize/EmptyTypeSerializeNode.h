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
 * @file EmptyTypeSerializeNode.h
 * @brief Header file for the EmptyTypeSerializeNode class.
 * @date 16/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the EmptyTypeSerializeNode class.
 */

#ifndef _SUP_EmptyTypeSerializeNode_h_
#define _SUP_EmptyTypeSerializeNode_h_

#include "AnyTypeSerializeNode.h"

#include <string>

namespace sup
{
namespace dto
{
/**
 * @brief Serialization node for the empty type.
 */
class EmptyTypeSerializeNode : public IAnyTypeSerializeNode
{
public:
  EmptyTypeSerializeNode(const AnyType* anytype);
  ~EmptyTypeSerializeNode() override;

  std::unique_ptr<IAnyTypeSerializeNode> NextChild() override;

  void AddProlog(IAnySerializer<AnyType>& serializer) const override;
  void AddSeparator(IAnySerializer<AnyType>& serializer) const override;
  void AddEpilog(IAnySerializer<AnyType>& serializer) const override;
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_EmptyTypeSerializeNode_h_
