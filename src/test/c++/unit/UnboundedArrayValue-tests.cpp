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

#include "sup/dto/AnyValue.h"
#include "sup/dto/AnyValueExceptions.h"

using namespace sup::dto;

TEST(UnboundedArrayValueTest, EmptyElementType)
{
  EXPECT_THROW(UnboundedArrayValue({AnyValue{}}), InvalidOperationException);
}

TEST(UnboundedArrayValueTest, UnboundedArrayType)
{
  AnyValue my_array = UnboundedArrayValue({
    {SignedInteger64, 1}, 2, 3, 4, 5
  }, "my_array_t");
  auto my_array_t = UnboundedArrayType(SignedInteger64, "my_array_t");
  EXPECT_FALSE(IsEmptyValue(my_array));
  EXPECT_FALSE(IsStructValue(my_array));
  EXPECT_FALSE(IsArrayValue(my_array));
  EXPECT_TRUE(IsUnboundedArrayValue(my_array));
  EXPECT_FALSE(IsScalarValue(my_array));
  EXPECT_EQ(my_array.GetTypeCode(), TypeCode::UnboundedArray);
  EXPECT_EQ(my_array.GetType(), my_array_t);
  EXPECT_EQ(my_array.GetTypeName(), "my_array_t");
  EXPECT_EQ(my_array.NumberOfElements(), 5);
  EXPECT_EQ(my_array[0], 1);
  EXPECT_EQ(my_array["[1]"], 2);
  EXPECT_EQ(my_array["[2]."], 3);
  my_array[1] = 25;
  EXPECT_EQ(my_array["[1]"], 25);
}

TEST(UnboundedArrayValueTest, Construction)
{
  // Construct from AnyType
  auto my_array_t = UnboundedArrayType(SignedInteger64, "my_array_t");
  AnyValue my_array{my_array_t};
  EXPECT_FALSE(IsEmptyValue(my_array));
  EXPECT_FALSE(IsStructValue(my_array));
  EXPECT_FALSE(IsArrayValue(my_array));
  EXPECT_TRUE(IsUnboundedArrayValue(my_array));
  EXPECT_FALSE(IsScalarValue(my_array));
  EXPECT_EQ(my_array.GetTypeCode(), TypeCode::UnboundedArray);
  EXPECT_EQ(my_array.GetType(), my_array_t);
  EXPECT_EQ(my_array.GetTypeName(), "my_array_t");
  EXPECT_EQ(my_array.NumberOfElements(), 0);

  // Construct from AnyType and AnyValue
  AnyValue my_other_array = UnboundedArrayValue({
    {SignedInteger64, 1}, 2, 3, 4, 5
  }, "my_array_t");
  AnyValue my_second_array{my_array_t, my_other_array};
  EXPECT_FALSE(IsEmptyValue(my_second_array));
  EXPECT_FALSE(IsStructValue(my_second_array));
  EXPECT_FALSE(IsArrayValue(my_second_array));
  EXPECT_TRUE(IsUnboundedArrayValue(my_second_array));
  EXPECT_FALSE(IsScalarValue(my_second_array));
  EXPECT_EQ(my_second_array.GetTypeCode(), TypeCode::UnboundedArray);
  EXPECT_EQ(my_second_array.GetType(), my_array_t);
  EXPECT_EQ(my_second_array.GetTypeName(), "my_array_t");
  EXPECT_EQ(my_second_array.NumberOfElements(), 5);

  // zero-size array:
  std::string zero_size_name = "zero_size_array_t";
  AnyValue zero_size_array(AnyType::unbounded_array_tag, SignedInteger8, zero_size_name);
  EXPECT_FALSE(IsEmptyValue(zero_size_array));
  EXPECT_FALSE(IsStructValue(zero_size_array));
  EXPECT_FALSE(IsArrayValue(zero_size_array));
  EXPECT_TRUE(IsUnboundedArrayValue(zero_size_array));
  EXPECT_FALSE(IsScalarValue(zero_size_array));
  EXPECT_EQ(zero_size_array.GetTypeCode(), TypeCode::UnboundedArray);
  EXPECT_EQ(zero_size_array.GetType(),
            AnyType(AnyType::unbounded_array_tag, SignedInteger8, zero_size_name));
  EXPECT_NE(zero_size_array.GetType(), AnyType(0, SignedInteger8, zero_size_name));
  EXPECT_NE(zero_size_array.GetType(),
            AnyType(AnyType::unbounded_array_tag, UnsignedInteger8, zero_size_name));
  EXPECT_NE(zero_size_array.GetType(),
            AnyType(AnyType::unbounded_array_tag, SignedInteger8, "different_name"));
  EXPECT_EQ(zero_size_array.GetTypeName(), zero_size_name);
  EXPECT_EQ(zero_size_array.NumberOfElements(), 0);

  // Zero size array cannot be constructed from a list:
  EXPECT_THROW(UnboundedArrayValue({}), InvalidOperationException);
}

