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

#include "anytype_compare_node.h"

namespace sup
{
namespace dto
{

AnyTypeCompareNode::AnyTypeCompareNode(const AnyType* left, const AnyType* right)
  : m_left{left}
  , m_right{right}
  , m_n_children{m_left->NumberOfChildren()}
  , m_index{0}
{}

}  // namespace dto

}  // namespace sup
