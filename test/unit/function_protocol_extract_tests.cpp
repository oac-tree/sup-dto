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

#include <sup/dto/anytype_helper.h>
#include <sup/rpc/function_protocol_extract.h>

using namespace sup::rpc;

class FunctionProtocolExtractTest : public ::testing::Test
{
protected:
  FunctionProtocolExtractTest();
  virtual ~FunctionProtocolExtractTest();
};

TEST_F(FunctionProtocolExtractTest, Boolean)
{
  sup::dto::AnyValue input = {
    { "flag", true },
    { "wrong_type", 5 }
  };
  bool b = false;
  EXPECT_FALSE(FunctionProtocolExtract(b, input, "does_not_exist"));
  EXPECT_FALSE(b);
  EXPECT_FALSE(FunctionProtocolExtract(b, input, "wrong_type"));
  EXPECT_FALSE(b);
  EXPECT_TRUE(FunctionProtocolExtract(b, input, "flag"));
  EXPECT_TRUE(b);
}

TEST_F(FunctionProtocolExtractTest, String)
{
  sup::dto::AnyValue input = {
    { "string", "string_value" },
    { "wrong_type", 5 }
  };
  std::string str;
  EXPECT_FALSE(FunctionProtocolExtract(str, input, "does_not_exist"));
  EXPECT_TRUE(str.empty());
  EXPECT_FALSE(FunctionProtocolExtract(str, input, "wrong_type"));
  EXPECT_TRUE(str.empty());
  EXPECT_TRUE(FunctionProtocolExtract(str, input, "string"));
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(str, "string_value");
}

TEST_F(FunctionProtocolExtractTest, StringList)
{
  sup::dto::AnyValue input = {
    { "string_list", sup::dto::ArrayValue({"one", "two", "three"}) },
    { "wrong_type", 5 }
  };
  std::vector<std::string> string_list;
  EXPECT_FALSE(FunctionProtocolExtract(string_list, input, "does_not_exist"));
  EXPECT_TRUE(string_list.empty());
  EXPECT_FALSE(FunctionProtocolExtract(string_list, input, "wrong_type"));
  EXPECT_TRUE(string_list.empty());
  EXPECT_TRUE(FunctionProtocolExtract(string_list, input, "string_list"));
  EXPECT_FALSE(string_list.empty());
  ASSERT_EQ(string_list.size(), 3);
  EXPECT_EQ(string_list[0], "one");
  EXPECT_EQ(string_list[1], "two");
  EXPECT_EQ(string_list[2], "three");
}

TEST_F(FunctionProtocolExtractTest, AnyValue)
{
  sup::dto::AnyValue input = {
    { "string", "string_value" },
    { "number", 5 }
  };
  sup::dto::AnyValue anyvalue;
  EXPECT_FALSE(FunctionProtocolExtract(anyvalue, input, "does_not_exist"));
  EXPECT_TRUE(sup::dto::IsEmptyValue(anyvalue));
  sup::dto::AnyValue wrong_output{ sup::dto::StringType, "" };
  EXPECT_FALSE(FunctionProtocolExtract(wrong_output, input, "number"));
  EXPECT_TRUE(FunctionProtocolExtract(anyvalue, input, "number"));
  EXPECT_FALSE(sup::dto::IsEmptyValue(anyvalue));
  EXPECT_EQ(anyvalue, 5);
}

TEST_F(FunctionProtocolExtractTest, AnyType)
{
  sup::dto::AnyType anytype = {{
    { "enabled", sup::dto::BooleanType },
    { "counter", sup::dto::UnsignedInteger32Type }
  }, "counter_t"};
  auto json_type = sup::dto::AnyTypeToJSONString(anytype);
  sup::dto::AnyValue input = {
    { "type", json_type },
    { "wrong_type", {sup::dto::BooleanType, true }},
    { "cannot_be_parsed", {sup::dto::StringType, "this_is_not_a_valid_anytype_json"}}
  };
  sup::dto::AnyType extracted_type;
  EXPECT_FALSE(FunctionProtocolExtract(extracted_type, input, "does_not_exist"));
  EXPECT_TRUE(sup::dto::IsEmptyType(extracted_type));
  EXPECT_FALSE(FunctionProtocolExtract(extracted_type, input, "wrong_type"));
  EXPECT_TRUE(sup::dto::IsEmptyType(extracted_type));
  EXPECT_FALSE(FunctionProtocolExtract(extracted_type, input, "cannot_be_parsed"));
  EXPECT_TRUE(sup::dto::IsEmptyType(extracted_type));
  EXPECT_TRUE(FunctionProtocolExtract(extracted_type, input, "type"));
  EXPECT_FALSE(sup::dto::IsEmptyType(extracted_type));
  EXPECT_EQ(extracted_type, anytype);
}

FunctionProtocolExtractTest::FunctionProtocolExtractTest() = default;

FunctionProtocolExtractTest::~FunctionProtocolExtractTest() = default;
