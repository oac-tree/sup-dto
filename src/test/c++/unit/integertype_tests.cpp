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

#include "sup/dto/anytype.h"
#include "sup/dto/anyvalue_exceptions.h"

using namespace sup::dto;

TEST(IntegerTypeTest, Character8Type)
{
  AnyType char_type{TypeCode::Char8};
  EXPECT_EQ(char_type, Character8Type);
  EXPECT_NE(char_type, UnsignedInteger8Type);
  EXPECT_FALSE(IsEmptyType(char_type));
  EXPECT_FALSE(IsStructType(char_type));
  EXPECT_FALSE(IsArrayType(char_type));
  EXPECT_FALSE(IsUnboundedArrayType(char_type));
  EXPECT_TRUE(IsScalarType(char_type));
  EXPECT_EQ(char_type.GetTypeCode(), TypeCode::Char8);
  EXPECT_EQ(char_type.GetTypeName(), kChar8TypeName);
  EXPECT_THROW(char_type["field"], InvalidOperationException);

  AnyType copy_char8 = char_type;
  EXPECT_EQ(copy_char8, Character8Type);
  EXPECT_NE(copy_char8, UnsignedInteger8Type);
  EXPECT_FALSE(IsEmptyType(copy_char8));
  EXPECT_FALSE(IsStructType(copy_char8));
  EXPECT_FALSE(IsArrayType(copy_char8));
  EXPECT_FALSE(IsUnboundedArrayType(copy_char8));
  EXPECT_TRUE(IsScalarType(copy_char8));
  EXPECT_EQ(copy_char8.GetTypeCode(), TypeCode::Char8);
  EXPECT_EQ(copy_char8.GetTypeName(), kChar8TypeName);
  EXPECT_THROW(copy_char8["field"], InvalidOperationException);
}

TEST(IntegerTypeTest, SignedInteger8Type)
{
  AnyType int8_type{TypeCode::Int8};
  EXPECT_EQ(int8_type, SignedInteger8Type);
  EXPECT_NE(int8_type, UnsignedInteger8Type);
  EXPECT_FALSE(IsEmptyType(int8_type));
  EXPECT_FALSE(IsStructType(int8_type));
  EXPECT_FALSE(IsArrayType(int8_type));
  EXPECT_FALSE(IsUnboundedArrayType(int8_type));
  EXPECT_TRUE(IsScalarType(int8_type));
  EXPECT_EQ(int8_type.GetTypeCode(), TypeCode::Int8);
  EXPECT_EQ(int8_type.GetTypeName(), kInt8TypeName);
  EXPECT_THROW(int8_type["field"], InvalidOperationException);

  AnyType copy_int8 = int8_type;
  EXPECT_EQ(copy_int8, SignedInteger8Type);
  EXPECT_NE(copy_int8, UnsignedInteger8Type);
  EXPECT_FALSE(IsEmptyType(copy_int8));
  EXPECT_FALSE(IsStructType(copy_int8));
  EXPECT_FALSE(IsArrayType(copy_int8));
  EXPECT_FALSE(IsUnboundedArrayType(copy_int8));
  EXPECT_TRUE(IsScalarType(copy_int8));
  EXPECT_EQ(copy_int8.GetTypeCode(), TypeCode::Int8);
  EXPECT_EQ(copy_int8.GetTypeName(), kInt8TypeName);
  EXPECT_THROW(copy_int8["field"], InvalidOperationException);
}

