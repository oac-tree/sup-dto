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
 * Copyright (c) : 2010-2024 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#ifndef SUP_DTO_FIELD_UTILS_H_
#define SUP_DTO_FIELD_UTILS_H_

#include <string>
#include <utility>

namespace sup
{
namespace dto
{
namespace utils
{
void VerifyMemberName(const std::string& name);

std::pair<std::string, std::string> StripFirstFieldName(const std::string& fieldname);

}  // namespace utils

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_FIELD_UTILS_H_
