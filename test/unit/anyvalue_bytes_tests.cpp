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

#include <sup/dto/parse/ctype_parser.h>

#include <sup/dto/anyvalue.h>

#include <cstring>

using namespace sup::dto;

TEST(AnyValueBytesTest, Empty)
{
  // Empty value
  AnyValue value{};
  {
    // Using host order
    const auto bytes = ToBytes(value);
    AnyValue parsed{value.GetType()};
    EXPECT_NO_THROW(FromBytes(parsed, bytes.data(), bytes.size()));
    EXPECT_EQ(parsed, value);
  }
  {
    // Using network order
    const auto bytes = ToNetworkOrderBytes(value);
    AnyValue parsed{value.GetType()};
    EXPECT_NO_THROW(FromNetworkOrderBytes(parsed, bytes.data(), bytes.size()));
    EXPECT_EQ(parsed, value);
  }
}

TEST(AnyValueBytesTest, Structure)
{
  // Structure with valid string length
  AnyValue value = {{
    {"street", {StringType, "Main street"}},
    {"number", {UnsignedInteger16Type, 1033}}
  }};
  {
    // Using host order
    const auto bytes = ToBytes(value);
    AnyValue parsed{value.GetType()};
    EXPECT_NO_THROW(FromBytes(parsed, bytes.data(), bytes.size()));
    EXPECT_EQ(parsed, value);
  }
  {
    // Using network order
    const auto bytes = ToNetworkOrderBytes(value);
    AnyValue parsed{value.GetType()};
    EXPECT_NO_THROW(FromNetworkOrderBytes(parsed, bytes.data(), bytes.size()));
    EXPECT_EQ(parsed, value);
  }
}

TEST(AnyValueBytesTest, Array)
{
  // Array
  AnyValue value = ArrayValue({42, 43, 44, 45});
  {
    // Using host order
    const auto bytes = ToBytes(value);
    AnyValue parsed{value.GetType()};
    EXPECT_NO_THROW(FromBytes(parsed, bytes.data(), bytes.size()));
    EXPECT_EQ(parsed, value);
  }
  {
    // Using network order
    const auto bytes = ToNetworkOrderBytes(value);
    AnyValue parsed{value.GetType()};
    EXPECT_NO_THROW(FromNetworkOrderBytes(parsed, bytes.data(), bytes.size()));
    EXPECT_EQ(parsed, value);
  }
}

TEST(AnyValueBytesTest, NestedStructure)
{
  // Nested structure with valid string length
  AnyValue value = {{
    {"name", {StringType, "Jimi"}},
    {"address", {
      {"street", {StringType, "Main street"}},
      {"number", {UnsignedInteger16Type, 1033}}
    }}
  }};
  {
    // Using host order
    const auto bytes = ToBytes(value);
    AnyValue parsed{value.GetType()};
    EXPECT_NO_THROW(FromBytes(parsed, bytes.data(), bytes.size()));
    EXPECT_EQ(parsed, value);
  }
  {
    // Using network order
    const auto bytes = ToNetworkOrderBytes(value);
    AnyValue parsed{value.GetType()};
    EXPECT_NO_THROW(FromNetworkOrderBytes(parsed, bytes.data(), bytes.size()));
    EXPECT_EQ(parsed, value);
  }
}

TEST(AnyValueBytesTest, ArrayOfStructs)
{
  // Array with structure elements
  AnyType struct_t{{
    {"setpoint", Float64Type},
    {"mode", UnsignedInteger16Type}
  }};
  AnyValue el_1{struct_t};
  el_1["setpoint"] = 3.14;
  el_1["mode"] = 42U;
  AnyValue el_2{struct_t};
  el_1["setpoint"] = 10.0;
  el_1["mode"] = 1U;
  // Array
  AnyValue value = ArrayValue({el_1, el_2});
  {
    // Using host order
    const auto bytes = ToBytes(value);
    AnyValue parsed{value.GetType()};
    EXPECT_NO_THROW(FromBytes(parsed, bytes.data(), bytes.size()));
    EXPECT_EQ(parsed, value);
  }
  {
    // Using network order
    const auto bytes = ToNetworkOrderBytes(value);
    AnyValue parsed{value.GetType()};
    EXPECT_NO_THROW(FromNetworkOrderBytes(parsed, bytes.data(), bytes.size()));
    EXPECT_EQ(parsed, value);
  }
}

TEST(AnyValueBytesTest, StructureWithArray)
{
  // Structure with array member
  AnyValue value = {{
    {"name", {StringType, "Jimi"}},
    {"friends", ArrayValue({"Lisa", "Dave", "Freddy"})}
  }};
  {
    // Using host order
    const auto bytes = ToBytes(value);
    AnyValue parsed{value.GetType()};
    EXPECT_NO_THROW(FromBytes(parsed, bytes.data(), bytes.size()));
    EXPECT_EQ(parsed, value);
  }
  {
    // Using network order
    const auto bytes = ToNetworkOrderBytes(value);
    AnyValue parsed{value.GetType()};
    EXPECT_NO_THROW(FromNetworkOrderBytes(parsed, bytes.data(), bytes.size()));
    EXPECT_EQ(parsed, value);
  }
}
