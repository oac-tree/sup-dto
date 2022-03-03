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

#include "JSONPerformance.h"

#include "AnyType.h"
#include "AnyValue.h"
#include "AnyValueHelper.h"

using namespace sup::dto;

int main()
{
  auto scalar_mix_t = performance::CreateScalarMix_Type();
  performance::MeasureSerializeParse(scalar_mix_t);
}