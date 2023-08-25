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

#ifndef SUP_DTO_BINARY_PARSER_FUNCTIONS_H_
#define SUP_DTO_BINARY_PARSER_FUNCTIONS_H_

#include <sup/dto/parse/binary_parser.h>

namespace sup
{
namespace dto
{
template <typename T>
T ParseBinaryScalarT(ByteIterator& it, const ByteIterator& end)
{
  (void)it;
  (void)end;
  return {};
}

std::string ParseBinaryString(ByteIterator& it, const ByteIterator& end);

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_BINARY_PARSER_FUNCTIONS_H_