TEST(IntegerTypeTest, UnsignedInteger8Type)
{
  AnyType uint8_type{TypeCode::UInt8};
  EXPECT_EQ(uint8_type, UnsignedInteger8Type);
  EXPECT_NE(uint8_type, SignedInteger8Type);
  EXPECT_FALSE(IsEmptyType(uint8_type));
  EXPECT_FALSE(IsStructType(uint8_type));
  EXPECT_FALSE(IsArrayType(uint8_type));
  EXPECT_FALSE(IsUnboundedArrayType(uint8_type));
  EXPECT_TRUE(IsScalarType(uint8_type));
  EXPECT_EQ(uint8_type.GetTypeCode(), TypeCode::UInt8);
  EXPECT_EQ(uint8_type.GetTypeName(), kUInt8TypeName);
  EXPECT_THROW(uint8_type["field"], InvalidOperationException);

  AnyType moved_uint8 = std::move(uint8_type);
  EXPECT_EQ(moved_uint8, UnsignedInteger8Type);
  EXPECT_NE(moved_uint8, SignedInteger8Type);
  EXPECT_TRUE(IsEmptyType(uint8_type)); // Moved from type is always empty
  EXPECT_EQ(uint8_type, EmptyType);
  EXPECT_FALSE(IsEmptyType(moved_uint8));
  EXPECT_FALSE(IsStructType(moved_uint8));
  EXPECT_FALSE(IsArrayType(moved_uint8));
  EXPECT_FALSE(IsUnboundedArrayType(moved_uint8));
  EXPECT_TRUE(IsScalarType(moved_uint8));
  EXPECT_EQ(moved_uint8.GetTypeCode(), TypeCode::UInt8);
  EXPECT_EQ(moved_uint8.GetTypeName(), kUInt8TypeName);
  EXPECT_THROW(moved_uint8["field"], InvalidOperationException);
}

TEST(IntegerTypeTest, SignedInteger16Type)
{
  AnyType int16_type{TypeCode::Int16};
  EXPECT_EQ(int16_type, SignedInteger16Type);
  EXPECT_NE(int16_type, UnsignedInteger16Type);
  EXPECT_FALSE(IsEmptyType(int16_type));
  EXPECT_FALSE(IsStructType(int16_type));
  EXPECT_FALSE(IsArrayType(int16_type));
  EXPECT_FALSE(IsUnboundedArrayType(int16_type));
  EXPECT_TRUE(IsScalarType(int16_type));
  EXPECT_EQ(int16_type.GetTypeCode(), TypeCode::Int16);
  EXPECT_EQ(int16_type.GetTypeName(), kInt16TypeName);
  EXPECT_THROW(int16_type["field"], InvalidOperationException);

  AnyType copy_int16 = int16_type;
  EXPECT_EQ(copy_int16, SignedInteger16Type);
  EXPECT_NE(copy_int16, UnsignedInteger16Type);
  EXPECT_FALSE(IsEmptyType(copy_int16));
  EXPECT_FALSE(IsStructType(copy_int16));
  EXPECT_FALSE(IsArrayType(copy_int16));
  EXPECT_FALSE(IsUnboundedArrayType(copy_int16));
  EXPECT_TRUE(IsScalarType(copy_int16));
  EXPECT_EQ(copy_int16.GetTypeCode(), TypeCode::Int16);
  EXPECT_EQ(copy_int16.GetTypeName(), kInt16TypeName);
  EXPECT_THROW(copy_int16["field"], InvalidOperationException);
}

TEST(IntegerTypeTest, UnsignedInteger16Type)
{
  AnyType uint16_type{TypeCode::UInt16};
  EXPECT_EQ(uint16_type, UnsignedInteger16Type);
  EXPECT_NE(uint16_type, SignedInteger16Type);
  EXPECT_FALSE(IsEmptyType(uint16_type));
  EXPECT_FALSE(IsStructType(uint16_type));
  EXPECT_FALSE(IsArrayType(uint16_type));
  EXPECT_FALSE(IsUnboundedArrayType(uint16_type));
  EXPECT_TRUE(IsScalarType(uint16_type));
  EXPECT_EQ(uint16_type.GetTypeCode(), TypeCode::UInt16);
  EXPECT_EQ(uint16_type.GetTypeName(), kUInt16TypeName);
  EXPECT_THROW(uint16_type["field"], InvalidOperationException);

  AnyType moved_uint16 = std::move(uint16_type);
  EXPECT_EQ(moved_uint16, UnsignedInteger16Type);
  EXPECT_NE(moved_uint16, SignedInteger16Type);
  EXPECT_TRUE(IsEmptyType(uint16_type)); // Moved from type is always empty
  EXPECT_EQ(uint16_type, EmptyType);
  EXPECT_FALSE(IsEmptyType(moved_uint16));
  EXPECT_FALSE(IsStructType(moved_uint16));
  EXPECT_FALSE(IsArrayType(moved_uint16));
  EXPECT_FALSE(IsUnboundedArrayType(moved_uint16));
  EXPECT_TRUE(IsScalarType(moved_uint16));
  EXPECT_EQ(moved_uint16.GetTypeCode(), TypeCode::UInt16);
  EXPECT_EQ(moved_uint16.GetTypeName(), kUInt16TypeName);
  EXPECT_THROW(moved_uint16["field"], InvalidOperationException);
}

