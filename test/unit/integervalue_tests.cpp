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

#include <sup/dto/anyvalue.h>
#include <sup/dto/anyvalue_exceptions.h>

using namespace sup::dto;

TEST(IntegerValueTest, Character8Value)
{
  AnyValue char8_value{Character8Type};
  EXPECT_EQ(char8_value.GetType(), Character8Type);
  EXPECT_NE(char8_value.GetType(), UnsignedInteger8Type);
  EXPECT_FALSE(IsEmptyValue(char8_value));
  EXPECT_FALSE(IsStructValue(char8_value));
  EXPECT_FALSE(IsArrayValue(char8_value));
  EXPECT_TRUE(IsScalarValue(char8_value));
  EXPECT_EQ(char8_value.GetTypeCode(), TypeCode::Char8);
  EXPECT_EQ(char8_value.GetTypeName(), kChar8TypeName);
  EXPECT_THROW(char8_value["field"], InvalidOperationException);
  EXPECT_EQ(char8_value.As<boolean>(), false);
  EXPECT_EQ(char8_value.As<int8>(), 0);
  EXPECT_EQ(char8_value.As<uint8>(), 0);
  EXPECT_EQ(char8_value.As<int16>(), 0);
  EXPECT_EQ(char8_value.As<uint16>(), 0);
  EXPECT_EQ(char8_value.As<int32>(), 0);
  EXPECT_EQ(char8_value.As<uint32>(), 0);
  EXPECT_EQ(char8_value.As<int64>(), 0);
  EXPECT_EQ(char8_value.As<uint64>(), 0);
  EXPECT_EQ(char8_value.As<float32>(), 0.0);
  EXPECT_EQ(char8_value.As<float64>(), 0.0);
  int64 target_val;
  EXPECT_TRUE(char8_value.As(target_val));
  EXPECT_EQ(target_val, 0);
  EXPECT_THROW(char8_value.As<std::string>(), InvalidConversionException);
  std::string str_val;
  EXPECT_FALSE(char8_value.As(str_val));
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
  EXPECT_EQ(char8_value.As<float32>(), float(init_val));
  EXPECT_EQ(char8_value.As<float64>(), double(init_val));
  EXPECT_TRUE(char8_value.As(target_val));
  EXPECT_EQ(target_val, init_val);
  EXPECT_THROW(char8_value.As<std::string>(), InvalidConversionException);
  EXPECT_FALSE(char8_value.As(str_val));
  EXPECT_EQ(char8_value, init_val);

  const AnyValue copy = char8_value;
  EXPECT_TRUE(IsScalarValue(copy));
  EXPECT_EQ(copy, char8_value);
  EXPECT_FALSE(IsEmptyValue(copy));
  EXPECT_FALSE(IsStructValue(copy));
  EXPECT_FALSE(IsArrayValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Char8);
  EXPECT_EQ(copy.GetTypeName(), kChar8TypeName);
  EXPECT_THROW(copy["field"], InvalidOperationException);
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
  EXPECT_EQ(moved.GetTypeName(), kChar8TypeName);
  EXPECT_THROW(moved["field"], InvalidOperationException);
  EXPECT_EQ(moved.As<boolean>(), true);
  EXPECT_EQ(moved.As<char8>(), init_val);

  char8 literal = 'L';
  AnyValue char8_from_literal = literal;
  EXPECT_EQ(char8_from_literal.GetType(), Character8Type);
  EXPECT_NE(char8_from_literal.GetType(), SignedInteger32Type);
  EXPECT_FALSE(IsEmptyValue(char8_from_literal));
  EXPECT_FALSE(IsStructValue(char8_from_literal));
  EXPECT_FALSE(IsArrayValue(char8_from_literal));
  EXPECT_TRUE(IsScalarValue(char8_from_literal));
  EXPECT_EQ(char8_from_literal.GetTypeCode(), TypeCode::Char8);
  EXPECT_EQ(char8_from_literal.GetTypeName(), kChar8TypeName);
  EXPECT_THROW(char8_from_literal["field"], InvalidOperationException);
  EXPECT_EQ(char8_from_literal.As<char8>(), literal);
  char8_from_literal = 'M';
  EXPECT_EQ(char8_from_literal.As<boolean>(), true);
  EXPECT_EQ(char8_from_literal.As<char8>(), 'M');
  EXPECT_EQ(char8_from_literal.As<int32>(), 'M');

  AnyValue char8_from_typed_literal = {Character8Type, 5};
  EXPECT_EQ(char8_from_typed_literal.GetType(), Character8Type);
  EXPECT_NE(char8_from_typed_literal.GetType(), BooleanType);
  EXPECT_FALSE(IsEmptyValue(char8_from_typed_literal));
  EXPECT_FALSE(IsStructValue(char8_from_typed_literal));
  EXPECT_FALSE(IsArrayValue(char8_from_typed_literal));
  EXPECT_TRUE(IsScalarValue(char8_from_typed_literal));
  EXPECT_EQ(char8_from_typed_literal.GetTypeCode(), TypeCode::Char8);
  EXPECT_EQ(char8_from_typed_literal.GetTypeName(), kChar8TypeName);
  EXPECT_THROW(char8_from_typed_literal["field"], InvalidOperationException);
  EXPECT_EQ(char8_from_typed_literal.As<int8>(), 5);
  char8_from_typed_literal = 0;
  EXPECT_EQ(char8_from_typed_literal.As<boolean>(), false);
  EXPECT_EQ(char8_from_typed_literal.As<int8>(), 0);
  EXPECT_EQ(char8_from_typed_literal.As<int32>(), 0);
}

