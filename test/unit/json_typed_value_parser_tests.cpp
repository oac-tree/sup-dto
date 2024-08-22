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
 * Copyright (c) : 2010-2024 ITER Organization,
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

#include <sup/dto/parse/serialization_constants.h>

#include <sup/dto/anyvalue.h>
#include <sup/dto/json_value_parser.h>

using namespace sup::dto;

class JSONTypedValueParserTest : public ::testing::Test
{
protected:
  JSONTypedValueParserTest();
  virtual ~JSONTypedValueParserTest();

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

JSONTypedValueParserTest::JSONTypedValueParserTest() = default;

JSONTypedValueParserTest::~JSONTypedValueParserTest() = default;