TEST(UnboundedArrayValueTest, CopyConstruction)
{
  AnyValue my_array = UnboundedArrayValue({
    {SignedInteger64, 1}, 2, 3, 4, 5
  }, "my_array_t");
  AnyType my_array_t(AnyType::unbounded_array_tag, SignedInteger64, "my_array_t");
  EXPECT_FALSE(IsEmptyValue(my_array));
  EXPECT_FALSE(IsStructValue(my_array));
  EXPECT_FALSE(IsArrayValue(my_array));
  EXPECT_TRUE(IsUnboundedArrayValue(my_array));
  EXPECT_FALSE(IsScalarValue(my_array));
  EXPECT_EQ(my_array.GetTypeCode(), TypeCode::UnboundedArray);
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
  EXPECT_FALSE(IsArrayValue(copy));
  EXPECT_TRUE(IsUnboundedArrayValue(copy));
  EXPECT_FALSE(IsScalarValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::UnboundedArray);
  EXPECT_EQ(copy.GetType(), my_array_t);
  EXPECT_EQ(copy.GetTypeName(), "my_array_t");
  EXPECT_EQ(copy.NumberOfElements(), 5);
  EXPECT_EQ(copy[0], 1);
  EXPECT_EQ(copy["[1]"], 2);
  EXPECT_EQ(copy["[2]."], 3);
}

TEST(UnboundedArrayValueTest, CopyAssignment)
{
  AnyValue my_array = UnboundedArrayValue({
    {SignedInteger32, 1}, 2, 3, 4, 5
  }, "my_array_t");
  EXPECT_EQ(my_array.NumberOfElements(), 5);
  AnyValue my_array_copy = UnboundedArrayValue({
    {SignedInteger32, 3}, 2, 1
  }, "my_array_t");
  EXPECT_EQ(my_array_copy.NumberOfElements(), 3);
  EXPECT_EQ(my_array_copy[0], 3);
  EXPECT_EQ(my_array_copy[1], 2);
  EXPECT_EQ(my_array_copy[2], 1);
  EXPECT_NE(my_array_copy, my_array);

  EXPECT_NO_THROW(my_array_copy = my_array);
  EXPECT_EQ(my_array_copy.NumberOfElements(), 5);
  EXPECT_EQ(my_array_copy[0], 1);
  EXPECT_EQ(my_array_copy[1], 2);
  EXPECT_EQ(my_array_copy[2], 3);
  EXPECT_EQ(my_array_copy[3], 4);
  EXPECT_EQ(my_array_copy[4], 5);
  EXPECT_EQ(my_array_copy, my_array);
}

