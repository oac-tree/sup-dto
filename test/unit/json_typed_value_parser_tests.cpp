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

#include <gtest/gtest.h>

#include <sup/dto/parse/serialization_constants.h>

#include <sup/dto/anyvalue.h>
#include <sup/dto/anyvalue_helper.h>
#include <sup/dto/json_value_parser.h>

#include <string>
#include <vector>

using namespace sup::dto;

class JSONTypedValueParserTest : public ::testing::Test
{
protected:
  JSONTypedValueParserTest();
  ~JSONTypedValueParserTest() override;

  JSONAnyValueParser m_parser;
};

TEST_F(JSONTypedValueParserTest, EmptySuccess)
{
  AnyValue expected;
  EXPECT_TRUE(m_parser.TypedParseString(EmptyType, "null"));
  auto parsed_val = m_parser.MoveAnyValue();
  EXPECT_EQ(expected, parsed_val);
}

TEST_F(JSONTypedValueParserTest, BooleanSuccess)
{
  AnyValue expected{BooleanType, true};
  EXPECT_TRUE(m_parser.TypedParseString(BooleanType, "true"));
  auto parsed_val = m_parser.MoveAnyValue();
  EXPECT_EQ(expected, parsed_val);
}

TEST_F(JSONTypedValueParserTest, IntegerSuccess)
{
  {
    AnyValue expected{Character8Type, 42};
    EXPECT_TRUE(m_parser.TypedParseString(Character8Type, "42"));
    auto parsed_val = m_parser.MoveAnyValue();
    EXPECT_EQ(expected, parsed_val);
  }
  {
    AnyValue expected{SignedInteger8Type, 42};
    EXPECT_TRUE(m_parser.TypedParseString(SignedInteger8Type, "42"));
    auto parsed_val = m_parser.MoveAnyValue();
    EXPECT_EQ(expected, parsed_val);
  }
  {
    AnyValue expected{UnsignedInteger8Type, 42};
    EXPECT_TRUE(m_parser.TypedParseString(UnsignedInteger8Type, "42"));
    auto parsed_val = m_parser.MoveAnyValue();
    EXPECT_EQ(expected, parsed_val);
  }
  {
    AnyValue expected{SignedInteger16Type, 42};
    EXPECT_TRUE(m_parser.TypedParseString(SignedInteger16Type, "42"));
    auto parsed_val = m_parser.MoveAnyValue();
    EXPECT_EQ(expected, parsed_val);
  }
  {
    AnyValue expected{UnsignedInteger16Type, 42};
    EXPECT_TRUE(m_parser.TypedParseString(UnsignedInteger16Type, "42"));
    auto parsed_val = m_parser.MoveAnyValue();
    EXPECT_EQ(expected, parsed_val);
  }
  {
    AnyValue expected{SignedInteger32Type, 42};
    EXPECT_TRUE(m_parser.TypedParseString(SignedInteger32Type, "42"));
    auto parsed_val = m_parser.MoveAnyValue();
    EXPECT_EQ(expected, parsed_val);
  }
  {
    AnyValue expected{UnsignedInteger32Type, 42};
    EXPECT_TRUE(m_parser.TypedParseString(UnsignedInteger32Type, "42"));
    auto parsed_val = m_parser.MoveAnyValue();
    EXPECT_EQ(expected, parsed_val);
  }
  {
    AnyValue expected{SignedInteger64Type, 42};
    EXPECT_TRUE(m_parser.TypedParseString(SignedInteger64Type, "42"));
    auto parsed_val = m_parser.MoveAnyValue();
    EXPECT_EQ(expected, parsed_val);
  }
  {
    AnyValue expected{UnsignedInteger64Type, 42};
    EXPECT_TRUE(m_parser.TypedParseString(UnsignedInteger64Type, "42"));
    auto parsed_val = m_parser.MoveAnyValue();
    EXPECT_EQ(expected, parsed_val);
  }
  {
    AnyValue expected{Float32Type, 3.14f};
    EXPECT_TRUE(m_parser.TypedParseString(Float32Type, "3.14"));
    auto parsed_val = m_parser.MoveAnyValue();
    EXPECT_EQ(expected, parsed_val);
  }
  {
    AnyValue expected{Float64Type, 3.14};
    EXPECT_TRUE(m_parser.TypedParseString(Float64Type, "3.14"));
    auto parsed_val = m_parser.MoveAnyValue();
    EXPECT_EQ(expected, parsed_val);
  }
  {
    AnyValue expected{StringType, "somevalue"};
    EXPECT_TRUE(m_parser.TypedParseString(StringType, "\"somevalue\""));
    auto parsed_val = m_parser.MoveAnyValue();
    EXPECT_EQ(expected, parsed_val);
  }
}

