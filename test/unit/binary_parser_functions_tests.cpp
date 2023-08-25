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

#include <sup/dto/parse/binary_parser_functions.h>
#include <sup/dto/serialize/binary_serialization_functions.h>
#include <sup/dto/serialize/binary_tokens.h>

#include <sup/dto/anyvalue.h>

using namespace sup::dto;

class BinaryParserFunctionsTest : public ::testing::Test
{
protected:
  BinaryParserFunctionsTest();
  virtual ~BinaryParserFunctionsTest();
};

TEST_F(BinaryParserFunctionsTest, Booleans)
{
  {
    // false
    AnyValue val = false;
    std::vector<uint8> representation;
    EXPECT_NO_THROW(AppendBinaryScalar(representation, val));
    // token byte makes the total size larger by 1
    ASSERT_EQ(representation.size(), 2);
    EXPECT_EQ(representation[0], BOOL_TOKEN);
    auto it = representation.begin() + 1;
    auto read_back = ParseBinaryScalarT<sup::dto::boolean>(it, representation.end());
    EXPECT_EQ(read_back, false);
    EXPECT_EQ(it, representation.end());
  }
  {
    // false
    AnyValue val = true;
    std::vector<uint8> representation;
    EXPECT_NO_THROW(AppendBinaryScalar(representation, val));
    // token byte makes the total size larger by 1
    ASSERT_EQ(representation.size(), 2);
    EXPECT_EQ(representation[0], BOOL_TOKEN);
    auto it = representation.begin() + 1;
    auto read_back = ParseBinaryScalarT<sup::dto::boolean>(it, representation.end());
    EXPECT_EQ(read_back, true);
    EXPECT_EQ(it, representation.end());
  }
}

TEST_F(BinaryParserFunctionsTest, Integers)
{
  {
    // Int8
    AnyValue val{SignedInteger8Type, -1};
    std::vector<uint8> representation;
    EXPECT_NO_THROW(AppendBinaryScalar(representation, val));
    // token byte makes the total size larger by 1
    ASSERT_EQ(representation.size(), 2);
    EXPECT_EQ(representation[0], INT8_TOKEN);
    auto it = representation.begin() + 1;
    auto read_back = ParseBinaryScalarT<sup::dto::int8>(it, representation.end());
    EXPECT_EQ(read_back, -1);
    EXPECT_EQ(it, representation.end());
  }
  {
    // UInt16
    uint16 int_value = 42;
    AnyValue val = int_value;
    std::vector<uint8> representation;
    EXPECT_NO_THROW(AppendBinaryScalar(representation, val));
    // token byte makes the total size larger by 1
    ASSERT_EQ(representation.size(), 3);
    EXPECT_EQ(representation[0], UINT16_TOKEN);
    auto it = representation.begin() + 1;
    auto read_back = ParseBinaryScalarT<sup::dto::uint16>(it, representation.end());
    EXPECT_EQ(read_back, int_value);
    EXPECT_EQ(it, representation.end());
  }
  {
    // Int32
    int32 int_value = -8;
    AnyValue val = int_value;
    std::vector<uint8> representation;
    EXPECT_NO_THROW(AppendBinaryScalar(representation, val));
    // token byte makes the total size larger by 1
    ASSERT_EQ(representation.size(), 5);
    EXPECT_EQ(representation[0], INT32_TOKEN);
    auto it = representation.begin() + 1;
    auto read_back = ParseBinaryScalarT<sup::dto::int32>(it, representation.end());
    EXPECT_EQ(read_back, int_value);
    EXPECT_EQ(it, representation.end());
  }
  {
    // UInt64
    uint64 int_value = 42;
    AnyValue val = int_value;
    std::vector<uint8> representation;
    EXPECT_NO_THROW(AppendBinaryScalar(representation, val));
    // token byte makes the total size larger by 1
    ASSERT_EQ(representation.size(), 9);
    EXPECT_EQ(representation[0], UINT64_TOKEN);
    auto it = representation.begin() + 1;
    auto read_back = ParseBinaryScalarT<sup::dto::uint64>(it, representation.end());
    EXPECT_EQ(read_back, int_value);
    EXPECT_EQ(it, representation.end());
  }
}

