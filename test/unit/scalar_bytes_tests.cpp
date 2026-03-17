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
 * Copyright (c) : 2010-2026 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 * SPDX-License-Identifier: MIT
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file LICENSE located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include <sup/dto/low_level/scalar_from_bytes.h>
#include <sup/dto/low_level/scalar_to_bytes.h>

#include <gtest/gtest.h>

#include <algorithm>

using namespace sup::dto;

namespace
{
inline bool IsLittleEndian()
{
  sup::dto::uint32 val = 1U;
  return *(sup::dto::uint8*)std::addressof(val) == 1U;
}

std::vector<AnyValue> GetTestScalars();
}  // unnamed namespace

class ScalarBytesTest : public ::testing::Test
{
protected:
  ScalarBytesTest();
  virtual ~ScalarBytesTest();
};

TEST_F(ScalarBytesTest, CheckToHostOrder)
{
  std::function<std::vector<uint8>(const AnyValue&)> SameAsHostOrder =
    IsLittleEndian() ? ScalarToLittleEndianOrder
                     : ScalarToNetwokOrder;
  std::function<std::vector<uint8>(const AnyValue&)> DifferentAsHostOrder =
    IsLittleEndian() ? ScalarToNetwokOrder
                     : ScalarToLittleEndianOrder;
  {
    // boolean
    AnyValue val{true};
    const auto host_bytes = ScalarToHostOrder(val);
    const auto same_as_host_bytes = SameAsHostOrder(val);
    const auto different_as_host_bytes = DifferentAsHostOrder(val);
    ASSERT_EQ(host_bytes.size(), same_as_host_bytes.size());
    ASSERT_EQ(host_bytes.size(), different_as_host_bytes.size());

    EXPECT_EQ(host_bytes, same_as_host_bytes);
    EXPECT_EQ(host_bytes, different_as_host_bytes);
  }
  {
    // char8
    AnyValue val{Character8Type, 42};
    const auto host_bytes = ScalarToHostOrder(val);
    const auto same_as_host_bytes = SameAsHostOrder(val);
    const auto different_as_host_bytes = DifferentAsHostOrder(val);
    ASSERT_EQ(host_bytes.size(), same_as_host_bytes.size());
    ASSERT_EQ(host_bytes.size(), different_as_host_bytes.size());

    EXPECT_EQ(host_bytes, same_as_host_bytes);
    EXPECT_EQ(host_bytes, different_as_host_bytes);
  }
  {
    // int8
    AnyValue val{SignedInteger8Type, 42};
    const auto host_bytes = ScalarToHostOrder(val);
    const auto same_as_host_bytes = SameAsHostOrder(val);
    const auto different_as_host_bytes = DifferentAsHostOrder(val);
    ASSERT_EQ(host_bytes.size(), same_as_host_bytes.size());
    ASSERT_EQ(host_bytes.size(), different_as_host_bytes.size());

    EXPECT_EQ(host_bytes, same_as_host_bytes);
    EXPECT_EQ(host_bytes, different_as_host_bytes);
  }
  {
    // uint8
    AnyValue val{UnsignedInteger8Type, 42};
    const auto host_bytes = ScalarToHostOrder(val);
    const auto same_as_host_bytes = SameAsHostOrder(val);
    const auto different_as_host_bytes = DifferentAsHostOrder(val);
    ASSERT_EQ(host_bytes.size(), same_as_host_bytes.size());
    ASSERT_EQ(host_bytes.size(), different_as_host_bytes.size());

    EXPECT_EQ(host_bytes, same_as_host_bytes);
    EXPECT_EQ(host_bytes, different_as_host_bytes);
  }
  {
    // int16
    AnyValue val{SignedInteger16Type, 0x1234};
    const auto host_bytes = ScalarToHostOrder(val);
    const auto same_as_host_bytes = SameAsHostOrder(val);
    auto different_as_host_bytes = DifferentAsHostOrder(val);
    ASSERT_EQ(host_bytes.size(), same_as_host_bytes.size());
    ASSERT_EQ(host_bytes.size(), different_as_host_bytes.size());

    EXPECT_EQ(host_bytes, same_as_host_bytes);
    EXPECT_NE(host_bytes, different_as_host_bytes);
    std::reverse(different_as_host_bytes.begin(), different_as_host_bytes.end());
    EXPECT_EQ(host_bytes, different_as_host_bytes);
  }
  {
    // uint16
    AnyValue val{UnsignedInteger16Type, 0x1234};
    const auto host_bytes = ScalarToHostOrder(val);
    const auto same_as_host_bytes = SameAsHostOrder(val);
    auto different_as_host_bytes = DifferentAsHostOrder(val);
    ASSERT_EQ(host_bytes.size(), same_as_host_bytes.size());
    ASSERT_EQ(host_bytes.size(), different_as_host_bytes.size());

    EXPECT_EQ(host_bytes, same_as_host_bytes);
    EXPECT_NE(host_bytes, different_as_host_bytes);
    std::reverse(different_as_host_bytes.begin(), different_as_host_bytes.end());
    EXPECT_EQ(host_bytes, different_as_host_bytes);
  }
  {
    // int32
    AnyValue val{SignedInteger32Type, 0x12345678};
    const auto host_bytes = ScalarToHostOrder(val);
    const auto same_as_host_bytes = SameAsHostOrder(val);
    auto different_as_host_bytes = DifferentAsHostOrder(val);
    ASSERT_EQ(host_bytes.size(), same_as_host_bytes.size());
    ASSERT_EQ(host_bytes.size(), different_as_host_bytes.size());

    EXPECT_EQ(host_bytes, same_as_host_bytes);
    EXPECT_NE(host_bytes, different_as_host_bytes);
    std::reverse(different_as_host_bytes.begin(), different_as_host_bytes.end());
    EXPECT_EQ(host_bytes, different_as_host_bytes);
  }
  {
    // uint32
    AnyValue val{UnsignedInteger32Type, 0x12345678};
    const auto host_bytes = ScalarToHostOrder(val);
    const auto same_as_host_bytes = SameAsHostOrder(val);
    auto different_as_host_bytes = DifferentAsHostOrder(val);
    ASSERT_EQ(host_bytes.size(), same_as_host_bytes.size());
    ASSERT_EQ(host_bytes.size(), different_as_host_bytes.size());

    EXPECT_EQ(host_bytes, same_as_host_bytes);
    EXPECT_NE(host_bytes, different_as_host_bytes);
    std::reverse(different_as_host_bytes.begin(), different_as_host_bytes.end());
    EXPECT_EQ(host_bytes, different_as_host_bytes);
  }
  {
    // int64
    AnyValue val{SignedInteger64Type, 0x1234567890ABCDEF};
    const auto host_bytes = ScalarToHostOrder(val);
    const auto same_as_host_bytes = SameAsHostOrder(val);
    auto different_as_host_bytes = DifferentAsHostOrder(val);
    ASSERT_EQ(host_bytes.size(), same_as_host_bytes.size());
    ASSERT_EQ(host_bytes.size(), different_as_host_bytes.size());

    EXPECT_EQ(host_bytes, same_as_host_bytes);
    EXPECT_NE(host_bytes, different_as_host_bytes);
    std::reverse(different_as_host_bytes.begin(), different_as_host_bytes.end());
    EXPECT_EQ(host_bytes, different_as_host_bytes);
  }
  {
    // uint64
    AnyValue val{UnsignedInteger64Type, 0x1234567890ABCDEF};
    const auto host_bytes = ScalarToHostOrder(val);
    const auto same_as_host_bytes = SameAsHostOrder(val);
    auto different_as_host_bytes = DifferentAsHostOrder(val);
    ASSERT_EQ(host_bytes.size(), same_as_host_bytes.size());
    ASSERT_EQ(host_bytes.size(), different_as_host_bytes.size());

    EXPECT_EQ(host_bytes, same_as_host_bytes);
    EXPECT_NE(host_bytes, different_as_host_bytes);
    std::reverse(different_as_host_bytes.begin(), different_as_host_bytes.end());
    EXPECT_EQ(host_bytes, different_as_host_bytes);
  }
  {
    // float32
    AnyValue val{Float32Type, 4.136e-15};
    const auto host_bytes = ScalarToHostOrder(val);
    const auto same_as_host_bytes = SameAsHostOrder(val);
    auto different_as_host_bytes = DifferentAsHostOrder(val);
    ASSERT_EQ(host_bytes.size(), same_as_host_bytes.size());
    ASSERT_EQ(host_bytes.size(), different_as_host_bytes.size());

    EXPECT_EQ(host_bytes, same_as_host_bytes);
    EXPECT_NE(host_bytes, different_as_host_bytes);
    std::reverse(different_as_host_bytes.begin(), different_as_host_bytes.end());
    EXPECT_EQ(host_bytes, different_as_host_bytes);
  }
  {
    // float64
    AnyValue val{Float64Type, 6.626e-34};
    const auto host_bytes = ScalarToHostOrder(val);
    const auto same_as_host_bytes = SameAsHostOrder(val);
    auto different_as_host_bytes = DifferentAsHostOrder(val);
    ASSERT_EQ(host_bytes.size(), same_as_host_bytes.size());
    ASSERT_EQ(host_bytes.size(), different_as_host_bytes.size());

    EXPECT_EQ(host_bytes, same_as_host_bytes);
    EXPECT_NE(host_bytes, different_as_host_bytes);
    std::reverse(different_as_host_bytes.begin(), different_as_host_bytes.end());
    EXPECT_EQ(host_bytes, different_as_host_bytes);
  }
  {
    // string
    AnyValue val{StringType, "Hello world!"};
    const auto host_bytes = ScalarToHostOrder(val);
    const auto same_as_host_bytes = SameAsHostOrder(val);
    const auto different_as_host_bytes = DifferentAsHostOrder(val);
    ASSERT_EQ(host_bytes.size(), same_as_host_bytes.size());
    ASSERT_EQ(host_bytes.size(), different_as_host_bytes.size());

    EXPECT_EQ(host_bytes, same_as_host_bytes);
    EXPECT_EQ(host_bytes, different_as_host_bytes);
  }
  {
    // string too long
    AnyValue val{StringType, "The maximum allowed size for fixed-length strings is 64 characters"};
    EXPECT_THROW(ScalarToHostOrder(val), SerializeException);
    EXPECT_THROW(SameAsHostOrder(val), SerializeException);
    EXPECT_THROW(DifferentAsHostOrder(val), SerializeException);
  }
}

