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

#ifndef SUP_DTO_BASIC_SCALAR_TYPES_H_
#define SUP_DTO_BASIC_SCALAR_TYPES_H_

namespace sup
{
namespace dto
{

using boolean = bool;
using char8 = char;
using int8 = signed char;
using uint8 = unsigned char;
using int16 = signed short;
using uint16 = unsigned short;
using int32 = signed int;
using uint32 = unsigned int;
using int64 = signed long;
using uint64 = unsigned long;
using float32 = float;
using float64 = double;

// Only used for (de)serializing C types:
const uint32 kStringMaxLength = 64u;

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_BASIC_SCALAR_TYPES_H_
