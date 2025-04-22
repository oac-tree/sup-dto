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

#ifndef SUP_DTO_BINARY_TOKENS_H_
#define SUP_DTO_BINARY_TOKENS_H_

#include <sup/dto/basic_scalar_types.h>

namespace sup
{
namespace dto
{

const sup::dto::uint8 EMPTY_TOKEN      = 0x00u;
const sup::dto::uint8 BOOL_TOKEN       = 0x01u;
const sup::dto::uint8 CHAR8_TOKEN      = 0x02u;
const sup::dto::uint8 INT8_TOKEN       = 0x03u;
const sup::dto::uint8 UINT8_TOKEN      = 0x04u;
const sup::dto::uint8 INT16_TOKEN      = 0x05u;
const sup::dto::uint8 UINT16_TOKEN     = 0x06u;
const sup::dto::uint8 INT32_TOKEN      = 0x07u;
const sup::dto::uint8 UINT32_TOKEN     = 0x08u;
const sup::dto::uint8 INT64_TOKEN      = 0x09u;
const sup::dto::uint8 UINT64_TOKEN     = 0x0Au;
const sup::dto::uint8 FLOAT32_TOKEN    = 0x0Bu;
const sup::dto::uint8 FLOAT64_TOKEN    = 0x0Cu;
const sup::dto::uint8 STRING_TOKEN     = 0x0Du;

const sup::dto::uint8 START_STRUCT_TOKEN = 0x20u;
const sup::dto::uint8 END_STRUCT_TOKEN   = 0x21u;
const sup::dto::uint8 START_ARRAY_TOKEN  = 0x22u;
const sup::dto::uint8 END_ARRAY_TOKEN    = 0x23u;

const sup::dto::uint8 ANYVALUE_TOKEN   = 0xE0u;
const sup::dto::uint8 ANYTYPE_TOKEN    = 0xE1u;

const sup::dto::uint8 SHORT_SIZE_LIMIT = 0xFFu;
const sup::dto::uint8 LONG_SIZE_TOKEN = SHORT_SIZE_LIMIT;

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_BINARY_TOKENS_H_
