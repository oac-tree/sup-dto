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
  {
    AnyValue value{5, UnsignedInteger32Type};
    EXPECT_TRUE(IsArrayValue(value));
    EXPECT_FALSE(TryAssign(value[2], "oops"));
    EXPECT_TRUE(IsArrayValue(value));
  }
}

TEST(AnyValueHelperTest, ConvertAllowExtraSourceFieldsToEmptyTargetType)
{
  {
    // Emtpy value succeeds
    AnyType anytype{};
    AnyValue value{};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second, value);
  }
  {
    // Scalar value fails
    AnyType anytype{};
    AnyValue value{UnsignedInteger64Type, 42U};
    AnyValue expected{};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Struct value fails
    AnyType anytype{};
    AnyValue value = {{
      { "mode", {UnsignedInteger16Type, 3U }},
      { "setpoint", {Float64Type, 3.14 }}
    }};
    AnyValue expected{};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Array value fails
    AnyType anytype{};
    AnyValue value = ArrayValue({0, 1, 2, 3, 4});
    AnyValue expected{};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
}

TEST(AnyValueHelperTest, ConvertAllowExtraSourceFieldsToScalarTargetType)
{
  {
    // Simple scalar conversion
    AnyType anytype{UnsignedInteger32Type};
    AnyValue value{UnsignedInteger8Type, 42U};
    AnyValue expected{UnsignedInteger32Type, 42U};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Scalar that doesn't allow conversion (too big) will fail and return empty value
    AnyType anytype{UnsignedInteger8Type};
    AnyValue value{UnsignedInteger32Type, 1729U};
    AnyValue expected{};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Struct value fails
    AnyType anytype{UnsignedInteger32Type};
    AnyValue value = {{
      { "value", {UnsignedInteger8Type, 3U }},
      { "ignored", "this field will not be considered"}
    }};
    AnyValue expected{};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Array value fails
    AnyType anytype{UnsignedInteger32Type};
    AnyValue value = ArrayValue({0, 1, 2, 3, 4});
    AnyValue expected{};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
}

TEST(AnyValueHelperTest, ConvertAllowExtraSourceFieldsToStructTargetType)
{
  {
    // Scalar will not convert to struct
    AnyType anytype{{
      { "mode", UnsignedInteger32Type },
      { "description", StringType }
    }};
    AnyValue value{UnsignedInteger8Type, 42U};
    AnyValue expected{};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Struct with same fields will do only scalar conversion of leafs
    AnyType anytype{{
      { "mode", UnsignedInteger32Type },
      { "description", StringType }
    }};
    AnyValue value = {{
      { "mode", {UnsignedInteger8Type, 42U }},
      { "description", "this field does not need conversion"}
    }};
    AnyValue expected = {{
      { "mode", {UnsignedInteger32Type, 42U }},
      { "description", "this field does not need conversion"}
    }};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Struct with superset of fields will just drop those fields in conversion
    AnyType anytype{{
      { "mode", UnsignedInteger32Type },
      { "description", StringType }
    }};
    AnyValue value = {{
      { "mode", {UnsignedInteger8Type, 42U }},
      { "description", "this field does not need conversion"},
      { "not_relevant", true }
    }};
    AnyValue expected = {{
      { "mode", {UnsignedInteger32Type, 42U }},
      { "description", "this field does not need conversion"}
    }};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Struct with subset of fields will not convert and return empty
    AnyType anytype{{
      { "mode", UnsignedInteger32Type },
      { "description", StringType }
    }};
    AnyValue value = {{
      { "mode", {UnsignedInteger8Type, 42U }}
    }};
    AnyValue expected{};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
}

TEST(AnyValueHelperTest, ConvertAllowExtraSourceFieldsToArrayTargetType)
{
  {
    // Scalar will not convert to array
    AnyType anytype{2, UnsignedInteger16Type};
    AnyValue value{UnsignedInteger8Type, 42U};
    AnyValue expected{};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Struct will not convert to array
    AnyType anytype{2, UnsignedInteger16Type};
    AnyValue value = {{
      { "0", {UnsignedInteger8Type, 42U }},
      { "1", {UnsignedInteger8Type, 42U }}
    }};
    AnyValue expected{};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Array of right size will convert
    AnyType anytype{2, UnsignedInteger16Type};
    AnyValue value = ArrayValue({ {UnsignedInteger8Type, 42U }, 43U});
    AnyValue expected =
      ArrayValue({ {UnsignedInteger16Type, 42U }, 43U});
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Array of larger size will not convert and return empty
    AnyType anytype{2, UnsignedInteger16Type};
    AnyValue value =
      ArrayValue({ {UnsignedInteger8Type, 42U }, 43U, 44U});
    AnyValue expected{};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Array of smaller size will not convert and return empty
    AnyType anytype{3, UnsignedInteger16Type};
    AnyValue value =
      ArrayValue({ {UnsignedInteger8Type, 42U }, 43U});
    AnyValue expected{};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
}

TEST(AnyValueHelperTest, ConvertAllowExtraTargetFieldsToEmptyTargetType)
{
  {
    // Emtpy value succeeds
    AnyType anytype{};
    AnyValue value{};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second, value);
  }
  {
    // Scalar value fails
    AnyType anytype{};
    AnyValue value{UnsignedInteger64Type, 42U};
    AnyValue expected{};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Struct value fails
    AnyType anytype{};
    AnyValue value = {{
      { "mode", {UnsignedInteger16Type, 3U }},
      { "setpoint", {Float64Type, 3.14 }}
    }};
    AnyValue expected{};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Array value fails
    AnyType anytype{};
    AnyValue value = ArrayValue({0, 1, 2, 3, 4});
    AnyValue expected{};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
}

TEST(AnyValueHelperTest, ConvertAllowExtraTargetFieldsToScalarTargetType)
{
  {
    // Simple scalar conversion
    AnyType anytype{UnsignedInteger32Type};
    AnyValue value{UnsignedInteger8Type, 42U};
    AnyValue expected{UnsignedInteger32Type, 42U};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Scalar that doesn't allow conversion (too big) will fail and return empty value
    AnyType anytype{UnsignedInteger8Type};
    AnyValue value{UnsignedInteger32Type, 1729U};
    AnyValue expected{};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Struct value fails
    AnyType anytype{UnsignedInteger32Type};
    AnyValue value = {{
      { "value", {UnsignedInteger8Type, 3U }},
      { "ignored", "this field will not be considered"}
    }};
    AnyValue expected{};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Array value fails
    AnyType anytype{UnsignedInteger32Type};
    AnyValue value = ArrayValue({0, 1, 2, 3, 4});
    AnyValue expected{};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
}

TEST(AnyValueHelperTest, ConvertAllowExtraTargetFieldsToStructTargetType)
{
  {
    // Scalar will not convert to struct
    AnyType anytype{{
      { "mode", UnsignedInteger32Type },
      { "description", StringType }
    }};
    AnyValue value{UnsignedInteger8Type, 42U};
    AnyValue expected{};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Struct with same fields will do only scalar conversion of leafs
    AnyType anytype{{
      { "mode", UnsignedInteger32Type },
      { "description", StringType }
    }};
    AnyValue value = {{
      { "mode", {UnsignedInteger8Type, 42U }},
      { "description", "this field does not need conversion"}
    }};
    AnyValue expected = {{
      { "mode", {UnsignedInteger32Type, 42U }},
      { "description", "this field does not need conversion"}
    }};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Struct with subset of fields will only convert those to the result value
    AnyType anytype{{
      { "mode", UnsignedInteger32Type },
      { "description", StringType },
      { "flag", BooleanType }
    }};
    AnyValue value = {{
      { "mode", {UnsignedInteger8Type, 42U }},
      { "flag", true }
    }};
    AnyValue expected = {{
      { "mode", {UnsignedInteger32Type, 42U }},
      { "flag", true }
    }};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Struct with superset of fields will not convert and return empty
    AnyType anytype{{
      { "mode", UnsignedInteger32Type }
    }};
    AnyValue value = {{
      { "mode", {UnsignedInteger8Type, 42U }},
      { "description", {StringType, "field_too_much"} }
    }};
    AnyValue expected{};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
}

TEST(AnyValueHelperTest, ConvertAllowExtraTargetFieldsToArrayTargetType)
{
  {
    // Scalar will not convert to array
    AnyType anytype{2, UnsignedInteger16Type};
    AnyValue value{UnsignedInteger8Type, 42U};
    AnyValue expected{};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Struct will not convert to array
    AnyType anytype{2, UnsignedInteger16Type};
    AnyValue value = {{
      { "0", {UnsignedInteger8Type, 42U }},
      { "1", {UnsignedInteger8Type, 42U }}
    }};
    AnyValue expected{};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Array of right size will convert
    AnyType anytype{2, UnsignedInteger16Type};
    AnyValue value = ArrayValue({ {UnsignedInteger8Type, 42U }, 43U});
    AnyValue expected =
      ArrayValue({ {UnsignedInteger16Type, 42U }, 43U});
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Array of larger size will not convert and return empty
    AnyType anytype{2, UnsignedInteger16Type};
    AnyValue value =
      ArrayValue({ {UnsignedInteger8Type, 42U }, 43U, 44U});
    AnyValue expected{};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Array of smaller size will not convert and return empty
    AnyType anytype{3, UnsignedInteger16Type};
    AnyValue value =
      ArrayValue({ {UnsignedInteger8Type, 42U }, 43U});
    AnyValue expected{};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
}
