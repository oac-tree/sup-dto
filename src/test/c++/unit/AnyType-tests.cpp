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

class AnyTypeTest : public ::testing::Test
{
protected:
  AnyTypeTest();
  virtual ~AnyTypeTest();
};

TEST_F(AnyTypeTest, TypeCodes)
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

TEST_F(AnyTypeTest, EmptyType)
{
  AnyType empty_type{};
  EXPECT_EQ(empty_type, EmptyType);
  EXPECT_NE(empty_type, SignedInteger8);
  EXPECT_TRUE(IsEmptyType(empty_type));
  EXPECT_FALSE(IsStructType(empty_type));
  EXPECT_FALSE(IsArrayType(empty_type));
  EXPECT_FALSE(IsScalarType(empty_type));
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

TEST_F(AnyTypeTest, StructOfScalarType)
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

TEST_F(AnyTypeTest, StructOfStructType)
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

TEST_F(AnyTypeTest, ScalarTypes)
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

AnyTypeTest::AnyTypeTest() = default;

AnyTypeTest::~AnyTypeTest() = default;
