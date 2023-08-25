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

#ifndef SUP_DTO_BINARY_TOKENS_H_
#define SUP_DTO_BINARY_TOKENS_H_

#include <sup/dto/basic_scalar_types.h>

namespace sup
{
namespace dto
{

const sup::dto::uint8 EMPTY_TOKEN      = 0x00;
const sup::dto::uint8 BOOL_TOKEN       = 0x01;
const sup::dto::uint8 CHAR8_TOKEN      = 0x02;
const sup::dto::uint8 INT8_TOKEN       = 0x03;
const sup::dto::uint8 UINT8_TOKEN      = 0x04;
const sup::dto::uint8 INT16_TOKEN      = 0x05;
const sup::dto::uint8 UINT16_TOKEN     = 0x06;
const sup::dto::uint8 INT32_TOKEN      = 0x07;
const sup::dto::uint8 UINT32_TOKEN     = 0x08;
const sup::dto::uint8 INT64_TOKEN      = 0x09;
const sup::dto::uint8 UINT64_TOKEN     = 0x0A;
const sup::dto::uint8 FLOAT32_TOKEN    = 0x0B;
const sup::dto::uint8 FLOAT64_TOKEN    = 0x0C;
const sup::dto::uint8 STRING_TOKEN     = 0x0D;

const sup::dto::uint8 START_STRUCT_TOKEN = 0x20;
const sup::dto::uint8 END_STRUCT_TOKEN   = 0x21;
const sup::dto::uint8 START_ARRAY_TOKEN  = 0x22;
const sup::dto::uint8 END_ARRAY_TOKEN    = 0x23;

const sup::dto::uint8 ANYVALUE_TOKEN    = 0xE0;
const sup::dto::uint8 ANYTYPE_TOKEN    = 0xE1;

const sup::dto::uint8 SHORT_STRING_LENGTH_LIMIT = 0xFF;
const sup::dto::uint8 LONG_STRING_LENGTH_TOKEN = SHORT_STRING_LENGTH_LIMIT;

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_BINARY_TOKENS_H_
