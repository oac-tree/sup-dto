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
 * Copyright (c) : 2010-2025 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include "performance.h"

#include <sup/dto/anytype.h>
#include <sup/dto/anyvalue.h>
#include <sup/dto/anyvalue_helper.h>

#include <iostream>

using namespace sup::dto;

int main()
{
  performance::PrintDateTime();

  // Measure AnyType copy and equality checks
  std::cout << "Test AnyType copy/equality performance" << std::endl;
  std::cout << "**************************************" << std::endl;
  performance::RunTestFunction(performance::MeasureCopyAnyType);

  std::cout << std::endl;

  // Measure AnyType copy and equality checks
  std::cout << "Test AnyValue copy/equality performance" << std::endl;
  std::cout << "***************************************" << std::endl;
  performance::RunTestFunction(performance::MeasureCopyAnyValue);

  std::cout << std::endl;

  // Measure JSON performance:
  std::cout << "Test JSON serialize/parse performance" << std::endl;
  std::cout << "*************************************" << std::endl;
  performance::RunTestFunction(performance::MeasureEncoderWithValue<performance::JSONEncoder>);

  std::cout << std::endl;

  // Measure binary performance:
  std::cout << "Test binary serialize/parse performance" << std::endl;
  std::cout << "***************************************" << std::endl;
  performance::RunTestFunction(performance::MeasureEncoderWithValue<performance::BinaryEncoder>);
}