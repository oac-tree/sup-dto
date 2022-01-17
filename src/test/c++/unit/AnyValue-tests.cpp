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

class AnyValueTest : public ::testing::Test
{
protected:
  AnyValueTest();
  virtual ~AnyValueTest();
};

TEST_F(AnyValueTest, EmptyValue)
{
  AnyValue empty_value{};
  EXPECT_EQ(empty_value.GetType(), EmptyType);
  EXPECT_NE(empty_value.GetType(), SignedInteger8);
  EXPECT_TRUE(IsEmptyValue(empty_value));
  EXPECT_FALSE(IsStructValue(empty_value));
  EXPECT_FALSE(IsArrayValue(empty_value));
  EXPECT_FALSE(IsScalarValue(empty_value));
  EXPECT_EQ(empty_value.GetTypeCode(), TypeCode::Empty);
  EXPECT_EQ(empty_value.GetTypeName(), EMPTY_TYPE_NAME);
  EXPECT_THROW(empty_value["field"], KeyNotAllowedException);
  EXPECT_THROW(empty_value.As<boolean>(), InvalidConversionException);
  EXPECT_THROW(empty_value.As<int8>(), InvalidConversionException);
  EXPECT_THROW(empty_value.As<uint8>(), InvalidConversionException);
  EXPECT_THROW(empty_value.As<int16>(), InvalidConversionException);
  EXPECT_THROW(empty_value.As<uint16>(), InvalidConversionException);
  EXPECT_THROW(empty_value.As<int32>(), InvalidConversionException);
  EXPECT_THROW(empty_value.As<uint32>(), InvalidConversionException);
  EXPECT_THROW(empty_value.As<int64>(), InvalidConversionException);
  EXPECT_THROW(empty_value.As<uint64>(), InvalidConversionException);

  const AnyValue copy = empty_value;
  EXPECT_TRUE(IsEmptyValue(copy));
  EXPECT_EQ(copy, empty_value);
  EXPECT_FALSE(IsStructValue(copy));
  EXPECT_FALSE(IsArrayValue(copy));
  EXPECT_FALSE(IsScalarValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Empty);
  EXPECT_EQ(copy.GetTypeName(), EMPTY_TYPE_NAME);
  EXPECT_THROW(copy["field"], KeyNotAllowedException);

  AnyValue moved = std::move(empty_value);
  EXPECT_TRUE(IsEmptyValue(empty_value)); // Moved from value is always empty
  EXPECT_EQ(empty_value.GetType(), EmptyType);
  EXPECT_TRUE(IsEmptyValue(moved));
  EXPECT_EQ(moved, copy);
  EXPECT_FALSE(IsStructValue(moved));
  EXPECT_FALSE(IsArrayValue(moved));
  EXPECT_FALSE(IsScalarValue(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Empty);
  EXPECT_EQ(moved.GetTypeName(), EMPTY_TYPE_NAME);
  EXPECT_THROW(moved["field"], KeyNotAllowedException);
}

TEST_F(AnyValueTest, StructValue)
{
  AnyValue my_struct{{
    {"index", {UnsignedInteger64, 1}},
    {"coordinates", {{
      {"x", 0},
      {"y", 5}
    }, "coord_t"}},
    {"enabled", true}
  }, "my_struct_t"};
  EXPECT_EQ(my_struct["index"], 1);
  EXPECT_EQ(my_struct["coordinates.x"], 0);
  EXPECT_EQ(my_struct["coordinates.y"], 5);
  EXPECT_EQ(my_struct["enabled"], true);
  my_struct["coordinates.x"] = 23;
  EXPECT_EQ(my_struct["coordinates.x"], 23);
}

TEST_F(AnyValueTest, BooleanValue)
{
  AnyValue boolean_value{Boolean};
  EXPECT_EQ(boolean_value.GetType(), Boolean);
  EXPECT_NE(boolean_value.GetType(), SignedInteger8);
  EXPECT_FALSE(IsEmptyValue(boolean_value));
  EXPECT_FALSE(IsStructValue(boolean_value));
  EXPECT_FALSE(IsArrayValue(boolean_value));
  EXPECT_TRUE(IsScalarValue(boolean_value));
  EXPECT_EQ(boolean_value.GetTypeCode(), TypeCode::Bool);
  EXPECT_EQ(boolean_value.GetTypeName(), BOOLEAN_TYPE_NAME);
  EXPECT_THROW(boolean_value["field"], KeyNotAllowedException);
  EXPECT_EQ(boolean_value.As<boolean>(), false);
  EXPECT_EQ(boolean_value.As<int8>(), 0);
  EXPECT_EQ(boolean_value.As<uint8>(), 0);
  EXPECT_EQ(boolean_value.As<int16>(), 0);
  EXPECT_EQ(boolean_value.As<uint16>(), 0);
  EXPECT_EQ(boolean_value.As<int32>(), 0);
  EXPECT_EQ(boolean_value.As<uint32>(), 0);
  EXPECT_EQ(boolean_value.As<int64>(), 0);
  EXPECT_EQ(boolean_value.As<uint64>(), 0);
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
  EXPECT_EQ(boolean_value, true);

  const AnyValue copy = boolean_value;
  EXPECT_TRUE(IsScalarValue(copy));
  EXPECT_EQ(copy, boolean_value);
  EXPECT_FALSE(IsEmptyValue(copy));
  EXPECT_FALSE(IsStructValue(copy));
  EXPECT_FALSE(IsArrayValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Bool);
  EXPECT_EQ(copy.GetTypeName(), BOOLEAN_TYPE_NAME);
  EXPECT_THROW(copy["field"], KeyNotAllowedException);
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
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Bool);
  EXPECT_EQ(moved.GetTypeName(), BOOLEAN_TYPE_NAME);
  EXPECT_THROW(moved["field"], KeyNotAllowedException);
  EXPECT_EQ(moved.As<boolean>(), true);
  EXPECT_EQ(moved.As<int8>(), 1);
  EXPECT_EQ(moved.As<uint8>(), 1u);

  AnyValue boolean_from_literal = true;
  EXPECT_EQ(boolean_from_literal.GetType(), Boolean);
  EXPECT_NE(boolean_from_literal.GetType(), SignedInteger8);
  EXPECT_FALSE(IsEmptyValue(boolean_from_literal));
  EXPECT_FALSE(IsStructValue(boolean_from_literal));
  EXPECT_FALSE(IsArrayValue(boolean_from_literal));
  EXPECT_TRUE(IsScalarValue(boolean_from_literal));
  EXPECT_EQ(boolean_from_literal.GetTypeCode(), TypeCode::Bool);
  EXPECT_EQ(boolean_from_literal.GetTypeName(), BOOLEAN_TYPE_NAME);
  EXPECT_THROW(boolean_from_literal["field"], KeyNotAllowedException);
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
  EXPECT_TRUE(IsScalarValue(boolean_from_typed_literal));
  EXPECT_EQ(boolean_from_typed_literal.GetTypeCode(), TypeCode::Bool);
  EXPECT_EQ(boolean_from_typed_literal.GetTypeName(), BOOLEAN_TYPE_NAME);
  EXPECT_THROW(boolean_from_typed_literal["field"], KeyNotAllowedException);
  EXPECT_EQ(boolean_from_typed_literal.As<boolean>(), true);
  boolean_from_typed_literal = false;
  EXPECT_EQ(boolean_from_typed_literal.As<boolean>(), false);
  EXPECT_EQ(boolean_from_typed_literal.As<int8>(), 0);
  EXPECT_EQ(boolean_from_typed_literal.As<uint8>(), 0);
}

