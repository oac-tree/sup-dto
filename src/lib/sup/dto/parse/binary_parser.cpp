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
#include <sup/dto/parse/binary_value_parser_helper.h>

namespace sup
{
namespace dto
{

AnyValue ParseAnyValue(ByteIterator& it, const ByteIterator& end)
{
  BinaryValueParserHelper helper;
  while (it != end)
  {
    if (!helper.HandleToken(it, end))
    {
      break;
    }
  }
  // Make sure the helper has correctly finished (e.g. stack empty)
  return helper.MoveAnyValue();
}

AnyType ParseAnyType(ByteIterator& it, const ByteIterator& end)
{
  BinaryTypeParserHelper helper;
  while (it != end)
  {
    if (!helper.HandleToken(it, end))
    {
      break;
    }
  }
  return helper.MoveAnyType();
}

}  // namespace dto

}  // namespace sup