TEST(IntegerValueTest, SignedInteger8Value)
{
  AnyValue int8_value{SignedInteger8Type};
  EXPECT_EQ(int8_value.GetType(), SignedInteger8Type);
  EXPECT_NE(int8_value.GetType(), UnsignedInteger8Type);
  EXPECT_FALSE(IsEmptyValue(int8_value));
  EXPECT_FALSE(IsStructValue(int8_value));
  EXPECT_FALSE(IsArrayValue(int8_value));
  EXPECT_TRUE(IsScalarValue(int8_value));
  EXPECT_EQ(int8_value.GetTypeCode(), TypeCode::Int8);
  EXPECT_EQ(int8_value.GetTypeName(), kInt8TypeName);
  EXPECT_THROW(int8_value["field"], InvalidOperationException);
  EXPECT_EQ(int8_value.As<boolean>(), false);
  EXPECT_EQ(int8_value.As<int8>(), 0);
  EXPECT_EQ(int8_value.As<uint8>(), 0);
  EXPECT_EQ(int8_value.As<int16>(), 0);
  EXPECT_EQ(int8_value.As<uint16>(), 0);
  EXPECT_EQ(int8_value.As<int32>(), 0);
  EXPECT_EQ(int8_value.As<uint32>(), 0);
  EXPECT_EQ(int8_value.As<int64>(), 0);
  EXPECT_EQ(int8_value.As<uint64>(), 0);
  EXPECT_EQ(int8_value.As<float32>(), 0.0);
  EXPECT_EQ(int8_value.As<float64>(), 0.0);
  int64 target_val;
  EXPECT_TRUE(int8_value.As(target_val));
  EXPECT_EQ(target_val, 0);
  EXPECT_THROW(int8_value.As<std::string>(), InvalidConversionException);
  std::string str_val;
  EXPECT_FALSE(int8_value.As(str_val));
  EXPECT_NO_THROW(int8_value.ConvertFrom(25));
  EXPECT_EQ(int8_value.As<boolean>(), true);
  EXPECT_EQ(int8_value.As<int8>(), 25);
  EXPECT_EQ(int8_value.As<uint8>(), 25);
  EXPECT_EQ(int8_value.As<int16>(), 25);
  EXPECT_EQ(int8_value.As<uint16>(), 25);
  EXPECT_EQ(int8_value.As<int32>(), 25);
  EXPECT_EQ(int8_value.As<uint32>(), 25);
  EXPECT_EQ(int8_value.As<int64>(), 25);
  EXPECT_EQ(int8_value.As<uint64>(), 25);
  EXPECT_EQ(int8_value.As<float32>(), 25.0);
  EXPECT_EQ(int8_value.As<float64>(), 25.0);
  EXPECT_TRUE(int8_value.As(target_val));
  EXPECT_EQ(target_val, 25);
  EXPECT_THROW(int8_value.As<std::string>(), InvalidConversionException);
  EXPECT_FALSE(int8_value.As(str_val));
  EXPECT_EQ(int8_value, 25);

  const AnyValue copy = int8_value;
  EXPECT_TRUE(IsScalarValue(copy));
  EXPECT_EQ(copy, int8_value);
  EXPECT_FALSE(IsEmptyValue(copy));
  EXPECT_FALSE(IsStructValue(copy));
  EXPECT_FALSE(IsArrayValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Int8);
  EXPECT_EQ(copy.GetTypeName(), kInt8TypeName);
  EXPECT_THROW(copy["field"], InvalidOperationException);
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
  EXPECT_EQ(moved.GetTypeName(), kInt8TypeName);
  EXPECT_THROW(moved["field"], InvalidOperationException);
  EXPECT_EQ(moved.As<boolean>(), true);
  EXPECT_EQ(moved.As<int32>(), 25);

  int8 literal = 74;
  AnyValue int8_from_literal = literal;
  EXPECT_EQ(int8_from_literal.GetType(), SignedInteger8Type);
  EXPECT_NE(int8_from_literal.GetType(), SignedInteger32Type);
  EXPECT_FALSE(IsEmptyValue(int8_from_literal));
  EXPECT_FALSE(IsStructValue(int8_from_literal));
  EXPECT_FALSE(IsArrayValue(int8_from_literal));
  EXPECT_TRUE(IsScalarValue(int8_from_literal));
  EXPECT_EQ(int8_from_literal.GetTypeCode(), TypeCode::Int8);
  EXPECT_EQ(int8_from_literal.GetTypeName(), kInt8TypeName);
  EXPECT_THROW(int8_from_literal["field"], InvalidOperationException);
  EXPECT_EQ(int8_from_literal.As<int8>(), literal);
  int8_from_literal = -18;
  EXPECT_EQ(int8_from_literal.As<boolean>(), true);
  EXPECT_EQ(int8_from_literal.As<int8>(), -18);
  EXPECT_EQ(int8_from_literal.As<int32>(), -18);

  AnyValue int8_from_typed_literal = {SignedInteger8Type, 5};
  EXPECT_EQ(int8_from_typed_literal.GetType(), SignedInteger8Type);
  EXPECT_NE(int8_from_typed_literal.GetType(), BooleanType);
  EXPECT_FALSE(IsEmptyValue(int8_from_typed_literal));
  EXPECT_FALSE(IsStructValue(int8_from_typed_literal));
  EXPECT_FALSE(IsArrayValue(int8_from_typed_literal));
  EXPECT_TRUE(IsScalarValue(int8_from_typed_literal));
  EXPECT_EQ(int8_from_typed_literal.GetTypeCode(), TypeCode::Int8);
  EXPECT_EQ(int8_from_typed_literal.GetTypeName(), kInt8TypeName);
  EXPECT_THROW(int8_from_typed_literal["field"], InvalidOperationException);
  EXPECT_EQ(int8_from_typed_literal.As<int8>(), 5);
  int8_from_typed_literal = 0;
  EXPECT_EQ(int8_from_typed_literal.As<boolean>(), false);
  EXPECT_EQ(int8_from_typed_literal.As<int8>(), 0);
  EXPECT_EQ(int8_from_typed_literal.As<int32>(), 0);
}

