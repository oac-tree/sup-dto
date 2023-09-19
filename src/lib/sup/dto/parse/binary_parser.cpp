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

#include "binary_parser.h"

#include <sup/dto/parse/binary_type_parser_helper.h>

namespace sup
{
namespace dto
{

AnyType ParseAnyType(ByteIterator& iter, ByteIterator end)
{
  BinaryTypeParserHelper helper;
  while (iter != end)
  {
    if (!helper.HandleToken(iter, end))
    {
      break;
    }
  }
  return helper.MoveAnyType();
}

}  // namespace dto

}  // namespace sup