TEST_F(JSONTypedValueParserTest, EmptyFailure)
{
  EXPECT_FALSE(m_parser.TypedParseString(EmptyType, "zero"));
  auto parsed_val = m_parser.MoveAnyValue();
  EXPECT_TRUE(IsEmptyValue(parsed_val));
}

TEST_F(JSONTypedValueParserTest, BooleanFailure)
{
  EXPECT_FALSE(m_parser.TypedParseString(BooleanType, "sotrue"));
  auto parsed_val = m_parser.MoveAnyValue();
  EXPECT_TRUE(IsEmptyValue(parsed_val));
}

TEST_F(JSONTypedValueParserTest, IntegerFailure)
{
  {
    EXPECT_FALSE(m_parser.TypedParseString(UnsignedInteger32Type, "fifty-one"));
    auto parsed_val = m_parser.MoveAnyValue();
    EXPECT_TRUE(IsEmptyValue(parsed_val));
  }
  {
    EXPECT_FALSE(m_parser.TypedParseString(Float64Type, R"RAW({"level":3.14})RAW"));
    auto parsed_val = m_parser.MoveAnyValue();
    EXPECT_TRUE(IsEmptyValue(parsed_val));
  }
}

TEST_F(JSONTypedValueParserTest, StructFailure)
{
  AnyType simple_struct_type({
    {"id", StringType},
    {"number", UnsignedInteger64Type}
  });
  {
    std::string correct_values = R"RAW({"id":"BQRT-7HFR","number":5678})RAW";
    EXPECT_TRUE(m_parser.TypedParseString(simple_struct_type, correct_values));
    auto parsed_val = m_parser.MoveAnyValue();
    EXPECT_TRUE(parsed_val.HasField("id"));
    EXPECT_EQ(parsed_val["id"].As<std::string>(), "BQRT-7HFR");
    EXPECT_TRUE(parsed_val.HasField("number"));
    EXPECT_EQ(parsed_val["number"].As<uint64>(), 5678u);
  }
  {
    std::string wrong_values = R"RAW({"identity":"BQRT-7HFR","index":5678})RAW";
    EXPECT_FALSE(m_parser.TypedParseString(simple_struct_type, wrong_values));
    auto parsed_val = m_parser.MoveAnyValue();
    EXPECT_FALSE(parsed_val.HasField("id"));
    EXPECT_FALSE(parsed_val.HasField("number"));
    EXPECT_TRUE(IsEmptyValue(parsed_val));
  }
}

TEST_F(JSONTypedValueParserTest, ArrayFailure)
{
  AnyType simple_array_type(3, SignedInteger32Type);
  {
    std::string correct_values = R"RAW([-3, 7, 23])RAW";
    EXPECT_TRUE(m_parser.TypedParseString(simple_array_type, correct_values));
    auto parsed_val = m_parser.MoveAnyValue();
    EXPECT_EQ(parsed_val.NumberOfElements(), 3);
    EXPECT_EQ(parsed_val[0], -3);
    EXPECT_EQ(parsed_val[1], 7);
    EXPECT_EQ(parsed_val[2], 23);
  }
  {
    std::string wrong_values = R"RAW({"values":[-3, 7, 23]})RAW";
    EXPECT_FALSE(m_parser.TypedParseString(simple_array_type, wrong_values));
    auto parsed_val = m_parser.MoveAnyValue();
    EXPECT_EQ(parsed_val.NumberOfElements(), 0);
    EXPECT_TRUE(IsEmptyValue(parsed_val));
  }
}

// INVARIANT (relied upon by external units — do not weaken these tests):
// TypedParseString resolves struct members by name, so the result is independent of JSON
// key order; member order comes from the AnyType. Downstream code depends on this (e.g.
// psps-dto reconstructs values from a Postgres jsonb column, which reorders keys). Making
// the parser order-sensitive would silently corrupt those consumers, so keep these green
// by preserving the invariant, not by relaxing the assertions.

TEST_F(JSONTypedValueParserTest, StructMemberOrderIndependence)
{
  AnyType struct_type({
    {"id", StringType},
    {"number", UnsignedInteger64Type}
  });
  // Keys in reverse order relative to the type definition (as jsonb may reorder them).
  const std::string reordered = R"RAW({"number":5678,"id":"BQRT-7HFR"})RAW";
  ASSERT_TRUE(m_parser.TypedParseString(struct_type, reordered));
  auto parsed_val = m_parser.MoveAnyValue();
  ASSERT_TRUE(parsed_val.HasField("id"));
  ASSERT_TRUE(parsed_val.HasField("number"));
  EXPECT_EQ(parsed_val["id"].As<std::string>(), "BQRT-7HFR");
  EXPECT_EQ(parsed_val["number"].As<uint64>(), 5678u);
}