TEST(IntegerValueTest, UnsignedInteger8Value)
{
  AnyValue uint8_value{UnsignedInteger8Type};
  EXPECT_EQ(uint8_value.GetType(), UnsignedInteger8Type);
  EXPECT_NE(uint8_value.GetType(), SignedInteger32Type);
  EXPECT_FALSE(IsEmptyValue(uint8_value));
  EXPECT_FALSE(IsStructValue(uint8_value));
  EXPECT_FALSE(IsArrayValue(uint8_value));
  EXPECT_TRUE(IsScalarValue(uint8_value));
  EXPECT_EQ(uint8_value.GetTypeCode(), TypeCode::UInt8);
  EXPECT_EQ(uint8_value.GetTypeName(), kUInt8TypeName);
  EXPECT_THROW(uint8_value["field"], InvalidOperationException);
  EXPECT_EQ(uint8_value.As<boolean>(), false);
  EXPECT_EQ(uint8_value.As<int8>(), 0);
  EXPECT_EQ(uint8_value.As<uint8>(), 0);
  EXPECT_EQ(uint8_value.As<int16>(), 0);
  EXPECT_EQ(uint8_value.As<uint16>(), 0);
  EXPECT_EQ(uint8_value.As<int32>(), 0);
  EXPECT_EQ(uint8_value.As<uint32>(), 0);
  EXPECT_EQ(uint8_value.As<int64>(), 0);
  EXPECT_EQ(uint8_value.As<uint64>(), 0);
  EXPECT_EQ(uint8_value.As<float32>(), 0.0);
  EXPECT_EQ(uint8_value.As<float64>(), 0.0);
  int64 target_val;
  EXPECT_TRUE(uint8_value.As(target_val));
  EXPECT_EQ(target_val, 0);
  EXPECT_THROW(uint8_value.As<std::string>(), InvalidConversionException);
  std::string str_val;
  EXPECT_FALSE(uint8_value.As(str_val));
  EXPECT_NO_THROW(uint8_value.ConvertFrom(25));
  EXPECT_EQ(uint8_value.As<boolean>(), true);
  EXPECT_EQ(uint8_value.As<int8>(), 25);
  EXPECT_EQ(uint8_value.As<uint8>(), 25);
  EXPECT_EQ(uint8_value.As<int16>(), 25);
  EXPECT_EQ(uint8_value.As<uint16>(), 25);
  EXPECT_EQ(uint8_value.As<int32>(), 25);
  EXPECT_EQ(uint8_value.As<uint32>(), 25);
  EXPECT_EQ(uint8_value.As<int64>(), 25);
  EXPECT_EQ(uint8_value.As<uint64>(), 25);
  EXPECT_EQ(uint8_value.As<float32>(), 25.0);
  EXPECT_EQ(uint8_value.As<float64>(), 25.0);
  EXPECT_TRUE(uint8_value.As(target_val));
  EXPECT_EQ(target_val, 25);
  EXPECT_THROW(uint8_value.As<std::string>(), InvalidConversionException);
  EXPECT_FALSE(uint8_value.As(str_val));
  EXPECT_EQ(uint8_value, 25);

  const AnyValue copy = uint8_value;
  EXPECT_TRUE(IsScalarValue(copy));
  EXPECT_EQ(copy, uint8_value);
  EXPECT_FALSE(IsEmptyValue(copy));
  EXPECT_FALSE(IsStructValue(copy));
  EXPECT_FALSE(IsArrayValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::UInt8);
  EXPECT_EQ(copy.GetTypeName(), kUInt8TypeName);
  EXPECT_THROW(copy["field"], InvalidOperationException);
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
  EXPECT_EQ(moved.GetTypeName(), kUInt8TypeName);
  EXPECT_THROW(moved["field"], InvalidOperationException);
  EXPECT_EQ(moved.As<boolean>(), true);
  EXPECT_EQ(moved.As<int32>(), 25);

  uint8 literal = 74;
  AnyValue uint8_from_literal = literal;
  EXPECT_EQ(uint8_from_literal.GetType(), UnsignedInteger8Type);
  EXPECT_NE(uint8_from_literal.GetType(), SignedInteger32Type);
  EXPECT_FALSE(IsEmptyValue(uint8_from_literal));
  EXPECT_FALSE(IsStructValue(uint8_from_literal));
  EXPECT_FALSE(IsArrayValue(uint8_from_literal));
  EXPECT_TRUE(IsScalarValue(uint8_from_literal));
  EXPECT_EQ(uint8_from_literal.GetTypeCode(), TypeCode::UInt8);
  EXPECT_EQ(uint8_from_literal.GetTypeName(), kUInt8TypeName);
  EXPECT_THROW(uint8_from_literal["field"], InvalidOperationException);
  EXPECT_EQ(uint8_from_literal.As<uint8>(), literal);
  uint8_from_literal = 18;
  EXPECT_EQ(uint8_from_literal.As<boolean>(), true);
  EXPECT_EQ(uint8_from_literal.As<uint8>(), 18);
  EXPECT_EQ(uint8_from_literal.As<int32>(), 18);

  AnyValue uint8_from_typed_literal = {UnsignedInteger8Type, 5};
  EXPECT_EQ(uint8_from_typed_literal.GetType(), UnsignedInteger8Type);
  EXPECT_NE(uint8_from_typed_literal.GetType(), BooleanType);
  EXPECT_FALSE(IsEmptyValue(uint8_from_typed_literal));
  EXPECT_FALSE(IsStructValue(uint8_from_typed_literal));
  EXPECT_FALSE(IsArrayValue(uint8_from_typed_literal));
  EXPECT_TRUE(IsScalarValue(uint8_from_typed_literal));
  EXPECT_EQ(uint8_from_typed_literal.GetTypeCode(), TypeCode::UInt8);
  EXPECT_EQ(uint8_from_typed_literal.GetTypeName(), kUInt8TypeName);
  EXPECT_THROW(uint8_from_typed_literal["field"], InvalidOperationException);
  EXPECT_EQ(uint8_from_typed_literal.As<uint8>(), 5);
  uint8_from_typed_literal = 0;
  EXPECT_EQ(uint8_from_typed_literal.As<boolean>(), false);
  EXPECT_EQ(uint8_from_typed_literal.As<uint8>(), 0);
  EXPECT_EQ(uint8_from_typed_literal.As<int32>(), 0);
}

