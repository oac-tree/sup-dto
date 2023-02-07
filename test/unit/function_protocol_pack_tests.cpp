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

#include <sup/rpc/rpc_exceptions.h>
#include <sup/rpc/function_protocol_pack.h>

using namespace sup::rpc;

class FunctionProtocolPackTest : public ::testing::Test
{
protected:
  FunctionProtocolPackTest();
  virtual ~FunctionProtocolPackTest();

  sup::dto::AnyValue m_empty;
  sup::dto::AnyValue m_array;
  sup::dto::AnyValue m_scalar;
  sup::dto::AnyValue m_struct;
};

TEST_F(FunctionProtocolPackTest, Boolean)
{
  EXPECT_THROW(FunctionProtocolPack(m_array, "whatever", true), InvalidOperationException);
  EXPECT_THROW(FunctionProtocolPack(m_scalar, "whatever", true), InvalidOperationException);
  EXPECT_THROW(FunctionProtocolPack(m_struct, "field_exists", true), InvalidOperationException);

  EXPECT_NO_THROW(FunctionProtocolPack(m_struct, "new_field", true));
  ASSERT_TRUE(m_struct.HasField("new_field"));
  EXPECT_EQ(m_struct["new_field"], true);

  EXPECT_NO_THROW(FunctionProtocolPack(m_empty, "new_field", true));
  ASSERT_TRUE(m_empty.HasField("new_field"));
  EXPECT_EQ(m_empty["new_field"], true);
}

TEST_F(FunctionProtocolPackTest, String)
{
  const std::string str = "string_value";
  EXPECT_THROW(FunctionProtocolPack(m_array, "whatever", str), InvalidOperationException);
  EXPECT_THROW(FunctionProtocolPack(m_scalar, "whatever", str), InvalidOperationException);
  EXPECT_THROW(FunctionProtocolPack(m_struct, "field_exists", str), InvalidOperationException);

  EXPECT_NO_THROW(FunctionProtocolPack(m_struct, "new_field", str));
  ASSERT_TRUE(m_struct.HasField("new_field"));
  EXPECT_EQ(m_struct["new_field"], str);

  EXPECT_NO_THROW(FunctionProtocolPack(m_empty, "new_field", str));
  ASSERT_TRUE(m_empty.HasField("new_field"));
  EXPECT_EQ(m_empty["new_field"], str);
}

TEST_F(FunctionProtocolPackTest, StringList)
{
  const std::vector<std::string> string_list{ "one", "two", "three" };
  EXPECT_THROW(FunctionProtocolPack(m_array, "whatever", string_list), InvalidOperationException);
  EXPECT_THROW(FunctionProtocolPack(m_scalar, "whatever", string_list), InvalidOperationException);
  EXPECT_THROW(FunctionProtocolPack(m_struct, "field_exists", string_list),
               InvalidOperationException);

  EXPECT_NO_THROW(FunctionProtocolPack(m_struct, "new_field", string_list));
  ASSERT_TRUE(m_struct.HasField("new_field"));
  const auto& field_1 = m_struct["new_field"];
  EXPECT_TRUE(sup::dto::IsArrayValue(field_1));
  EXPECT_EQ(field_1.NumberOfElements(), 3);
  EXPECT_EQ(field_1[0], "one");
  EXPECT_EQ(field_1[1], "two");
  EXPECT_EQ(field_1[2], "three");

  EXPECT_NO_THROW(FunctionProtocolPack(m_empty, "new_field", string_list));
  ASSERT_TRUE(m_empty.HasField("new_field"));
  const auto& field_2 = m_empty["new_field"];
  EXPECT_TRUE(sup::dto::IsArrayValue(field_2));
  EXPECT_EQ(field_2.NumberOfElements(), 3);
  EXPECT_EQ(field_2[0], "one");
  EXPECT_EQ(field_2[1], "two");
  EXPECT_EQ(field_2[2], "three");
}

TEST_F(FunctionProtocolPackTest, AnyValue)
{
  sup::dto::AnyValue anyvalue = {
    { "flag", true },
    { "count", {21, sup::dto::UnsignedInteger32Type }}
  };
  EXPECT_THROW(FunctionProtocolPack(m_array, "whatever", anyvalue), InvalidOperationException);
  EXPECT_THROW(FunctionProtocolPack(m_scalar, "whatever", anyvalue), InvalidOperationException);
  EXPECT_THROW(FunctionProtocolPack(m_struct, "field_exists", anyvalue), InvalidOperationException);

  EXPECT_NO_THROW(FunctionProtocolPack(m_struct, "new_field", anyvalue));
  ASSERT_TRUE(m_struct.HasField("new_field"));
  EXPECT_EQ(m_struct["new_field"], anyvalue);

  EXPECT_NO_THROW(FunctionProtocolPack(m_empty, "new_field", anyvalue));
  ASSERT_TRUE(m_empty.HasField("new_field"));
  EXPECT_EQ(m_empty["new_field"], anyvalue);
}

FunctionProtocolPackTest::FunctionProtocolPackTest()
  : m_empty{}
  , m_array{sup::dto::AnyType{0, sup::dto::StringType}}
  , m_scalar{sup::dto::UnsignedInteger8Type}
  , m_struct{ {"field_exists", "doesntmatter"}}
{}

FunctionProtocolPackTest::~FunctionProtocolPackTest() = default;