TEST(IntegerTypeTest, SignedInteger32Type)
{
  AnyType int32_type{TypeCode::Int32};
  EXPECT_EQ(int32_type, SignedInteger32Type);
  EXPECT_NE(int32_type, UnsignedInteger32Type);
  EXPECT_FALSE(IsEmptyType(int32_type));
  EXPECT_FALSE(IsStructType(int32_type));
  EXPECT_FALSE(IsArrayType(int32_type));
  EXPECT_FALSE(IsUnboundedArrayType(int32_type));
  EXPECT_TRUE(IsScalarType(int32_type));
  EXPECT_EQ(int32_type.GetTypeCode(), TypeCode::Int32);
  EXPECT_EQ(int32_type.GetTypeName(), kInt32TypeName);
  EXPECT_THROW(int32_type["field"], InvalidOperationException);

  AnyType copy_int32 = int32_type;
  EXPECT_EQ(copy_int32, SignedInteger32Type);
  EXPECT_NE(copy_int32, UnsignedInteger32Type);
  EXPECT_FALSE(IsEmptyType(copy_int32));
  EXPECT_FALSE(IsStructType(copy_int32));
  EXPECT_FALSE(IsArrayType(copy_int32));
  EXPECT_FALSE(IsUnboundedArrayType(copy_int32));
  EXPECT_TRUE(IsScalarType(copy_int32));
  EXPECT_EQ(copy_int32.GetTypeCode(), TypeCode::Int32);
  EXPECT_EQ(copy_int32.GetTypeName(), kInt32TypeName);
  EXPECT_THROW(copy_int32["field"], InvalidOperationException);
}

TEST(IntegerTypeTest, UnsignedInteger32Type)
{
  AnyType uint32_type{TypeCode::UInt32};
  EXPECT_EQ(uint32_type, UnsignedInteger32Type);
  EXPECT_NE(uint32_type, SignedInteger32Type);
  EXPECT_FALSE(IsEmptyType(uint32_type));
  EXPECT_FALSE(IsStructType(uint32_type));
  EXPECT_FALSE(IsArrayType(uint32_type));
  EXPECT_FALSE(IsUnboundedArrayType(uint32_type));
  EXPECT_TRUE(IsScalarType(uint32_type));
  EXPECT_EQ(uint32_type.GetTypeCode(), TypeCode::UInt32);
  EXPECT_EQ(uint32_type.GetTypeName(), kUInt32TypeName);
  EXPECT_THROW(uint32_type["field"], InvalidOperationException);

  AnyType moved_uint32 = std::move(uint32_type);
  EXPECT_EQ(moved_uint32, UnsignedInteger32Type);
  EXPECT_NE(moved_uint32, SignedInteger32Type);
  EXPECT_TRUE(IsEmptyType(uint32_type)); // Moved from type is always empty
  EXPECT_EQ(uint32_type, EmptyType);
  EXPECT_FALSE(IsEmptyType(moved_uint32));
  EXPECT_FALSE(IsStructType(moved_uint32));
  EXPECT_FALSE(IsArrayType(moved_uint32));
  EXPECT_FALSE(IsUnboundedArrayType(moved_uint32));
  EXPECT_TRUE(IsScalarType(moved_uint32));
  EXPECT_EQ(moved_uint32.GetTypeCode(), TypeCode::UInt32);
  EXPECT_EQ(moved_uint32.GetTypeName(), kUInt32TypeName);
  EXPECT_THROW(moved_uint32["field"], InvalidOperationException);
}

