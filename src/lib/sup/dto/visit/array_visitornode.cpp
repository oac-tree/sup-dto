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
 * Copyright (c) : 2010-2026 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 * SPDX-License-Identifier: MIT
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file LICENSE located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include "array_visitornode.h"

namespace sup
{
namespace dto
{

template <>
std::unique_ptr<IAnyVisitorNode<AnyType>> ArrayVisitorNode<AnyType>::NextChild()
{
  if (m_next_index > 0)
  {
    return {};
  }
  ++m_next_index;
  AnyType *element_type = &this->GetValue()->operator[]("[]");
  return CreateVisitorNode(element_type);
}

template <>
std::unique_ptr<IAnyVisitorNode<const AnyType>> ArrayVisitorNode<const AnyType>::NextChild()
{
  if (m_next_index > 0)
  {
    return {};
  }
  ++m_next_index;
  const AnyType *element_type = &this->GetValue()->operator[]("[]");
  return CreateVisitorNode(element_type);
}

}  // namespace dto

}  // namespace sup