TEST(IntegerValueTest, SignedInteger16Value)
{
  AnyValue int16_value{SignedInteger16Type};
  EXPECT_EQ(int16_value.GetType(), SignedInteger16Type);
  EXPECT_NE(int16_value.GetType(), UnsignedInteger16Type);
  EXPECT_FALSE(IsEmptyValue(int16_value));
  EXPECT_FALSE(IsStructValue(int16_value));
  EXPECT_FALSE(IsArrayValue(int16_value));
  EXPECT_TRUE(IsScalarValue(int16_value));
  EXPECT_EQ(int16_value.GetTypeCode(), TypeCode::Int16);
  EXPECT_EQ(int16_value.GetTypeName(), kInt16TypeName);
  EXPECT_THROW(int16_value["field"], InvalidOperationException);
  EXPECT_EQ(int16_value.As<boolean>(), false);
  EXPECT_EQ(int16_value.As<int8>(), 0);
  EXPECT_EQ(int16_value.As<uint8>(), 0);
  EXPECT_EQ(int16_value.As<int16>(), 0);
  EXPECT_EQ(int16_value.As<uint16>(), 0);
  EXPECT_EQ(int16_value.As<int32>(), 0);
  EXPECT_EQ(int16_value.As<uint32>(), 0);
  EXPECT_EQ(int16_value.As<int64>(), 0);
  EXPECT_EQ(int16_value.As<uint64>(), 0);
  EXPECT_EQ(int16_value.As<float32>(), 0.0);
  EXPECT_EQ(int16_value.As<float64>(), 0.0);
  int64 target_val;
  EXPECT_TRUE(int16_value.As(target_val));
  EXPECT_EQ(target_val, 0);
  EXPECT_THROW(int16_value.As<std::string>(), InvalidConversionException);
  std::string str_val;
  EXPECT_FALSE(int16_value.As(str_val));
  auto new_val = 25;
  EXPECT_NO_THROW(int16_value.ConvertFrom(new_val));
  EXPECT_EQ(int16_value.As<boolean>(), true);
  EXPECT_EQ(int16_value.As<int8>(), new_val);
  EXPECT_EQ(int16_value.As<uint8>(), new_val);
  EXPECT_EQ(int16_value.As<int16>(), new_val);
  EXPECT_EQ(int16_value.As<uint16>(), new_val);
  EXPECT_EQ(int16_value.As<int32>(), new_val);
  EXPECT_EQ(int16_value.As<uint32>(), new_val);
  EXPECT_EQ(int16_value.As<int64>(), new_val);
  EXPECT_EQ(int16_value.As<uint64>(), new_val);
  EXPECT_EQ(int16_value.As<float32>(), new_val);
  EXPECT_EQ(int16_value.As<float64>(), new_val);
  EXPECT_TRUE(int16_value.As(target_val));
  EXPECT_EQ(target_val, new_val);
  EXPECT_THROW(int16_value.As<std::string>(), InvalidConversionException);
  EXPECT_FALSE(int16_value.As(str_val));
  EXPECT_EQ(int16_value, 25);

  const AnyValue copy = int16_value;
  EXPECT_TRUE(IsScalarValue(copy));
  EXPECT_EQ(copy, int16_value);
  EXPECT_FALSE(IsEmptyValue(copy));
  EXPECT_FALSE(IsStructValue(copy));
  EXPECT_FALSE(IsArrayValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Int16);
  EXPECT_EQ(copy.GetTypeName(), kInt16TypeName);
  EXPECT_THROW(copy["field"], InvalidOperationException);
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
  EXPECT_EQ(moved.GetTypeName(), kInt16TypeName);
  EXPECT_THROW(moved["field"], InvalidOperationException);
  EXPECT_EQ(moved.As<boolean>(), true);
  EXPECT_EQ(moved.As<int32>(), 25);

  int16 literal = 74;
  AnyValue int16_from_literal = literal;
  EXPECT_EQ(int16_from_literal.GetType(), SignedInteger16Type);
  EXPECT_NE(int16_from_literal.GetType(), SignedInteger32Type);
  EXPECT_FALSE(IsEmptyValue(int16_from_literal));
  EXPECT_FALSE(IsStructValue(int16_from_literal));
  EXPECT_FALSE(IsArrayValue(int16_from_literal));
  EXPECT_TRUE(IsScalarValue(int16_from_literal));
  EXPECT_EQ(int16_from_literal.GetTypeCode(), TypeCode::Int16);
  EXPECT_EQ(int16_from_literal.GetTypeName(), kInt16TypeName);
  EXPECT_THROW(int16_from_literal["field"], InvalidOperationException);
  EXPECT_EQ(int16_from_literal.As<int16>(), literal);
  int16_from_literal = -18;
  EXPECT_EQ(int16_from_literal.As<boolean>(), true);
  EXPECT_EQ(int16_from_literal.As<int16>(), -18);
  EXPECT_EQ(int16_from_literal.As<int32>(), -18);

  AnyValue int16_from_typed_literal = {SignedInteger16Type, 5};
  EXPECT_EQ(int16_from_typed_literal.GetType(), SignedInteger16Type);
  EXPECT_NE(int16_from_typed_literal.GetType(), BooleanType);
  EXPECT_FALSE(IsEmptyValue(int16_from_typed_literal));
  EXPECT_FALSE(IsStructValue(int16_from_typed_literal));
  EXPECT_FALSE(IsArrayValue(int16_from_typed_literal));
  EXPECT_TRUE(IsScalarValue(int16_from_typed_literal));
  EXPECT_EQ(int16_from_typed_literal.GetTypeCode(), TypeCode::Int16);
  EXPECT_EQ(int16_from_typed_literal.GetTypeName(), kInt16TypeName);
  EXPECT_THROW(int16_from_typed_literal["field"], InvalidOperationException);
  EXPECT_EQ(int16_from_typed_literal.As<int16>(), 5);
  int16_from_typed_literal = 0;
  EXPECT_EQ(int16_from_typed_literal.As<boolean>(), false);
  EXPECT_EQ(int16_from_typed_literal.As<int16>(), 0);
  EXPECT_EQ(int16_from_typed_literal.As<int32>(), 0);
}

TEST(IntegerValueTest, UnsignedInteger16Value)
{
  AnyValue uint16_value{UnsignedInteger16Type};
  EXPECT_EQ(uint16_value.GetType(), UnsignedInteger16Type);
  EXPECT_NE(uint16_value.GetType(), SignedInteger32Type);
  EXPECT_FALSE(IsEmptyValue(uint16_value));
  EXPECT_FALSE(IsStructValue(uint16_value));
  EXPECT_FALSE(IsArrayValue(uint16_value));
  EXPECT_TRUE(IsScalarValue(uint16_value));
  EXPECT_EQ(uint16_value.GetTypeCode(), TypeCode::UInt16);
  EXPECT_EQ(uint16_value.GetTypeName(), kUInt16TypeName);
  EXPECT_THROW(uint16_value["field"], InvalidOperationException);
  EXPECT_EQ(uint16_value.As<boolean>(), false);
  EXPECT_EQ(uint16_value.As<int8>(), 0);
  EXPECT_EQ(uint16_value.As<uint8>(), 0);
  EXPECT_EQ(uint16_value.As<int16>(), 0);
  EXPECT_EQ(uint16_value.As<uint16>(), 0);
  EXPECT_EQ(uint16_value.As<int32>(), 0);
  EXPECT_EQ(uint16_value.As<uint32>(), 0);
  EXPECT_EQ(uint16_value.As<int64>(), 0);
  EXPECT_EQ(uint16_value.As<uint64>(), 0);
  EXPECT_EQ(uint16_value.As<float32>(), 0.0);
  EXPECT_EQ(uint16_value.As<float64>(), 0.0);
  int64 target_val;
  EXPECT_TRUE(uint16_value.As(target_val));
  EXPECT_EQ(target_val, 0);
  EXPECT_THROW(uint16_value.As<std::string>(), InvalidConversionException);
  std::string str_val;
  EXPECT_FALSE(uint16_value.As(str_val));
  auto new_val = 25;
  EXPECT_NO_THROW(uint16_value.ConvertFrom(new_val));
  EXPECT_EQ(uint16_value.As<boolean>(), true);
  EXPECT_EQ(uint16_value.As<int8>(), new_val);
  EXPECT_EQ(uint16_value.As<uint8>(), new_val);
  EXPECT_EQ(uint16_value.As<int16>(), new_val);
  EXPECT_EQ(uint16_value.As<uint16>(), new_val);
  EXPECT_EQ(uint16_value.As<int32>(), new_val);
  EXPECT_EQ(uint16_value.As<uint32>(), new_val);
  EXPECT_EQ(uint16_value.As<int64>(), new_val);
  EXPECT_EQ(uint16_value.As<uint64>(), new_val);
  EXPECT_EQ(uint16_value.As<float32>(), new_val);
  EXPECT_EQ(uint16_value.As<float64>(), new_val);
  EXPECT_TRUE(uint16_value.As(target_val));
  EXPECT_EQ(target_val, new_val);
  EXPECT_THROW(uint16_value.As<std::string>(), InvalidConversionException);
  EXPECT_FALSE(uint16_value.As(str_val));
  EXPECT_EQ(uint16_value, new_val);

  const AnyValue copy = uint16_value;
  EXPECT_TRUE(IsScalarValue(copy));
  EXPECT_EQ(copy, uint16_value);
  EXPECT_FALSE(IsEmptyValue(copy));
  EXPECT_FALSE(IsStructValue(copy));
  EXPECT_FALSE(IsArrayValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::UInt16);
  EXPECT_EQ(copy.GetTypeName(), kUInt16TypeName);
  EXPECT_THROW(copy["field"], InvalidOperationException);
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
  EXPECT_EQ(moved.GetTypeName(), kUInt16TypeName);
  EXPECT_THROW(moved["field"], InvalidOperationException);
  EXPECT_EQ(moved.As<boolean>(), true);
  EXPECT_EQ(moved.As<int32>(), new_val);

  uint16 literal = 74;
  AnyValue uint16_from_literal = literal;
  EXPECT_EQ(uint16_from_literal.GetType(), UnsignedInteger16Type);
  EXPECT_NE(uint16_from_literal.GetType(), SignedInteger32Type);
  EXPECT_FALSE(IsEmptyValue(uint16_from_literal));
  EXPECT_FALSE(IsStructValue(uint16_from_literal));
  EXPECT_FALSE(IsArrayValue(uint16_from_literal));
  EXPECT_TRUE(IsScalarValue(uint16_from_literal));
  EXPECT_EQ(uint16_from_literal.GetTypeCode(), TypeCode::UInt16);
  EXPECT_EQ(uint16_from_literal.GetTypeName(), kUInt16TypeName);
  EXPECT_THROW(uint16_from_literal["field"], InvalidOperationException);
  EXPECT_EQ(uint16_from_literal.As<uint16>(), literal);
  uint16_from_literal = 116;
  EXPECT_EQ(uint16_from_literal.As<boolean>(), true);
  EXPECT_EQ(uint16_from_literal.As<uint16>(), 116);
  EXPECT_EQ(uint16_from_literal.As<int32>(), 116);

  AnyValue uint16_from_typed_literal = {UnsignedInteger16Type, 5};
  EXPECT_EQ(uint16_from_typed_literal.GetType(), UnsignedInteger16Type);
  EXPECT_NE(uint16_from_typed_literal.GetType(), BooleanType);
  EXPECT_FALSE(IsEmptyValue(uint16_from_typed_literal));
  EXPECT_FALSE(IsStructValue(uint16_from_typed_literal));
  EXPECT_FALSE(IsArrayValue(uint16_from_typed_literal));
  EXPECT_TRUE(IsScalarValue(uint16_from_typed_literal));
  EXPECT_EQ(uint16_from_typed_literal.GetTypeCode(), TypeCode::UInt16);
  EXPECT_EQ(uint16_from_typed_literal.GetTypeName(), kUInt16TypeName);
  EXPECT_THROW(uint16_from_typed_literal["field"], InvalidOperationException);
  EXPECT_EQ(uint16_from_typed_literal.As<uint16>(), 5);
  uint16_from_typed_literal = 0;
  EXPECT_EQ(uint16_from_typed_literal.As<boolean>(), false);
  EXPECT_EQ(uint16_from_typed_literal.As<uint16>(), 0);
  EXPECT_EQ(uint16_from_typed_literal.As<int32>(), 0);
}

