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

#ifndef SUP_DTO_NODE_UTILS_H_
#define SUP_DTO_NODE_UTILS_H_

#include <limits>

namespace sup
{
namespace dto
{
constexpr std::size_t kInvalidIndex = std::numeric_limits<std::size_t>::max();

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_NODE_UTILS_H_
