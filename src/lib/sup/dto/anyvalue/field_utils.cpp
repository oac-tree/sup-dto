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

#include "field_utils.h"

#include <sup/dto/anyvalue_exceptions.h>

namespace sup
{
namespace dto
{
namespace utils
{
void VerifyMemberName(const std::string& name)
{
  if (name.empty())
  {
    throw InvalidOperationException("Member names cannot be empty");
  }
  if (name.find_first_of(" [].") != std::string::npos)
  {
    throw InvalidOperationException("Member names cannot contain spaces, square brackets or dots");
  }
}

}  // namespace utils

}  // namespace dto

}  // namespace sup
