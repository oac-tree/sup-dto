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

#include <sup/dto/low_level/binary_serialization_functions.h>
#include <sup/dto/serialize/binary_tokens.h>
#include <sup/dto/anyvalue.h>

using namespace sup::dto;

class BinarySerializationFunctionsTest : public ::testing::Test
{
protected:
  BinarySerializationFunctionsTest();
  virtual ~BinarySerializationFunctionsTest();
};

TEST_F(BinarySerializationFunctionsTest, Booleans)
{
  {
    // false
    AnyValue val = false;
    std::vector<uint8> representation;
    EXPECT_NO_THROW(AppendBinaryScalar(representation, val));
    ASSERT_EQ(representation.size(), 1);
    EXPECT_EQ(representation[0], 0);
  }
  {
    // false
    AnyValue val = true;
    std::vector<uint8> representation;
    EXPECT_NO_THROW(AppendBinaryScalar(representation, val));
    ASSERT_EQ(representation.size(), 1);
    EXPECT_EQ(representation[0], 1);
  }
}

TEST_F(BinarySerializationFunctionsTest, Integers)
{
  {
    // Int8
    AnyValue val{SignedInteger8Type, -1};
    std::vector<uint8> representation;
    EXPECT_NO_THROW(AppendBinaryScalar(representation, val));
    ASSERT_EQ(representation.size(), 1);
    auto byte_val = static_cast<uint8>(val.As<int8>());
    EXPECT_EQ(representation[0], byte_val);
  }
  {
    // UInt16
    uint16 int_value = 42;
    AnyValue val = int_value;
    std::vector<uint8> representation;
    EXPECT_NO_THROW(AppendBinaryScalar(representation, val));
    ASSERT_EQ(representation.size(), 2);
    uint16 readback_val;
    std::memcpy(&readback_val, representation.data(), 2);
    EXPECT_EQ(int_value, readback_val);
    // little endian tested, as current implementation depends on it
    EXPECT_EQ(representation[0], val.As<uint8>());
  }
  {
    // Int32
    int32 int_value = -8;
    AnyValue val = int_value;
    std::vector<uint8> representation;
    EXPECT_NO_THROW(AppendBinaryScalar(representation, val));
    ASSERT_EQ(representation.size(), 4);
    int32 readback_val;
    std::memcpy(&readback_val, representation.data(), 4);
    EXPECT_EQ(int_value, readback_val);
    // little endian tested, as current implementation depends on it
    auto byte_val = static_cast<uint8>(val.As<int8>());
    EXPECT_EQ(representation[0], byte_val);
  }
  {
    // UInt64
    uint64 int_value = 42;
    AnyValue val = int_value;
    std::vector<uint8> representation;
    EXPECT_NO_THROW(AppendBinaryScalar(representation, val));
    ASSERT_EQ(representation.size(), 8);
    uint64 readback_val;
    std::memcpy(&readback_val, representation.data(), 8);
    EXPECT_EQ(int_value, readback_val);
    // little endian tested, as current implementation depends on it
    EXPECT_EQ(representation[0], val.As<uint8>());
  }
}

TEST_F(BinarySerializationFunctionsTest, Floats)
{
  {
    // Float32
    float32 float_val = 3.14f;
    AnyValue val{Float32Type, float_val};
    std::vector<uint8> representation;
    EXPECT_NO_THROW(AppendBinaryScalar(representation, val));
    ASSERT_EQ(representation.size(), 4);
    float32 readback_val;
    std::memcpy(&readback_val, representation.data(), 4);
    EXPECT_EQ(float_val, readback_val);
  }
  {
    // Float64
    float64 float_val = 3.14159;
    AnyValue val{Float64Type, float_val};
    std::vector<uint8> representation;
    EXPECT_NO_THROW(AppendBinaryScalar(representation, val));
    ASSERT_EQ(representation.size(), 8);
    float64 readback_val;
    std::memcpy(&readback_val, representation.data(), 8);
    EXPECT_EQ(float_val, readback_val);
  }
}

