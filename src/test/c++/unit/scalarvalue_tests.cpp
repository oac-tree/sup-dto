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

#include "sup/dto/anyvalue.h"
#include "sup/dto/anyvalue_exceptions.h"

using namespace sup::dto;

TEST(ScalarValueTest, EmptyValue)
{
  AnyValue empty_value{};
  EXPECT_EQ(empty_value.GetType(), EmptyType);
  EXPECT_NE(empty_value.GetType(), SignedInteger8);
  EXPECT_TRUE(IsEmptyValue(empty_value));
  EXPECT_FALSE(IsStructValue(empty_value));
  EXPECT_FALSE(IsArrayValue(empty_value));
  EXPECT_FALSE(IsUnboundedArrayValue(empty_value));
  EXPECT_FALSE(IsScalarValue(empty_value));
  EXPECT_EQ(empty_value.GetTypeCode(), TypeCode::Empty);
  EXPECT_EQ(empty_value.GetTypeName(), EMPTY_TYPE_NAME);
  EXPECT_EQ(empty_value.NumberOfMembers(), 0);
  EXPECT_THROW(empty_value["field"], InvalidOperationException);
  EXPECT_THROW(empty_value.As<boolean>(), InvalidConversionException);
  EXPECT_THROW(empty_value.As<char8>(), InvalidConversionException);
  EXPECT_THROW(empty_value.As<int8>(), InvalidConversionException);
  EXPECT_THROW(empty_value.As<uint8>(), InvalidConversionException);
  EXPECT_THROW(empty_value.As<int16>(), InvalidConversionException);
  EXPECT_THROW(empty_value.As<uint16>(), InvalidConversionException);
  EXPECT_THROW(empty_value.As<int32>(), InvalidConversionException);
  EXPECT_THROW(empty_value.As<uint32>(), InvalidConversionException);
  EXPECT_THROW(empty_value.As<int64>(), InvalidConversionException);
  EXPECT_THROW(empty_value.As<uint64>(), InvalidConversionException);
  EXPECT_THROW(empty_value.As<float32>(), InvalidConversionException);
  EXPECT_THROW(empty_value.As<float64>(), InvalidConversionException);
  EXPECT_THROW(empty_value.As<std::string>(), InvalidConversionException);

  const AnyValue copy = empty_value;
  EXPECT_TRUE(IsEmptyValue(copy));
  EXPECT_EQ(copy, empty_value);
  EXPECT_FALSE(IsStructValue(copy));
  EXPECT_FALSE(IsArrayValue(copy));
  EXPECT_FALSE(IsUnboundedArrayValue(copy));
  EXPECT_FALSE(IsScalarValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Empty);
  EXPECT_EQ(copy.GetTypeName(), EMPTY_TYPE_NAME);
  EXPECT_THROW(copy["field"], InvalidOperationException);

  AnyValue copy_again;
  copy_again = empty_value;
  EXPECT_TRUE(IsEmptyValue(copy_again));
  EXPECT_EQ(copy_again, empty_value);
  EXPECT_FALSE(IsStructValue(copy_again));
  EXPECT_FALSE(IsArrayValue(copy_again));
  EXPECT_FALSE(IsUnboundedArrayValue(copy_again));
  EXPECT_FALSE(IsScalarValue(copy_again));
  EXPECT_EQ(copy_again.GetTypeCode(), TypeCode::Empty);
  EXPECT_EQ(copy_again.GetTypeName(), EMPTY_TYPE_NAME);
  EXPECT_THROW(copy_again["field"], InvalidOperationException);

  AnyValue moved = std::move(empty_value);
  EXPECT_TRUE(IsEmptyValue(empty_value)); // Moved from value is always empty
  EXPECT_EQ(empty_value.GetType(), EmptyType);
  EXPECT_TRUE(IsEmptyValue(moved));
  EXPECT_EQ(moved, copy);
  EXPECT_FALSE(IsStructValue(moved));
  EXPECT_FALSE(IsArrayValue(moved));
  EXPECT_FALSE(IsUnboundedArrayValue(moved));
  EXPECT_FALSE(IsScalarValue(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Empty);
  EXPECT_EQ(moved.GetTypeName(), EMPTY_TYPE_NAME);
  EXPECT_THROW(moved["field"], InvalidOperationException);

  AnyValue empty_from_type{EmptyType};
  EXPECT_TRUE(IsEmptyValue(empty_from_type));
  EXPECT_EQ(empty_from_type.GetType(), EmptyType);
  EXPECT_EQ(empty_from_type, moved);
  EXPECT_FALSE(IsStructValue(empty_from_type));
  EXPECT_FALSE(IsArrayValue(empty_from_type));
  EXPECT_FALSE(IsUnboundedArrayValue(empty_from_type));
  EXPECT_FALSE(IsScalarValue(empty_from_type));
  EXPECT_EQ(empty_from_type.GetTypeCode(), TypeCode::Empty);
  EXPECT_EQ(empty_from_type.GetTypeName(), EMPTY_TYPE_NAME);
  EXPECT_THROW(empty_from_type["field"], InvalidOperationException);
}

TEST(ScalarValueTest, ScalarEqualityName)
{
  AnyValue two_scalars{{
    {"signed", {SignedInteger8, -5}},
    {"unsigned", {UnsignedInteger8, 22}}
  }};
  AnyValue scalar{UnsignedInteger16, 35};
  AnyValue other_scalar{SignedInteger32, -74};
  EXPECT_NE(scalar, two_scalars);
  EXPECT_NE(scalar, other_scalar);
  EXPECT_EQ(scalar, scalar);
  EXPECT_EQ(scalar, 35);
}

TEST(ScalarValueTest, BooleanValue)
{
  AnyValue boolean_value{Boolean};
  EXPECT_EQ(boolean_value.GetType(), Boolean);
  EXPECT_NE(boolean_value.GetType(), SignedInteger8);
  EXPECT_FALSE(IsEmptyValue(boolean_value));
  EXPECT_FALSE(IsStructValue(boolean_value));
  EXPECT_FALSE(IsArrayValue(boolean_value));
  EXPECT_FALSE(IsUnboundedArrayValue(boolean_value));
  EXPECT_TRUE(IsScalarValue(boolean_value));
  EXPECT_EQ(boolean_value.GetTypeCode(), TypeCode::Bool);
  EXPECT_EQ(boolean_value.GetTypeName(), BOOLEAN_TYPE_NAME);
  EXPECT_THROW(boolean_value["field"], InvalidOperationException);
  EXPECT_EQ(boolean_value.As<boolean>(), false);
  EXPECT_EQ(boolean_value.As<int8>(), 0);
  EXPECT_EQ(boolean_value.As<uint8>(), 0);
  EXPECT_EQ(boolean_value.As<int16>(), 0);
  EXPECT_EQ(boolean_value.As<uint16>(), 0);
  EXPECT_EQ(boolean_value.As<int32>(), 0);
  EXPECT_EQ(boolean_value.As<uint32>(), 0);
  EXPECT_EQ(boolean_value.As<int64>(), 0);
  EXPECT_EQ(boolean_value.As<uint64>(), 0);
  EXPECT_EQ(boolean_value.As<float32>(), 0.0);
  EXPECT_EQ(boolean_value.As<float64>(), 0.0);
  EXPECT_THROW(boolean_value.As<std::string>(), InvalidConversionException);
  boolean_value = true;
  EXPECT_EQ(boolean_value.As<boolean>(), true);
  EXPECT_EQ(boolean_value.As<int8>(), 1);
  EXPECT_EQ(boolean_value.As<uint8>(), 1u);
  EXPECT_EQ(boolean_value.As<int16>(), 1);
  EXPECT_EQ(boolean_value.As<uint16>(), 1);
  EXPECT_EQ(boolean_value.As<int32>(), 1);
  EXPECT_EQ(boolean_value.As<uint32>(), 1);
  EXPECT_EQ(boolean_value.As<int64>(), 1);
  EXPECT_EQ(boolean_value.As<uint64>(), 1);
  EXPECT_EQ(boolean_value.As<float32>(), 1.0);
  EXPECT_EQ(boolean_value.As<float64>(), 1.0);
  EXPECT_THROW(boolean_value.As<std::string>(), InvalidConversionException);
  EXPECT_EQ(boolean_value, true);

  const AnyValue copy = boolean_value;
  EXPECT_TRUE(IsScalarValue(copy));
  EXPECT_EQ(copy, boolean_value);
  EXPECT_FALSE(IsEmptyValue(copy));
  EXPECT_FALSE(IsStructValue(copy));
  EXPECT_FALSE(IsArrayValue(copy));
  EXPECT_FALSE(IsUnboundedArrayValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Bool);
  EXPECT_EQ(copy.GetTypeName(), BOOLEAN_TYPE_NAME);
  EXPECT_THROW(copy["field"], InvalidOperationException);
  EXPECT_EQ(copy.As<boolean>(), true);
  EXPECT_EQ(copy.As<int8>(), 1);
  EXPECT_EQ(copy.As<uint8>(), 1u);
  EXPECT_EQ(copy, true);

  AnyValue moved = std::move(boolean_value);
  EXPECT_TRUE(IsEmptyValue(boolean_value)); // Moved from value is always empty
  EXPECT_EQ(boolean_value.GetType(), EmptyType);
  EXPECT_TRUE(IsScalarValue(moved));
  EXPECT_EQ(moved, copy);
  EXPECT_FALSE(IsEmptyValue(moved));
  EXPECT_FALSE(IsStructValue(moved));
  EXPECT_FALSE(IsArrayValue(moved));
  EXPECT_FALSE(IsUnboundedArrayValue(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Bool);
  EXPECT_EQ(moved.GetTypeName(), BOOLEAN_TYPE_NAME);
  EXPECT_THROW(moved["field"], InvalidOperationException);
  EXPECT_EQ(moved.As<boolean>(), true);
  EXPECT_EQ(moved.As<int8>(), 1);
  EXPECT_EQ(moved.As<uint8>(), 1u);

  AnyValue boolean_from_literal = true;
  EXPECT_EQ(boolean_from_literal.GetType(), Boolean);
  EXPECT_NE(boolean_from_literal.GetType(), SignedInteger8);
  EXPECT_FALSE(IsEmptyValue(boolean_from_literal));
  EXPECT_FALSE(IsStructValue(boolean_from_literal));
  EXPECT_FALSE(IsArrayValue(boolean_from_literal));
  EXPECT_FALSE(IsUnboundedArrayValue(boolean_from_literal));
  EXPECT_TRUE(IsScalarValue(boolean_from_literal));
  EXPECT_EQ(boolean_from_literal.GetTypeCode(), TypeCode::Bool);
  EXPECT_EQ(boolean_from_literal.GetTypeName(), BOOLEAN_TYPE_NAME);
  EXPECT_THROW(boolean_from_literal["field"], InvalidOperationException);
  EXPECT_EQ(boolean_from_literal.As<boolean>(), true);
  boolean_from_literal = false;
  EXPECT_EQ(boolean_from_literal.As<boolean>(), false);
  EXPECT_EQ(boolean_from_literal.As<int8>(), 0);
  EXPECT_EQ(boolean_from_literal.As<uint8>(), 0);

  AnyValue boolean_from_typed_literal = {Boolean, 5};
  EXPECT_EQ(boolean_from_typed_literal.GetType(), Boolean);
  EXPECT_NE(boolean_from_typed_literal.GetType(), SignedInteger8);
  EXPECT_FALSE(IsEmptyValue(boolean_from_typed_literal));
  EXPECT_FALSE(IsStructValue(boolean_from_typed_literal));
  EXPECT_FALSE(IsArrayValue(boolean_from_typed_literal));
  EXPECT_FALSE(IsUnboundedArrayValue(boolean_from_typed_literal));
  EXPECT_TRUE(IsScalarValue(boolean_from_typed_literal));
  EXPECT_EQ(boolean_from_typed_literal.GetTypeCode(), TypeCode::Bool);
  EXPECT_EQ(boolean_from_typed_literal.GetTypeName(), BOOLEAN_TYPE_NAME);
  EXPECT_THROW(boolean_from_typed_literal["field"], InvalidOperationException);
  EXPECT_EQ(boolean_from_typed_literal.As<boolean>(), true);
  boolean_from_typed_literal = false;
  EXPECT_EQ(boolean_from_typed_literal.As<boolean>(), false);
  EXPECT_EQ(boolean_from_typed_literal.As<int8>(), 0);
  EXPECT_EQ(boolean_from_typed_literal.As<uint8>(), 0);
}

TEST(ScalarValueTest, Float32Value)
{
  AnyValue float32_value{Float32};
  EXPECT_EQ(float32_value.GetType(), Float32);
  EXPECT_NE(float32_value.GetType(), SignedInteger64);
  EXPECT_FALSE(IsEmptyValue(float32_value));
  EXPECT_FALSE(IsStructValue(float32_value));
  EXPECT_FALSE(IsArrayValue(float32_value));
  EXPECT_FALSE(IsUnboundedArrayValue(float32_value));
  EXPECT_TRUE(IsScalarValue(float32_value));
  EXPECT_EQ(float32_value.GetTypeCode(), TypeCode::Float32);
  EXPECT_EQ(float32_value.GetTypeName(), FLOAT32_TYPE_NAME);
  EXPECT_THROW(float32_value["field"], InvalidOperationException);
  EXPECT_EQ(float32_value.As<boolean>(), false);
  EXPECT_EQ(float32_value.As<int8>(), 0);
  EXPECT_EQ(float32_value.As<uint8>(), 0);
  EXPECT_EQ(float32_value.As<int16>(), 0);
  EXPECT_EQ(float32_value.As<uint16>(), 0);
  EXPECT_EQ(float32_value.As<int32>(), 0);
  EXPECT_EQ(float32_value.As<uint32>(), 0);
  EXPECT_EQ(float32_value.As<int64>(), 0);
  EXPECT_EQ(float32_value.As<uint64>(), 0);
  EXPECT_DOUBLE_EQ(float32_value.As<float32>(), 0.0);
  EXPECT_DOUBLE_EQ(float32_value.As<float64>(), 0.0);
  EXPECT_THROW(float32_value.As<std::string>(), InvalidConversionException);
  auto new_val = 8.25;
  int trunc_val = new_val;
  float32_value = new_val;
  EXPECT_EQ(float32_value.As<boolean>(), true);
  EXPECT_EQ(float32_value.As<int8>(), trunc_val);
  EXPECT_EQ(float32_value.As<uint8>(), trunc_val);
  EXPECT_EQ(float32_value.As<int16>(), trunc_val);
  EXPECT_EQ(float32_value.As<uint16>(), trunc_val);
  EXPECT_EQ(float32_value.As<int32>(), trunc_val);
  EXPECT_EQ(float32_value.As<uint32>(), trunc_val);
  EXPECT_EQ(float32_value.As<int64>(), trunc_val);
  EXPECT_EQ(float32_value.As<uint64>(), trunc_val);
  EXPECT_DOUBLE_EQ(float32_value.As<float32>(), new_val);
  EXPECT_DOUBLE_EQ(float32_value.As<float64>(), new_val);
  EXPECT_THROW(float32_value.As<std::string>(), InvalidConversionException);
  EXPECT_EQ(float32_value, new_val);

  const AnyValue copy = float32_value;
  EXPECT_TRUE(IsScalarValue(copy));
  EXPECT_EQ(copy, float32_value);
  EXPECT_FALSE(IsEmptyValue(copy));
  EXPECT_FALSE(IsStructValue(copy));
  EXPECT_FALSE(IsArrayValue(copy));
  EXPECT_FALSE(IsUnboundedArrayValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Float32);
  EXPECT_EQ(copy.GetTypeName(), FLOAT32_TYPE_NAME);
  EXPECT_THROW(copy["field"], InvalidOperationException);
  EXPECT_DOUBLE_EQ(copy.As<float32>(), new_val);
  EXPECT_EQ(copy.As<int32>(), trunc_val);
  EXPECT_EQ(copy, new_val);

  AnyValue moved = std::move(float32_value);
  EXPECT_TRUE(IsEmptyValue(float32_value)); // Moved from value is always empty
  EXPECT_EQ(float32_value.GetType(), EmptyType);
  EXPECT_TRUE(IsScalarValue(moved));
  EXPECT_EQ(moved, copy);
  EXPECT_FALSE(IsEmptyValue(moved));
  EXPECT_FALSE(IsStructValue(moved));
  EXPECT_FALSE(IsArrayValue(moved));
  EXPECT_FALSE(IsUnboundedArrayValue(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Float32);
  EXPECT_EQ(moved.GetTypeName(), FLOAT32_TYPE_NAME);
  EXPECT_THROW(moved["field"], InvalidOperationException);
  EXPECT_EQ(moved.As<boolean>(), true);
  EXPECT_DOUBLE_EQ(moved.As<float32>(), new_val);

  float32 literal = -4.5;
  AnyValue float32_from_literal = literal;
  EXPECT_EQ(float32_from_literal.GetType(), Float32);
  EXPECT_NE(float32_from_literal.GetType(), SignedInteger64);
  EXPECT_FALSE(IsEmptyValue(float32_from_literal));
  EXPECT_FALSE(IsStructValue(float32_from_literal));
  EXPECT_FALSE(IsArrayValue(float32_from_literal));
  EXPECT_FALSE(IsUnboundedArrayValue(float32_from_literal));
  EXPECT_TRUE(IsScalarValue(float32_from_literal));
  EXPECT_EQ(float32_from_literal.GetTypeCode(), TypeCode::Float32);
  EXPECT_EQ(float32_from_literal.GetTypeName(), FLOAT32_TYPE_NAME);
  EXPECT_THROW(float32_from_literal["field"], InvalidOperationException);
  EXPECT_DOUBLE_EQ(float32_from_literal.As<float32>(), literal);
  float32_from_literal = 88.125;
  EXPECT_EQ(float32_from_literal.As<boolean>(), true);
  EXPECT_EQ(float32_from_literal.As<float32>(), 88.125);
  EXPECT_EQ(float32_from_literal.As<int32>(), (int32)88.125);

  AnyValue float32_from_typed_literal = {Float32, 5};
  EXPECT_EQ(float32_from_typed_literal.GetType(), Float32);
  EXPECT_NE(float32_from_typed_literal.GetType(), Boolean);
  EXPECT_FALSE(IsEmptyValue(float32_from_typed_literal));
  EXPECT_FALSE(IsStructValue(float32_from_typed_literal));
  EXPECT_FALSE(IsArrayValue(float32_from_typed_literal));
  EXPECT_FALSE(IsUnboundedArrayValue(float32_from_typed_literal));
  EXPECT_TRUE(IsScalarValue(float32_from_typed_literal));
  EXPECT_EQ(float32_from_typed_literal.GetTypeCode(), TypeCode::Float32);
  EXPECT_EQ(float32_from_typed_literal.GetTypeName(), FLOAT32_TYPE_NAME);
  EXPECT_THROW(float32_from_typed_literal["field"], InvalidOperationException);
  EXPECT_DOUBLE_EQ(float32_from_typed_literal.As<float32>(), 5.0);
  float32_from_typed_literal = 0;
  EXPECT_EQ(float32_from_typed_literal.As<boolean>(), false);
  EXPECT_DOUBLE_EQ(float32_from_typed_literal.As<float32>(), 0);
  EXPECT_EQ(float32_from_typed_literal.As<int32>(), 0);
}

TEST(ScalarValueTest, Float64Value)
{
  AnyValue float64_value{Float64};
  EXPECT_EQ(float64_value.GetType(), Float64);
  EXPECT_NE(float64_value.GetType(), SignedInteger64);
  EXPECT_FALSE(IsEmptyValue(float64_value));
  EXPECT_FALSE(IsStructValue(float64_value));
  EXPECT_FALSE(IsArrayValue(float64_value));
  EXPECT_FALSE(IsUnboundedArrayValue(float64_value));
  EXPECT_TRUE(IsScalarValue(float64_value));
  EXPECT_EQ(float64_value.GetTypeCode(), TypeCode::Float64);
  EXPECT_EQ(float64_value.GetTypeName(), FLOAT64_TYPE_NAME);
  EXPECT_THROW(float64_value["field"], InvalidOperationException);
  EXPECT_EQ(float64_value.As<boolean>(), false);
  EXPECT_EQ(float64_value.As<int8>(), 0);
  EXPECT_EQ(float64_value.As<uint8>(), 0);
  EXPECT_EQ(float64_value.As<int16>(), 0);
  EXPECT_EQ(float64_value.As<uint16>(), 0);
  EXPECT_EQ(float64_value.As<int32>(), 0);
  EXPECT_EQ(float64_value.As<uint32>(), 0);
  EXPECT_EQ(float64_value.As<int64>(), 0);
  EXPECT_EQ(float64_value.As<uint64>(), 0);
  EXPECT_DOUBLE_EQ(float64_value.As<float32>(), 0.0);
  EXPECT_DOUBLE_EQ(float64_value.As<float64>(), 0.0);
  EXPECT_THROW(float64_value.As<std::string>(), InvalidConversionException);
  auto new_val = 8.25;
  int trunc_val = new_val;
  float64_value = new_val;
  EXPECT_EQ(float64_value.As<boolean>(), true);
  EXPECT_EQ(float64_value.As<int8>(), trunc_val);
  EXPECT_EQ(float64_value.As<uint8>(), trunc_val);
  EXPECT_EQ(float64_value.As<int16>(), trunc_val);
  EXPECT_EQ(float64_value.As<uint16>(), trunc_val);
  EXPECT_EQ(float64_value.As<int32>(), trunc_val);
  EXPECT_EQ(float64_value.As<uint32>(), trunc_val);
  EXPECT_EQ(float64_value.As<int64>(), trunc_val);
  EXPECT_EQ(float64_value.As<uint64>(), trunc_val);
  EXPECT_DOUBLE_EQ(float64_value.As<float32>(), new_val);
  EXPECT_DOUBLE_EQ(float64_value.As<float64>(), new_val);
  EXPECT_THROW(float64_value.As<std::string>(), InvalidConversionException);
  EXPECT_EQ(float64_value, new_val);

  const AnyValue copy = float64_value;
  EXPECT_TRUE(IsScalarValue(copy));
  EXPECT_EQ(copy, float64_value);
  EXPECT_FALSE(IsEmptyValue(copy));
  EXPECT_FALSE(IsStructValue(copy));
  EXPECT_FALSE(IsArrayValue(copy));
  EXPECT_FALSE(IsUnboundedArrayValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Float64);
  EXPECT_EQ(copy.GetTypeName(), FLOAT64_TYPE_NAME);
  EXPECT_THROW(copy["field"], InvalidOperationException);
  EXPECT_DOUBLE_EQ(copy.As<float64>(), new_val);
  EXPECT_EQ(copy.As<int32>(), trunc_val);
  EXPECT_EQ(copy, new_val);

  AnyValue moved = std::move(float64_value);
  EXPECT_TRUE(IsEmptyValue(float64_value)); // Moved from value is always empty
  EXPECT_EQ(float64_value.GetType(), EmptyType);
  EXPECT_TRUE(IsScalarValue(moved));
  EXPECT_EQ(moved, copy);
  EXPECT_FALSE(IsEmptyValue(moved));
  EXPECT_FALSE(IsStructValue(moved));
  EXPECT_FALSE(IsArrayValue(moved));
  EXPECT_FALSE(IsUnboundedArrayValue(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Float64);
  EXPECT_EQ(moved.GetTypeName(), FLOAT64_TYPE_NAME);
  EXPECT_THROW(moved["field"], InvalidOperationException);
  EXPECT_EQ(moved.As<boolean>(), true);
  EXPECT_DOUBLE_EQ(moved.As<float64>(), new_val);

  float64 literal = -4.5;
  AnyValue float64_from_literal = literal;
  EXPECT_EQ(float64_from_literal.GetType(), Float64);
  EXPECT_NE(float64_from_literal.GetType(), SignedInteger64);
  EXPECT_FALSE(IsEmptyValue(float64_from_literal));
  EXPECT_FALSE(IsStructValue(float64_from_literal));
  EXPECT_FALSE(IsArrayValue(float64_from_literal));
  EXPECT_FALSE(IsUnboundedArrayValue(float64_from_literal));
  EXPECT_TRUE(IsScalarValue(float64_from_literal));
  EXPECT_EQ(float64_from_literal.GetTypeCode(), TypeCode::Float64);
  EXPECT_EQ(float64_from_literal.GetTypeName(), FLOAT64_TYPE_NAME);
  EXPECT_THROW(float64_from_literal["field"], InvalidOperationException);
  EXPECT_DOUBLE_EQ(float64_from_literal.As<float64>(), literal);
  float64_from_literal = 88.125;
  EXPECT_EQ(float64_from_literal.As<boolean>(), true);
  EXPECT_EQ(float64_from_literal.As<float64>(), 88.125);
  EXPECT_EQ(float64_from_literal.As<int32>(), (int32)88.125);

  AnyValue float64_from_typed_literal = {Float64, 5};
  EXPECT_EQ(float64_from_typed_literal.GetType(), Float64);
  EXPECT_NE(float64_from_typed_literal.GetType(), Boolean);
  EXPECT_FALSE(IsEmptyValue(float64_from_typed_literal));
  EXPECT_FALSE(IsStructValue(float64_from_typed_literal));
  EXPECT_FALSE(IsArrayValue(float64_from_typed_literal));
  EXPECT_FALSE(IsUnboundedArrayValue(float64_from_typed_literal));
  EXPECT_TRUE(IsScalarValue(float64_from_typed_literal));
  EXPECT_EQ(float64_from_typed_literal.GetTypeCode(), TypeCode::Float64);
  EXPECT_EQ(float64_from_typed_literal.GetTypeName(), FLOAT64_TYPE_NAME);
  EXPECT_THROW(float64_from_typed_literal["field"], InvalidOperationException);
  EXPECT_DOUBLE_EQ(float64_from_typed_literal.As<float64>(), 5.0);
  float64_from_typed_literal = 0;
  EXPECT_EQ(float64_from_typed_literal.As<boolean>(), false);
  EXPECT_DOUBLE_EQ(float64_from_typed_literal.As<float64>(), 0);
  EXPECT_EQ(float64_from_typed_literal.As<int32>(), 0);
}

TEST(ScalarValueTest, StringValue)
{
  AnyValue string_value{String};
  EXPECT_EQ(string_value.GetType(), String);
  EXPECT_NE(string_value.GetType(), SignedInteger64);
  EXPECT_FALSE(IsEmptyValue(string_value));
  EXPECT_FALSE(IsStructValue(string_value));
  EXPECT_FALSE(IsArrayValue(string_value));
  EXPECT_FALSE(IsUnboundedArrayValue(string_value));
  EXPECT_TRUE(IsScalarValue(string_value));
  EXPECT_EQ(string_value.GetTypeCode(), TypeCode::String);
  EXPECT_EQ(string_value.GetTypeName(), STRING_TYPE_NAME);
  EXPECT_THROW(string_value["field"], InvalidOperationException);
  EXPECT_THROW(string_value.As<boolean>(), InvalidConversionException);
  EXPECT_THROW(string_value.As<char8>(), InvalidConversionException);
  EXPECT_THROW(string_value.As<int8>(), InvalidConversionException);
  EXPECT_THROW(string_value.As<uint8>(), InvalidConversionException);
  EXPECT_THROW(string_value.As<int16>(), InvalidConversionException);
  EXPECT_THROW(string_value.As<uint16>(), InvalidConversionException);
  EXPECT_THROW(string_value.As<int32>(), InvalidConversionException);
  EXPECT_THROW(string_value.As<uint32>(), InvalidConversionException);
  EXPECT_THROW(string_value.As<int64>(), InvalidConversionException);
  EXPECT_THROW(string_value.As<uint64>(), InvalidConversionException);
  EXPECT_THROW(string_value.As<float32>(), InvalidConversionException);
  EXPECT_THROW(string_value.As<float64>(), InvalidConversionException);
  EXPECT_EQ(string_value.As<std::string>(), "");
  std::string new_val = "new value";
  string_value = new_val.c_str();
  EXPECT_THROW(string_value.As<boolean>(), InvalidConversionException);
  EXPECT_THROW(string_value.As<char8>(), InvalidConversionException);
  EXPECT_THROW(string_value.As<int8>(), InvalidConversionException);
  EXPECT_THROW(string_value.As<uint8>(), InvalidConversionException);
  EXPECT_THROW(string_value.As<int16>(), InvalidConversionException);
  EXPECT_THROW(string_value.As<uint16>(), InvalidConversionException);
  EXPECT_THROW(string_value.As<int32>(), InvalidConversionException);
  EXPECT_THROW(string_value.As<uint32>(), InvalidConversionException);
  EXPECT_THROW(string_value.As<int64>(), InvalidConversionException);
  EXPECT_THROW(string_value.As<uint64>(), InvalidConversionException);
  EXPECT_THROW(string_value.As<float32>(), InvalidConversionException);
  EXPECT_THROW(string_value.As<float64>(), InvalidConversionException);
  EXPECT_EQ(string_value.As<std::string>(), new_val);
  EXPECT_EQ(string_value, new_val);

  const AnyValue copy = string_value;
  EXPECT_TRUE(IsScalarValue(copy));
  EXPECT_EQ(copy, string_value);
  EXPECT_FALSE(IsEmptyValue(copy));
  EXPECT_FALSE(IsStructValue(copy));
  EXPECT_FALSE(IsArrayValue(copy));
  EXPECT_FALSE(IsUnboundedArrayValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::String);
  EXPECT_EQ(copy.GetTypeName(), STRING_TYPE_NAME);
  EXPECT_THROW(copy["field"], InvalidOperationException);
  EXPECT_EQ(copy.As<std::string>(), new_val);
  EXPECT_THROW(copy.As<int32>(), InvalidConversionException);
  EXPECT_EQ(copy, new_val);

  AnyValue moved = std::move(string_value);
  EXPECT_TRUE(IsEmptyValue(string_value)); // Moved from value is always empty
  EXPECT_EQ(string_value.GetType(), EmptyType);
  EXPECT_TRUE(IsScalarValue(moved));
  EXPECT_EQ(moved, copy);
  EXPECT_FALSE(IsEmptyValue(moved));
  EXPECT_FALSE(IsStructValue(moved));
  EXPECT_FALSE(IsArrayValue(moved));
  EXPECT_FALSE(IsUnboundedArrayValue(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::String);
  EXPECT_EQ(moved.GetTypeName(), STRING_TYPE_NAME);
  EXPECT_THROW(moved["field"], InvalidOperationException);
  EXPECT_EQ(moved.As<std::string>(), new_val);
  EXPECT_THROW(moved.As<int32>(), InvalidConversionException);

  std::string literal = "literal";
  AnyValue string_from_literal = literal;
  EXPECT_EQ(string_from_literal.GetType(), String);
  EXPECT_NE(string_from_literal.GetType(), SignedInteger64);
  EXPECT_FALSE(IsEmptyValue(string_from_literal));
  EXPECT_FALSE(IsStructValue(string_from_literal));
  EXPECT_FALSE(IsArrayValue(string_from_literal));
  EXPECT_FALSE(IsUnboundedArrayValue(string_from_literal));
  EXPECT_TRUE(IsScalarValue(string_from_literal));
  EXPECT_EQ(string_from_literal.GetTypeCode(), TypeCode::String);
  EXPECT_EQ(string_from_literal.GetTypeName(), STRING_TYPE_NAME);
  EXPECT_THROW(string_from_literal["field"], InvalidOperationException);
  EXPECT_EQ(string_from_literal.As<std::string>(), literal);
  EXPECT_THROW(string_from_literal.As<int32>(), InvalidConversionException);
  string_from_literal = std::string("assign string");
  EXPECT_EQ(string_from_literal.As<std::string>(), "assign string");
  EXPECT_THROW(string_from_literal.As<int32>(), InvalidConversionException);

  AnyValue string_from_typed_literal = {String, "typed literal"};
  EXPECT_EQ(string_from_typed_literal.GetType(), String);
  EXPECT_NE(string_from_typed_literal.GetType(), Boolean);
  EXPECT_FALSE(IsEmptyValue(string_from_typed_literal));
  EXPECT_FALSE(IsStructValue(string_from_typed_literal));
  EXPECT_FALSE(IsArrayValue(string_from_typed_literal));
  EXPECT_FALSE(IsUnboundedArrayValue(string_from_typed_literal));
  EXPECT_TRUE(IsScalarValue(string_from_typed_literal));
  EXPECT_EQ(string_from_typed_literal.GetTypeCode(), TypeCode::String);
  EXPECT_EQ(string_from_typed_literal.GetTypeName(), STRING_TYPE_NAME);
  EXPECT_THROW(string_from_typed_literal["field"], InvalidOperationException);
  EXPECT_EQ(string_from_typed_literal.As<std::string>(), "typed literal");
  EXPECT_THROW(string_from_typed_literal.As<int32>(), InvalidConversionException);
}
