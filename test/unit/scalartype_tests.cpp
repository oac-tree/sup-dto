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
 * Copyright (c) : 2010-2023 ITER Organization,
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

#include <sup/dto/anytype.h>
#include <sup/dto/anyvalue_exceptions.h>

using namespace sup::dto;

TEST(ScalarTypeTest, EmptyType)
{
  AnyType empty_type{};
  EXPECT_EQ(empty_type, EmptyType);
  EXPECT_NE(empty_type, SignedInteger8Type);
  EXPECT_TRUE(IsEmptyType(empty_type));
  EXPECT_FALSE(IsStructType(empty_type));
  EXPECT_FALSE(IsArrayType(empty_type));
  EXPECT_FALSE(IsScalarType(empty_type));
  EXPECT_EQ(empty_type.NumberOfMembers(), 0);
  EXPECT_EQ(empty_type.GetTypeCode(), TypeCode::Empty);
  EXPECT_EQ(empty_type.GetTypeName(), kEmptyTypeName);
  EXPECT_THROW(empty_type["field"], InvalidOperationException);

  const AnyType copy = empty_type;
  EXPECT_TRUE(IsEmptyType(copy));
  EXPECT_EQ(copy, EmptyType);
  EXPECT_FALSE(IsStructType(copy));
  EXPECT_FALSE(IsArrayType(copy));
  EXPECT_FALSE(IsScalarType(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Empty);
  EXPECT_EQ(copy.GetTypeName(), kEmptyTypeName);
  EXPECT_THROW(copy["field"], InvalidOperationException);

  AnyType moved = std::move(empty_type);
  EXPECT_TRUE(IsEmptyType(empty_type)); // Moved from type is always empty
  EXPECT_EQ(empty_type, EmptyType);
  EXPECT_TRUE(IsEmptyType(moved));
  EXPECT_EQ(copy, EmptyType);
  EXPECT_FALSE(IsStructType(moved));
  EXPECT_FALSE(IsArrayType(moved));
  EXPECT_FALSE(IsScalarType(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Empty);
  EXPECT_EQ(moved.GetTypeName(), kEmptyTypeName);
  EXPECT_THROW(moved["field"], InvalidOperationException);

  // Creation of non-scalar types using typecode throws
  EXPECT_THROW(AnyType{TypeCode::Empty}, InvalidOperationException);
}

TEST(ScalarTypeTest, BooleanType)
{
  AnyType boolean_type{TypeCode::Bool};
  EXPECT_EQ(boolean_type, BooleanType);
  EXPECT_NE(boolean_type, UnsignedInteger8Type);
  EXPECT_FALSE(IsEmptyType(boolean_type));
  EXPECT_FALSE(IsStructType(boolean_type));
  EXPECT_FALSE(IsArrayType(boolean_type));
  EXPECT_TRUE(IsScalarType(boolean_type));
  EXPECT_EQ(boolean_type.GetTypeCode(), TypeCode::Bool);
  EXPECT_EQ(boolean_type.GetTypeName(), kBooleanTypeName);
  EXPECT_THROW(boolean_type["field"], InvalidOperationException);

  AnyType copy_boolean = boolean_type;
  EXPECT_EQ(copy_boolean, BooleanType);
  EXPECT_NE(copy_boolean, UnsignedInteger8Type);
  EXPECT_FALSE(IsEmptyType(copy_boolean));
  EXPECT_FALSE(IsStructType(copy_boolean));
  EXPECT_FALSE(IsArrayType(copy_boolean));
  EXPECT_TRUE(IsScalarType(copy_boolean));
  EXPECT_EQ(copy_boolean.GetTypeCode(), TypeCode::Bool);
  EXPECT_EQ(copy_boolean.GetTypeName(), kBooleanTypeName);
  EXPECT_THROW(copy_boolean["field"], InvalidOperationException);
}

TEST(ScalarTypeTest, Float32Type)
{
  AnyType float32_type{TypeCode::Float32};
  EXPECT_EQ(float32_type, Float32Type);
  EXPECT_NE(float32_type, SignedInteger64Type);
  EXPECT_FALSE(IsEmptyType(float32_type));
  EXPECT_FALSE(IsStructType(float32_type));
  EXPECT_FALSE(IsArrayType(float32_type));
  EXPECT_TRUE(IsScalarType(float32_type));
  EXPECT_EQ(float32_type.GetTypeCode(), TypeCode::Float32);
  EXPECT_EQ(float32_type.GetTypeName(), kFloat32TypeName);
  EXPECT_THROW(float32_type["field"], InvalidOperationException);

  AnyType moved_float32 = std::move(float32_type);
  EXPECT_EQ(moved_float32, Float32Type);
  EXPECT_NE(moved_float32, SignedInteger64Type);
  EXPECT_TRUE(IsEmptyType(float32_type)); // Moved from type is always empty
  EXPECT_EQ(float32_type, EmptyType);
  EXPECT_FALSE(IsEmptyType(moved_float32));
  EXPECT_FALSE(IsStructType(moved_float32));
  EXPECT_FALSE(IsArrayType(moved_float32));
  EXPECT_TRUE(IsScalarType(moved_float32));
  EXPECT_EQ(moved_float32.GetTypeCode(), TypeCode::Float32);
  EXPECT_EQ(moved_float32.GetTypeName(), kFloat32TypeName);
  EXPECT_THROW(moved_float32["field"], InvalidOperationException);
}

TEST(ScalarTypeTest, Float64Type)
{
  AnyType float64_type{TypeCode::Float64};
  EXPECT_EQ(float64_type, Float64Type);
  EXPECT_NE(float64_type, SignedInteger64Type);
  EXPECT_FALSE(IsEmptyType(float64_type));
  EXPECT_FALSE(IsStructType(float64_type));
  EXPECT_FALSE(IsArrayType(float64_type));
  EXPECT_TRUE(IsScalarType(float64_type));
  EXPECT_EQ(float64_type.GetTypeCode(), TypeCode::Float64);
  EXPECT_EQ(float64_type.GetTypeName(), kFloat64TypeName);
  EXPECT_THROW(float64_type["field"], InvalidOperationException);

  AnyType moved_float64 = std::move(float64_type);
  EXPECT_EQ(moved_float64, Float64Type);
  EXPECT_NE(moved_float64, SignedInteger64Type);
  EXPECT_TRUE(IsEmptyType(float64_type)); // Moved from type is always empty
  EXPECT_EQ(float64_type, EmptyType);
  EXPECT_FALSE(IsEmptyType(moved_float64));
  EXPECT_FALSE(IsStructType(moved_float64));
  EXPECT_FALSE(IsArrayType(moved_float64));
  EXPECT_TRUE(IsScalarType(moved_float64));
  EXPECT_EQ(moved_float64.GetTypeCode(), TypeCode::Float64);
  EXPECT_EQ(moved_float64.GetTypeName(), kFloat64TypeName);
  EXPECT_THROW(moved_float64["field"], InvalidOperationException);
}
