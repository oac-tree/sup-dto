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
 * @file AnyTypeSerializeStack.h
 * @brief Header file for AnyType serialization stack.
 * @date 16/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the AnyType serialization stack.
 */

#ifndef _SUP_AnyTypeSerializeStack_h_
#define _SUP_AnyTypeSerializeStack_h_

#include "AnySerializeNode.h"

#include <stack>

namespace sup
{
namespace dto
{

/**
 * @brief AnyType serialization node stack.
 *
 * @details This stack handles serialization calls on push/pop.
 */
class AnyTypeSerializeStack
{
public:
  AnyTypeSerializeStack();
  ~AnyTypeSerializeStack() = default;

  bool empty() const;

  AnyTypeSerializeNode& top();

  void push(AnyTypeSerializeNode&& node, IAnySerializer<AnyType>& serializer);
  void pop(IAnySerializer<AnyType>& serializer);

private:
  std::stack<AnyTypeSerializeNode> node_stack;
  bool add_separator;
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_AnyTypeSerializeStack_h_
