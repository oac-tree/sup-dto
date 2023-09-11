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
 * Copyright (c) : 2010-2023 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
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

std::pair<std::string, std::string> StripFirstFieldName(const std::string& fieldname)
{
  auto pos = fieldname.find_first_of("[.");
  if (pos == std::string::npos)
  {
    return { fieldname, ""};
  }
  auto first = fieldname.substr(0u, pos);
  auto rest = fieldname.substr(pos);
  if (rest[0u] == '.')
  {
    // Only strip dots
    rest = rest.substr(1u);
  }
  return { first, rest };
}

}  // namespace utils

}  // namespace dto

}  // namespace sup
