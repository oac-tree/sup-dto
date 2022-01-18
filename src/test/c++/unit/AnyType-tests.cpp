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

#include "AnyType.h"
#include "AnyValueExceptions.h"

using namespace sup::dto;

TEST(AnyTypeTest, TypeCodes)
{
  EXPECT_TRUE(IsEmptyTypeCode(TypeCode::Empty));
  EXPECT_FALSE(IsStructTypeCode(TypeCode::Empty));
  EXPECT_FALSE(IsArrayTypeCode(TypeCode::Empty));
  EXPECT_FALSE(IsScalarTypeCode(TypeCode::Empty));

  EXPECT_FALSE(IsEmptyTypeCode(TypeCode::Struct));
  EXPECT_TRUE(IsStructTypeCode(TypeCode::Struct));
  EXPECT_FALSE(IsArrayTypeCode(TypeCode::Struct));
  EXPECT_FALSE(IsScalarTypeCode(TypeCode::Struct));

  EXPECT_FALSE(IsEmptyTypeCode(TypeCode::Array));
  EXPECT_FALSE(IsStructTypeCode(TypeCode::Array));
  EXPECT_TRUE(IsArrayTypeCode(TypeCode::Array));
  EXPECT_FALSE(IsScalarTypeCode(TypeCode::Array));

  EXPECT_FALSE(IsEmptyTypeCode(TypeCode::Int8));
  EXPECT_FALSE(IsStructTypeCode(TypeCode::Int8));
  EXPECT_FALSE(IsArrayTypeCode(TypeCode::Int8));
  EXPECT_TRUE(IsScalarTypeCode(TypeCode::Int8));

  EXPECT_FALSE(IsEmptyTypeCode(TypeCode::UInt8));
  EXPECT_FALSE(IsStructTypeCode(TypeCode::UInt8));
  EXPECT_FALSE(IsArrayTypeCode(TypeCode::UInt8));
  EXPECT_TRUE(IsScalarTypeCode(TypeCode::UInt8));
}

