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

#include <sup/dto/anytype.h>
#include <sup/dto/anyvalue.h>
#include <sup/dto/anyvalue_helper.h>

using namespace sup::dto;

TEST(AnyValueHelperTest, TryConvertSimple)
{
  AnyValue unsigned_value{UnsignedInteger16Type};
  EXPECT_EQ(unsigned_value, 0);

  EXPECT_TRUE(TryConvert(unsigned_value, 42));
  EXPECT_EQ(unsigned_value, 42);

  EXPECT_FALSE(TryConvert(unsigned_value, -3));
  EXPECT_EQ(unsigned_value, 42);

  EXPECT_FALSE(TryConvert(unsigned_value, 120000u));
  EXPECT_EQ(unsigned_value, 42);
}

TEST(AnyValueHelperTest, TryConvertEmpty)
{
  {
    AnyValue empty_value{};
    EXPECT_TRUE(IsEmptyValue(empty_value));
    EXPECT_FALSE(TryConvert(empty_value, 42));
    EXPECT_TRUE(IsEmptyValue(empty_value));
  }
  {
    AnyValue empty_value{};
    AnyValue struct_value{
      {"flag", true},
      {"value", {Float32Type, 1.5}}
    };
    EXPECT_TRUE(IsEmptyValue(empty_value));
    EXPECT_FALSE(TryConvert(empty_value, struct_value));
    EXPECT_TRUE(IsEmptyValue(empty_value));
  }
  {
    AnyValue empty_value{};
    AnyValue struct_value{
      {"flag", true},
      {"value", {Float32Type, 1.5}}
    };
    EXPECT_TRUE(IsEmptyValue(empty_value));
    EXPECT_NO_THROW(empty_value = struct_value);
    ASSERT_TRUE(empty_value.HasField("flag"));
    EXPECT_EQ(empty_value["flag"], true);
    ASSERT_TRUE(empty_value.HasField("value"));
    EXPECT_EQ(empty_value["value"], 1.5);
  }
}

TEST(AnyValueHelperTest, TryAssignIfEmptyOrConvert)
{
  {
    AnyValue empty_value{};
    EXPECT_TRUE(IsEmptyValue(empty_value));
    EXPECT_TRUE(TryAssignIfEmptyOrConvert(empty_value, 42));
    EXPECT_TRUE(IsScalarValue(empty_value));
  }
  {
    AnyValue value{UnsignedInteger16Type, 3};
    EXPECT_TRUE(IsScalarValue(value));
    EXPECT_TRUE(TryAssignIfEmptyOrConvert(value, 42));
    EXPECT_TRUE(IsScalarValue(value));
    EXPECT_EQ(value.GetType(), UnsignedInteger16Type);
    EXPECT_EQ(value.As<uint16>(), 42u);
  }
  {
    AnyValue value{{
      {"a", true},
      {"b", 42}
    }};
    EXPECT_TRUE(IsStructValue(value));
    EXPECT_FALSE(TryAssignIfEmptyOrConvert(value, 42));
    EXPECT_TRUE(IsStructValue(value));
  }
}