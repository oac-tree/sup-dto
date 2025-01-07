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

#include <gtest/gtest.h>

#include <sup/dto/anyvalue.h>
#include <sup/dto/anyvalue_exceptions.h>

using namespace sup::dto;

TEST(ArrayValueInvariantTest, StructElement)
{
  // define array of structures
  AnyType two_scalars{{
    {"first", UnsignedInteger8Type},
    {"second", UnsignedInteger8Type}
  }};
  std::string array_name = "two_scalar_array";
  AnyValue array_value{2, two_scalars, array_name};
  EXPECT_TRUE(IsArrayValue(array_value));

  // Do not allow changing type of array elements that are structs:
  // EXPECT_THROW(array_value[0].AddMember("NotAllowed", 13), InvalidOperationException);
}

TEST(ArrayValueInvariantTest, ArrayElement)
{
  // define array of arrays
  AnyValue scalar_array{5, SignedInteger32Type, "int32x5"};
  AnyValue array_value = ArrayValue({scalar_array, scalar_array}, "int32x5x2");
  EXPECT_TRUE(IsArrayValue(array_value));

  // Do not allow changing type of array elements that are arrays:
  EXPECT_THROW(array_value[1].AddElement({SignedInteger32Type, 1}), InvalidOperationException);
}

TEST(ArrayValueInvariantTest, ComplexElement)
{
  // define array of struct containing array
  AnyValue scalar_array{5, SignedInteger32Type, "int32x5"};
  AnyValue struct_el{{
    {"scalars", scalar_array},
    {"name", "Scalar list"}
  }, "struct_el"};
  AnyValue array_value = ArrayValue({struct_el, struct_el}, "structx2");
  EXPECT_TRUE(IsArrayValue(array_value));

  // Do not allow changing type of array elements:
  EXPECT_THROW(array_value["[0].scalars"].AddElement({SignedInteger32Type, 1}), InvalidOperationException);
}