TEST(AnyTypeTest, EmptyType)
{
  AnyType empty_type{};
  EXPECT_EQ(empty_type, EmptyType);
  EXPECT_NE(empty_type, SignedInteger8);
  EXPECT_TRUE(IsEmptyType(empty_type));
  EXPECT_FALSE(IsStructType(empty_type));
  EXPECT_FALSE(IsArrayType(empty_type));
  EXPECT_FALSE(IsScalarType(empty_type));
  EXPECT_EQ(empty_type.NumberOfMembers(), 0);
  EXPECT_EQ(empty_type.GetTypeCode(), TypeCode::Empty);
  EXPECT_EQ(empty_type.GetTypeName(), EMPTY_TYPE_NAME);
  EXPECT_THROW(empty_type["field"], KeyNotAllowedException);

  const AnyType copy = empty_type;
  EXPECT_TRUE(IsEmptyType(copy));
  EXPECT_EQ(copy, EmptyType);
  EXPECT_FALSE(IsStructType(copy));
  EXPECT_FALSE(IsArrayType(copy));
  EXPECT_FALSE(IsScalarType(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Empty);
  EXPECT_EQ(copy.GetTypeName(), EMPTY_TYPE_NAME);
  EXPECT_THROW(copy["field"], KeyNotAllowedException);

  AnyType moved = std::move(empty_type);
  EXPECT_TRUE(IsEmptyType(empty_type)); // Moved from type is always empty
  EXPECT_EQ(empty_type, EmptyType);
  EXPECT_TRUE(IsEmptyType(moved));
  EXPECT_EQ(copy, EmptyType);
  EXPECT_FALSE(IsStructType(moved));
  EXPECT_FALSE(IsArrayType(moved));
  EXPECT_FALSE(IsScalarType(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Empty);
  EXPECT_EQ(moved.GetTypeName(), EMPTY_TYPE_NAME);
  EXPECT_THROW(moved["field"], KeyNotAllowedException);
}

TEST(AnyTypeTest, StructOfScalarType)
{
  const std::string two_scalar_name = "scalar_pair";
  AnyType two_scalars{{
    {"signed", SignedInteger8},
    {"unsigned", UnsignedInteger8}
  }, two_scalar_name};
  EXPECT_FALSE(IsEmptyType(two_scalars));
  EXPECT_TRUE(IsStructType(two_scalars));
  EXPECT_FALSE(IsArrayType(two_scalars));
  EXPECT_FALSE(IsScalarType(two_scalars));
  EXPECT_EQ(two_scalars.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(two_scalars.GetTypeName(), two_scalar_name);
  EXPECT_THROW(two_scalars[""], EmptyKeyException);
  EXPECT_THROW(two_scalars["unknownfield"], UnknownKeyException);
  auto& signed_type = two_scalars["signed"];
  auto& unsigned_type = two_scalars["unsigned"];
  EXPECT_EQ(signed_type.GetTypeCode(), TypeCode::Int8);
  EXPECT_EQ(unsigned_type.GetTypeCode(), TypeCode::UInt8);

  AnyType copy = two_scalars;
  EXPECT_EQ(copy, two_scalars);
}

TEST(AnyTypeTest, StructOfStructType)
{
  const std::string nested_name = "nested_struct";
  AnyType two_scalars{{
    {"signed", SignedInteger8},
    {"unsigned", UnsignedInteger8}
  }};
  AnyType nested_type{{
    {"scalars", two_scalars},
    {"single", {
      {"first", SignedInteger8},
      {"second", SignedInteger8}
    }}
  }, nested_name};
  EXPECT_FALSE(IsEmptyType(nested_type));
  EXPECT_TRUE(IsStructType(nested_type));
  EXPECT_FALSE(IsArrayType(nested_type));
  EXPECT_FALSE(IsScalarType(nested_type));
  EXPECT_EQ(nested_type.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(nested_type.GetTypeName(), nested_name);
  EXPECT_THROW(nested_type[""], EmptyKeyException);
  EXPECT_THROW(nested_type["unknownfield"], UnknownKeyException);
  auto& scalars_type = nested_type["scalars"];
  auto& signed_type = nested_type["single.first"];
  EXPECT_EQ(scalars_type.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(scalars_type.GetTypeName(), "");
  EXPECT_EQ(signed_type.GetTypeCode(), TypeCode::Int8);

  const std::string nested_with_name_name = "nested_struct_with_name";
  const std::string embedded_name = "embedded_name";
  AnyType nested_type_with_name{{
    {"scalars", two_scalars},
    {"single", {{
      {"first", SignedInteger8},
      {"second", SignedInteger8}
    }, embedded_name}}
  }, nested_with_name_name};
  EXPECT_NE(nested_type_with_name, nested_type); // struct names are different
  EXPECT_FALSE(IsEmptyType(nested_type_with_name));
  EXPECT_TRUE(IsStructType(nested_type_with_name));
  EXPECT_FALSE(IsArrayType(nested_type_with_name));
  EXPECT_FALSE(IsScalarType(nested_type_with_name));
  EXPECT_EQ(nested_type_with_name.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(nested_type_with_name.GetTypeName(), nested_with_name_name);
  EXPECT_THROW(nested_type_with_name[""], EmptyKeyException);
  EXPECT_THROW(nested_type_with_name["unknownfield"], UnknownKeyException);
  auto& single_type = nested_type_with_name["single"];
  auto& signed_type2 = nested_type_with_name["scalars.signed"];
  EXPECT_EQ(single_type.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(single_type.GetTypeName(), embedded_name);
  EXPECT_EQ(signed_type2.GetTypeCode(), TypeCode::Int8);
}

TEST(AnyTypeTest, Boolean)
{
  AnyType boolean_type{TypeCode::Bool};
  EXPECT_EQ(boolean_type, Boolean);
  EXPECT_NE(boolean_type, UnsignedInteger8);
  EXPECT_FALSE(IsEmptyType(boolean_type));
  EXPECT_FALSE(IsStructType(boolean_type));
  EXPECT_FALSE(IsArrayType(boolean_type));
  EXPECT_TRUE(IsScalarType(boolean_type));
  EXPECT_EQ(boolean_type.GetTypeCode(), TypeCode::Bool);
  EXPECT_EQ(boolean_type.GetTypeName(), BOOLEAN_TYPE_NAME);
  EXPECT_THROW(boolean_type["field"], KeyNotAllowedException);

  AnyType copy_boolean = boolean_type;
  EXPECT_EQ(copy_boolean, Boolean);
  EXPECT_NE(copy_boolean, UnsignedInteger8);
  EXPECT_FALSE(IsEmptyType(copy_boolean));
  EXPECT_FALSE(IsStructType(copy_boolean));
  EXPECT_FALSE(IsArrayType(copy_boolean));
  EXPECT_TRUE(IsScalarType(copy_boolean));
  EXPECT_EQ(copy_boolean.GetTypeCode(), TypeCode::Bool);
  EXPECT_EQ(copy_boolean.GetTypeName(), BOOLEAN_TYPE_NAME);
  EXPECT_THROW(copy_boolean["field"], KeyNotAllowedException);
}

TEST(AnyTypeTest, Character8)
{
  AnyType char_type{TypeCode::Char8};
  EXPECT_EQ(char_type, Character8);
  EXPECT_NE(char_type, UnsignedInteger8);
  EXPECT_FALSE(IsEmptyType(char_type));
  EXPECT_FALSE(IsStructType(char_type));
  EXPECT_FALSE(IsArrayType(char_type));
  EXPECT_TRUE(IsScalarType(char_type));
  EXPECT_EQ(char_type.GetTypeCode(), TypeCode::Char8);
  EXPECT_EQ(char_type.GetTypeName(), CHAR8_TYPE_NAME);
  EXPECT_THROW(char_type["field"], KeyNotAllowedException);

  AnyType copy_char8 = char_type;
  EXPECT_EQ(copy_char8, Character8);
  EXPECT_NE(copy_char8, UnsignedInteger8);
  EXPECT_FALSE(IsEmptyType(copy_char8));
  EXPECT_FALSE(IsStructType(copy_char8));
  EXPECT_FALSE(IsArrayType(copy_char8));
  EXPECT_TRUE(IsScalarType(copy_char8));
  EXPECT_EQ(copy_char8.GetTypeCode(), TypeCode::Char8);
  EXPECT_EQ(copy_char8.GetTypeName(), CHAR8_TYPE_NAME);
  EXPECT_THROW(copy_char8["field"], KeyNotAllowedException);
}

TEST(AnyTypeTest, SignedInteger8)
{
  AnyType int8_type{TypeCode::Int8};
  EXPECT_EQ(int8_type, SignedInteger8);
  EXPECT_NE(int8_type, UnsignedInteger8);
  EXPECT_FALSE(IsEmptyType(int8_type));
  EXPECT_FALSE(IsStructType(int8_type));
  EXPECT_FALSE(IsArrayType(int8_type));
  EXPECT_TRUE(IsScalarType(int8_type));
  EXPECT_EQ(int8_type.GetTypeCode(), TypeCode::Int8);
  EXPECT_EQ(int8_type.GetTypeName(), INT8_TYPE_NAME);
  EXPECT_THROW(int8_type["field"], KeyNotAllowedException);

  AnyType copy_int8 = int8_type;
  EXPECT_EQ(copy_int8, SignedInteger8);
  EXPECT_NE(copy_int8, UnsignedInteger8);
  EXPECT_FALSE(IsEmptyType(copy_int8));
  EXPECT_FALSE(IsStructType(copy_int8));
  EXPECT_FALSE(IsArrayType(copy_int8));
  EXPECT_TRUE(IsScalarType(copy_int8));
  EXPECT_EQ(copy_int8.GetTypeCode(), TypeCode::Int8);
  EXPECT_EQ(copy_int8.GetTypeName(), INT8_TYPE_NAME);
  EXPECT_THROW(copy_int8["field"], KeyNotAllowedException);
}

TEST(AnyTypeTest, UnsignedInteger8)
{
  AnyType uint8_type{TypeCode::UInt8};
  EXPECT_EQ(uint8_type, UnsignedInteger8);
  EXPECT_NE(uint8_type, SignedInteger8);
  EXPECT_FALSE(IsEmptyType(uint8_type));
  EXPECT_FALSE(IsStructType(uint8_type));
  EXPECT_FALSE(IsArrayType(uint8_type));
  EXPECT_TRUE(IsScalarType(uint8_type));
  EXPECT_EQ(uint8_type.GetTypeCode(), TypeCode::UInt8);
  EXPECT_EQ(uint8_type.GetTypeName(), UINT8_TYPE_NAME);
  EXPECT_THROW(uint8_type["field"], KeyNotAllowedException);

  AnyType moved_uint8 = std::move(uint8_type);
  EXPECT_EQ(moved_uint8, UnsignedInteger8);
  EXPECT_NE(moved_uint8, SignedInteger8);
  EXPECT_TRUE(IsEmptyType(uint8_type)); // Moved from type is always empty
  EXPECT_EQ(uint8_type, EmptyType);
  EXPECT_FALSE(IsEmptyType(moved_uint8));
  EXPECT_FALSE(IsStructType(moved_uint8));
  EXPECT_FALSE(IsArrayType(moved_uint8));
  EXPECT_TRUE(IsScalarType(moved_uint8));
  EXPECT_EQ(moved_uint8.GetTypeCode(), TypeCode::UInt8);
  EXPECT_EQ(moved_uint8.GetTypeName(), UINT8_TYPE_NAME);
  EXPECT_THROW(moved_uint8["field"], KeyNotAllowedException);
}

TEST(AnyTypeTest, SignedInteger16)
{
  AnyType int16_type{TypeCode::Int16};
  EXPECT_EQ(int16_type, SignedInteger16);
  EXPECT_NE(int16_type, UnsignedInteger16);
  EXPECT_FALSE(IsEmptyType(int16_type));
  EXPECT_FALSE(IsStructType(int16_type));
  EXPECT_FALSE(IsArrayType(int16_type));
  EXPECT_TRUE(IsScalarType(int16_type));
  EXPECT_EQ(int16_type.GetTypeCode(), TypeCode::Int16);
  EXPECT_EQ(int16_type.GetTypeName(), INT16_TYPE_NAME);
  EXPECT_THROW(int16_type["field"], KeyNotAllowedException);

  AnyType copy_int16 = int16_type;
  EXPECT_EQ(copy_int16, SignedInteger16);
  EXPECT_NE(copy_int16, UnsignedInteger16);
  EXPECT_FALSE(IsEmptyType(copy_int16));
  EXPECT_FALSE(IsStructType(copy_int16));
  EXPECT_FALSE(IsArrayType(copy_int16));
  EXPECT_TRUE(IsScalarType(copy_int16));
  EXPECT_EQ(copy_int16.GetTypeCode(), TypeCode::Int16);
  EXPECT_EQ(copy_int16.GetTypeName(), INT16_TYPE_NAME);
  EXPECT_THROW(copy_int16["field"], KeyNotAllowedException);
}

TEST(AnyTypeTest, UnsignedInteger16)
{
  AnyType uint16_type{TypeCode::UInt16};
  EXPECT_EQ(uint16_type, UnsignedInteger16);
  EXPECT_NE(uint16_type, SignedInteger16);
  EXPECT_FALSE(IsEmptyType(uint16_type));
  EXPECT_FALSE(IsStructType(uint16_type));
  EXPECT_FALSE(IsArrayType(uint16_type));
  EXPECT_TRUE(IsScalarType(uint16_type));
  EXPECT_EQ(uint16_type.GetTypeCode(), TypeCode::UInt16);
  EXPECT_EQ(uint16_type.GetTypeName(), UINT16_TYPE_NAME);
  EXPECT_THROW(uint16_type["field"], KeyNotAllowedException);

  AnyType moved_uint16 = std::move(uint16_type);
  EXPECT_EQ(moved_uint16, UnsignedInteger16);
  EXPECT_NE(moved_uint16, SignedInteger16);
  EXPECT_TRUE(IsEmptyType(uint16_type)); // Moved from type is always empty
  EXPECT_EQ(uint16_type, EmptyType);
  EXPECT_FALSE(IsEmptyType(moved_uint16));
  EXPECT_FALSE(IsStructType(moved_uint16));
  EXPECT_FALSE(IsArrayType(moved_uint16));
  EXPECT_TRUE(IsScalarType(moved_uint16));
  EXPECT_EQ(moved_uint16.GetTypeCode(), TypeCode::UInt16);
  EXPECT_EQ(moved_uint16.GetTypeName(), UINT16_TYPE_NAME);
  EXPECT_THROW(moved_uint16["field"], KeyNotAllowedException);
}

TEST(AnyTypeTest, SignedInteger32)
{
  AnyType int32_type{TypeCode::Int32};
  EXPECT_EQ(int32_type, SignedInteger32);
  EXPECT_NE(int32_type, UnsignedInteger32);
  EXPECT_FALSE(IsEmptyType(int32_type));
  EXPECT_FALSE(IsStructType(int32_type));
  EXPECT_FALSE(IsArrayType(int32_type));
  EXPECT_TRUE(IsScalarType(int32_type));
  EXPECT_EQ(int32_type.GetTypeCode(), TypeCode::Int32);
  EXPECT_EQ(int32_type.GetTypeName(), INT32_TYPE_NAME);
  EXPECT_THROW(int32_type["field"], KeyNotAllowedException);

  AnyType copy_int32 = int32_type;
  EXPECT_EQ(copy_int32, SignedInteger32);
  EXPECT_NE(copy_int32, UnsignedInteger32);
  EXPECT_FALSE(IsEmptyType(copy_int32));
  EXPECT_FALSE(IsStructType(copy_int32));
  EXPECT_FALSE(IsArrayType(copy_int32));
  EXPECT_TRUE(IsScalarType(copy_int32));
  EXPECT_EQ(copy_int32.GetTypeCode(), TypeCode::Int32);
  EXPECT_EQ(copy_int32.GetTypeName(), INT32_TYPE_NAME);
  EXPECT_THROW(copy_int32["field"], KeyNotAllowedException);
}

TEST(AnyTypeTest, UnsignedInteger32)
{
  AnyType uint32_type{TypeCode::UInt32};
  EXPECT_EQ(uint32_type, UnsignedInteger32);
  EXPECT_NE(uint32_type, SignedInteger32);
  EXPECT_FALSE(IsEmptyType(uint32_type));
  EXPECT_FALSE(IsStructType(uint32_type));
  EXPECT_FALSE(IsArrayType(uint32_type));
  EXPECT_TRUE(IsScalarType(uint32_type));
  EXPECT_EQ(uint32_type.GetTypeCode(), TypeCode::UInt32);
  EXPECT_EQ(uint32_type.GetTypeName(), UINT32_TYPE_NAME);
  EXPECT_THROW(uint32_type["field"], KeyNotAllowedException);

  AnyType moved_uint32 = std::move(uint32_type);
  EXPECT_EQ(moved_uint32, UnsignedInteger32);
  EXPECT_NE(moved_uint32, SignedInteger32);
  EXPECT_TRUE(IsEmptyType(uint32_type)); // Moved from type is always empty
  EXPECT_EQ(uint32_type, EmptyType);
  EXPECT_FALSE(IsEmptyType(moved_uint32));
  EXPECT_FALSE(IsStructType(moved_uint32));
  EXPECT_FALSE(IsArrayType(moved_uint32));
  EXPECT_TRUE(IsScalarType(moved_uint32));
  EXPECT_EQ(moved_uint32.GetTypeCode(), TypeCode::UInt32);
  EXPECT_EQ(moved_uint32.GetTypeName(), UINT32_TYPE_NAME);
  EXPECT_THROW(moved_uint32["field"], KeyNotAllowedException);
}

TEST(AnyTypeTest, SignedInteger64)
{
  AnyType int64_type{TypeCode::Int64};
  EXPECT_EQ(int64_type, SignedInteger64);
  EXPECT_NE(int64_type, UnsignedInteger64);
  EXPECT_FALSE(IsEmptyType(int64_type));
  EXPECT_FALSE(IsStructType(int64_type));
  EXPECT_FALSE(IsArrayType(int64_type));
  EXPECT_TRUE(IsScalarType(int64_type));
  EXPECT_EQ(int64_type.GetTypeCode(), TypeCode::Int64);
  EXPECT_EQ(int64_type.GetTypeName(), INT64_TYPE_NAME);
  EXPECT_THROW(int64_type["field"], KeyNotAllowedException);

  AnyType copy_int64 = int64_type;
  EXPECT_EQ(copy_int64, SignedInteger64);
  EXPECT_NE(copy_int64, UnsignedInteger64);
  EXPECT_FALSE(IsEmptyType(copy_int64));
  EXPECT_FALSE(IsStructType(copy_int64));
  EXPECT_FALSE(IsArrayType(copy_int64));
  EXPECT_TRUE(IsScalarType(copy_int64));
  EXPECT_EQ(copy_int64.GetTypeCode(), TypeCode::Int64);
  EXPECT_EQ(copy_int64.GetTypeName(), INT64_TYPE_NAME);
  EXPECT_THROW(copy_int64["field"], KeyNotAllowedException);
}

TEST(AnyTypeTest, UnsignedInteger64)
{
  AnyType uint64_type{TypeCode::UInt64};
  EXPECT_EQ(uint64_type, UnsignedInteger64);
  EXPECT_NE(uint64_type, SignedInteger64);
  EXPECT_FALSE(IsEmptyType(uint64_type));
  EXPECT_FALSE(IsStructType(uint64_type));
  EXPECT_FALSE(IsArrayType(uint64_type));
  EXPECT_TRUE(IsScalarType(uint64_type));
  EXPECT_EQ(uint64_type.GetTypeCode(), TypeCode::UInt64);
  EXPECT_EQ(uint64_type.GetTypeName(), UINT64_TYPE_NAME);
  EXPECT_THROW(uint64_type["field"], KeyNotAllowedException);

  AnyType moved_uint64 = std::move(uint64_type);
  EXPECT_EQ(moved_uint64, UnsignedInteger64);
  EXPECT_NE(moved_uint64, SignedInteger64);
  EXPECT_TRUE(IsEmptyType(uint64_type)); // Moved from type is always empty
  EXPECT_EQ(uint64_type, EmptyType);
  EXPECT_FALSE(IsEmptyType(moved_uint64));
  EXPECT_FALSE(IsStructType(moved_uint64));
  EXPECT_FALSE(IsArrayType(moved_uint64));
  EXPECT_TRUE(IsScalarType(moved_uint64));
  EXPECT_EQ(moved_uint64.GetTypeCode(), TypeCode::UInt64);
  EXPECT_EQ(moved_uint64.GetTypeName(), UINT64_TYPE_NAME);
  EXPECT_THROW(moved_uint64["field"], KeyNotAllowedException);
}

TEST(AnyTypeTest, Float32)
{
  AnyType float32_type{TypeCode::Float32};
  EXPECT_EQ(float32_type, Float32);
  EXPECT_NE(float32_type, SignedInteger64);
  EXPECT_FALSE(IsEmptyType(float32_type));
  EXPECT_FALSE(IsStructType(float32_type));
  EXPECT_FALSE(IsArrayType(float32_type));
  EXPECT_TRUE(IsScalarType(float32_type));
  EXPECT_EQ(float32_type.GetTypeCode(), TypeCode::Float32);
  EXPECT_EQ(float32_type.GetTypeName(), FLOAT32_TYPE_NAME);
  EXPECT_THROW(float32_type["field"], KeyNotAllowedException);

  AnyType moved_float32 = std::move(float32_type);
  EXPECT_EQ(moved_float32, Float32);
  EXPECT_NE(moved_float32, SignedInteger64);
  EXPECT_TRUE(IsEmptyType(float32_type)); // Moved from type is always empty
  EXPECT_EQ(float32_type, EmptyType);
  EXPECT_FALSE(IsEmptyType(moved_float32));
  EXPECT_FALSE(IsStructType(moved_float32));
  EXPECT_FALSE(IsArrayType(moved_float32));
  EXPECT_TRUE(IsScalarType(moved_float32));
  EXPECT_EQ(moved_float32.GetTypeCode(), TypeCode::Float32);
  EXPECT_EQ(moved_float32.GetTypeName(), FLOAT32_TYPE_NAME);
  EXPECT_THROW(moved_float32["field"], KeyNotAllowedException);
}

TEST(AnyTypeTest, Float64)
{
  AnyType float64_type{TypeCode::Float64};
  EXPECT_EQ(float64_type, Float64);
  EXPECT_NE(float64_type, SignedInteger64);
  EXPECT_FALSE(IsEmptyType(float64_type));
  EXPECT_FALSE(IsStructType(float64_type));
  EXPECT_FALSE(IsArrayType(float64_type));
  EXPECT_TRUE(IsScalarType(float64_type));
  EXPECT_EQ(float64_type.GetTypeCode(), TypeCode::Float64);
  EXPECT_EQ(float64_type.GetTypeName(), FLOAT64_TYPE_NAME);
  EXPECT_THROW(float64_type["field"], KeyNotAllowedException);

  AnyType moved_float64 = std::move(float64_type);
  EXPECT_EQ(moved_float64, Float64);
  EXPECT_NE(moved_float64, SignedInteger64);
  EXPECT_TRUE(IsEmptyType(float64_type)); // Moved from type is always empty
  EXPECT_EQ(float64_type, EmptyType);
  EXPECT_FALSE(IsEmptyType(moved_float64));
  EXPECT_FALSE(IsStructType(moved_float64));
  EXPECT_FALSE(IsArrayType(moved_float64));
  EXPECT_TRUE(IsScalarType(moved_float64));
  EXPECT_EQ(moved_float64.GetTypeCode(), TypeCode::Float64);
  EXPECT_EQ(moved_float64.GetTypeName(), FLOAT64_TYPE_NAME);
  EXPECT_THROW(moved_float64["field"], KeyNotAllowedException);
}

TEST(AnyTypeTest, CopyConstruction)
{
  const std::string nested_name = "nested_struct";
  AnyType two_scalars{{
    {"signed", SignedInteger8},
    {"unsigned", UnsignedInteger8}
  }};
  AnyType nested_type{{
    {"scalars", two_scalars},
    {"single", {
      {"first", SignedInteger8},
      {"second", SignedInteger8}
    }}
  }, nested_name};
  EXPECT_TRUE(IsStructType(nested_type));
  EXPECT_EQ(nested_type.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(nested_type.GetTypeName(), nested_name);

  AnyType copy = nested_type;
  EXPECT_EQ(copy, nested_type);
  EXPECT_TRUE(IsStructType(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(copy.GetTypeName(), nested_name);
  EXPECT_TRUE(copy.HasMember("scalars"));
  EXPECT_TRUE(copy.HasMember("single"));
  EXPECT_FALSE(copy.HasMember("index"));

  copy.AddMember("index", UnsignedInteger64);
  EXPECT_NE(copy, nested_type);
  EXPECT_TRUE(IsStructType(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(copy.GetTypeName(), nested_name);
  EXPECT_TRUE(copy.HasMember("scalars"));
  EXPECT_TRUE(copy.HasMember("single"));
  EXPECT_TRUE(copy.HasMember("index"));
}

TEST(AnyTypeTest, CopyAssignment)
{
  const std::string nested_name = "nested_struct";
  AnyType two_scalars{{
    {"signed", SignedInteger8},
    {"unsigned", UnsignedInteger8}
  }};
  AnyType nested_type{{
    {"scalars", two_scalars},
    {"single", {
      {"first", SignedInteger8},
      {"second", SignedInteger8}
    }}
  }, nested_name};
  EXPECT_TRUE(IsStructType(nested_type));
  EXPECT_EQ(nested_type.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(nested_type.GetTypeName(), nested_name);

  AnyType copy;
  copy = nested_type;
  EXPECT_EQ(copy, nested_type);
  EXPECT_TRUE(IsStructType(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(copy.GetTypeName(), nested_name);

  copy.AddMember("index", UnsignedInteger64);
  EXPECT_NE(copy, nested_type);
  EXPECT_TRUE(IsStructType(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(copy.GetTypeName(), nested_name);
}

TEST(AnyTypeTest, MoveConstruction)
{
  const std::string nested_name = "nested_struct";
  AnyType two_scalars{{
    {"signed", SignedInteger8},
    {"unsigned", UnsignedInteger8}
  }};
  AnyType nested_type{{
    {"scalars", two_scalars},
    {"single", {
      {"first", SignedInteger8},
      {"second", SignedInteger8}
    }}
  }, nested_name};
  EXPECT_TRUE(IsStructType(nested_type));
  EXPECT_EQ(nested_type.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(nested_type.GetTypeName(), nested_name);

  AnyType moved = std::move(nested_type);
  EXPECT_NE(moved, nested_type);
  EXPECT_TRUE(IsEmptyType(nested_type));
  EXPECT_TRUE(IsStructType(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(moved.GetTypeName(), nested_name);
  EXPECT_TRUE(moved.HasMember("scalars"));
  EXPECT_TRUE(moved.HasMember("single"));
  EXPECT_FALSE(moved.HasMember("index"));

  moved.AddMember("index", UnsignedInteger64);
  EXPECT_NE(moved, nested_type);
  EXPECT_TRUE(IsStructType(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(moved.GetTypeName(), nested_name);
  EXPECT_TRUE(moved.HasMember("scalars"));
  EXPECT_TRUE(moved.HasMember("single"));
  EXPECT_TRUE(moved.HasMember("index"));
}

TEST(AnyTypeTest, MoveAssignment)
{
  const std::string nested_name = "nested_struct";
  AnyType two_scalars{{
    {"signed", SignedInteger8},
    {"unsigned", UnsignedInteger8}
  }};
  AnyType nested_type{{
    {"scalars", two_scalars},
    {"single", {
      {"first", SignedInteger8},
      {"second", SignedInteger8}
    }}
  }, nested_name};
  EXPECT_TRUE(IsStructType(nested_type));
  EXPECT_EQ(nested_type.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(nested_type.GetTypeName(), nested_name);

  AnyType moved;
  moved = std::move(nested_type);
  EXPECT_NE(moved, nested_type);
  EXPECT_TRUE(IsEmptyType(nested_type));
  EXPECT_TRUE(IsStructType(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(moved.GetTypeName(), nested_name);
  EXPECT_TRUE(moved.HasMember("scalars"));
  EXPECT_TRUE(moved.HasMember("single"));
  EXPECT_FALSE(moved.HasMember("index"));

  moved.AddMember("index", UnsignedInteger64);
  EXPECT_NE(moved, nested_type);
  EXPECT_TRUE(IsStructType(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(moved.GetTypeName(), nested_name);
  EXPECT_TRUE(moved.HasMember("scalars"));
  EXPECT_TRUE(moved.HasMember("single"));
  EXPECT_TRUE(moved.HasMember("index"));
}

TEST(AnyTypeTest, MemberAccess)
{
  const std::string nested_name = "nested_struct";
  AnyType two_scalars{{
    {"signed", SignedInteger8},
    {"unsigned", UnsignedInteger8}
  }};
  AnyType nested_type = (EmptyStructType(nested_name)
                            .AddMember("scalars", two_scalars)
                            .AddMember("single", EmptyStructType()
                                .AddMember("first", SignedInteger8)
                                .AddMember("second", SignedInteger8)));
  EXPECT_TRUE(IsStructType(nested_type));
  EXPECT_EQ(nested_type.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(nested_type.GetTypeName(), nested_name);
  EXPECT_TRUE(nested_type.HasMember("scalars"));
  EXPECT_TRUE(nested_type.HasMember("single"));
  EXPECT_FALSE(nested_type.HasMember("index"));
  auto member_fields = nested_type.MemberNames();
  EXPECT_EQ(member_fields.size(), 2);
  EXPECT_EQ(nested_type.NumberOfMembers(), 2);
  EXPECT_EQ(member_fields[0], "scalars");
  EXPECT_EQ(member_fields[1], "single");
  nested_type.AddMember("index", UnsignedInteger64);
  EXPECT_TRUE(nested_type.HasMember("index"));
  member_fields = nested_type.MemberNames();
  EXPECT_EQ(member_fields.size(), 3);
  EXPECT_EQ(nested_type.NumberOfMembers(), 3);
  EXPECT_EQ(member_fields[0], "scalars");
  EXPECT_EQ(member_fields[1], "single");
  EXPECT_EQ(member_fields[2], "index");

  // test presence of composite field indices
  EXPECT_TRUE(nested_type.HasMember("scalars.signed"));
  EXPECT_FALSE(nested_type.HasMember("scalars.unknown"));
}