TEST_F(JSONTypedValueParserTest, StructMemberOrderFollowsType)
{
  AnyType struct_type({
    {"id", StringType},
    {"number", UnsignedInteger64Type}
  });
  const std::string in_order = R"RAW({"id":"X","number":1})RAW";
  const std::string reordered = R"RAW({"number":1,"id":"X"})RAW";

  ASSERT_TRUE(m_parser.TypedParseString(struct_type, in_order));
  auto in_order_val = m_parser.MoveAnyValue();
  ASSERT_TRUE(m_parser.TypedParseString(struct_type, reordered));
  auto reordered_val = m_parser.MoveAnyValue();

  // The value is identical regardless of key order in the JSON text ...
  EXPECT_EQ(in_order_val, reordered_val);
  // ... and the resulting member order is dictated by the type, not the JSON.
  const std::vector<std::string> expected_order{"id", "number"};
  EXPECT_EQ(in_order_val.MemberNames(), expected_order);
  EXPECT_EQ(reordered_val.MemberNames(), expected_order);
}

TEST_F(JSONTypedValueParserTest, NestedStructMemberOrderIndependence)
{
  AnyType inner_type({
    {"a", SignedInteger32Type},
    {"b", SignedInteger32Type}
  });
  AnyType outer_type({
    {"first", StringType},
    {"nested", inner_type},
    {"last", BooleanType}
  });
  // Keys reversed at every object level.
  const std::string reordered =
    R"RAW({"last":true,"nested":{"b":2,"a":1},"first":"hello"})RAW";
  ASSERT_TRUE(m_parser.TypedParseString(outer_type, reordered));
  auto parsed_val = m_parser.MoveAnyValue();
  EXPECT_EQ(parsed_val["first"].As<std::string>(), "hello");
  EXPECT_EQ(parsed_val["nested"]["a"].As<int32>(), 1);
  EXPECT_EQ(parsed_val["nested"]["b"].As<int32>(), 2);
  EXPECT_EQ(parsed_val["last"].As<boolean>(), true);
  const std::vector<std::string> outer_order{"first", "nested", "last"};
  const std::vector<std::string> inner_order{"a", "b"};
  EXPECT_EQ(parsed_val.MemberNames(), outer_order);
  EXPECT_EQ(parsed_val["nested"].MemberNames(), inner_order);
}

TEST_F(JSONTypedValueParserTest, ArrayOfStructsMemberOrderIndependence)
{
  AnyType element_type({
    {"first_member", StringType},
    {"second_member", UnsignedInteger32Type}
  });
  AnyType array_type(2, element_type);
  // Member keys reversed inside each element; array element order is preserved (arrays
  // are ordered and jsonb keeps array order).
  const std::string json =
    R"RAW([{"second_member":10,"first_member":"a"},)RAW"
    R"RAW({"second_member":20,"first_member":"b"}])RAW";
  ASSERT_TRUE(m_parser.TypedParseString(array_type, json));
  auto parsed_val = m_parser.MoveAnyValue();
  ASSERT_EQ(parsed_val.NumberOfElements(), 2u);
  EXPECT_EQ(parsed_val[0]["first_member"].As<std::string>(), "a");
  EXPECT_EQ(parsed_val[0]["second_member"].As<uint32>(), 10u);
  EXPECT_EQ(parsed_val[1]["first_member"].As<std::string>(), "b");
  EXPECT_EQ(parsed_val[1]["second_member"].As<uint32>(), 20u);
}

TEST_F(JSONTypedValueParserTest, ValuesToJSONRoundTrip)
{
  AnyType struct_type({
    {"id", StringType},
    {"number", UnsignedInteger64Type},
    {"flag", BooleanType}
  });
  AnyValue original{struct_type};
  original["id"] = std::string{"abc"};
  original["number"] = static_cast<uint64>(9001);
  original["flag"] = true;

  const std::string json = ValuesToJSONString(original);
  ASSERT_TRUE(m_parser.TypedParseString(struct_type, json));
  auto round_tripped = m_parser.MoveAnyValue();
  EXPECT_EQ(round_tripped, original);
}

JSONTypedValueParserTest::JSONTypedValueParserTest() = default;

JSONTypedValueParserTest::~JSONTypedValueParserTest() = default;