TEST(IntegerValueTest, SignedInteger32Value)
{
  AnyValue int32_value{SignedInteger32Type};
  EXPECT_EQ(int32_value.GetType(), SignedInteger32Type);
  EXPECT_NE(int32_value.GetType(), UnsignedInteger32Type);
  EXPECT_FALSE(IsEmptyValue(int32_value));
  EXPECT_FALSE(IsStructValue(int32_value));
  EXPECT_FALSE(IsArrayValue(int32_value));
  EXPECT_TRUE(IsScalarValue(int32_value));
  EXPECT_EQ(int32_value.GetTypeCode(), TypeCode::Int32);
  EXPECT_EQ(int32_value.GetTypeName(), kInt32TypeName);
  EXPECT_THROW(int32_value["field"], InvalidOperationException);
  EXPECT_EQ(int32_value.As<boolean>(), false);
  EXPECT_EQ(int32_value.As<int8>(), 0);
  EXPECT_EQ(int32_value.As<uint8>(), 0);
  EXPECT_EQ(int32_value.As<int16>(), 0);
  EXPECT_EQ(int32_value.As<uint16>(), 0);
  EXPECT_EQ(int32_value.As<int32>(), 0);
  EXPECT_EQ(int32_value.As<uint32>(), 0);
  EXPECT_EQ(int32_value.As<int64>(), 0);
  EXPECT_EQ(int32_value.As<uint64>(), 0);
  EXPECT_EQ(int32_value.As<float32>(), 0.0);
  EXPECT_EQ(int32_value.As<float64>(), 0.0);
  int64 target_val;
  EXPECT_TRUE(int32_value.As(target_val));
  EXPECT_EQ(target_val, 0);
  EXPECT_THROW(int32_value.As<std::string>(), InvalidConversionException);
  std::string str_val;
  EXPECT_FALSE(int32_value.As(str_val));
  auto new_val = 25;
  EXPECT_NO_THROW(int32_value.ConvertFrom(new_val));
  EXPECT_EQ(int32_value.As<boolean>(), true);
  EXPECT_EQ(int32_value.As<int8>(), new_val);
  EXPECT_EQ(int32_value.As<uint8>(), new_val);
  EXPECT_EQ(int32_value.As<int16>(), new_val);
  EXPECT_EQ(int32_value.As<uint16>(), new_val);
  EXPECT_EQ(int32_value.As<int32>(), new_val);
  EXPECT_EQ(int32_value.As<uint32>(), new_val);
  EXPECT_EQ(int32_value.As<int64>(), new_val);
  EXPECT_EQ(int32_value.As<uint64>(), new_val);
  EXPECT_EQ(int32_value.As<float32>(), new_val);
  EXPECT_EQ(int32_value.As<float64>(), new_val);
  EXPECT_TRUE(int32_value.As(target_val));
  EXPECT_EQ(target_val, new_val);
  EXPECT_THROW(int32_value.As<std::string>(), InvalidConversionException);
  EXPECT_FALSE(int32_value.As(str_val));
  EXPECT_EQ(int32_value, new_val);

  const AnyValue copy = int32_value;
  EXPECT_TRUE(IsScalarValue(copy));
  EXPECT_EQ(copy, int32_value);
  EXPECT_FALSE(IsEmptyValue(copy));
  EXPECT_FALSE(IsStructValue(copy));
  EXPECT_FALSE(IsArrayValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Int32);
  EXPECT_EQ(copy.GetTypeName(), kInt32TypeName);
  EXPECT_THROW(copy["field"], InvalidOperationException);
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
  EXPECT_EQ(moved.GetTypeName(), kInt32TypeName);
  EXPECT_THROW(moved["field"], InvalidOperationException);
  EXPECT_EQ(moved.As<boolean>(), true);
  EXPECT_EQ(moved.As<int32>(), 25);

  int32 literal = 74;
  AnyValue int32_from_literal = literal;
  EXPECT_EQ(int32_from_literal.GetType(), SignedInteger32Type);
  EXPECT_NE(int32_from_literal.GetType(), SignedInteger16Type);
  EXPECT_FALSE(IsEmptyValue(int32_from_literal));
  EXPECT_FALSE(IsStructValue(int32_from_literal));
  EXPECT_FALSE(IsArrayValue(int32_from_literal));
  EXPECT_TRUE(IsScalarValue(int32_from_literal));
  EXPECT_EQ(int32_from_literal.GetTypeCode(), TypeCode::Int32);
  EXPECT_EQ(int32_from_literal.GetTypeName(), kInt32TypeName);
  EXPECT_THROW(int32_from_literal["field"], InvalidOperationException);
  EXPECT_EQ(int32_from_literal.As<int32>(), literal);
  int32_from_literal = -18;
  EXPECT_EQ(int32_from_literal.As<boolean>(), true);
  EXPECT_EQ(int32_from_literal.As<int32>(), -18);
  EXPECT_EQ(int32_from_literal.As<int16>(), -18);

  AnyValue int32_from_typed_literal = {SignedInteger32Type, 5};
  EXPECT_EQ(int32_from_typed_literal.GetType(), SignedInteger32Type);
  EXPECT_NE(int32_from_typed_literal.GetType(), BooleanType);
  EXPECT_FALSE(IsEmptyValue(int32_from_typed_literal));
  EXPECT_FALSE(IsStructValue(int32_from_typed_literal));
  EXPECT_FALSE(IsArrayValue(int32_from_typed_literal));
  EXPECT_TRUE(IsScalarValue(int32_from_typed_literal));
  EXPECT_EQ(int32_from_typed_literal.GetTypeCode(), TypeCode::Int32);
  EXPECT_EQ(int32_from_typed_literal.GetTypeName(), kInt32TypeName);
  EXPECT_THROW(int32_from_typed_literal["field"], InvalidOperationException);
  EXPECT_EQ(int32_from_typed_literal.As<int32>(), 5);
  int32_from_typed_literal = 0;
  EXPECT_EQ(int32_from_typed_literal.As<boolean>(), false);
  EXPECT_EQ(int32_from_typed_literal.As<int16>(), 0);
  EXPECT_EQ(int32_from_typed_literal.As<int32>(), 0);
}