TEST_F(BinaryParserFunctionsTest, Floats)
{
  {
    // Float32
    float32 float_val = 3.14f;
    AnyValue val{Float32Type, float_val};
    std::vector<uint8> representation;
    EXPECT_NO_THROW(AppendBinaryScalar(representation, val));
    // token byte makes the total size larger by 1
    ASSERT_EQ(representation.size(), 5);
    EXPECT_EQ(representation[0], FLOAT32_TOKEN);
    auto it = representation.begin() + 1;
    auto read_back = ParseBinaryScalarT<sup::dto::float32>(it, representation.end());
    EXPECT_EQ(read_back, float_val);
    EXPECT_EQ(it, representation.end());
  }
  {
    // Float64
    float64 float_val = 3.14159;
    AnyValue val{Float64Type, float_val};
    std::vector<uint8> representation;
    EXPECT_NO_THROW(AppendBinaryScalar(representation, val));
    // token byte makes the total size larger by 1
    ASSERT_EQ(representation.size(), 9);
    EXPECT_EQ(representation[0], FLOAT64_TOKEN);
    auto it = representation.begin() + 1;
    auto read_back = ParseBinaryScalarT<sup::dto::float64>(it, representation.end());
    EXPECT_EQ(read_back, float_val);
    EXPECT_EQ(it, representation.end());
  }
}

TEST_F(BinaryParserFunctionsTest, Strings)
{
  {
    // non empty string anyvalue
    std::string str = "non_empty";
    AnyValue val = str;
    std::vector<uint8> representation;
    EXPECT_NO_THROW(AppendBinaryScalar(representation, val));
    // string token and size byte make the total size larger by 2
    ASSERT_EQ(representation.size(), str.size() + 2);
    EXPECT_EQ(representation[0], STRING_TOKEN);
    auto it = representation.begin() + 1;
    auto read_back = ParseBinaryString(it, representation.end());
    EXPECT_EQ(read_back, str);
    EXPECT_EQ(it, representation.end());
  }
  {
    // empty string anyvalue
    std::string str = "";
    AnyValue val = str;
    std::vector<uint8> representation;
    EXPECT_NO_THROW(AppendBinaryScalar(representation, val));
    // string token and size byte make the total size larger by 2
    ASSERT_EQ(representation.size(), 2);
    EXPECT_EQ(representation[0], STRING_TOKEN);
    auto it = representation.begin() + 1;
    auto read_back = ParseBinaryString(it, representation.end());
    EXPECT_EQ(read_back, str);
    EXPECT_EQ(it, representation.end());
  }
  {
    // non empty string
    std::string str = "non_empty";
    std::vector<uint8> representation;
    EXPECT_NO_THROW(AppendBinaryString(representation, str));
    // string token and size byte make the total size larger by 2
    ASSERT_EQ(representation.size(), str.size() + 2);
    EXPECT_EQ(representation[0], STRING_TOKEN);
    auto it = representation.begin() + 1;
    auto read_back = ParseBinaryString(it, representation.end());
    EXPECT_EQ(read_back, str);
    EXPECT_EQ(it, representation.end());
  }
  {
    // empty string
    std::string str = "";
    std::vector<uint8> representation;
    EXPECT_NO_THROW(AppendBinaryString(representation, str));
    // string token and size byte make the total size larger by 2
    ASSERT_EQ(representation.size(), 2);
    EXPECT_EQ(representation[0], STRING_TOKEN);
    auto it = representation.begin() + 1;
    auto read_back = ParseBinaryString(it, representation.end());
    EXPECT_EQ(read_back, str);
    EXPECT_EQ(it, representation.end());
  }
  {
    // long string (size = SHORT_STRING_LENGTH_LIMIT)
    std::string str(SHORT_STRING_LENGTH_LIMIT, 'x');
    std::vector<uint8> representation;
    EXPECT_NO_THROW(AppendBinaryString(representation, str));
    // string token and size bytes make the total size larger by 2 + sizeof(std::size_t)
    ASSERT_EQ(representation.size(), str.size() + 2 + sizeof(std::size_t));
    EXPECT_EQ(representation[0], STRING_TOKEN);
    auto it = representation.begin() + 1;
    auto read_back = ParseBinaryString(it, representation.end());
    EXPECT_EQ(read_back, str);
    EXPECT_EQ(it, representation.end());
  }
  {
    // long string (size > SHORT_STRING_LENGTH_LIMIT)
    std::string str(10 * SHORT_STRING_LENGTH_LIMIT, 'x');
    std::vector<uint8> representation;
    EXPECT_NO_THROW(AppendBinaryString(representation, str));
    // string token and size bytes make the total size larger by 2 + sizeof(std::size_t)
    ASSERT_EQ(representation.size(), str.size() + 2 + sizeof(std::size_t));
    EXPECT_EQ(representation[0], STRING_TOKEN);
    auto it = representation.begin() + 1;
    auto read_back = ParseBinaryString(it, representation.end());
    EXPECT_EQ(read_back, str);
    EXPECT_EQ(it, representation.end());
  }
}

BinaryParserFunctionsTest::BinaryParserFunctionsTest() = default;

BinaryParserFunctionsTest::~BinaryParserFunctionsTest() = default;