TEST_F(ScalarBytesTest, CheckToSpecificByteOrders)
{
  {
    // bool
    AnyValue val{BooleanType, true};
    const auto le_order_bytes = ScalarToLittleEndianOrder(val);
    const auto nw_order_bytes = ScalarToNetwokOrder(val);
    ASSERT_EQ(le_order_bytes.size(), 1U);
    ASSERT_EQ(le_order_bytes.size(), nw_order_bytes.size());

    EXPECT_EQ(le_order_bytes[0], 0x01);

    EXPECT_EQ(nw_order_bytes[0], 0x01);
  }
  {
    // char8
    AnyValue val{Character8Type, 0x12};
    const auto le_order_bytes = ScalarToLittleEndianOrder(val);
    const auto nw_order_bytes = ScalarToNetwokOrder(val);
    ASSERT_EQ(le_order_bytes.size(), 1U);
    ASSERT_EQ(le_order_bytes.size(), nw_order_bytes.size());

    EXPECT_EQ(le_order_bytes[0], 0x12);

    EXPECT_EQ(nw_order_bytes[0], 0x12);
  }
  {
    // int8
    AnyValue val{SignedInteger8Type, 0x12};
    const auto le_order_bytes = ScalarToLittleEndianOrder(val);
    const auto nw_order_bytes = ScalarToNetwokOrder(val);
    ASSERT_EQ(le_order_bytes.size(), 1U);
    ASSERT_EQ(le_order_bytes.size(), nw_order_bytes.size());

    EXPECT_EQ(le_order_bytes[0], 0x12);

    EXPECT_EQ(nw_order_bytes[0], 0x12);
  }
  {
    // uint8
    AnyValue val{UnsignedInteger8Type, 0x12};
    const auto le_order_bytes = ScalarToLittleEndianOrder(val);
    const auto nw_order_bytes = ScalarToNetwokOrder(val);
    ASSERT_EQ(le_order_bytes.size(), 1U);
    ASSERT_EQ(le_order_bytes.size(), nw_order_bytes.size());

    EXPECT_EQ(le_order_bytes[0], 0x12);

    EXPECT_EQ(nw_order_bytes[0], 0x12);
  }
  {
    // int16
    AnyValue val{SignedInteger16Type, 0x1234};
    const auto le_order_bytes = ScalarToLittleEndianOrder(val);
    const auto nw_order_bytes = ScalarToNetwokOrder(val);
    ASSERT_EQ(le_order_bytes.size(), 2U);
    ASSERT_EQ(le_order_bytes.size(), nw_order_bytes.size());

    EXPECT_EQ(le_order_bytes[0], 0x34);
    EXPECT_EQ(le_order_bytes[1], 0x12);

    EXPECT_EQ(nw_order_bytes[0], 0x12);
    EXPECT_EQ(nw_order_bytes[1], 0x34);
  }
  {
    // uint16
    AnyValue val{UnsignedInteger16Type, 0x1234};
    const auto le_order_bytes = ScalarToLittleEndianOrder(val);
    const auto nw_order_bytes = ScalarToNetwokOrder(val);
    ASSERT_EQ(le_order_bytes.size(), 2U);
    ASSERT_EQ(le_order_bytes.size(), nw_order_bytes.size());

    EXPECT_EQ(le_order_bytes[0], 0x34);
    EXPECT_EQ(le_order_bytes[1], 0x12);

    EXPECT_EQ(nw_order_bytes[0], 0x12);
    EXPECT_EQ(nw_order_bytes[1], 0x34);
  }
  {
    // int32
    AnyValue val{SignedInteger32Type, 0x12345678};
    const auto le_order_bytes = ScalarToLittleEndianOrder(val);
    const auto nw_order_bytes = ScalarToNetwokOrder(val);
    ASSERT_EQ(le_order_bytes.size(), 4U);
    ASSERT_EQ(le_order_bytes.size(), nw_order_bytes.size());

    EXPECT_EQ(le_order_bytes[0], 0x78);
    EXPECT_EQ(le_order_bytes[1], 0x56);
    EXPECT_EQ(le_order_bytes[2], 0x34);
    EXPECT_EQ(le_order_bytes[3], 0x12);

    EXPECT_EQ(nw_order_bytes[0], 0x12);
    EXPECT_EQ(nw_order_bytes[1], 0x34);
    EXPECT_EQ(nw_order_bytes[2], 0x56);
    EXPECT_EQ(nw_order_bytes[3], 0x78);
  }
  {
    // uint32
    AnyValue val{UnsignedInteger32Type, 0x12345678};
    const auto le_order_bytes = ScalarToLittleEndianOrder(val);
    const auto nw_order_bytes = ScalarToNetwokOrder(val);
    ASSERT_EQ(le_order_bytes.size(), 4U);
    ASSERT_EQ(le_order_bytes.size(), nw_order_bytes.size());

    EXPECT_EQ(le_order_bytes[0], 0x78);
    EXPECT_EQ(le_order_bytes[1], 0x56);
    EXPECT_EQ(le_order_bytes[2], 0x34);
    EXPECT_EQ(le_order_bytes[3], 0x12);

    EXPECT_EQ(nw_order_bytes[0], 0x12);
    EXPECT_EQ(nw_order_bytes[1], 0x34);
    EXPECT_EQ(nw_order_bytes[2], 0x56);
    EXPECT_EQ(nw_order_bytes[3], 0x78);
  }
  {
    // int64
    AnyValue val{SignedInteger64Type, 0x1234567890ABCDEF};
    const auto le_order_bytes = ScalarToLittleEndianOrder(val);
    const auto nw_order_bytes = ScalarToNetwokOrder(val);
    ASSERT_EQ(le_order_bytes.size(), 8U);
    ASSERT_EQ(le_order_bytes.size(), nw_order_bytes.size());

    EXPECT_EQ(le_order_bytes[0], 0xEF);
    EXPECT_EQ(le_order_bytes[1], 0xCD);
    EXPECT_EQ(le_order_bytes[2], 0xAB);
    EXPECT_EQ(le_order_bytes[3], 0x90);
    EXPECT_EQ(le_order_bytes[4], 0x78);
    EXPECT_EQ(le_order_bytes[5], 0x56);
    EXPECT_EQ(le_order_bytes[6], 0x34);
    EXPECT_EQ(le_order_bytes[7], 0x12);

    EXPECT_EQ(nw_order_bytes[0], 0x12);
    EXPECT_EQ(nw_order_bytes[1], 0x34);
    EXPECT_EQ(nw_order_bytes[2], 0x56);
    EXPECT_EQ(nw_order_bytes[3], 0x78);
    EXPECT_EQ(nw_order_bytes[4], 0x90);
    EXPECT_EQ(nw_order_bytes[5], 0xAB);
    EXPECT_EQ(nw_order_bytes[6], 0xCD);
    EXPECT_EQ(nw_order_bytes[7], 0xEF);
  }
  {
    // uint64
    AnyValue val{UnsignedInteger64Type, 0x1234567890ABCDEF};
    const auto le_order_bytes = ScalarToLittleEndianOrder(val);
    const auto nw_order_bytes = ScalarToNetwokOrder(val);
    ASSERT_EQ(le_order_bytes.size(), 8U);
    ASSERT_EQ(le_order_bytes.size(), nw_order_bytes.size());

    EXPECT_EQ(le_order_bytes[0], 0xEF);
    EXPECT_EQ(le_order_bytes[1], 0xCD);
    EXPECT_EQ(le_order_bytes[2], 0xAB);
    EXPECT_EQ(le_order_bytes[3], 0x90);
    EXPECT_EQ(le_order_bytes[4], 0x78);
    EXPECT_EQ(le_order_bytes[5], 0x56);
    EXPECT_EQ(le_order_bytes[6], 0x34);
    EXPECT_EQ(le_order_bytes[7], 0x12);

    EXPECT_EQ(nw_order_bytes[0], 0x12);
    EXPECT_EQ(nw_order_bytes[1], 0x34);
    EXPECT_EQ(nw_order_bytes[2], 0x56);
    EXPECT_EQ(nw_order_bytes[3], 0x78);
    EXPECT_EQ(nw_order_bytes[4], 0x90);
    EXPECT_EQ(nw_order_bytes[5], 0xAB);
    EXPECT_EQ(nw_order_bytes[6], 0xCD);
    EXPECT_EQ(nw_order_bytes[7], 0xEF);
  }
  {
    // float32
    AnyValue val{Float32Type, 4.136e-15};
    const auto le_order_bytes = ScalarToLittleEndianOrder(val);
    auto nw_order_bytes = ScalarToNetwokOrder(val);
    ASSERT_EQ(le_order_bytes.size(), 4U);
    ASSERT_EQ(le_order_bytes.size(), nw_order_bytes.size());

    EXPECT_NE(le_order_bytes, nw_order_bytes);
    std::reverse(nw_order_bytes.begin(), nw_order_bytes.end());
    EXPECT_EQ(le_order_bytes, nw_order_bytes);
  }
  {
    // float64
    AnyValue val{Float64Type, 6.626e-34};
    const auto le_order_bytes = ScalarToLittleEndianOrder(val);
    auto nw_order_bytes = ScalarToNetwokOrder(val);
    ASSERT_EQ(le_order_bytes.size(), 8U);
    ASSERT_EQ(le_order_bytes.size(), nw_order_bytes.size());

    EXPECT_NE(le_order_bytes, nw_order_bytes);
    std::reverse(nw_order_bytes.begin(), nw_order_bytes.end());
    EXPECT_EQ(le_order_bytes, nw_order_bytes);
  }
  {
    // string
    AnyValue val{StringType, "Hello world!"};
    const auto le_order_bytes = ScalarToLittleEndianOrder(val);
    auto nw_order_bytes = ScalarToNetwokOrder(val);
    ASSERT_EQ(le_order_bytes.size(), 64U);
    ASSERT_EQ(le_order_bytes.size(), nw_order_bytes.size());

    EXPECT_EQ(le_order_bytes, nw_order_bytes);
  }
  {
    // string too long
    AnyValue val{StringType, "The maximum allowed size for fixed-length strings is 64 characters"};
    EXPECT_THROW(ScalarToLittleEndianOrder(val), SerializeException);
    EXPECT_THROW(ScalarToNetwokOrder(val), SerializeException);
  }
}

