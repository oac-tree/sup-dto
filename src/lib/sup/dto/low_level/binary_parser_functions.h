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

#ifndef SUP_DTO_BINARY_PARSER_FUNCTIONS_H_
#define SUP_DTO_BINARY_PARSER_FUNCTIONS_H_

#include <sup/dto/parse/binary_parser.h>

#include <array>
#include <functional>

namespace sup
{
namespace dto
{

sup::dto::uint8 FetchToken(ByteIterator& it);

std::string ParseBinaryString(ByteIterator& it, ByteIterator end);

sup::dto::uint64 ParseSize(ByteIterator& it, ByteIterator end);

void ParseBinaryScalar(AnyValue& anyvalue, ByteIterator& it, ByteIterator end);

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_BINARY_PARSER_FUNCTIONS_H_
