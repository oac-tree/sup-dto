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

#include <gtest/gtest.h>

#include "AnyValue.h"

using namespace sup::dto;

struct __attribute__((__packed__)) TwoScalarsType
{
  int8 signed_scalar;
  uint8 unsigned_scalar;
};

TEST(AnyValueToCTypeTest, Success)
{
  AnyValue two_scalars = {{
    {"signed", {SignedInteger8, 1}},
    {"unsigned", {UnsignedInteger8, 12}}
  }};
  auto two_scalars_c = two_scalars.As<TwoScalarsType>();
  auto byte_array = AnyValueToByteArray(two_scalars);
  std::cout << (int)byte_array[0] << ", " << (int)byte_array[1];

  EXPECT_EQ(two_scalars_c.signed_scalar, 1);
  EXPECT_EQ(two_scalars_c.unsigned_scalar, 12);
}