TEST_F(ScalarBytesTest, UnsupportedTypes)
{
  {
    // Empty value
    AnyValue val{};
    EXPECT_THROW(ScalarToHostOrder(val), SerializeException);
    EXPECT_THROW(ScalarToLittleEndianOrder(val), SerializeException);
    EXPECT_THROW(ScalarToNetwokOrder(val), SerializeException);
  }
  {
    // Struct value
    AnyValue val = {{
      { "level", { Float64Type, 5.0 }},
      { "flag", { BooleanType, true}}
    }};
    EXPECT_THROW(ScalarToHostOrder(val), SerializeException);
    EXPECT_THROW(ScalarToLittleEndianOrder(val), SerializeException);
    EXPECT_THROW(ScalarToNetwokOrder(val), SerializeException);
  }
  {
    // Array value
    AnyValue val = ArrayValue({ 0, 1, 2, 4});
    EXPECT_THROW(ScalarToHostOrder(val), SerializeException);
    EXPECT_THROW(ScalarToLittleEndianOrder(val), SerializeException);
    EXPECT_THROW(ScalarToNetwokOrder(val), SerializeException);
  }
}

TEST_F(ScalarBytesTest, CheckFromHostOrder)
{
  std::function<std::size_t(AnyValue&, const uint8*, std::size_t,
                            std::size_t)> SameAsHostOrder =
    IsLittleEndian() ? AssignFromLittleEndianOrder
                     : AssignFromNetworkOrder;
  std::function<std::size_t(AnyValue&, const uint8*, std::size_t,
                            std::size_t)> DifferentAsHostOrder =
    IsLittleEndian() ? AssignFromNetworkOrder
                     : AssignFromLittleEndianOrder;
  {
    // boolean
    AnyType anytype{BooleanType};
    AnyValue val{anytype, true};
    const auto host_bytes = ScalarToHostOrder(val);

    // Using the same byte order during parsing
    AnyValue parsed{anytype};
    EXPECT_EQ(SameAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_EQ(parsed, val);

    // Using a different byte order during parsing
    EXPECT_EQ(DifferentAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_EQ(parsed, val);
  }
  {
    // char8
    AnyType anytype{Character8Type};
    AnyValue val{anytype, 42};
    const auto host_bytes = ScalarToHostOrder(val);

    // Using the same byte order during parsing
    AnyValue parsed{anytype};
    EXPECT_EQ(SameAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_EQ(parsed, val);

    // Using a different byte order during parsing
    EXPECT_EQ(DifferentAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_EQ(parsed, val);
  }
  {
    // int8
    AnyType anytype{SignedInteger8Type};
    AnyValue val{anytype, 42};
    const auto host_bytes = ScalarToHostOrder(val);

    // Using the same byte order during parsing
    AnyValue parsed{anytype};
    EXPECT_EQ(SameAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_EQ(parsed, val);

    // Using a different byte order during parsing
    EXPECT_EQ(DifferentAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_EQ(parsed, val);
  }
  {
    // uint8
    AnyType anytype{UnsignedInteger8Type};
    AnyValue val{anytype, 42};
    const auto host_bytes = ScalarToHostOrder(val);

    // Using the same byte order during parsing
    AnyValue parsed{anytype};
    EXPECT_EQ(SameAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_EQ(parsed, val);

    // Using a different byte order during parsing
    EXPECT_EQ(DifferentAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_EQ(parsed, val);
  }
  {
    // int16
    AnyType anytype{SignedInteger16Type};
    AnyValue val{anytype, 0x1234};
    auto host_bytes = ScalarToHostOrder(val);

    // Using the same byte order during parsing
    AnyValue parsed{anytype};
    EXPECT_EQ(SameAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_EQ(parsed, val);

    // Using a different byte order during parsing
    EXPECT_EQ(DifferentAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_NE(parsed, val);

    // Reverse bytes
    std::reverse(host_bytes.begin(), host_bytes.end());
    EXPECT_EQ(DifferentAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_EQ(parsed, val);
  }
  {
    // uint16
    AnyType anytype{UnsignedInteger16Type};
    AnyValue val{anytype, 0x1234};
    auto host_bytes = ScalarToHostOrder(val);

    // Using the same byte order during parsing
    AnyValue parsed{anytype};
    EXPECT_EQ(SameAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_EQ(parsed, val);

    // Using a different byte order during parsing
    EXPECT_EQ(DifferentAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_NE(parsed, val);

    // Reverse bytes
    std::reverse(host_bytes.begin(), host_bytes.end());
    EXPECT_EQ(DifferentAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_EQ(parsed, val);
  }
  {
    // int32
    AnyType anytype{SignedInteger32Type};
    AnyValue val{anytype, 0x12345678};
    auto host_bytes = ScalarToHostOrder(val);

    // Using the same byte order during parsing
    AnyValue parsed{anytype};
    EXPECT_EQ(SameAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_EQ(parsed, val);

    // Using a different byte order during parsing
    EXPECT_EQ(DifferentAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_NE(parsed, val);

    // Reverse bytes
    std::reverse(host_bytes.begin(), host_bytes.end());
    EXPECT_EQ(DifferentAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_EQ(parsed, val);
  }
  {
    // uint32
    AnyType anytype{UnsignedInteger32Type};
    AnyValue val{anytype, 0x12345678};
    auto host_bytes = ScalarToHostOrder(val);

    // Using the same byte order during parsing
    AnyValue parsed{anytype};
    EXPECT_EQ(SameAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_EQ(parsed, val);

    // Using a different byte order during parsing
    EXPECT_EQ(DifferentAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_NE(parsed, val);

    // Reverse bytes
    std::reverse(host_bytes.begin(), host_bytes.end());
    EXPECT_EQ(DifferentAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_EQ(parsed, val);
  }
  {
    // int64
    AnyType anytype{SignedInteger64Type};
    AnyValue val{anytype, 0x1234567890ABCDEF};
    auto host_bytes = ScalarToHostOrder(val);

    // Using the same byte order during parsing
    AnyValue parsed{anytype};
    EXPECT_EQ(SameAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_EQ(parsed, val);

    // Using a different byte order during parsing
    EXPECT_EQ(DifferentAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_NE(parsed, val);

    // Reverse bytes
    std::reverse(host_bytes.begin(), host_bytes.end());
    EXPECT_EQ(DifferentAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_EQ(parsed, val);
  }
  {
    // uint64
    AnyType anytype{UnsignedInteger64Type};
    AnyValue val{anytype, 0x1234567890ABCDEF};
    auto host_bytes = ScalarToHostOrder(val);

    // Using the same byte order during parsing
    AnyValue parsed{anytype};
    EXPECT_EQ(SameAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_EQ(parsed, val);

    // Using a different byte order during parsing
    EXPECT_EQ(DifferentAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_NE(parsed, val);

    // Reverse bytes
    std::reverse(host_bytes.begin(), host_bytes.end());
    EXPECT_EQ(DifferentAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_EQ(parsed, val);
  }
  {
    // float32
    AnyType anytype{Float32Type};
    AnyValue val{anytype, 4.136e-15};
    auto host_bytes = ScalarToHostOrder(val);

    // Using the same byte order during parsing
    AnyValue parsed{anytype};
    EXPECT_EQ(SameAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_EQ(parsed, val);

    // Using a different byte order during parsing
    EXPECT_EQ(DifferentAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_NE(parsed, val);

    // Reverse bytes
    std::reverse(host_bytes.begin(), host_bytes.end());
    EXPECT_EQ(DifferentAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_EQ(parsed, val);
  }
  {
    // float64
    AnyType anytype{Float64Type};
    AnyValue val{anytype, 6.626e-34};
    auto host_bytes = ScalarToHostOrder(val);

    // Using the same byte order during parsing
    AnyValue parsed{anytype};
    EXPECT_EQ(SameAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_EQ(parsed, val);

    // Using a different byte order during parsing
    EXPECT_EQ(DifferentAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_NE(parsed, val);

    // Reverse bytes
    std::reverse(host_bytes.begin(), host_bytes.end());
    EXPECT_EQ(DifferentAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_EQ(parsed, val);
  }
  {
    // string
    AnyType anytype{StringType};
    AnyValue val{anytype, "Hello world!"};
    auto host_bytes = ScalarToHostOrder(val);

    // Using the same byte order during parsing
    AnyValue parsed{anytype};
    EXPECT_EQ(SameAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_EQ(parsed, val);

    // Using a different byte order during parsing
    EXPECT_EQ(DifferentAsHostOrder(parsed, host_bytes.data(), host_bytes.size(), 0),
              host_bytes.size());
    EXPECT_EQ(parsed, val);
  }
}

TEST_F(ScalarBytesTest, SerializeParse)
{
  const auto test_scalars = GetTestScalars();
  {
    // Host order
    for (const auto& test_scalar : test_scalars)
    {
      const auto bytes = ScalarToHostOrder(test_scalar);
      AnyValue parsed{test_scalar.GetType()};
      EXPECT_EQ(AssignFromHostOrder(parsed, bytes.data(), bytes.size(), 0), bytes.size());
      EXPECT_EQ(parsed, test_scalar);
    }
  }
  {
    // Little endian order
    for (const auto& test_scalar : test_scalars)
    {
      const auto bytes = ScalarToLittleEndianOrder(test_scalar);
      AnyValue parsed{test_scalar.GetType()};
      EXPECT_EQ(AssignFromLittleEndianOrder(parsed, bytes.data(), bytes.size(), 0), bytes.size());
      EXPECT_EQ(parsed, test_scalar);
    }
  }
  {
    // Network order
    for (const auto& test_scalar : test_scalars)
    {
      const auto bytes = ScalarToNetwokOrder(test_scalar);
      AnyValue parsed{test_scalar.GetType()};
      EXPECT_EQ(AssignFromNetworkOrder(parsed, bytes.data(), bytes.size(), 0), bytes.size());
      EXPECT_EQ(parsed, test_scalar);
    }
  }
}

ScalarBytesTest::ScalarBytesTest() = default;

ScalarBytesTest::~ScalarBytesTest() = default;

namespace
{
std::vector<AnyValue> GetTestScalars()
{
  std::vector<AnyValue> result;
  result.emplace_back(BooleanType, true);
  result.emplace_back(Character8Type, 42);
  result.emplace_back(SignedInteger8Type, 42);
  result.emplace_back(UnsignedInteger8Type, 42);
  result.emplace_back(SignedInteger16Type, 0x1234);
  result.emplace_back(UnsignedInteger16Type, 0x1234);
  result.emplace_back(SignedInteger32Type, 0x12345678);
  result.emplace_back(UnsignedInteger32Type, 0x12345678);
  result.emplace_back(SignedInteger64Type, 0x1234567890ABCDEF);
  result.emplace_back(UnsignedInteger64Type, 0x1234567890ABCDEF);
  result.emplace_back(Float32Type, 4.136e-15);
  result.emplace_back(Float64Type, 6.626e-34);
  result.emplace_back(StringType, "Hello world!");
  return result;
}

}  // unnamed namespace
