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
 * Copyright (c) : 2010-2025 ITER Organization,
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
#include <sup/dto/anytype_helper.h>
#include <sup/dto/serialize/binary_tokens.h>

using namespace sup::dto;

class BinaryTypeSerializationTest : public ::testing::Test
{
protected:
  BinaryTypeSerializationTest();
  virtual ~BinaryTypeSerializationTest();
};

TEST_F(BinaryTypeSerializationTest, Booleans)
{
  AnyType anytype = BooleanType;
  auto representation = AnyTypeToBinary(anytype);
  ASSERT_EQ(representation.size(), 2);
  EXPECT_EQ(representation[0], ANYTYPE_TOKEN);
  EXPECT_EQ(representation[1], BOOL_TOKEN);
}

TEST_F(BinaryTypeSerializationTest, Integers)
{
  {
    // Int8
    AnyType anytype = SignedInteger8Type;
    auto representation = AnyTypeToBinary(anytype);
    ASSERT_EQ(representation.size(), 2);
    EXPECT_EQ(representation[0], ANYTYPE_TOKEN);
    EXPECT_EQ(representation[1], INT8_TOKEN);
  }
  {
    // UInt8
    AnyType anytype = UnsignedInteger8Type;
    auto representation = AnyTypeToBinary(anytype);
    ASSERT_EQ(representation.size(), 2);
    EXPECT_EQ(representation[0], ANYTYPE_TOKEN);
    EXPECT_EQ(representation[1], UINT8_TOKEN);
  }
  {
    // Int16
    AnyType anytype = SignedInteger16Type;
    auto representation = AnyTypeToBinary(anytype);
    ASSERT_EQ(representation.size(), 2);
    EXPECT_EQ(representation[0], ANYTYPE_TOKEN);
    EXPECT_EQ(representation[1], INT16_TOKEN);
  }
  {
    // UInt16
    AnyType anytype = UnsignedInteger16Type;
    auto representation = AnyTypeToBinary(anytype);
    ASSERT_EQ(representation.size(), 2);
    EXPECT_EQ(representation[0], ANYTYPE_TOKEN);
    EXPECT_EQ(representation[1], UINT16_TOKEN);
  }
  {
    // Int32
    AnyType anytype = SignedInteger32Type;
    auto representation = AnyTypeToBinary(anytype);
    ASSERT_EQ(representation.size(), 2);
    EXPECT_EQ(representation[0], ANYTYPE_TOKEN);
    EXPECT_EQ(representation[1], INT32_TOKEN);
  }
  {
    // UInt32
    AnyType anytype = UnsignedInteger32Type;
    auto representation = AnyTypeToBinary(anytype);
    ASSERT_EQ(representation.size(), 2);
    EXPECT_EQ(representation[0], ANYTYPE_TOKEN);
    EXPECT_EQ(representation[1], UINT32_TOKEN);
  }
  {
    // Int64
    AnyType anytype = SignedInteger64Type;
    auto representation = AnyTypeToBinary(anytype);
    ASSERT_EQ(representation.size(), 2);
    EXPECT_EQ(representation[0], ANYTYPE_TOKEN);
    EXPECT_EQ(representation[1], INT64_TOKEN);
  }
  {
    // UInt64
    AnyType anytype = UnsignedInteger64Type;
    auto representation = AnyTypeToBinary(anytype);
    ASSERT_EQ(representation.size(), 2);
    EXPECT_EQ(representation[0], ANYTYPE_TOKEN);
    EXPECT_EQ(representation[1], UINT64_TOKEN);
  }
}

TEST_F(BinaryTypeSerializationTest, Floats)
{
  {
    // Float32
    AnyType anytype = Float32Type;
    auto representation = AnyTypeToBinary(anytype);
    ASSERT_EQ(representation.size(), 2);
    EXPECT_EQ(representation[0], ANYTYPE_TOKEN);
    EXPECT_EQ(representation[1], FLOAT32_TOKEN);
  }
  {
    // Float64
    AnyType anytype = Float64Type;
    auto representation = AnyTypeToBinary(anytype);
    ASSERT_EQ(representation.size(), 2);
    EXPECT_EQ(representation[0], ANYTYPE_TOKEN);
    EXPECT_EQ(representation[1], FLOAT64_TOKEN);
  }
}

TEST_F(BinaryTypeSerializationTest, Strings)
{
  AnyType anytype = StringType;
  auto representation = AnyTypeToBinary(anytype);
  ASSERT_EQ(representation.size(), 2);
  EXPECT_EQ(representation[0], ANYTYPE_TOKEN);
  EXPECT_EQ(representation[1], STRING_TOKEN);
}

BinaryTypeSerializationTest::BinaryTypeSerializationTest() = default;

BinaryTypeSerializationTest::~BinaryTypeSerializationTest() = default;