TEST(IntegerValueTest, UnsignedInteger32Value)
{
  AnyValue uint32_value{UnsignedInteger32Type};
  EXPECT_EQ(uint32_value.GetType(), UnsignedInteger32Type);
  EXPECT_NE(uint32_value.GetType(), SignedInteger32Type);
  EXPECT_FALSE(IsEmptyValue(uint32_value));
  EXPECT_FALSE(IsStructValue(uint32_value));
  EXPECT_FALSE(IsArrayValue(uint32_value));
  EXPECT_TRUE(IsScalarValue(uint32_value));
  EXPECT_EQ(uint32_value.GetTypeCode(), TypeCode::UInt32);
  EXPECT_EQ(uint32_value.GetTypeName(), kUInt32TypeName);
  EXPECT_THROW(uint32_value["field"], InvalidOperationException);
  EXPECT_EQ(uint32_value.As<boolean>(), false);
  EXPECT_EQ(uint32_value.As<int8>(), 0);
  EXPECT_EQ(uint32_value.As<uint8>(), 0);
  EXPECT_EQ(uint32_value.As<int16>(), 0);
  EXPECT_EQ(uint32_value.As<uint16>(), 0);
  EXPECT_EQ(uint32_value.As<int32>(), 0);
  EXPECT_EQ(uint32_value.As<uint32>(), 0);
  EXPECT_EQ(uint32_value.As<int64>(), 0);
  EXPECT_EQ(uint32_value.As<uint64>(), 0);
  EXPECT_EQ(uint32_value.As<float32>(), 0.0);
  EXPECT_EQ(uint32_value.As<float64>(), 0.0);
  int64 target_val;
  EXPECT_TRUE(uint32_value.As(target_val));
  EXPECT_EQ(target_val, 0);
  EXPECT_THROW(uint32_value.As<std::string>(), InvalidConversionException);
  std::string str_val;
  EXPECT_FALSE(uint32_value.As(str_val));
  auto new_val = 25;
  EXPECT_NO_THROW(uint32_value.ConvertFrom(new_val));
  EXPECT_EQ(uint32_value.As<boolean>(), true);
  EXPECT_EQ(uint32_value.As<int8>(), new_val);
  EXPECT_EQ(uint32_value.As<uint8>(), new_val);
  EXPECT_EQ(uint32_value.As<int16>(), new_val);
  EXPECT_EQ(uint32_value.As<uint16>(), new_val);
  EXPECT_EQ(uint32_value.As<int32>(), new_val);
  EXPECT_EQ(uint32_value.As<uint32>(), new_val);
  EXPECT_EQ(uint32_value.As<int64>(), new_val);
  EXPECT_EQ(uint32_value.As<uint64>(), new_val);
  EXPECT_EQ(uint32_value.As<float32>(), new_val);
  EXPECT_EQ(uint32_value.As<float64>(), new_val);
  EXPECT_TRUE(uint32_value.As(target_val));
  EXPECT_EQ(target_val, new_val);
  EXPECT_THROW(uint32_value.As<std::string>(), InvalidConversionException);
  EXPECT_FALSE(uint32_value.As(str_val));
  EXPECT_EQ(uint32_value, new_val);

  const AnyValue copy = uint32_value;
  EXPECT_TRUE(IsScalarValue(copy));
  EXPECT_EQ(copy, uint32_value);
  EXPECT_FALSE(IsEmptyValue(copy));
  EXPECT_FALSE(IsStructValue(copy));
  EXPECT_FALSE(IsArrayValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::UInt32);
  EXPECT_EQ(copy.GetTypeName(), kUInt32TypeName);
  EXPECT_THROW(copy["field"], InvalidOperationException);
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
  EXPECT_EQ(moved.GetTypeName(), kUInt32TypeName);
  EXPECT_THROW(moved["field"], InvalidOperationException);
  EXPECT_EQ(moved.As<boolean>(), true);
  EXPECT_EQ(moved.As<int32>(), new_val);

  uint32 literal = 74;
  AnyValue uint32_from_literal = literal;
  EXPECT_EQ(uint32_from_literal.GetType(), UnsignedInteger32Type);
  EXPECT_NE(uint32_from_literal.GetType(), SignedInteger32Type);
  EXPECT_FALSE(IsEmptyValue(uint32_from_literal));
  EXPECT_FALSE(IsStructValue(uint32_from_literal));
  EXPECT_FALSE(IsArrayValue(uint32_from_literal));
  EXPECT_TRUE(IsScalarValue(uint32_from_literal));
  EXPECT_EQ(uint32_from_literal.GetTypeCode(), TypeCode::UInt32);
  EXPECT_EQ(uint32_from_literal.GetTypeName(), kUInt32TypeName);
  EXPECT_THROW(uint32_from_literal["field"], InvalidOperationException);
  EXPECT_EQ(uint32_from_literal.As<uint32>(), literal);
  uint32_from_literal = 116;
  EXPECT_EQ(uint32_from_literal.As<boolean>(), true);
  EXPECT_EQ(uint32_from_literal.As<uint32>(), 116);
  EXPECT_EQ(uint32_from_literal.As<int32>(), 116);

  AnyValue uint32_from_typed_literal = {UnsignedInteger32Type, 5};
  EXPECT_EQ(uint32_from_typed_literal.GetType(), UnsignedInteger32Type);
  EXPECT_NE(uint32_from_typed_literal.GetType(), BooleanType);
  EXPECT_FALSE(IsEmptyValue(uint32_from_typed_literal));
  EXPECT_FALSE(IsStructValue(uint32_from_typed_literal));
  EXPECT_FALSE(IsArrayValue(uint32_from_typed_literal));
  EXPECT_TRUE(IsScalarValue(uint32_from_typed_literal));
  EXPECT_EQ(uint32_from_typed_literal.GetTypeCode(), TypeCode::UInt32);
  EXPECT_EQ(uint32_from_typed_literal.GetTypeName(), kUInt32TypeName);
  EXPECT_THROW(uint32_from_typed_literal["field"], InvalidOperationException);
  EXPECT_EQ(uint32_from_typed_literal.As<uint32>(), 5);
  uint32_from_typed_literal = 0;
  EXPECT_EQ(uint32_from_typed_literal.As<boolean>(), false);
  EXPECT_EQ(uint32_from_typed_literal.As<uint32>(), 0);
  EXPECT_EQ(uint32_from_typed_literal.As<int32>(), 0);
}

