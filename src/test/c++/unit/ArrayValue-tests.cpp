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
#include "AnyValueExceptions.h"

using namespace sup::dto;

TEST(ArrayValueTest, ArrayValue)
{
  AnyValue my_array = ArrayValue({
    {SignedInteger64, 1}, 2, 3, 4, 5
  }, "my_array_t");
  AnyType my_array_t(5, SignedInteger64, "my_array_t");
  EXPECT_FALSE(IsEmptyValue(my_array));
  EXPECT_FALSE(IsStructValue(my_array));
  EXPECT_TRUE(IsArrayValue(my_array));
  EXPECT_FALSE(IsScalarValue(my_array));
  EXPECT_EQ(my_array.GetTypeCode(), TypeCode::Array);
  EXPECT_EQ(my_array.GetType(), my_array_t);
  EXPECT_EQ(my_array.GetTypeName(), "my_array_t");
  EXPECT_EQ(my_array.NumberOfElements(), 5);
  EXPECT_EQ(my_array[0], 1);
  EXPECT_EQ(my_array["[1]"], 2);
  EXPECT_EQ(my_array["[2]."], 3);
  my_array[1] = 25;
  EXPECT_EQ(my_array["[1]"], 25);
}

TEST(ArrayValueTest, Construction)
{
  // zero-size array:
  std::string zero_size_name = "zero_size_array_t";
  AnyValue zero_size_array(0, SignedInteger8, zero_size_name);
  EXPECT_FALSE(IsEmptyValue(zero_size_array));
  EXPECT_FALSE(IsStructValue(zero_size_array));
  EXPECT_TRUE(IsArrayValue(zero_size_array));
  EXPECT_FALSE(IsScalarValue(zero_size_array));
  EXPECT_EQ(zero_size_array.GetTypeCode(), TypeCode::Array);
  EXPECT_EQ(zero_size_array.GetType(), AnyType(0, SignedInteger8, zero_size_name));
  EXPECT_NE(zero_size_array.GetType(), AnyType(1, SignedInteger8, zero_size_name));
  EXPECT_NE(zero_size_array.GetType(), AnyType(0, UnsignedInteger8, zero_size_name));
  EXPECT_NE(zero_size_array.GetType(), AnyType(0, SignedInteger8, "different_name"));
  EXPECT_EQ(zero_size_array.GetTypeName(), zero_size_name);
  EXPECT_EQ(zero_size_array.NumberOfElements(), 0);

  // Zero size array cannot be constructed from a list:
  EXPECT_THROW(ArrayValue({}), InvalidOperationException);
}

TEST(ArrayValueTest, CopyConstruction)
{
  AnyValue my_array = ArrayValue({
    {SignedInteger64, 1}, 2, 3, 4, 5
  }, "my_array_t");
  AnyType my_array_t(5, SignedInteger64, "my_array_t");
  EXPECT_FALSE(IsEmptyValue(my_array));
  EXPECT_FALSE(IsStructValue(my_array));
  EXPECT_TRUE(IsArrayValue(my_array));
  EXPECT_FALSE(IsScalarValue(my_array));
  EXPECT_EQ(my_array.GetTypeCode(), TypeCode::Array);
  EXPECT_EQ(my_array.GetType(), my_array_t);
  EXPECT_EQ(my_array.GetTypeName(), "my_array_t");
  EXPECT_EQ(my_array.NumberOfElements(), 5);
  EXPECT_EQ(my_array[0], 1);
  EXPECT_EQ(my_array["[1]"], 2);
  EXPECT_EQ(my_array["[2]."], 3);

  AnyValue copy{my_array};
  EXPECT_EQ(copy, my_array);
  EXPECT_FALSE(IsEmptyValue(copy));
  EXPECT_FALSE(IsStructValue(copy));
  EXPECT_TRUE(IsArrayValue(copy));
  EXPECT_FALSE(IsScalarValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Array);
  EXPECT_EQ(copy.GetType(), my_array_t);
  EXPECT_EQ(copy.GetTypeName(), "my_array_t");
  EXPECT_EQ(copy.NumberOfElements(), 5);
  EXPECT_EQ(copy[0], 1);
  EXPECT_EQ(copy["[1]"], 2);
  EXPECT_EQ(copy["[2]."], 3);
}

TEST(ArrayValueTest, ElementAccess)
{
  AnyValue my_array = ArrayValue({
    {SignedInteger64, 1}, 2, 3, 4, 5
  }, "my_array_t");
  EXPECT_EQ(my_array["[0]"], 1);
  EXPECT_EQ(my_array[0], 1);
  EXPECT_EQ(my_array.NumberOfElements(), 5);
  my_array["[1]"] = 12;
  my_array[2] = 13;
  EXPECT_EQ(my_array["[2]"], 13);
  EXPECT_EQ(my_array[1], 12);

  AnyValue scalar = {UnsignedInteger16, 55};
  EXPECT_THROW(scalar["[0]"], InvalidOperationException);
  EXPECT_THROW(scalar[0], InvalidOperationException);
  EXPECT_EQ(scalar.NumberOfElements(), 0);

  AnyValue two_scalars = {{
    {"signed", {SignedInteger8, 1}},
    {"unsigned", {UnsignedInteger8, 12}}
  }};
  EXPECT_THROW(two_scalars["[0]"], UnknownKeyException);
  EXPECT_THROW(two_scalars[0], InvalidOperationException);
  EXPECT_EQ(two_scalars.NumberOfElements(), 0);
}

TEST(ArrayValueTest, InvalidElementAccess)
{
  AnyValue my_array = ArrayValue({
    {SignedInteger64, 1}, 2, 3, 4, 5
  }, "my_array_t");
  EXPECT_THROW(my_array[""], InvalidOperationException);
  EXPECT_THROW(my_array["3"], InvalidOperationException);
  EXPECT_THROW(my_array["[3"], InvalidOperationException);
  EXPECT_THROW(my_array["[6]"], InvalidOperationException);
  EXPECT_THROW(my_array[5], InvalidOperationException);
  EXPECT_THROW(my_array["[three]"], InvalidOperationException);
  EXPECT_THROW(my_array["[123456789012345678901]"], InvalidOperationException);
}

TEST(ArrayValueTest, ArrayEquality)
{
  AnyValue my_array = ArrayValue({
    {SignedInteger64, 1}, 2, 3, 4, 5
  }, "my_array_t");
  AnyType my_array_t(5, SignedInteger64, "my_array_t");
  AnyValue other(my_array_t);
  EXPECT_NE(my_array, other);
  other = my_array;
  EXPECT_EQ(my_array, other);
  AnyValue scalar = 4u;
  EXPECT_NE(my_array, scalar);
}

TEST(ArrayValueTest, InvalidArrayAssign)
{
  AnyValue my_array = ArrayValue({
    {SignedInteger64, 1}, 2, 3, 4, 5
  }, "my_array_t");
  EXPECT_FALSE(IsEmptyValue(my_array));
  EXPECT_FALSE(IsStructValue(my_array));
  EXPECT_TRUE(IsArrayValue(my_array));
  EXPECT_FALSE(IsScalarValue(my_array));
  AnyType my_array_t(9, SignedInteger64, "my_array_t");
  AnyValue other(my_array_t);
  EXPECT_FALSE(IsEmptyValue(other));
  EXPECT_FALSE(IsStructValue(other));
  EXPECT_TRUE(IsArrayValue(other));
  EXPECT_FALSE(IsScalarValue(other));
  EXPECT_THROW(other = my_array, InvalidConversionException);
  AnyValue scalar = 4u;
  EXPECT_THROW(other = scalar, InvalidConversionException);
}
