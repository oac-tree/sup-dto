/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : SUP - DTO
 *
 * Description   : Unit test code
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

#ifndef SUP_DTO_SCALAR_FROM_BYTES_H_
#define SUP_DTO_SCALAR_FROM_BYTES_H_

#include <sup/dto/anyvalue.h>

namespace sup
{
namespace dto
{

std::size_t AssignFromHostOrder(AnyValue& anyvalue, const uint8* bytes, std::size_t size,
                                std::size_t position);

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_SCALAR_FROM_BYTES_H_