TEST(IntegerValueTest, SignedInteger64Value)
{
  AnyValue int64_value{SignedInteger64Type};
  EXPECT_EQ(int64_value.GetType(), SignedInteger64Type);
  EXPECT_NE(int64_value.GetType(), UnsignedInteger32Type);
  EXPECT_FALSE(IsEmptyValue(int64_value));
  EXPECT_FALSE(IsStructValue(int64_value));
  EXPECT_FALSE(IsArrayValue(int64_value));
  EXPECT_TRUE(IsScalarValue(int64_value));
  EXPECT_EQ(int64_value.GetTypeCode(), TypeCode::Int64);
  EXPECT_EQ(int64_value.GetTypeName(), kInt64TypeName);
  EXPECT_THROW(int64_value["field"], InvalidOperationException);
  EXPECT_EQ(int64_value.As<boolean>(), false);
  EXPECT_EQ(int64_value.As<int8>(), 0);
  EXPECT_EQ(int64_value.As<uint8>(), 0);
  EXPECT_EQ(int64_value.As<int16>(), 0);
  EXPECT_EQ(int64_value.As<uint16>(), 0);
  EXPECT_EQ(int64_value.As<int32>(), 0);
  EXPECT_EQ(int64_value.As<uint32>(), 0);
  EXPECT_EQ(int64_value.As<int64>(), 0);
  EXPECT_EQ(int64_value.As<uint64>(), 0);
  EXPECT_EQ(int64_value.As<float32>(), 0.0);
  EXPECT_EQ(int64_value.As<float64>(), 0.0);
  int64 target_val;
  EXPECT_TRUE(int64_value.As(target_val));
  EXPECT_EQ(target_val, 0);
  EXPECT_THROW(int64_value.As<std::string>(), InvalidConversionException);
  std::string str_val;
  EXPECT_FALSE(int64_value.As(str_val));
  auto new_val = 25;
  EXPECT_NO_THROW(int64_value.ConvertFrom(new_val));
  EXPECT_EQ(int64_value.As<boolean>(), true);
  EXPECT_EQ(int64_value.As<int8>(), new_val);
  EXPECT_EQ(int64_value.As<uint8>(), new_val);
  EXPECT_EQ(int64_value.As<int16>(), new_val);
  EXPECT_EQ(int64_value.As<uint16>(), new_val);
  EXPECT_EQ(int64_value.As<int32>(), new_val);
  EXPECT_EQ(int64_value.As<uint32>(), new_val);
  EXPECT_EQ(int64_value.As<int64>(), new_val);
  EXPECT_EQ(int64_value.As<uint64>(), new_val);
  EXPECT_EQ(int64_value.As<float32>(), new_val);
  EXPECT_EQ(int64_value.As<float64>(), new_val);
  EXPECT_TRUE(int64_value.As(target_val));
  EXPECT_EQ(target_val, new_val);
  EXPECT_THROW(int64_value.As<std::string>(), InvalidConversionException);
  EXPECT_FALSE(int64_value.As(str_val));
  EXPECT_EQ(int64_value, new_val);

  const AnyValue copy = int64_value;
  EXPECT_TRUE(IsScalarValue(copy));
  EXPECT_EQ(copy, int64_value);
  EXPECT_FALSE(IsEmptyValue(copy));
  EXPECT_FALSE(IsStructValue(copy));
  EXPECT_FALSE(IsArrayValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Int64);
  EXPECT_EQ(copy.GetTypeName(), kInt64TypeName);
  EXPECT_THROW(copy["field"], InvalidOperationException);
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
  EXPECT_EQ(moved.GetTypeName(), kInt64TypeName);
  EXPECT_THROW(moved["field"], InvalidOperationException);
  EXPECT_EQ(moved.As<boolean>(), true);
  EXPECT_EQ(moved.As<int64>(), 25);

  int64 literal = 74;
  AnyValue int64_from_literal = literal;
  EXPECT_EQ(int64_from_literal.GetType(), SignedInteger64Type);
  EXPECT_NE(int64_from_literal.GetType(), SignedInteger16Type);
  EXPECT_FALSE(IsEmptyValue(int64_from_literal));
  EXPECT_FALSE(IsStructValue(int64_from_literal));
  EXPECT_FALSE(IsArrayValue(int64_from_literal));
  EXPECT_TRUE(IsScalarValue(int64_from_literal));
  EXPECT_EQ(int64_from_literal.GetTypeCode(), TypeCode::Int64);
  EXPECT_EQ(int64_from_literal.GetTypeName(), kInt64TypeName);
  EXPECT_THROW(int64_from_literal["field"], InvalidOperationException);
  EXPECT_EQ(int64_from_literal.As<int64>(), literal);
  int64_from_literal = -18;
  EXPECT_EQ(int64_from_literal.As<boolean>(), true);
  EXPECT_EQ(int64_from_literal.As<int64>(), -18);
  EXPECT_EQ(int64_from_literal.As<int16>(), -18);

  AnyValue int64_from_typed_literal = {SignedInteger64Type, 5};
  EXPECT_EQ(int64_from_typed_literal.GetType(), SignedInteger64Type);
  EXPECT_NE(int64_from_typed_literal.GetType(), BooleanType);
  EXPECT_FALSE(IsEmptyValue(int64_from_typed_literal));
  EXPECT_FALSE(IsStructValue(int64_from_typed_literal));
  EXPECT_FALSE(IsArrayValue(int64_from_typed_literal));
  EXPECT_TRUE(IsScalarValue(int64_from_typed_literal));
  EXPECT_EQ(int64_from_typed_literal.GetTypeCode(), TypeCode::Int64);
  EXPECT_EQ(int64_from_typed_literal.GetTypeName(), kInt64TypeName);
  EXPECT_THROW(int64_from_typed_literal["field"], InvalidOperationException);
  EXPECT_EQ(int64_from_typed_literal.As<int64>(), 5);
  int64_from_typed_literal = 0;
  EXPECT_EQ(int64_from_typed_literal.As<boolean>(), false);
  EXPECT_EQ(int64_from_typed_literal.As<int16>(), 0);
  EXPECT_EQ(int64_from_typed_literal.As<int64>(), 0);
}

