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

#include <sup/dto/anytype.h>
#include <sup/dto/anyvalue.h>
#include <sup/dto/anyvalue_helper.h>

#include <gtest/gtest.h>

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
    const AnyValue struct_value{{"flag", true}, {"value", {Float32Type, 1.5}}};
    EXPECT_TRUE(IsEmptyValue(empty_value));
    EXPECT_FALSE(TryConvert(empty_value, struct_value));
    EXPECT_TRUE(IsEmptyValue(empty_value));
  }
  {
    AnyValue empty_value{};
    const AnyValue struct_value{{"flag", true}, {"value", {Float32Type, 1.5}}};
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
    AnyValue value{{{"a", true}, {"b", 42}}};
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
    const AnyType anytype{};
    const AnyValue value{};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second, value);
  }
  {
    // Scalar value fails
    const AnyType anytype{};
    const AnyValue value{UnsignedInteger64Type, 42U};
    const AnyValue expected{};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Struct value fails
    const AnyType anytype{};
    const AnyValue value = {
        {{"mode", {UnsignedInteger16Type, 3U}}, {"setpoint", {Float64Type, 3.14}}}};
    const AnyValue expected{};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Array value fails
    const AnyType anytype{};
    const AnyValue value = ArrayValue({0, 1, 2, 3, 4});
    const AnyValue expected{};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
}

