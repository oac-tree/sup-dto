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
 * Copyright (c) : 2010-2025 ITER Organization,
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

#include "anyvalue_compare_node.h"

namespace sup
{
namespace dto
{

AnyValueCompareNode::AnyValueCompareNode(const AnyValue* left, const AnyValue* right)
  : m_left{left}
  , m_right{right}
  , m_n_children{m_left->NumberOfChildren()}
  , m_index{0}
{}

}  // namespace dto

}  // namespace sup