TEST_F(BinarySerializationFunctionsTest, Strings)
{
  {
    // non empty string anyvalue
    std::string str = "non_empty";
    AnyValue val = str;
    std::vector<uint8> representation;
    EXPECT_NO_THROW(AppendBinaryScalar(representation, val));
    // string size byte makes the total size larger by 1
    ASSERT_EQ(representation.size(), str.size() + 1);
    EXPECT_EQ(representation[0], str.size());
  }
  {
    // empty string anyvalue
    std::string str = "";
    AnyValue val = str;
    std::vector<uint8> representation;
    EXPECT_NO_THROW(AppendBinaryScalar(representation, val));
    // string size byte make thes total size larger by 1
    ASSERT_EQ(representation.size(), 1);
    EXPECT_EQ(representation[0], str.size());
  }
  {
    // non empty string
    std::string str = "non_empty";
    std::vector<uint8> representation;
    EXPECT_NO_THROW(AppendBinaryString(representation, str));
    // string token and size byte make the total size larger by 2
    ASSERT_EQ(representation.size(), str.size() + 2);
    EXPECT_EQ(representation[0], STRING_TOKEN);
    EXPECT_EQ(representation[1], str.size());
  }
  {
    // empty string
    std::string str = "";
    std::vector<uint8> representation;
    EXPECT_NO_THROW(AppendBinaryString(representation, str));
    // string token and size byte make the total size larger by 2
    ASSERT_EQ(representation.size(), 2);
    EXPECT_EQ(representation[0], STRING_TOKEN);
    EXPECT_EQ(representation[1], str.size());
  }
  {
    // long string (size = SHORT_STRING_LENGTH_LIMIT)
    std::string str(SHORT_SIZE_LIMIT, 'x');
    std::vector<uint8> representation;
    EXPECT_NO_THROW(AppendBinaryString(representation, str));
    // string token and size bytes make the total size larger by 2 + sizeof(std::size_t)
    ASSERT_EQ(representation.size(), str.size() + 2 + sizeof(std::size_t));
    EXPECT_EQ(representation[0], STRING_TOKEN);
    EXPECT_EQ(representation[1], LONG_SIZE_TOKEN);
    std::size_t readback_size;
    std::memcpy(&readback_size, representation.data() + 2, sizeof(std::size_t));
    EXPECT_EQ(readback_size, str.size());
  }
  {
    // long string (size > SHORT_STRING_LENGTH_LIMIT)
    std::string str(10 * SHORT_SIZE_LIMIT, 'x');
    std::vector<uint8> representation;
    EXPECT_NO_THROW(AppendBinaryString(representation, str));
    // string token and size bytes make the total size larger by 2 + sizeof(std::size_t)
    ASSERT_EQ(representation.size(), str.size() + 2 + sizeof(std::size_t));
    EXPECT_EQ(representation[0], STRING_TOKEN);
    EXPECT_EQ(representation[1], LONG_SIZE_TOKEN);
    std::size_t readback_size;
    std::memcpy(&readback_size, representation.data() + 2, sizeof(std::size_t));
    EXPECT_EQ(readback_size, str.size());
  }
}

TEST_F(BinarySerializationFunctionsTest, NonScalars)
{
  std::vector<uint8> representation;
  {
    // empty type
    AnyValue val;
    EXPECT_THROW(AppendBinaryScalar(representation, val), SerializeException);
    EXPECT_EQ(representation.size(), 0);
  }
  {
    // struct type
    AnyValue val({
      {"value", 1}
    });
    EXPECT_THROW(AppendBinaryScalar(representation, val), SerializeException);
    EXPECT_EQ(representation.size(), 0);
  }
  {
    // array type
    AnyValue val(2, SignedInteger16Type);
    EXPECT_THROW(AppendBinaryScalar(representation, val), SerializeException);
    EXPECT_EQ(representation.size(), 0);
  }
}

BinarySerializationFunctionsTest::BinarySerializationFunctionsTest() = default;

BinarySerializationFunctionsTest::~BinarySerializationFunctionsTest() = default;