TEST(AnyValueHelperTest, ConvertAllowExtraSourceFieldsToScalarTargetType)
{
  {
    // Simple scalar conversion
    const AnyType anytype{UnsignedInteger32Type};
    const AnyValue value{UnsignedInteger8Type, 42U};
    const AnyValue expected{UnsignedInteger32Type, 42U};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Scalar that doesn't allow conversion (too big) will fail and return empty value
    const AnyType anytype{UnsignedInteger8Type};
    const AnyValue value{UnsignedInteger32Type, 1729U};
    const AnyValue expected{};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Struct value fails
    const AnyType anytype{UnsignedInteger32Type};
    const AnyValue value = {
        {{"value", {UnsignedInteger8Type, 3U}}, {"ignored", "this field will not be considered"}}};
    AnyValue expected{};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Array value fails
    const AnyType anytype{UnsignedInteger32Type};
    const AnyValue value = ArrayValue({0, 1, 2, 3, 4});
    const AnyValue expected{};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
}

TEST(AnyValueHelperTest, ConvertAllowExtraSourceFieldsToStructTargetType)
{
  {
    // Scalar will not convert to struct
    const AnyType anytype{{{"mode", UnsignedInteger32Type}, {"description", StringType}}};
    const AnyValue value{UnsignedInteger8Type, 42U};
    const AnyValue expected{};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Struct with same fields will do only scalar conversion of leafs
    const AnyType anytype{{{"mode", UnsignedInteger32Type}, {"description", StringType}}};
    const AnyValue value = {{{"mode", {UnsignedInteger8Type, 42U}},
                             {"description", "this field does not need conversion"}}};
    const AnyValue expected = {{{"mode", {UnsignedInteger32Type, 42U}},
                                {"description", "this field does not need conversion"}}};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Struct with superset of fields will just drop those fields in conversion
    const AnyType anytype{{{"mode", UnsignedInteger32Type}, {"description", StringType}}};
    const AnyValue value = {{{"mode", {UnsignedInteger8Type, 42U}},
                             {"description", "this field does not need conversion"},
                             {"not_relevant", true}}};
    const AnyValue expected = {{{"mode", {UnsignedInteger32Type, 42U}},
                                {"description", "this field does not need conversion"}}};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Structs with mismatching fields will fail and return empty
    const AnyType anytype{{{"mode", UnsignedInteger32Type}, {"flag", BooleanType}}};
    const AnyValue value = {{{"mode", {UnsignedInteger8Type, 42U}}, {"no_flag", true}}};
    const AnyValue expected{};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Struct with subset of fields will not convert and return empty
    const AnyType anytype{{{"mode", UnsignedInteger32Type}, {"description", StringType}}};
    const AnyValue value = {{{"mode", {UnsignedInteger8Type, 42U}}}};
    const AnyValue expected{};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
}

TEST(AnyValueHelperTest, ConvertAllowExtraSourceFieldsToArrayTargetType)
{
  {
    // Scalar will not convert to array
    const AnyType anytype{2, UnsignedInteger16Type};
    const AnyValue value{UnsignedInteger8Type, 42U};
    const AnyValue expected{};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Struct will not convert to array
    const AnyType anytype{2, UnsignedInteger16Type};
    const AnyValue value = {
        {{"0", {UnsignedInteger8Type, 42U}}, {"1", {UnsignedInteger8Type, 42U}}}};
    const AnyValue expected{};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Array of right size will convert
    const AnyType anytype{2, UnsignedInteger16Type};
    const AnyValue value = ArrayValue({{UnsignedInteger8Type, 42U}, 43U});
    const AnyValue expected = ArrayValue({{UnsignedInteger16Type, 42U}, 43U});
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Array of larger size will not convert and return empty
    const AnyType anytype{2, UnsignedInteger16Type};
    const AnyValue value = ArrayValue({{UnsignedInteger8Type, 42U}, 43U, 44U});
    const AnyValue expected{};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Array of smaller size will not convert and return empty
    const AnyType anytype{3, UnsignedInteger16Type};
    const AnyValue value = ArrayValue({{UnsignedInteger8Type, 42U}, 43U});
    const AnyValue expected{};
    auto result = TryConvertAllowExtraSourceFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
}

TEST(AnyValueHelperTest, ConvertAllowExtraTargetFieldsToEmptyTargetType)
{
  {
    // Emtpy value succeeds
    const AnyType anytype{};
    const AnyValue value{};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second, value);
  }
  {
    // Scalar value fails
    const AnyType anytype{};
    const AnyValue value{UnsignedInteger64Type, 42U};
    const AnyValue expected{};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Struct value fails
    const AnyType anytype{};
    const AnyValue value = {
        {{"mode", {UnsignedInteger16Type, 3U}}, {"setpoint", {Float64Type, 3.14}}}};
    const AnyValue expected{};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Array value fails
    const AnyType anytype{};
    const AnyValue value = ArrayValue({0, 1, 2, 3, 4});
    const AnyValue expected{};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
}

TEST(AnyValueHelperTest, ConvertAllowExtraTargetFieldsToScalarTargetType)
{
  {
    // Simple scalar conversion
    const AnyType anytype{UnsignedInteger32Type};
    const AnyValue value{UnsignedInteger8Type, 42U};
    const AnyValue expected{UnsignedInteger32Type, 42U};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Scalar that doesn't allow conversion (too big) will fail and return empty value
    const AnyType anytype{UnsignedInteger8Type};
    const AnyValue value{UnsignedInteger32Type, 1729U};
    const AnyValue expected{};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Struct value fails
    const AnyType anytype{UnsignedInteger32Type};
    const AnyValue value = {
        {{"value", {UnsignedInteger8Type, 3U}}, {"ignored", "this field will not be considered"}}};
    const AnyValue expected{};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Array value fails
    const AnyType anytype{UnsignedInteger32Type};
    const AnyValue value = ArrayValue({0, 1, 2, 3, 4});
    const AnyValue expected{};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
}

TEST(AnyValueHelperTest, ConvertAllowExtraTargetFieldsToStructTargetType)
{
  {
    // Scalar will not convert to struct
    const AnyType anytype{{{"mode", UnsignedInteger32Type}, {"description", StringType}}};
    const AnyValue value{UnsignedInteger8Type, 42U};
    const AnyValue expected{};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Struct with same fields will do only scalar conversion of leafs
    const AnyType anytype{{{"mode", UnsignedInteger32Type}, {"description", StringType}}};
    const AnyValue value = {{{"mode", {UnsignedInteger8Type, 42U}},
                             {"description", "this field does not need conversion"}}};
    const AnyValue expected = {{{"mode", {UnsignedInteger32Type, 42U}},
                                {"description", "this field does not need conversion"}}};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Struct with subset of fields will only convert those to the result value
    const AnyType anytype{
        {{"mode", UnsignedInteger32Type}, {"description", StringType}, {"flag", BooleanType}}};
    const AnyValue value = {{{"mode", {UnsignedInteger8Type, 42U}}, {"flag", true}}};
    const AnyValue expected = {{{"mode", {UnsignedInteger32Type, 42U}}, {"flag", true}}};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Structs with mismatching fields will fail and return empty
    const AnyType anytype{{{"mode", UnsignedInteger32Type}, {"flag", BooleanType}}};
    const AnyValue value = {{{"mode", {UnsignedInteger8Type, 42U}}, {"no_flag", true}}};
    const AnyValue expected{};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Struct with superset of fields will not convert and return empty
    const AnyType anytype{{{"mode", UnsignedInteger32Type}}};
    const AnyValue value = {
        {{"mode", {UnsignedInteger8Type, 42U}}, {"description", {StringType, "field_too_much"}}}};
    const AnyValue expected{};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
}

TEST(AnyValueHelperTest, ConvertAllowExtraTargetFieldsToStructTargetType_Complex)
{
  {
    // Struct of two similar structs
    const AnyType anytype{{
        {"sys1",
         {{{"setpoint", {sup::dto::Float64Type}}, {"mode", {sup::dto::UnsignedInteger16Type}}}}},
        {"sys2",
         {{{"setpoint", {sup::dto::Float64Type}}, {"mode", {sup::dto::UnsignedInteger16Type}}}}},
    }};
    const AnyValue value{{
        {"sys2", {{{"setpoint", {sup::dto::Float32Type, 10.0}}}}},
    }};
    const AnyValue expected{{
        {"sys2", {{{"setpoint", {sup::dto::Float64Type, 10.0}}}}},
    }};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second, expected);
    EXPECT_EQ(result.second.GetType(), expected.GetType());
  }
}

TEST(AnyValueHelperTest, ConvertAllowExtraTargetFieldsToArrayTargetType)
{
  {
    // Scalar will not convert to array
    const AnyType anytype{2, UnsignedInteger16Type};
    const AnyValue value{UnsignedInteger8Type, 42U};
    const AnyValue expected{};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Struct will not convert to array
    const AnyType anytype{2, UnsignedInteger16Type};
    const AnyValue value = {
        {{"0", {UnsignedInteger8Type, 42U}}, {"1", {UnsignedInteger8Type, 42U}}}};
    const AnyValue expected{};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Array of right size will convert
    const AnyType anytype{2, UnsignedInteger16Type};
    const AnyValue value = ArrayValue({{UnsignedInteger8Type, 42U}, 43U});
    const AnyValue expected = ArrayValue({{UnsignedInteger16Type, 42U}, 43U});
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Array of larger size will not convert and return empty
    const AnyType anytype{2, UnsignedInteger16Type};
    const AnyValue value = ArrayValue({{UnsignedInteger8Type, 42U}, 43U, 44U});
    const AnyValue expected{};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
  {
    // Array of smaller size will not convert and return empty
    const AnyType anytype{3, UnsignedInteger16Type};
    const AnyValue value = ArrayValue({{UnsignedInteger8Type, 42U}, 43U});
    const AnyValue expected{};
    auto result = TryConvertAllowExtraTargetFields(value, anytype);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, expected);
  }
}
