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
  EXPECT_TRUE(IsEmptyType(empty_type));
  EXPECT_FALSE(IsStructType(empty_type));
  EXPECT_FALSE(IsArrayType(empty_type));
  EXPECT_FALSE(IsScalarType(empty_type));
  EXPECT_EQ(empty_type.GetTypeCode(), TypeCode::Empty);
  EXPECT_EQ(empty_type.GetTypeName(), EMPTY_TYPE_NAME);
  EXPECT_THROW(empty_type["field"], std::out_of_range);

  const AnyType copy = empty_type;
  EXPECT_TRUE(IsEmptyType(copy));
  EXPECT_FALSE(IsStructType(copy));
  EXPECT_FALSE(IsArrayType(copy));
  EXPECT_FALSE(IsScalarType(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Empty);
  EXPECT_EQ(copy.GetTypeName(), EMPTY_TYPE_NAME);
  EXPECT_THROW(copy["field"], std::out_of_range);

  AnyType moved = std::move(empty_type);
  EXPECT_TRUE(IsEmptyType(empty_type)); // Moved from type is always empty
  EXPECT_TRUE(IsEmptyType(moved));
  EXPECT_FALSE(IsStructType(moved));
  EXPECT_FALSE(IsArrayType(moved));
  EXPECT_FALSE(IsScalarType(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Empty);
  EXPECT_EQ(moved.GetTypeName(), EMPTY_TYPE_NAME);
  EXPECT_THROW(moved["field"], std::out_of_range);
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
  EXPECT_THROW(two_scalars["unknownfield"], std::out_of_range);
}

TEST_F(AnyTypeTest, ScalarTypes)
{
  AnyType int8_type{TypeCode::Int8};
  EXPECT_FALSE(IsEmptyType(int8_type));
  EXPECT_FALSE(IsStructType(int8_type));
  EXPECT_FALSE(IsArrayType(int8_type));
  EXPECT_TRUE(IsScalarType(int8_type));
  EXPECT_EQ(int8_type.GetTypeCode(), TypeCode::Int8);
  EXPECT_EQ(int8_type.GetTypeName(), INT8_TYPE_NAME);
  EXPECT_THROW(int8_type["field"], std::out_of_range);

  AnyType uint8_type{TypeCode::UInt8};
  EXPECT_FALSE(IsEmptyType(uint8_type));
  EXPECT_FALSE(IsStructType(uint8_type));
  EXPECT_FALSE(IsArrayType(uint8_type));
  EXPECT_TRUE(IsScalarType(uint8_type));
  EXPECT_EQ(uint8_type.GetTypeCode(), TypeCode::UInt8);
  EXPECT_EQ(uint8_type.GetTypeName(), UINT8_TYPE_NAME);
  EXPECT_THROW(uint8_type["field"], std::out_of_range);

  AnyType copy_int8 = int8_type;
  EXPECT_FALSE(IsEmptyType(copy_int8));
  EXPECT_FALSE(IsStructType(copy_int8));
  EXPECT_FALSE(IsArrayType(copy_int8));
  EXPECT_TRUE(IsScalarType(copy_int8));
  EXPECT_EQ(copy_int8.GetTypeCode(), TypeCode::Int8);
  EXPECT_EQ(copy_int8.GetTypeName(), INT8_TYPE_NAME);
  EXPECT_THROW(copy_int8["field"], std::out_of_range);

  AnyType moved_uint8 = std::move(uint8_type);
  EXPECT_TRUE(IsEmptyType(uint8_type)); // Moved from type is always empty
  EXPECT_FALSE(IsEmptyType(moved_uint8));
  EXPECT_FALSE(IsStructType(moved_uint8));
  EXPECT_FALSE(IsArrayType(moved_uint8));
  EXPECT_TRUE(IsScalarType(moved_uint8));
  EXPECT_EQ(moved_uint8.GetTypeCode(), TypeCode::UInt8);
  EXPECT_EQ(moved_uint8.GetTypeName(), UINT8_TYPE_NAME);
  EXPECT_THROW(moved_uint8["field"], std::out_of_range);
}

AnyTypeTest::AnyTypeTest() = default;

AnyTypeTest::~AnyTypeTest() = default;