TEST(IntegerTypeTest, SignedInteger64Type)
{
  AnyType int64_type{TypeCode::Int64};
  EXPECT_EQ(int64_type, SignedInteger64Type);
  EXPECT_NE(int64_type, UnsignedInteger64Type);
  EXPECT_FALSE(IsEmptyType(int64_type));
  EXPECT_FALSE(IsStructType(int64_type));
  EXPECT_FALSE(IsArrayType(int64_type));
  EXPECT_FALSE(IsUnboundedArrayType(int64_type));
  EXPECT_TRUE(IsScalarType(int64_type));
  EXPECT_EQ(int64_type.GetTypeCode(), TypeCode::Int64);
  EXPECT_EQ(int64_type.GetTypeName(), kInt64TypeName);
  EXPECT_THROW(int64_type["field"], InvalidOperationException);

  AnyType copy_int64 = int64_type;
  EXPECT_EQ(copy_int64, SignedInteger64Type);
  EXPECT_NE(copy_int64, UnsignedInteger64Type);
  EXPECT_FALSE(IsEmptyType(copy_int64));
  EXPECT_FALSE(IsStructType(copy_int64));
  EXPECT_FALSE(IsArrayType(copy_int64));
  EXPECT_FALSE(IsUnboundedArrayType(copy_int64));
  EXPECT_TRUE(IsScalarType(copy_int64));
  EXPECT_EQ(copy_int64.GetTypeCode(), TypeCode::Int64);
  EXPECT_EQ(copy_int64.GetTypeName(), kInt64TypeName);
  EXPECT_THROW(copy_int64["field"], InvalidOperationException);
}

TEST(IntegerTypeTest, UnsignedInteger64Type)
{
  AnyType uint64_type{TypeCode::UInt64};
  EXPECT_EQ(uint64_type, UnsignedInteger64Type);
  EXPECT_NE(uint64_type, SignedInteger64Type);
  EXPECT_FALSE(IsEmptyType(uint64_type));
  EXPECT_FALSE(IsStructType(uint64_type));
  EXPECT_FALSE(IsArrayType(uint64_type));
  EXPECT_FALSE(IsUnboundedArrayType(uint64_type));
  EXPECT_TRUE(IsScalarType(uint64_type));
  EXPECT_EQ(uint64_type.GetTypeCode(), TypeCode::UInt64);
  EXPECT_EQ(uint64_type.GetTypeName(), kUInt64TypeName);
  EXPECT_THROW(uint64_type["field"], InvalidOperationException);

  AnyType moved_uint64 = std::move(uint64_type);
  EXPECT_EQ(moved_uint64, UnsignedInteger64Type);
  EXPECT_NE(moved_uint64, SignedInteger64Type);
  EXPECT_TRUE(IsEmptyType(uint64_type)); // Moved from type is always empty
  EXPECT_EQ(uint64_type, EmptyType);
  EXPECT_FALSE(IsEmptyType(moved_uint64));
  EXPECT_FALSE(IsStructType(moved_uint64));
  EXPECT_FALSE(IsArrayType(moved_uint64));
  EXPECT_FALSE(IsUnboundedArrayType(moved_uint64));
  EXPECT_TRUE(IsScalarType(moved_uint64));
  EXPECT_EQ(moved_uint64.GetTypeCode(), TypeCode::UInt64);
  EXPECT_EQ(moved_uint64.GetTypeName(), kUInt64TypeName);
  EXPECT_THROW(moved_uint64["field"], InvalidOperationException);
}