TEST(IntegerValueTest, UnsignedInteger64Value)
{
  AnyValue uint64_value{UnsignedInteger64Type};
  EXPECT_EQ(uint64_value.GetType(), UnsignedInteger64Type);
  EXPECT_NE(uint64_value.GetType(), SignedInteger64Type);
  EXPECT_FALSE(IsEmptyValue(uint64_value));
  EXPECT_FALSE(IsStructValue(uint64_value));
  EXPECT_FALSE(IsArrayValue(uint64_value));
  EXPECT_TRUE(IsScalarValue(uint64_value));
  EXPECT_EQ(uint64_value.GetTypeCode(), TypeCode::UInt64);
  EXPECT_EQ(uint64_value.GetTypeName(), kUInt64TypeName);
  EXPECT_THROW(uint64_value["field"], InvalidOperationException);
  EXPECT_EQ(uint64_value.As<boolean>(), false);
  EXPECT_EQ(uint64_value.As<int8>(), 0);
  EXPECT_EQ(uint64_value.As<uint8>(), 0);
  EXPECT_EQ(uint64_value.As<int16>(), 0);
  EXPECT_EQ(uint64_value.As<uint16>(), 0);
  EXPECT_EQ(uint64_value.As<int32>(), 0);
  EXPECT_EQ(uint64_value.As<uint32>(), 0);
  EXPECT_EQ(uint64_value.As<int64>(), 0);
  EXPECT_EQ(uint64_value.As<uint64>(), 0);
  EXPECT_EQ(uint64_value.As<float32>(), 0.0);
  EXPECT_EQ(uint64_value.As<float64>(), 0.0);
  int64 target_val;
  EXPECT_TRUE(uint64_value.As(target_val));
  EXPECT_EQ(target_val, 0);
  EXPECT_THROW(uint64_value.As<std::string>(), InvalidConversionException);
  std::string str_val;
  EXPECT_FALSE(uint64_value.As(str_val));
  auto new_val = 25;
  EXPECT_NO_THROW(uint64_value.ConvertFrom(new_val));
  EXPECT_EQ(uint64_value.As<boolean>(), true);
  EXPECT_EQ(uint64_value.As<int8>(), new_val);
  EXPECT_EQ(uint64_value.As<uint8>(), new_val);
  EXPECT_EQ(uint64_value.As<int16>(), new_val);
  EXPECT_EQ(uint64_value.As<uint16>(), new_val);
  EXPECT_EQ(uint64_value.As<int32>(), new_val);
  EXPECT_EQ(uint64_value.As<uint32>(), new_val);
  EXPECT_EQ(uint64_value.As<int64>(), new_val);
  EXPECT_EQ(uint64_value.As<uint64>(), new_val);
  EXPECT_EQ(uint64_value.As<float32>(), new_val);
  EXPECT_EQ(uint64_value.As<float64>(), new_val);
  EXPECT_TRUE(uint64_value.As(target_val));
  EXPECT_EQ(target_val, new_val);
  EXPECT_THROW(uint64_value.As<std::string>(), InvalidConversionException);
  EXPECT_FALSE(uint64_value.As(str_val));
  EXPECT_EQ(uint64_value, new_val);

  const AnyValue copy = uint64_value;
  EXPECT_TRUE(IsScalarValue(copy));
  EXPECT_EQ(copy, uint64_value);
  EXPECT_FALSE(IsEmptyValue(copy));
  EXPECT_FALSE(IsStructValue(copy));
  EXPECT_FALSE(IsArrayValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::UInt64);
  EXPECT_EQ(copy.GetTypeName(), kUInt64TypeName);
  EXPECT_THROW(copy["field"], InvalidOperationException);
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
  EXPECT_EQ(moved.GetTypeName(), kUInt64TypeName);
  EXPECT_THROW(moved["field"], InvalidOperationException);
  EXPECT_EQ(moved.As<boolean>(), true);
  EXPECT_EQ(moved.As<int64>(), new_val);

  uint64 literal = 74;
  AnyValue uint64_from_literal = literal;
  EXPECT_EQ(uint64_from_literal.GetType(), UnsignedInteger64Type);
  EXPECT_NE(uint64_from_literal.GetType(), SignedInteger64Type);
  EXPECT_FALSE(IsEmptyValue(uint64_from_literal));
  EXPECT_FALSE(IsStructValue(uint64_from_literal));
  EXPECT_FALSE(IsArrayValue(uint64_from_literal));
  EXPECT_TRUE(IsScalarValue(uint64_from_literal));
  EXPECT_EQ(uint64_from_literal.GetTypeCode(), TypeCode::UInt64);
  EXPECT_EQ(uint64_from_literal.GetTypeName(), kUInt64TypeName);
  EXPECT_THROW(uint64_from_literal["field"], InvalidOperationException);
  EXPECT_EQ(uint64_from_literal.As<uint64>(), literal);
  uint64_from_literal = 116;
  EXPECT_EQ(uint64_from_literal.As<boolean>(), true);
  EXPECT_EQ(uint64_from_literal.As<uint64>(), 116);
  EXPECT_EQ(uint64_from_literal.As<int32>(), 116);

  AnyValue uint64_from_typed_literal = {UnsignedInteger64Type, 5};
  EXPECT_EQ(uint64_from_typed_literal.GetType(), UnsignedInteger64Type);
  EXPECT_NE(uint64_from_typed_literal.GetType(), BooleanType);
  EXPECT_FALSE(IsEmptyValue(uint64_from_typed_literal));
  EXPECT_FALSE(IsStructValue(uint64_from_typed_literal));
  EXPECT_FALSE(IsArrayValue(uint64_from_typed_literal));
  EXPECT_TRUE(IsScalarValue(uint64_from_typed_literal));
  EXPECT_EQ(uint64_from_typed_literal.GetTypeCode(), TypeCode::UInt64);
  EXPECT_EQ(uint64_from_typed_literal.GetTypeName(), kUInt64TypeName);
  EXPECT_THROW(uint64_from_typed_literal["field"], InvalidOperationException);
  EXPECT_EQ(uint64_from_typed_literal.As<uint64>(), 5);
  uint64_from_typed_literal = 0;
  EXPECT_EQ(uint64_from_typed_literal.As<boolean>(), false);
  EXPECT_EQ(uint64_from_typed_literal.As<uint64>(), 0);
  EXPECT_EQ(uint64_from_typed_literal.As<int32>(), 0);
}