TEST(UnboundedArrayValueTest, ElementAccess)
{
  // Scalar array
  AnyValue my_array = UnboundedArrayValue({
    {SignedInteger64, 1}, 2, 3, 4, 5
  }, "my_array_t");
  EXPECT_EQ(my_array["[0]"], 1);
  EXPECT_EQ(my_array[0], 1);
  EXPECT_EQ(my_array.NumberOfElements(), 5);
  my_array["[1]"] = 12;
  my_array[2] = 13;
  EXPECT_EQ(my_array["[2]"], 13);
  EXPECT_EQ(my_array[1], 12);

  // Array of structs
  AnyValue el_struct{{
    {"x", 10},
    {"y", 20}
  }};
  AnyValue my_struct_array = UnboundedArrayValue({
    el_struct
  });
  EXPECT_EQ(my_struct_array["[0]x"], 10);
  EXPECT_EQ(my_struct_array["[0].y"], 20);
}

TEST(UnboundedArrayValueTest, Append)
{
  AnyValue my_array = UnboundedArrayValue({
    {SignedInteger64, 1}, 2, 3, 4, 5
  }, "my_array_t");
  EXPECT_EQ(my_array["[0]"], 1);
  EXPECT_EQ(my_array[0], 1);
  EXPECT_EQ(my_array.NumberOfElements(), 5);
  EXPECT_NO_THROW(my_array.Append(6));
  EXPECT_EQ(my_array.NumberOfElements(), 6);
  EXPECT_EQ(my_array[5], 6);
}

TEST(UnboundedArrayValueTest, InvalidElementAccess)
{
  AnyValue my_array = UnboundedArrayValue({
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

TEST(UnboundedArrayValueTest, InvalidAppend)
{
  // Bounded array
  AnyValue bounded_array = ArrayValue({
    {SignedInteger64, 1}, 2, 3, 4, 5
  }, "my_array_t");
  EXPECT_EQ(bounded_array.NumberOfElements(), 5);
  EXPECT_THROW(bounded_array.Append(6), InvalidOperationException);

  // Scalar
  AnyValue scalar(Float32, 1.0);
  EXPECT_THROW(bounded_array.Append(6), InvalidOperationException);

  // Structured value
  AnyValue two_scalars = {{
    {"signed", {SignedInteger8, 1}},
    {"unsigned", {UnsignedInteger8, 12}}
  }};
  EXPECT_THROW(two_scalars.Append(6), InvalidOperationException);
}

TEST(UnboundedArrayValueTest, Equality)
{
  AnyValue my_array = UnboundedArrayValue({
    {SignedInteger64, 1}, 2, 3, 4, 5
  }, "my_array_t");
  AnyType my_array_t(AnyType::unbounded_array_tag, SignedInteger64, "my_array_t");
  AnyValue other(my_array_t);
  EXPECT_NE(my_array, other);
  other = my_array;
  EXPECT_EQ(my_array, other);
  AnyValue scalar = 4u;
  EXPECT_NE(my_array, scalar);

  AnyValue bounded_array = ArrayValue({
    {SignedInteger64, 1}, 2, 3, 4, 5
  }, "my_array_t");
  EXPECT_NE(my_array, bounded_array);
}

TEST(UnboundedArrayValueTest, InvalidArrayAssign)
{
  AnyValue my_array = UnboundedArrayValue({
    {SignedInteger64, 1}, 2, 3, 4, 5
  }, "my_array_t");
  EXPECT_FALSE(IsEmptyValue(my_array));
  EXPECT_FALSE(IsStructValue(my_array));
  EXPECT_FALSE(IsArrayValue(my_array));
  EXPECT_TRUE(IsUnboundedArrayValue(my_array));
  EXPECT_FALSE(IsScalarValue(my_array));
  AnyType my_bounded_array_t(5, SignedInteger64, "my_array_t");
  AnyValue other(my_bounded_array_t);
  EXPECT_FALSE(IsEmptyValue(other));
  EXPECT_FALSE(IsStructValue(other));
  EXPECT_TRUE(IsArrayValue(other));
  EXPECT_FALSE(IsUnboundedArrayValue(other));
  EXPECT_FALSE(IsScalarValue(other));
  EXPECT_THROW(other = my_array, InvalidConversionException);
  EXPECT_THROW(my_array = other, InvalidConversionException);
  AnyValue scalar = 4u;
  EXPECT_THROW(other = scalar, InvalidConversionException);
}