TEST_F(AnyValueTest, SignedInteger8Value)
{
  AnyValue int8_value{SignedInteger8};
  EXPECT_EQ(int8_value.GetType(), SignedInteger8);
  EXPECT_NE(int8_value.GetType(), UnsignedInteger8);
  EXPECT_FALSE(IsEmptyValue(int8_value));
  EXPECT_FALSE(IsStructValue(int8_value));
  EXPECT_FALSE(IsArrayValue(int8_value));
  EXPECT_TRUE(IsScalarValue(int8_value));
  EXPECT_EQ(int8_value.GetTypeCode(), TypeCode::Int8);
  EXPECT_EQ(int8_value.GetTypeName(), INT8_TYPE_NAME);
  EXPECT_THROW(int8_value["field"], KeyNotAllowedException);
  EXPECT_EQ(int8_value.As<boolean>(), false);
  EXPECT_EQ(int8_value.As<int8>(), 0);
  EXPECT_EQ(int8_value.As<uint8>(), 0);
  EXPECT_EQ(int8_value.As<int16>(), 0);
  EXPECT_EQ(int8_value.As<uint16>(), 0);
  EXPECT_EQ(int8_value.As<int32>(), 0);
  EXPECT_EQ(int8_value.As<uint32>(), 0);
  EXPECT_EQ(int8_value.As<int64>(), 0);
  EXPECT_EQ(int8_value.As<uint64>(), 0);
  int8_value = 25;
  EXPECT_EQ(int8_value.As<boolean>(), true);
  EXPECT_EQ(int8_value.As<int8>(), 25);
  EXPECT_EQ(int8_value.As<uint8>(), 25);
  EXPECT_EQ(int8_value.As<int16>(), 25);
  EXPECT_EQ(int8_value.As<uint16>(), 25);
  EXPECT_EQ(int8_value.As<int32>(), 25);
  EXPECT_EQ(int8_value.As<uint32>(), 25);
  EXPECT_EQ(int8_value.As<int64>(), 25);
  EXPECT_EQ(int8_value.As<uint64>(), 25);
  EXPECT_EQ(int8_value, 25);

  const AnyValue copy = int8_value;
  EXPECT_TRUE(IsScalarValue(copy));
  EXPECT_EQ(copy, int8_value);
  EXPECT_FALSE(IsEmptyValue(copy));
  EXPECT_FALSE(IsStructValue(copy));
  EXPECT_FALSE(IsArrayValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Int8);
  EXPECT_EQ(copy.GetTypeName(), INT8_TYPE_NAME);
  EXPECT_THROW(copy["field"], KeyNotAllowedException);
  EXPECT_EQ(copy.As<boolean>(), true);
  EXPECT_EQ(copy.As<int32>(), 25);
  EXPECT_EQ(copy, 25);

  AnyValue moved = std::move(int8_value);
  EXPECT_TRUE(IsEmptyValue(int8_value)); // Moved from value is always empty
  EXPECT_EQ(int8_value.GetType(), EmptyType);
  EXPECT_TRUE(IsScalarValue(moved));
  EXPECT_EQ(moved, copy);
  EXPECT_FALSE(IsEmptyValue(moved));
  EXPECT_FALSE(IsStructValue(moved));
  EXPECT_FALSE(IsArrayValue(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Int8);
  EXPECT_EQ(moved.GetTypeName(), INT8_TYPE_NAME);
  EXPECT_THROW(moved["field"], KeyNotAllowedException);
  EXPECT_EQ(moved.As<boolean>(), true);
  EXPECT_EQ(moved.As<int32>(), 25);

  int8 literal = 74;
  AnyValue int8_from_literal = literal;
  EXPECT_EQ(int8_from_literal.GetType(), SignedInteger8);
  EXPECT_NE(int8_from_literal.GetType(), SignedInteger32);
  EXPECT_FALSE(IsEmptyValue(int8_from_literal));
  EXPECT_FALSE(IsStructValue(int8_from_literal));
  EXPECT_FALSE(IsArrayValue(int8_from_literal));
  EXPECT_TRUE(IsScalarValue(int8_from_literal));
  EXPECT_EQ(int8_from_literal.GetTypeCode(), TypeCode::Int8);
  EXPECT_EQ(int8_from_literal.GetTypeName(), INT8_TYPE_NAME);
  EXPECT_THROW(int8_from_literal["field"], KeyNotAllowedException);
  EXPECT_EQ(int8_from_literal.As<int8>(), literal);
  int8_from_literal = -18;
  EXPECT_EQ(int8_from_literal.As<boolean>(), true);
  EXPECT_EQ(int8_from_literal.As<int8>(), -18);
  EXPECT_EQ(int8_from_literal.As<int32>(), -18);

  AnyValue int8_from_typed_literal = {SignedInteger8, 5};
  EXPECT_EQ(int8_from_typed_literal.GetType(), SignedInteger8);
  EXPECT_NE(int8_from_typed_literal.GetType(), Boolean);
  EXPECT_FALSE(IsEmptyValue(int8_from_typed_literal));
  EXPECT_FALSE(IsStructValue(int8_from_typed_literal));
  EXPECT_FALSE(IsArrayValue(int8_from_typed_literal));
  EXPECT_TRUE(IsScalarValue(int8_from_typed_literal));
  EXPECT_EQ(int8_from_typed_literal.GetTypeCode(), TypeCode::Int8);
  EXPECT_EQ(int8_from_typed_literal.GetTypeName(), INT8_TYPE_NAME);
  EXPECT_THROW(int8_from_typed_literal["field"], KeyNotAllowedException);
  EXPECT_EQ(int8_from_typed_literal.As<int8>(), 5);
  int8_from_typed_literal = 0;
  EXPECT_EQ(int8_from_typed_literal.As<boolean>(), false);
  EXPECT_EQ(int8_from_typed_literal.As<int8>(), 0);
  EXPECT_EQ(int8_from_typed_literal.As<int32>(), 0);
}

TEST_F(AnyValueTest, Character8Value)
{
  AnyValue char8_value{Character8};
  EXPECT_EQ(char8_value.GetType(), Character8);
  EXPECT_NE(char8_value.GetType(), UnsignedInteger8);
  EXPECT_FALSE(IsEmptyValue(char8_value));
  EXPECT_FALSE(IsStructValue(char8_value));
  EXPECT_FALSE(IsArrayValue(char8_value));
  EXPECT_TRUE(IsScalarValue(char8_value));
  EXPECT_EQ(char8_value.GetTypeCode(), TypeCode::Char8);
  EXPECT_EQ(char8_value.GetTypeName(), CHAR8_TYPE_NAME);
  EXPECT_THROW(char8_value["field"], KeyNotAllowedException);
  EXPECT_EQ(char8_value.As<boolean>(), false);
  EXPECT_EQ(char8_value.As<int8>(), 0);
  EXPECT_EQ(char8_value.As<uint8>(), 0);
  EXPECT_EQ(char8_value.As<int16>(), 0);
  EXPECT_EQ(char8_value.As<uint16>(), 0);
  EXPECT_EQ(char8_value.As<int32>(), 0);
  EXPECT_EQ(char8_value.As<uint32>(), 0);
  EXPECT_EQ(char8_value.As<int64>(), 0);
  EXPECT_EQ(char8_value.As<uint64>(), 0);
  char init_val = 'b';
  char8_value = init_val;
  EXPECT_EQ(char8_value.As<boolean>(), true);
  EXPECT_EQ(char8_value.As<char8>(), init_val);
  EXPECT_EQ(char8_value.As<int8>(), init_val);
  EXPECT_EQ(char8_value.As<uint8>(), init_val);
  EXPECT_EQ(char8_value.As<int16>(), init_val);
  EXPECT_EQ(char8_value.As<uint16>(), init_val);
  EXPECT_EQ(char8_value.As<int32>(), init_val);
  EXPECT_EQ(char8_value.As<uint32>(), init_val);
  EXPECT_EQ(char8_value.As<int64>(), init_val);
  EXPECT_EQ(char8_value.As<uint64>(), init_val);
  EXPECT_EQ(char8_value, init_val);

  const AnyValue copy = char8_value;
  EXPECT_TRUE(IsScalarValue(copy));
  EXPECT_EQ(copy, char8_value);
  EXPECT_FALSE(IsEmptyValue(copy));
  EXPECT_FALSE(IsStructValue(copy));
  EXPECT_FALSE(IsArrayValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Char8);
  EXPECT_EQ(copy.GetTypeName(), CHAR8_TYPE_NAME);
  EXPECT_THROW(copy["field"], KeyNotAllowedException);
  EXPECT_EQ(copy.As<boolean>(), true);
  EXPECT_EQ(copy.As<char8>(), init_val);
  EXPECT_EQ(copy, init_val);

  AnyValue moved = std::move(char8_value);
  EXPECT_TRUE(IsEmptyValue(char8_value)); // Moved from value is always empty
  EXPECT_EQ(char8_value.GetType(), EmptyType);
  EXPECT_TRUE(IsScalarValue(moved));
  EXPECT_EQ(moved, copy);
  EXPECT_FALSE(IsEmptyValue(moved));
  EXPECT_FALSE(IsStructValue(moved));
  EXPECT_FALSE(IsArrayValue(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Char8);
  EXPECT_EQ(moved.GetTypeName(), CHAR8_TYPE_NAME);
  EXPECT_THROW(moved["field"], KeyNotAllowedException);
  EXPECT_EQ(moved.As<boolean>(), true);
  EXPECT_EQ(moved.As<char8>(), init_val);

  char8 literal = 'L';
  AnyValue char8_from_literal = literal;
  EXPECT_EQ(char8_from_literal.GetType(), Character8);
  EXPECT_NE(char8_from_literal.GetType(), SignedInteger32);
  EXPECT_FALSE(IsEmptyValue(char8_from_literal));
  EXPECT_FALSE(IsStructValue(char8_from_literal));
  EXPECT_FALSE(IsArrayValue(char8_from_literal));
  EXPECT_TRUE(IsScalarValue(char8_from_literal));
  EXPECT_EQ(char8_from_literal.GetTypeCode(), TypeCode::Char8);
  EXPECT_EQ(char8_from_literal.GetTypeName(), CHAR8_TYPE_NAME);
  EXPECT_THROW(char8_from_literal["field"], KeyNotAllowedException);
  EXPECT_EQ(char8_from_literal.As<char8>(), literal);
  char8_from_literal = 'M';
  EXPECT_EQ(char8_from_literal.As<boolean>(), true);
  EXPECT_EQ(char8_from_literal.As<char8>(), 'M');
  EXPECT_EQ(char8_from_literal.As<int32>(), 'M');

  AnyValue char8_from_typed_literal = {Character8, 5};
  EXPECT_EQ(char8_from_typed_literal.GetType(), Character8);
  EXPECT_NE(char8_from_typed_literal.GetType(), Boolean);
  EXPECT_FALSE(IsEmptyValue(char8_from_typed_literal));
  EXPECT_FALSE(IsStructValue(char8_from_typed_literal));
  EXPECT_FALSE(IsArrayValue(char8_from_typed_literal));
  EXPECT_TRUE(IsScalarValue(char8_from_typed_literal));
  EXPECT_EQ(char8_from_typed_literal.GetTypeCode(), TypeCode::Char8);
  EXPECT_EQ(char8_from_typed_literal.GetTypeName(), CHAR8_TYPE_NAME);
  EXPECT_THROW(char8_from_typed_literal["field"], KeyNotAllowedException);
  EXPECT_EQ(char8_from_typed_literal.As<int8>(), 5);
  char8_from_typed_literal = 0;
  EXPECT_EQ(char8_from_typed_literal.As<boolean>(), false);
  EXPECT_EQ(char8_from_typed_literal.As<int8>(), 0);
  EXPECT_EQ(char8_from_typed_literal.As<int32>(), 0);
}

TEST_F(AnyValueTest, UnsignedInteger8Value)
{
  AnyValue uint8_value{UnsignedInteger8};
  EXPECT_EQ(uint8_value.GetType(), UnsignedInteger8);
  EXPECT_NE(uint8_value.GetType(), SignedInteger32);
  EXPECT_FALSE(IsEmptyValue(uint8_value));
  EXPECT_FALSE(IsStructValue(uint8_value));
  EXPECT_FALSE(IsArrayValue(uint8_value));
  EXPECT_TRUE(IsScalarValue(uint8_value));
  EXPECT_EQ(uint8_value.GetTypeCode(), TypeCode::UInt8);
  EXPECT_EQ(uint8_value.GetTypeName(), UINT8_TYPE_NAME);
  EXPECT_THROW(uint8_value["field"], KeyNotAllowedException);
  EXPECT_EQ(uint8_value.As<boolean>(), false);
  EXPECT_EQ(uint8_value.As<int8>(), 0);
  EXPECT_EQ(uint8_value.As<uint8>(), 0);
  EXPECT_EQ(uint8_value.As<int16>(), 0);
  EXPECT_EQ(uint8_value.As<uint16>(), 0);
  EXPECT_EQ(uint8_value.As<int32>(), 0);
  EXPECT_EQ(uint8_value.As<uint32>(), 0);
  EXPECT_EQ(uint8_value.As<int64>(), 0);
  EXPECT_EQ(uint8_value.As<uint64>(), 0);
  uint8_value = 25;
  EXPECT_EQ(uint8_value.As<boolean>(), true);
  EXPECT_EQ(uint8_value.As<int8>(), 25);
  EXPECT_EQ(uint8_value.As<uint8>(), 25);
  EXPECT_EQ(uint8_value.As<int16>(), 25);
  EXPECT_EQ(uint8_value.As<uint16>(), 25);
  EXPECT_EQ(uint8_value.As<int32>(), 25);
  EXPECT_EQ(uint8_value.As<uint32>(), 25);
  EXPECT_EQ(uint8_value.As<int64>(), 25);
  EXPECT_EQ(uint8_value.As<uint64>(), 25);
  EXPECT_EQ(uint8_value, 25);

  const AnyValue copy = uint8_value;
  EXPECT_TRUE(IsScalarValue(copy));
  EXPECT_EQ(copy, uint8_value);
  EXPECT_FALSE(IsEmptyValue(copy));
  EXPECT_FALSE(IsStructValue(copy));
  EXPECT_FALSE(IsArrayValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::UInt8);
  EXPECT_EQ(copy.GetTypeName(), UINT8_TYPE_NAME);
  EXPECT_THROW(copy["field"], KeyNotAllowedException);
  EXPECT_EQ(copy.As<boolean>(), true);
  EXPECT_EQ(copy.As<int32>(), 25);
  EXPECT_EQ(copy, 25);

  AnyValue moved = std::move(uint8_value);
  EXPECT_TRUE(IsEmptyValue(uint8_value)); // Moved from value is always empty
  EXPECT_EQ(uint8_value.GetType(), EmptyType);
  EXPECT_TRUE(IsScalarValue(moved));
  EXPECT_EQ(moved, copy);
  EXPECT_FALSE(IsEmptyValue(moved));
  EXPECT_FALSE(IsStructValue(moved));
  EXPECT_FALSE(IsArrayValue(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::UInt8);
  EXPECT_EQ(moved.GetTypeName(), UINT8_TYPE_NAME);
  EXPECT_THROW(moved["field"], KeyNotAllowedException);
  EXPECT_EQ(moved.As<boolean>(), true);
  EXPECT_EQ(moved.As<int32>(), 25);

  uint8 literal = 74;
  AnyValue uint8_from_literal = literal;
  EXPECT_EQ(uint8_from_literal.GetType(), UnsignedInteger8);
  EXPECT_NE(uint8_from_literal.GetType(), SignedInteger32);
  EXPECT_FALSE(IsEmptyValue(uint8_from_literal));
  EXPECT_FALSE(IsStructValue(uint8_from_literal));
  EXPECT_FALSE(IsArrayValue(uint8_from_literal));
  EXPECT_TRUE(IsScalarValue(uint8_from_literal));
  EXPECT_EQ(uint8_from_literal.GetTypeCode(), TypeCode::UInt8);
  EXPECT_EQ(uint8_from_literal.GetTypeName(), UINT8_TYPE_NAME);
  EXPECT_THROW(uint8_from_literal["field"], KeyNotAllowedException);
  EXPECT_EQ(uint8_from_literal.As<uint8>(), literal);
  uint8_from_literal = 18;
  EXPECT_EQ(uint8_from_literal.As<boolean>(), true);
  EXPECT_EQ(uint8_from_literal.As<uint8>(), 18);
  EXPECT_EQ(uint8_from_literal.As<int32>(), 18);

  AnyValue uint8_from_typed_literal = {UnsignedInteger8, 5};
  EXPECT_EQ(uint8_from_typed_literal.GetType(), UnsignedInteger8);
  EXPECT_NE(uint8_from_typed_literal.GetType(), Boolean);
  EXPECT_FALSE(IsEmptyValue(uint8_from_typed_literal));
  EXPECT_FALSE(IsStructValue(uint8_from_typed_literal));
  EXPECT_FALSE(IsArrayValue(uint8_from_typed_literal));
  EXPECT_TRUE(IsScalarValue(uint8_from_typed_literal));
  EXPECT_EQ(uint8_from_typed_literal.GetTypeCode(), TypeCode::UInt8);
  EXPECT_EQ(uint8_from_typed_literal.GetTypeName(), UINT8_TYPE_NAME);
  EXPECT_THROW(uint8_from_typed_literal["field"], KeyNotAllowedException);
  EXPECT_EQ(uint8_from_typed_literal.As<uint8>(), 5);
  uint8_from_typed_literal = 0;
  EXPECT_EQ(uint8_from_typed_literal.As<boolean>(), false);
  EXPECT_EQ(uint8_from_typed_literal.As<uint8>(), 0);
  EXPECT_EQ(uint8_from_typed_literal.As<int32>(), 0);
}

TEST_F(AnyValueTest, SignedInteger16Value)
{
  AnyValue int16_value{SignedInteger16};
  EXPECT_EQ(int16_value.GetType(), SignedInteger16);
  EXPECT_NE(int16_value.GetType(), UnsignedInteger16);
  EXPECT_FALSE(IsEmptyValue(int16_value));
  EXPECT_FALSE(IsStructValue(int16_value));
  EXPECT_FALSE(IsArrayValue(int16_value));
  EXPECT_TRUE(IsScalarValue(int16_value));
  EXPECT_EQ(int16_value.GetTypeCode(), TypeCode::Int16);
  EXPECT_EQ(int16_value.GetTypeName(), INT16_TYPE_NAME);
  EXPECT_THROW(int16_value["field"], KeyNotAllowedException);
  EXPECT_EQ(int16_value.As<boolean>(), false);
  EXPECT_EQ(int16_value.As<int8>(), 0);
  EXPECT_EQ(int16_value.As<uint8>(), 0);
  EXPECT_EQ(int16_value.As<int16>(), 0);
  EXPECT_EQ(int16_value.As<uint16>(), 0);
  EXPECT_EQ(int16_value.As<int32>(), 0);
  EXPECT_EQ(int16_value.As<uint32>(), 0);
  EXPECT_EQ(int16_value.As<int64>(), 0);
  EXPECT_EQ(int16_value.As<uint64>(), 0);
  auto new_val = 25;
  int16_value = new_val;
  EXPECT_EQ(int16_value.As<boolean>(), true);
  EXPECT_EQ(int16_value.As<int8>(), new_val);
  EXPECT_EQ(int16_value.As<uint8>(), new_val);
  EXPECT_EQ(int16_value.As<int16>(), new_val);
  EXPECT_EQ(int16_value.As<uint16>(), new_val);
  EXPECT_EQ(int16_value.As<int32>(), new_val);
  EXPECT_EQ(int16_value.As<uint32>(), new_val);
  EXPECT_EQ(int16_value.As<int64>(), new_val);
  EXPECT_EQ(int16_value.As<uint64>(), new_val);
  EXPECT_EQ(int16_value, 25);

  const AnyValue copy = int16_value;
  EXPECT_TRUE(IsScalarValue(copy));
  EXPECT_EQ(copy, int16_value);
  EXPECT_FALSE(IsEmptyValue(copy));
  EXPECT_FALSE(IsStructValue(copy));
  EXPECT_FALSE(IsArrayValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Int16);
  EXPECT_EQ(copy.GetTypeName(), INT16_TYPE_NAME);
  EXPECT_THROW(copy["field"], KeyNotAllowedException);
  EXPECT_EQ(copy.As<boolean>(), true);
  EXPECT_EQ(copy.As<int32>(), new_val);
  EXPECT_EQ(copy, 25);

  AnyValue moved = std::move(int16_value);
  EXPECT_TRUE(IsEmptyValue(int16_value)); // Moved from value is always empty
  EXPECT_EQ(int16_value.GetType(), EmptyType);
  EXPECT_TRUE(IsScalarValue(moved));
  EXPECT_EQ(moved, copy);
  EXPECT_FALSE(IsEmptyValue(moved));
  EXPECT_FALSE(IsStructValue(moved));
  EXPECT_FALSE(IsArrayValue(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Int16);
  EXPECT_EQ(moved.GetTypeName(), INT16_TYPE_NAME);
  EXPECT_THROW(moved["field"], KeyNotAllowedException);
  EXPECT_EQ(moved.As<boolean>(), true);
  EXPECT_EQ(moved.As<int32>(), 25);

  int16 literal = 74;
  AnyValue int16_from_literal = literal;
  EXPECT_EQ(int16_from_literal.GetType(), SignedInteger16);
  EXPECT_NE(int16_from_literal.GetType(), SignedInteger32);
  EXPECT_FALSE(IsEmptyValue(int16_from_literal));
  EXPECT_FALSE(IsStructValue(int16_from_literal));
  EXPECT_FALSE(IsArrayValue(int16_from_literal));
  EXPECT_TRUE(IsScalarValue(int16_from_literal));
  EXPECT_EQ(int16_from_literal.GetTypeCode(), TypeCode::Int16);
  EXPECT_EQ(int16_from_literal.GetTypeName(), INT16_TYPE_NAME);
  EXPECT_THROW(int16_from_literal["field"], KeyNotAllowedException);
  EXPECT_EQ(int16_from_literal.As<int16>(), literal);
  int16_from_literal = -18;
  EXPECT_EQ(int16_from_literal.As<boolean>(), true);
  EXPECT_EQ(int16_from_literal.As<int16>(), -18);
  EXPECT_EQ(int16_from_literal.As<int32>(), -18);

  AnyValue int16_from_typed_literal = {SignedInteger16, 5};
  EXPECT_EQ(int16_from_typed_literal.GetType(), SignedInteger16);
  EXPECT_NE(int16_from_typed_literal.GetType(), Boolean);
  EXPECT_FALSE(IsEmptyValue(int16_from_typed_literal));
  EXPECT_FALSE(IsStructValue(int16_from_typed_literal));
  EXPECT_FALSE(IsArrayValue(int16_from_typed_literal));
  EXPECT_TRUE(IsScalarValue(int16_from_typed_literal));
  EXPECT_EQ(int16_from_typed_literal.GetTypeCode(), TypeCode::Int16);
  EXPECT_EQ(int16_from_typed_literal.GetTypeName(), INT16_TYPE_NAME);
  EXPECT_THROW(int16_from_typed_literal["field"], KeyNotAllowedException);
  EXPECT_EQ(int16_from_typed_literal.As<int16>(), 5);
  int16_from_typed_literal = 0;
  EXPECT_EQ(int16_from_typed_literal.As<boolean>(), false);
  EXPECT_EQ(int16_from_typed_literal.As<int16>(), 0);
  EXPECT_EQ(int16_from_typed_literal.As<int32>(), 0);
}

TEST_F(AnyValueTest, UnsignedInteger16Value)
{
  AnyValue uint16_value{UnsignedInteger16};
  EXPECT_EQ(uint16_value.GetType(), UnsignedInteger16);
  EXPECT_NE(uint16_value.GetType(), SignedInteger32);
  EXPECT_FALSE(IsEmptyValue(uint16_value));
  EXPECT_FALSE(IsStructValue(uint16_value));
  EXPECT_FALSE(IsArrayValue(uint16_value));
  EXPECT_TRUE(IsScalarValue(uint16_value));
  EXPECT_EQ(uint16_value.GetTypeCode(), TypeCode::UInt16);
  EXPECT_EQ(uint16_value.GetTypeName(), UINT16_TYPE_NAME);
  EXPECT_THROW(uint16_value["field"], KeyNotAllowedException);
  EXPECT_EQ(uint16_value.As<boolean>(), false);
  EXPECT_EQ(uint16_value.As<int8>(), 0);
  EXPECT_EQ(uint16_value.As<uint8>(), 0);
  EXPECT_EQ(uint16_value.As<int16>(), 0);
  EXPECT_EQ(uint16_value.As<uint16>(), 0);
  EXPECT_EQ(uint16_value.As<int32>(), 0);
  EXPECT_EQ(uint16_value.As<uint32>(), 0);
  EXPECT_EQ(uint16_value.As<int64>(), 0);
  EXPECT_EQ(uint16_value.As<uint64>(), 0);
  auto new_val = 25;
  uint16_value = new_val;
  EXPECT_EQ(uint16_value.As<boolean>(), true);
  EXPECT_EQ(uint16_value.As<int8>(), new_val);
  EXPECT_EQ(uint16_value.As<uint8>(), new_val);
  EXPECT_EQ(uint16_value.As<int16>(), new_val);
  EXPECT_EQ(uint16_value.As<uint16>(), new_val);
  EXPECT_EQ(uint16_value.As<int32>(), new_val);
  EXPECT_EQ(uint16_value.As<uint32>(), new_val);
  EXPECT_EQ(uint16_value.As<int64>(), new_val);
  EXPECT_EQ(uint16_value.As<uint64>(), new_val);
  EXPECT_EQ(uint16_value, new_val);

  const AnyValue copy = uint16_value;
  EXPECT_TRUE(IsScalarValue(copy));
  EXPECT_EQ(copy, uint16_value);
  EXPECT_FALSE(IsEmptyValue(copy));
  EXPECT_FALSE(IsStructValue(copy));
  EXPECT_FALSE(IsArrayValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::UInt16);
  EXPECT_EQ(copy.GetTypeName(), UINT16_TYPE_NAME);
  EXPECT_THROW(copy["field"], KeyNotAllowedException);
  EXPECT_EQ(copy.As<uint16>(), new_val);
  EXPECT_EQ(copy.As<int32>(), new_val);
  EXPECT_EQ(copy, new_val);

  AnyValue moved = std::move(uint16_value);
  EXPECT_TRUE(IsEmptyValue(uint16_value)); // Moved from value is always empty
  EXPECT_EQ(uint16_value.GetType(), EmptyType);
  EXPECT_TRUE(IsScalarValue(moved));
  EXPECT_EQ(moved, copy);
  EXPECT_FALSE(IsEmptyValue(moved));
  EXPECT_FALSE(IsStructValue(moved));
  EXPECT_FALSE(IsArrayValue(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::UInt16);
  EXPECT_EQ(moved.GetTypeName(), UINT16_TYPE_NAME);
  EXPECT_THROW(moved["field"], KeyNotAllowedException);
  EXPECT_EQ(moved.As<boolean>(), true);
  EXPECT_EQ(moved.As<int32>(), new_val);

  uint16 literal = 74;
  AnyValue uint16_from_literal = literal;
  EXPECT_EQ(uint16_from_literal.GetType(), UnsignedInteger16);
  EXPECT_NE(uint16_from_literal.GetType(), SignedInteger32);
  EXPECT_FALSE(IsEmptyValue(uint16_from_literal));
  EXPECT_FALSE(IsStructValue(uint16_from_literal));
  EXPECT_FALSE(IsArrayValue(uint16_from_literal));
  EXPECT_TRUE(IsScalarValue(uint16_from_literal));
  EXPECT_EQ(uint16_from_literal.GetTypeCode(), TypeCode::UInt16);
  EXPECT_EQ(uint16_from_literal.GetTypeName(), UINT16_TYPE_NAME);
  EXPECT_THROW(uint16_from_literal["field"], KeyNotAllowedException);
  EXPECT_EQ(uint16_from_literal.As<uint16>(), literal);
  uint16_from_literal = 116;
  EXPECT_EQ(uint16_from_literal.As<boolean>(), true);
  EXPECT_EQ(uint16_from_literal.As<uint16>(), 116);
  EXPECT_EQ(uint16_from_literal.As<int32>(), 116);

  AnyValue uint16_from_typed_literal = {UnsignedInteger16, 5};
  EXPECT_EQ(uint16_from_typed_literal.GetType(), UnsignedInteger16);
  EXPECT_NE(uint16_from_typed_literal.GetType(), Boolean);
  EXPECT_FALSE(IsEmptyValue(uint16_from_typed_literal));
  EXPECT_FALSE(IsStructValue(uint16_from_typed_literal));
  EXPECT_FALSE(IsArrayValue(uint16_from_typed_literal));
  EXPECT_TRUE(IsScalarValue(uint16_from_typed_literal));
  EXPECT_EQ(uint16_from_typed_literal.GetTypeCode(), TypeCode::UInt16);
  EXPECT_EQ(uint16_from_typed_literal.GetTypeName(), UINT16_TYPE_NAME);
  EXPECT_THROW(uint16_from_typed_literal["field"], KeyNotAllowedException);
  EXPECT_EQ(uint16_from_typed_literal.As<uint16>(), 5);
  uint16_from_typed_literal = 0;
  EXPECT_EQ(uint16_from_typed_literal.As<boolean>(), false);
  EXPECT_EQ(uint16_from_typed_literal.As<uint16>(), 0);
  EXPECT_EQ(uint16_from_typed_literal.As<int32>(), 0);
}

TEST_F(AnyValueTest, SignedInteger32Value)
{
  AnyValue int32_value{SignedInteger32};
  EXPECT_EQ(int32_value.GetType(), SignedInteger32);
  EXPECT_NE(int32_value.GetType(), UnsignedInteger32);
  EXPECT_FALSE(IsEmptyValue(int32_value));
  EXPECT_FALSE(IsStructValue(int32_value));
  EXPECT_FALSE(IsArrayValue(int32_value));
  EXPECT_TRUE(IsScalarValue(int32_value));
  EXPECT_EQ(int32_value.GetTypeCode(), TypeCode::Int32);
  EXPECT_EQ(int32_value.GetTypeName(), INT32_TYPE_NAME);
  EXPECT_THROW(int32_value["field"], KeyNotAllowedException);
  EXPECT_EQ(int32_value.As<boolean>(), false);
  EXPECT_EQ(int32_value.As<int8>(), 0);
  EXPECT_EQ(int32_value.As<uint8>(), 0);
  EXPECT_EQ(int32_value.As<int16>(), 0);
  EXPECT_EQ(int32_value.As<uint16>(), 0);
  EXPECT_EQ(int32_value.As<int32>(), 0);
  EXPECT_EQ(int32_value.As<uint32>(), 0);
  EXPECT_EQ(int32_value.As<int64>(), 0);
  EXPECT_EQ(int32_value.As<uint64>(), 0);
  auto new_val = 25;
  int32_value = new_val;
  EXPECT_EQ(int32_value.As<boolean>(), true);
  EXPECT_EQ(int32_value.As<int8>(), new_val);
  EXPECT_EQ(int32_value.As<uint8>(), new_val);
  EXPECT_EQ(int32_value.As<int16>(), new_val);
  EXPECT_EQ(int32_value.As<uint16>(), new_val);
  EXPECT_EQ(int32_value.As<int32>(), new_val);
  EXPECT_EQ(int32_value.As<uint32>(), new_val);
  EXPECT_EQ(int32_value.As<int64>(), new_val);
  EXPECT_EQ(int32_value.As<uint64>(), new_val);
  EXPECT_EQ(int32_value, new_val);

  const AnyValue copy = int32_value;
  EXPECT_TRUE(IsScalarValue(copy));
  EXPECT_EQ(copy, int32_value);
  EXPECT_FALSE(IsEmptyValue(copy));
  EXPECT_FALSE(IsStructValue(copy));
  EXPECT_FALSE(IsArrayValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Int32);
  EXPECT_EQ(copy.GetTypeName(), INT32_TYPE_NAME);
  EXPECT_THROW(copy["field"], KeyNotAllowedException);
  EXPECT_EQ(copy.As<boolean>(), true);
  EXPECT_EQ(copy.As<int32>(), new_val);
  EXPECT_EQ(copy, new_val);

  AnyValue moved = std::move(int32_value);
  EXPECT_TRUE(IsEmptyValue(int32_value)); // Moved from value is always empty
  EXPECT_EQ(int32_value.GetType(), EmptyType);
  EXPECT_TRUE(IsScalarValue(moved));
  EXPECT_EQ(moved, copy);
  EXPECT_FALSE(IsEmptyValue(moved));
  EXPECT_FALSE(IsStructValue(moved));
  EXPECT_FALSE(IsArrayValue(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Int32);
  EXPECT_EQ(moved.GetTypeName(), INT32_TYPE_NAME);
  EXPECT_THROW(moved["field"], KeyNotAllowedException);
  EXPECT_EQ(moved.As<boolean>(), true);
  EXPECT_EQ(moved.As<int32>(), 25);

  int32 literal = 74;
  AnyValue int32_from_literal = literal;
  EXPECT_EQ(int32_from_literal.GetType(), SignedInteger32);
  EXPECT_NE(int32_from_literal.GetType(), SignedInteger16);
  EXPECT_FALSE(IsEmptyValue(int32_from_literal));
  EXPECT_FALSE(IsStructValue(int32_from_literal));
  EXPECT_FALSE(IsArrayValue(int32_from_literal));
  EXPECT_TRUE(IsScalarValue(int32_from_literal));
  EXPECT_EQ(int32_from_literal.GetTypeCode(), TypeCode::Int32);
  EXPECT_EQ(int32_from_literal.GetTypeName(), INT32_TYPE_NAME);
  EXPECT_THROW(int32_from_literal["field"], KeyNotAllowedException);
  EXPECT_EQ(int32_from_literal.As<int32>(), literal);
  int32_from_literal = -18;
  EXPECT_EQ(int32_from_literal.As<boolean>(), true);
  EXPECT_EQ(int32_from_literal.As<int32>(), -18);
  EXPECT_EQ(int32_from_literal.As<int16>(), -18);

  AnyValue int32_from_typed_literal = {SignedInteger32, 5};
  EXPECT_EQ(int32_from_typed_literal.GetType(), SignedInteger32);
  EXPECT_NE(int32_from_typed_literal.GetType(), Boolean);
  EXPECT_FALSE(IsEmptyValue(int32_from_typed_literal));
  EXPECT_FALSE(IsStructValue(int32_from_typed_literal));
  EXPECT_FALSE(IsArrayValue(int32_from_typed_literal));
  EXPECT_TRUE(IsScalarValue(int32_from_typed_literal));
  EXPECT_EQ(int32_from_typed_literal.GetTypeCode(), TypeCode::Int32);
  EXPECT_EQ(int32_from_typed_literal.GetTypeName(), INT32_TYPE_NAME);
  EXPECT_THROW(int32_from_typed_literal["field"], KeyNotAllowedException);
  EXPECT_EQ(int32_from_typed_literal.As<int32>(), 5);
  int32_from_typed_literal = 0;
  EXPECT_EQ(int32_from_typed_literal.As<boolean>(), false);
  EXPECT_EQ(int32_from_typed_literal.As<int16>(), 0);
  EXPECT_EQ(int32_from_typed_literal.As<int32>(), 0);
}

TEST_F(AnyValueTest, UnsignedInteger32Value)
{
  AnyValue uint32_value{UnsignedInteger32};
  EXPECT_EQ(uint32_value.GetType(), UnsignedInteger32);
  EXPECT_NE(uint32_value.GetType(), SignedInteger32);
  EXPECT_FALSE(IsEmptyValue(uint32_value));
  EXPECT_FALSE(IsStructValue(uint32_value));
  EXPECT_FALSE(IsArrayValue(uint32_value));
  EXPECT_TRUE(IsScalarValue(uint32_value));
  EXPECT_EQ(uint32_value.GetTypeCode(), TypeCode::UInt32);
  EXPECT_EQ(uint32_value.GetTypeName(), UINT32_TYPE_NAME);
  EXPECT_THROW(uint32_value["field"], KeyNotAllowedException);
  EXPECT_EQ(uint32_value.As<boolean>(), false);
  EXPECT_EQ(uint32_value.As<int8>(), 0);
  EXPECT_EQ(uint32_value.As<uint8>(), 0);
  EXPECT_EQ(uint32_value.As<int16>(), 0);
  EXPECT_EQ(uint32_value.As<uint16>(), 0);
  EXPECT_EQ(uint32_value.As<int32>(), 0);
  EXPECT_EQ(uint32_value.As<uint32>(), 0);
  EXPECT_EQ(uint32_value.As<int64>(), 0);
  EXPECT_EQ(uint32_value.As<uint64>(), 0);
  auto new_val = 25;
  uint32_value = new_val;
  EXPECT_EQ(uint32_value.As<boolean>(), true);
  EXPECT_EQ(uint32_value.As<int8>(), new_val);
  EXPECT_EQ(uint32_value.As<uint8>(), new_val);
  EXPECT_EQ(uint32_value.As<int16>(), new_val);
  EXPECT_EQ(uint32_value.As<uint16>(), new_val);
  EXPECT_EQ(uint32_value.As<int32>(), new_val);
  EXPECT_EQ(uint32_value.As<uint32>(), new_val);
  EXPECT_EQ(uint32_value.As<int64>(), new_val);
  EXPECT_EQ(uint32_value.As<uint64>(), new_val);
  EXPECT_EQ(uint32_value, new_val);

  const AnyValue copy = uint32_value;
  EXPECT_TRUE(IsScalarValue(copy));
  EXPECT_EQ(copy, uint32_value);
  EXPECT_FALSE(IsEmptyValue(copy));
  EXPECT_FALSE(IsStructValue(copy));
  EXPECT_FALSE(IsArrayValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::UInt32);
  EXPECT_EQ(copy.GetTypeName(), UINT32_TYPE_NAME);
  EXPECT_THROW(copy["field"], KeyNotAllowedException);
  EXPECT_EQ(copy.As<uint32>(), new_val);
  EXPECT_EQ(copy.As<int32>(), new_val);
  EXPECT_EQ(copy, new_val);

  AnyValue moved = std::move(uint32_value);
  EXPECT_TRUE(IsEmptyValue(uint32_value)); // Moved from value is always empty
  EXPECT_EQ(uint32_value.GetType(), EmptyType);
  EXPECT_TRUE(IsScalarValue(moved));
  EXPECT_EQ(moved, copy);
  EXPECT_FALSE(IsEmptyValue(moved));
  EXPECT_FALSE(IsStructValue(moved));
  EXPECT_FALSE(IsArrayValue(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::UInt32);
  EXPECT_EQ(moved.GetTypeName(), UINT32_TYPE_NAME);
  EXPECT_THROW(moved["field"], KeyNotAllowedException);
  EXPECT_EQ(moved.As<boolean>(), true);
  EXPECT_EQ(moved.As<int32>(), new_val);

  uint32 literal = 74;
  AnyValue uint32_from_literal = literal;
  EXPECT_EQ(uint32_from_literal.GetType(), UnsignedInteger32);
  EXPECT_NE(uint32_from_literal.GetType(), SignedInteger32);
  EXPECT_FALSE(IsEmptyValue(uint32_from_literal));
  EXPECT_FALSE(IsStructValue(uint32_from_literal));
  EXPECT_FALSE(IsArrayValue(uint32_from_literal));
  EXPECT_TRUE(IsScalarValue(uint32_from_literal));
  EXPECT_EQ(uint32_from_literal.GetTypeCode(), TypeCode::UInt32);
  EXPECT_EQ(uint32_from_literal.GetTypeName(), UINT32_TYPE_NAME);
  EXPECT_THROW(uint32_from_literal["field"], KeyNotAllowedException);
  EXPECT_EQ(uint32_from_literal.As<uint32>(), literal);
  uint32_from_literal = 116;
  EXPECT_EQ(uint32_from_literal.As<boolean>(), true);
  EXPECT_EQ(uint32_from_literal.As<uint32>(), 116);
  EXPECT_EQ(uint32_from_literal.As<int32>(), 116);

  AnyValue uint32_from_typed_literal = {UnsignedInteger32, 5};
  EXPECT_EQ(uint32_from_typed_literal.GetType(), UnsignedInteger32);
  EXPECT_NE(uint32_from_typed_literal.GetType(), Boolean);
  EXPECT_FALSE(IsEmptyValue(uint32_from_typed_literal));
  EXPECT_FALSE(IsStructValue(uint32_from_typed_literal));
  EXPECT_FALSE(IsArrayValue(uint32_from_typed_literal));
  EXPECT_TRUE(IsScalarValue(uint32_from_typed_literal));
  EXPECT_EQ(uint32_from_typed_literal.GetTypeCode(), TypeCode::UInt32);
  EXPECT_EQ(uint32_from_typed_literal.GetTypeName(), UINT32_TYPE_NAME);
  EXPECT_THROW(uint32_from_typed_literal["field"], KeyNotAllowedException);
  EXPECT_EQ(uint32_from_typed_literal.As<uint32>(), 5);
  uint32_from_typed_literal = 0;
  EXPECT_EQ(uint32_from_typed_literal.As<boolean>(), false);
  EXPECT_EQ(uint32_from_typed_literal.As<uint32>(), 0);
  EXPECT_EQ(uint32_from_typed_literal.As<int32>(), 0);
}

TEST_F(AnyValueTest, SignedInteger64Value)
{
  AnyValue int64_value{SignedInteger64};
  EXPECT_EQ(int64_value.GetType(), SignedInteger64);
  EXPECT_NE(int64_value.GetType(), UnsignedInteger32);
  EXPECT_FALSE(IsEmptyValue(int64_value));
  EXPECT_FALSE(IsStructValue(int64_value));
  EXPECT_FALSE(IsArrayValue(int64_value));
  EXPECT_TRUE(IsScalarValue(int64_value));
  EXPECT_EQ(int64_value.GetTypeCode(), TypeCode::Int64);
  EXPECT_EQ(int64_value.GetTypeName(), INT64_TYPE_NAME);
  EXPECT_THROW(int64_value["field"], KeyNotAllowedException);
  EXPECT_EQ(int64_value.As<boolean>(), false);
  EXPECT_EQ(int64_value.As<int8>(), 0);
  EXPECT_EQ(int64_value.As<uint8>(), 0);
  EXPECT_EQ(int64_value.As<int16>(), 0);
  EXPECT_EQ(int64_value.As<uint16>(), 0);
  EXPECT_EQ(int64_value.As<int32>(), 0);
  EXPECT_EQ(int64_value.As<uint32>(), 0);
  EXPECT_EQ(int64_value.As<int64>(), 0);
  EXPECT_EQ(int64_value.As<uint64>(), 0);
  auto new_val = 25;
  int64_value = new_val;
  EXPECT_EQ(int64_value.As<boolean>(), true);
  EXPECT_EQ(int64_value.As<int8>(), new_val);
  EXPECT_EQ(int64_value.As<uint8>(), new_val);
  EXPECT_EQ(int64_value.As<int16>(), new_val);
  EXPECT_EQ(int64_value.As<uint16>(), new_val);
  EXPECT_EQ(int64_value.As<int32>(), new_val);
  EXPECT_EQ(int64_value.As<uint32>(), new_val);
  EXPECT_EQ(int64_value.As<int64>(), new_val);
  EXPECT_EQ(int64_value.As<uint64>(), new_val);
  EXPECT_EQ(int64_value, new_val);

  const AnyValue copy = int64_value;
  EXPECT_TRUE(IsScalarValue(copy));
  EXPECT_EQ(copy, int64_value);
  EXPECT_FALSE(IsEmptyValue(copy));
  EXPECT_FALSE(IsStructValue(copy));
  EXPECT_FALSE(IsArrayValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Int64);
  EXPECT_EQ(copy.GetTypeName(), INT64_TYPE_NAME);
  EXPECT_THROW(copy["field"], KeyNotAllowedException);
  EXPECT_EQ(copy.As<boolean>(), true);
  EXPECT_EQ(copy.As<int64>(), new_val);
  EXPECT_EQ(copy, new_val);

  AnyValue moved = std::move(int64_value);
  EXPECT_TRUE(IsEmptyValue(int64_value)); // Moved from value is always empty
  EXPECT_EQ(int64_value.GetType(), EmptyType);
  EXPECT_TRUE(IsScalarValue(moved));
  EXPECT_EQ(moved, copy);
  EXPECT_FALSE(IsEmptyValue(moved));
  EXPECT_FALSE(IsStructValue(moved));
  EXPECT_FALSE(IsArrayValue(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Int64);
  EXPECT_EQ(moved.GetTypeName(), INT64_TYPE_NAME);
  EXPECT_THROW(moved["field"], KeyNotAllowedException);
  EXPECT_EQ(moved.As<boolean>(), true);
  EXPECT_EQ(moved.As<int64>(), 25);

  int64 literal = 74;
  AnyValue int64_from_literal = literal;
  EXPECT_EQ(int64_from_literal.GetType(), SignedInteger64);
  EXPECT_NE(int64_from_literal.GetType(), SignedInteger16);
  EXPECT_FALSE(IsEmptyValue(int64_from_literal));
  EXPECT_FALSE(IsStructValue(int64_from_literal));
  EXPECT_FALSE(IsArrayValue(int64_from_literal));
  EXPECT_TRUE(IsScalarValue(int64_from_literal));
  EXPECT_EQ(int64_from_literal.GetTypeCode(), TypeCode::Int64);
  EXPECT_EQ(int64_from_literal.GetTypeName(), INT64_TYPE_NAME);
  EXPECT_THROW(int64_from_literal["field"], KeyNotAllowedException);
  EXPECT_EQ(int64_from_literal.As<int64>(), literal);
  int64_from_literal = -18;
  EXPECT_EQ(int64_from_literal.As<boolean>(), true);
  EXPECT_EQ(int64_from_literal.As<int64>(), -18);
  EXPECT_EQ(int64_from_literal.As<int16>(), -18);

  AnyValue int64_from_typed_literal = {SignedInteger64, 5};
  EXPECT_EQ(int64_from_typed_literal.GetType(), SignedInteger64);
  EXPECT_NE(int64_from_typed_literal.GetType(), Boolean);
  EXPECT_FALSE(IsEmptyValue(int64_from_typed_literal));
  EXPECT_FALSE(IsStructValue(int64_from_typed_literal));
  EXPECT_FALSE(IsArrayValue(int64_from_typed_literal));
  EXPECT_TRUE(IsScalarValue(int64_from_typed_literal));
  EXPECT_EQ(int64_from_typed_literal.GetTypeCode(), TypeCode::Int64);
  EXPECT_EQ(int64_from_typed_literal.GetTypeName(), INT64_TYPE_NAME);
  EXPECT_THROW(int64_from_typed_literal["field"], KeyNotAllowedException);
  EXPECT_EQ(int64_from_typed_literal.As<int64>(), 5);
  int64_from_typed_literal = 0;
  EXPECT_EQ(int64_from_typed_literal.As<boolean>(), false);
  EXPECT_EQ(int64_from_typed_literal.As<int16>(), 0);
  EXPECT_EQ(int64_from_typed_literal.As<int64>(), 0);
}

TEST_F(AnyValueTest, UnsignedInteger64Value)
{
  AnyValue uint64_value{UnsignedInteger64};
  EXPECT_EQ(uint64_value.GetType(), UnsignedInteger64);
  EXPECT_NE(uint64_value.GetType(), SignedInteger64);
  EXPECT_FALSE(IsEmptyValue(uint64_value));
  EXPECT_FALSE(IsStructValue(uint64_value));
  EXPECT_FALSE(IsArrayValue(uint64_value));
  EXPECT_TRUE(IsScalarValue(uint64_value));
  EXPECT_EQ(uint64_value.GetTypeCode(), TypeCode::UInt64);
  EXPECT_EQ(uint64_value.GetTypeName(), UINT64_TYPE_NAME);
  EXPECT_THROW(uint64_value["field"], KeyNotAllowedException);
  EXPECT_EQ(uint64_value.As<boolean>(), false);
  EXPECT_EQ(uint64_value.As<int8>(), 0);
  EXPECT_EQ(uint64_value.As<uint8>(), 0);
  EXPECT_EQ(uint64_value.As<int16>(), 0);
  EXPECT_EQ(uint64_value.As<uint16>(), 0);
  EXPECT_EQ(uint64_value.As<int32>(), 0);
  EXPECT_EQ(uint64_value.As<uint32>(), 0);
  EXPECT_EQ(uint64_value.As<int64>(), 0);
  EXPECT_EQ(uint64_value.As<uint64>(), 0);
  auto new_val = 25;
  uint64_value = new_val;
  EXPECT_EQ(uint64_value.As<boolean>(), true);
  EXPECT_EQ(uint64_value.As<int8>(), new_val);
  EXPECT_EQ(uint64_value.As<uint8>(), new_val);
  EXPECT_EQ(uint64_value.As<int16>(), new_val);
  EXPECT_EQ(uint64_value.As<uint16>(), new_val);
  EXPECT_EQ(uint64_value.As<int32>(), new_val);
  EXPECT_EQ(uint64_value.As<uint32>(), new_val);
  EXPECT_EQ(uint64_value.As<int64>(), new_val);
  EXPECT_EQ(uint64_value.As<uint64>(), new_val);
  EXPECT_EQ(uint64_value, new_val);

  const AnyValue copy = uint64_value;
  EXPECT_TRUE(IsScalarValue(copy));
  EXPECT_EQ(copy, uint64_value);
  EXPECT_FALSE(IsEmptyValue(copy));
  EXPECT_FALSE(IsStructValue(copy));
  EXPECT_FALSE(IsArrayValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::UInt64);
  EXPECT_EQ(copy.GetTypeName(), UINT64_TYPE_NAME);
  EXPECT_THROW(copy["field"], KeyNotAllowedException);
  EXPECT_EQ(copy.As<uint64>(), new_val);
  EXPECT_EQ(copy.As<int32>(), new_val);
  EXPECT_EQ(copy, new_val);

  AnyValue moved = std::move(uint64_value);
  EXPECT_TRUE(IsEmptyValue(uint64_value)); // Moved from value is always empty
  EXPECT_EQ(uint64_value.GetType(), EmptyType);
  EXPECT_TRUE(IsScalarValue(moved));
  EXPECT_EQ(moved, copy);
  EXPECT_FALSE(IsEmptyValue(moved));
  EXPECT_FALSE(IsStructValue(moved));
  EXPECT_FALSE(IsArrayValue(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::UInt64);
  EXPECT_EQ(moved.GetTypeName(), UINT64_TYPE_NAME);
  EXPECT_THROW(moved["field"], KeyNotAllowedException);
  EXPECT_EQ(moved.As<boolean>(), true);
  EXPECT_EQ(moved.As<int64>(), new_val);

  uint64 literal = 74;
  AnyValue uint64_from_literal = literal;
  EXPECT_EQ(uint64_from_literal.GetType(), UnsignedInteger64);
  EXPECT_NE(uint64_from_literal.GetType(), SignedInteger64);
  EXPECT_FALSE(IsEmptyValue(uint64_from_literal));
  EXPECT_FALSE(IsStructValue(uint64_from_literal));
  EXPECT_FALSE(IsArrayValue(uint64_from_literal));
  EXPECT_TRUE(IsScalarValue(uint64_from_literal));
  EXPECT_EQ(uint64_from_literal.GetTypeCode(), TypeCode::UInt64);
  EXPECT_EQ(uint64_from_literal.GetTypeName(), UINT64_TYPE_NAME);
  EXPECT_THROW(uint64_from_literal["field"], KeyNotAllowedException);
  EXPECT_EQ(uint64_from_literal.As<uint64>(), literal);
  uint64_from_literal = 116;
  EXPECT_EQ(uint64_from_literal.As<boolean>(), true);
  EXPECT_EQ(uint64_from_literal.As<uint64>(), 116);
  EXPECT_EQ(uint64_from_literal.As<int32>(), 116);

  AnyValue uint64_from_typed_literal = {UnsignedInteger64, 5};
  EXPECT_EQ(uint64_from_typed_literal.GetType(), UnsignedInteger64);
  EXPECT_NE(uint64_from_typed_literal.GetType(), Boolean);
  EXPECT_FALSE(IsEmptyValue(uint64_from_typed_literal));
  EXPECT_FALSE(IsStructValue(uint64_from_typed_literal));
  EXPECT_FALSE(IsArrayValue(uint64_from_typed_literal));
  EXPECT_TRUE(IsScalarValue(uint64_from_typed_literal));
  EXPECT_EQ(uint64_from_typed_literal.GetTypeCode(), TypeCode::UInt64);
  EXPECT_EQ(uint64_from_typed_literal.GetTypeName(), UINT64_TYPE_NAME);
  EXPECT_THROW(uint64_from_typed_literal["field"], KeyNotAllowedException);
  EXPECT_EQ(uint64_from_typed_literal.As<uint64>(), 5);
  uint64_from_typed_literal = 0;
  EXPECT_EQ(uint64_from_typed_literal.As<boolean>(), false);
  EXPECT_EQ(uint64_from_typed_literal.As<uint64>(), 0);
  EXPECT_EQ(uint64_from_typed_literal.As<int32>(), 0);
}

TEST_F(AnyValueTest, Float32Value)
{
  AnyValue float32_value{Float32};
  EXPECT_EQ(float32_value.GetType(), Float32);
  EXPECT_NE(float32_value.GetType(), SignedInteger64);
  EXPECT_FALSE(IsEmptyValue(float32_value));
  EXPECT_FALSE(IsStructValue(float32_value));
  EXPECT_FALSE(IsArrayValue(float32_value));
  EXPECT_TRUE(IsScalarValue(float32_value));
  EXPECT_EQ(float32_value.GetTypeCode(), TypeCode::Float32);
  EXPECT_EQ(float32_value.GetTypeName(), FLOAT32_TYPE_NAME);
  EXPECT_THROW(float32_value["field"], KeyNotAllowedException);
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
  EXPECT_EQ(float32_value, new_val);

  const AnyValue copy = float32_value;
  EXPECT_TRUE(IsScalarValue(copy));
  EXPECT_EQ(copy, float32_value);
  EXPECT_FALSE(IsEmptyValue(copy));
  EXPECT_FALSE(IsStructValue(copy));
  EXPECT_FALSE(IsArrayValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Float32);
  EXPECT_EQ(copy.GetTypeName(), FLOAT32_TYPE_NAME);
  EXPECT_THROW(copy["field"], KeyNotAllowedException);
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
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Float32);
  EXPECT_EQ(moved.GetTypeName(), FLOAT32_TYPE_NAME);
  EXPECT_THROW(moved["field"], KeyNotAllowedException);
  EXPECT_EQ(moved.As<boolean>(), true);
  EXPECT_DOUBLE_EQ(moved.As<float32>(), new_val);

  float32 literal = -4.5;
  AnyValue float32_from_literal = literal;
  EXPECT_EQ(float32_from_literal.GetType(), Float32);
  EXPECT_NE(float32_from_literal.GetType(), SignedInteger64);
  EXPECT_FALSE(IsEmptyValue(float32_from_literal));
  EXPECT_FALSE(IsStructValue(float32_from_literal));
  EXPECT_FALSE(IsArrayValue(float32_from_literal));
  EXPECT_TRUE(IsScalarValue(float32_from_literal));
  EXPECT_EQ(float32_from_literal.GetTypeCode(), TypeCode::Float32);
  EXPECT_EQ(float32_from_literal.GetTypeName(), FLOAT32_TYPE_NAME);
  EXPECT_THROW(float32_from_literal["field"], KeyNotAllowedException);
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
  EXPECT_TRUE(IsScalarValue(float32_from_typed_literal));
  EXPECT_EQ(float32_from_typed_literal.GetTypeCode(), TypeCode::Float32);
  EXPECT_EQ(float32_from_typed_literal.GetTypeName(), FLOAT32_TYPE_NAME);
  EXPECT_THROW(float32_from_typed_literal["field"], KeyNotAllowedException);
  EXPECT_DOUBLE_EQ(float32_from_typed_literal.As<float32>(), 5.0);
  float32_from_typed_literal = 0;
  EXPECT_EQ(float32_from_typed_literal.As<boolean>(), false);
  EXPECT_DOUBLE_EQ(float32_from_typed_literal.As<float32>(), 0);
  EXPECT_EQ(float32_from_typed_literal.As<int32>(), 0);
}

TEST_F(AnyValueTest, Float64Value)
{
  AnyValue float64_value{Float64};
  EXPECT_EQ(float64_value.GetType(), Float64);
  EXPECT_NE(float64_value.GetType(), SignedInteger64);
  EXPECT_FALSE(IsEmptyValue(float64_value));
  EXPECT_FALSE(IsStructValue(float64_value));
  EXPECT_FALSE(IsArrayValue(float64_value));
  EXPECT_TRUE(IsScalarValue(float64_value));
  EXPECT_EQ(float64_value.GetTypeCode(), TypeCode::Float64);
  EXPECT_EQ(float64_value.GetTypeName(), FLOAT64_TYPE_NAME);
  EXPECT_THROW(float64_value["field"], KeyNotAllowedException);
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
  EXPECT_EQ(float64_value, new_val);

  const AnyValue copy = float64_value;
  EXPECT_TRUE(IsScalarValue(copy));
  EXPECT_EQ(copy, float64_value);
  EXPECT_FALSE(IsEmptyValue(copy));
  EXPECT_FALSE(IsStructValue(copy));
  EXPECT_FALSE(IsArrayValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Float64);
  EXPECT_EQ(copy.GetTypeName(), FLOAT64_TYPE_NAME);
  EXPECT_THROW(copy["field"], KeyNotAllowedException);
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
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Float64);
  EXPECT_EQ(moved.GetTypeName(), FLOAT64_TYPE_NAME);
  EXPECT_THROW(moved["field"], KeyNotAllowedException);
  EXPECT_EQ(moved.As<boolean>(), true);
  EXPECT_DOUBLE_EQ(moved.As<float64>(), new_val);

  float64 literal = -4.5;
  AnyValue float64_from_literal = literal;
  EXPECT_EQ(float64_from_literal.GetType(), Float64);
  EXPECT_NE(float64_from_literal.GetType(), SignedInteger64);
  EXPECT_FALSE(IsEmptyValue(float64_from_literal));
  EXPECT_FALSE(IsStructValue(float64_from_literal));
  EXPECT_FALSE(IsArrayValue(float64_from_literal));
  EXPECT_TRUE(IsScalarValue(float64_from_literal));
  EXPECT_EQ(float64_from_literal.GetTypeCode(), TypeCode::Float64);
  EXPECT_EQ(float64_from_literal.GetTypeName(), FLOAT64_TYPE_NAME);
  EXPECT_THROW(float64_from_literal["field"], KeyNotAllowedException);
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
  EXPECT_TRUE(IsScalarValue(float64_from_typed_literal));
  EXPECT_EQ(float64_from_typed_literal.GetTypeCode(), TypeCode::Float64);
  EXPECT_EQ(float64_from_typed_literal.GetTypeName(), FLOAT64_TYPE_NAME);
  EXPECT_THROW(float64_from_typed_literal["field"], KeyNotAllowedException);
  EXPECT_DOUBLE_EQ(float64_from_typed_literal.As<float64>(), 5.0);
  float64_from_typed_literal = 0;
  EXPECT_EQ(float64_from_typed_literal.As<boolean>(), false);
  EXPECT_DOUBLE_EQ(float64_from_typed_literal.As<float64>(), 0);
  EXPECT_EQ(float64_from_typed_literal.As<int32>(), 0);
}

TEST_F(AnyValueTest, CopyConstruction)
{
  const std::string nested_name = "nested_struct";
  AnyValue two_scalars = {{
    {"signed", {SignedInteger8, 1}},
    {"unsigned", {UnsignedInteger8, 12}}
  }};
  AnyValue nested_val{{
    {"scalars", two_scalars},
    {"single", {
      {"first", {SignedInteger8, 0}},
      {"second", {SignedInteger8, 5}}
    }}
  }, nested_name};
  EXPECT_TRUE(IsStructValue(nested_val));
  EXPECT_EQ(nested_val.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(nested_val.GetTypeName(), nested_name);

  AnyValue copy = nested_val;
  EXPECT_EQ(copy, nested_val);
  EXPECT_TRUE(IsStructValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(copy.GetTypeName(), nested_name);
  EXPECT_TRUE(copy.HasMember("scalars"));
  EXPECT_TRUE(copy.HasMember("single"));
  EXPECT_FALSE(copy.HasMember("index"));

  copy.AddMember("index", {UnsignedInteger64, 2022});
  EXPECT_NE(copy, nested_val);
  EXPECT_TRUE(IsStructValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(copy.GetTypeName(), nested_name);
  EXPECT_TRUE(copy.HasMember("scalars"));
  EXPECT_TRUE(copy.HasMember("single"));
  EXPECT_TRUE(copy.HasMember("index"));
}

TEST_F(AnyValueTest, CopyAssignment)
{
  const std::string nested_name = "nested_struct";
  AnyValue two_scalars = {{
    {"signed", {SignedInteger8, 1}},
    {"unsigned", {UnsignedInteger8, 12}}
  }};
  AnyValue nested_val = (EmptyStructValue(nested_name)
                            .AddMember("scalars", two_scalars)
                            .AddMember("single", EmptyStructValue()
                                .AddMember("first", {SignedInteger8, 0})
                                .AddMember("second", {SignedInteger8, 5})));
  EXPECT_TRUE(IsStructValue(nested_val));
  EXPECT_EQ(nested_val.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(nested_val.GetTypeName(), nested_name);

  AnyValue copy;
  copy = nested_val;
  EXPECT_EQ(copy, nested_val);
  EXPECT_TRUE(IsStructValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(copy.GetTypeName(), nested_name);
  EXPECT_TRUE(copy.HasMember("scalars"));
  EXPECT_TRUE(copy.HasMember("single"));
  EXPECT_FALSE(copy.HasMember("index"));

  copy.AddMember("index", {UnsignedInteger64, 2022});
  EXPECT_NE(copy, nested_val);
  EXPECT_TRUE(IsStructValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(copy.GetTypeName(), nested_name);
  EXPECT_TRUE(copy.HasMember("scalars"));
  EXPECT_TRUE(copy.HasMember("single"));
  EXPECT_TRUE(copy.HasMember("index"));

  AnyValue copy_again{copy.GetType()};
  copy_again = copy;
  EXPECT_EQ(copy_again, copy);
  EXPECT_TRUE(IsStructValue(copy_again));
  EXPECT_EQ(copy_again.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(copy_again.GetTypeName(), nested_name);
  EXPECT_TRUE(copy_again.HasMember("scalars"));
  EXPECT_TRUE(copy_again.HasMember("single"));
  EXPECT_TRUE(copy_again.HasMember("index"));
}

TEST_F(AnyValueTest, MoveConstruction)
{
  const std::string nested_name = "nested_struct";
  AnyValue two_scalars = {{
    {"signed", {SignedInteger8, 1}},
    {"unsigned", {UnsignedInteger8, 12}}
  }};
  AnyValue nested_val{{
    {"scalars", two_scalars},
    {"single", {
      {"first", {SignedInteger8, 0}},
      {"second", {SignedInteger8, 5}}
    }}
  }, nested_name};
  EXPECT_TRUE(IsStructValue(nested_val));
  EXPECT_EQ(nested_val.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(nested_val.GetTypeName(), nested_name);

  AnyValue moved = std::move(nested_val);
  EXPECT_NE(moved, nested_val);
  EXPECT_TRUE(IsStructValue(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(moved.GetTypeName(), nested_name);
  EXPECT_TRUE(moved.HasMember("scalars"));
  EXPECT_TRUE(moved.HasMember("single"));
  EXPECT_FALSE(moved.HasMember("index"));

  moved.AddMember("index", {UnsignedInteger64, 2022});
  EXPECT_NE(moved, nested_val);
  EXPECT_TRUE(IsStructValue(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(moved.GetTypeName(), nested_name);
  EXPECT_TRUE(moved.HasMember("scalars"));
  EXPECT_TRUE(moved.HasMember("single"));
  EXPECT_TRUE(moved.HasMember("index"));
}

TEST_F(AnyValueTest, MoveAssignment)
{
  const std::string nested_name = "nested_struct";
  AnyValue two_scalars = {{
    {"signed", {SignedInteger8, 1}},
    {"unsigned", {UnsignedInteger8, 12}}
  }};
  AnyValue nested_val = (EmptyStructValue(nested_name)
                            .AddMember("scalars", two_scalars)
                            .AddMember("single", EmptyStructValue()
                                .AddMember("first", {SignedInteger8, 0})
                                .AddMember("second", {SignedInteger8, 5})));
  EXPECT_TRUE(IsStructValue(nested_val));
  EXPECT_EQ(nested_val.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(nested_val.GetTypeName(), nested_name);

  AnyValue moved;
  moved = std::move(nested_val);
  EXPECT_NE(moved, nested_val);
  EXPECT_TRUE(IsStructValue(moved));
  EXPECT_TRUE(IsEmptyValue(nested_val));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(moved.GetTypeName(), nested_name);
  EXPECT_TRUE(moved.HasMember("scalars"));
  EXPECT_TRUE(moved.HasMember("single"));
  EXPECT_FALSE(moved.HasMember("index"));

  moved.AddMember("index", {UnsignedInteger64, 2022});
  EXPECT_NE(moved, nested_val);
  EXPECT_TRUE(IsStructValue(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(moved.GetTypeName(), nested_name);
  EXPECT_TRUE(moved.HasMember("scalars"));
  EXPECT_TRUE(moved.HasMember("single"));
  EXPECT_TRUE(moved.HasMember("index"));

  AnyValue moved_again{moved.GetType()};
  moved_again = std::move(moved);
  EXPECT_NE(moved_again, moved);
  EXPECT_TRUE(IsStructValue(moved_again));
  EXPECT_TRUE(IsEmptyValue(moved));
  EXPECT_EQ(moved_again.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(moved_again.GetTypeName(), nested_name);
  EXPECT_TRUE(moved_again.HasMember("scalars"));
  EXPECT_TRUE(moved_again.HasMember("single"));
  EXPECT_TRUE(moved_again.HasMember("index"));
}

TEST_F(AnyValueTest, MemberAccess)
{
  const std::string nested_name = "nested_struct";
  AnyValue two_scalars = {{
    {"signed", {SignedInteger8, 1}},
    {"unsigned", {UnsignedInteger8, 12}}
  }};
  AnyValue nested_val{{
    {"scalars", two_scalars},
    {"single", {
      {"first", {SignedInteger8, 0}},
      {"second", {SignedInteger8, 5}}
    }}
  }, nested_name};
  EXPECT_TRUE(IsStructValue(nested_val));
  EXPECT_EQ(nested_val.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(nested_val.GetTypeName(), nested_name);

  AnyType nested_type{{
    {"scalars", two_scalars.GetType()},
    {"single", {
      {"first", SignedInteger8},
      {"second", SignedInteger8}
    }}
  }, nested_name};
  EXPECT_EQ(nested_val.GetType(), nested_type);

  EXPECT_TRUE(nested_val.HasMember("scalars"));
  EXPECT_TRUE(nested_val.HasMember("single"));
  EXPECT_FALSE(nested_val.HasMember("index"));
  auto member_fields = nested_val.MemberNames();
  EXPECT_EQ(member_fields.size(), 2);
  EXPECT_EQ(member_fields[0], "scalars");
  EXPECT_EQ(member_fields[1], "single");
  nested_val.AddMember("index", {UnsignedInteger64, 2022});
  EXPECT_TRUE(nested_val.HasMember("index"));
  member_fields = nested_val.MemberNames();
  EXPECT_EQ(member_fields.size(), 3);
  EXPECT_EQ(member_fields[0], "scalars");
  EXPECT_EQ(member_fields[1], "single");
  EXPECT_EQ(member_fields[2], "index");

  // test presence of composite field indices
  EXPECT_TRUE(nested_val.HasMember("scalars.signed"));
  EXPECT_FALSE(nested_val.HasMember("scalars.unknown"));

  // test values of fields
  EXPECT_EQ(nested_val["scalars.signed"], 1);
  EXPECT_EQ(nested_val["scalars.unsigned"], 12);
  EXPECT_EQ(nested_val["single.first"], 0);
  EXPECT_EQ(nested_val["single.second"], 5);
  EXPECT_EQ(nested_val["index"], 2022);
}

TEST_F(AnyValueTest, CastToAnyValue)
{
  const std::string nested_name = "nested_struct";
  AnyValue two_scalars = {{
    {"signed", {SignedInteger8, 1}},
    {"unsigned", {UnsignedInteger8, 12}}
  }};
  AnyValue nested_val = (EmptyStructValue(nested_name)
                            .AddMember("scalars", two_scalars)
                            .AddMember("single", EmptyStructValue()
                                .AddMember("first", {SignedInteger8, 0})
                                .AddMember("second", {SignedInteger8, 5})));
  EXPECT_TRUE(IsStructValue(nested_val));
  EXPECT_EQ(nested_val.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(nested_val.GetTypeName(), nested_name);

  AnyValue copy = nested_val.As<AnyValue>();
  EXPECT_EQ(copy, nested_val);
  EXPECT_TRUE(IsStructValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(copy.GetTypeName(), nested_name);
  EXPECT_TRUE(copy.HasMember("scalars"));
  EXPECT_TRUE(copy.HasMember("single"));
  EXPECT_FALSE(copy.HasMember("index"));

  copy.AddMember("index", {UnsignedInteger64, 2022});
  EXPECT_NE(copy, nested_val);
  EXPECT_TRUE(IsStructValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(copy.GetTypeName(), nested_name);
  EXPECT_TRUE(copy.HasMember("scalars"));
  EXPECT_TRUE(copy.HasMember("single"));
  EXPECT_TRUE(copy.HasMember("index"));
}

AnyValueTest::AnyValueTest() = default;

AnyValueTest::~AnyValueTest() = default;
