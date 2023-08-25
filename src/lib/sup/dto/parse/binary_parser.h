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

#ifndef SUP_DTO_BINARY_PARSER_H_
#define SUP_DTO_BINARY_PARSER_H_

#include <sup/dto/anyvalue.h>

#include <vector>

namespace sup
{
namespace dto
{
using ByteIterator = typename std::vector<sup::dto::uint8>::iterator;

AnyValue ParseAnyValue(ByteIterator& begin, const ByteIterator& end);

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_BINARY_PARSER_H_
