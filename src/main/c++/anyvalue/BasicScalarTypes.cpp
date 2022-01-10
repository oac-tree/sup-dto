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

#include "BasicScalarTypes.h"

namespace sup
{
namespace dto
{

static_assert(sizeof(int8) == 1, "int8 type needs to have size 1 byte");
static_assert(sizeof(uint8) == 1, "uint8 type needs to have size 1 byte");

}  // namespace dto

}  // namespace sup
