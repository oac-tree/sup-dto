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

#include <sup/dto/anyvalue.h>

using namespace sup::dto;

TEST(AnyValueFieldTest, SimpleStruct)
{
  AnyValue two_scalars = {{
    {"signed", {SignedInteger8Type, 1}},
    {"unsigned", {UnsignedInteger8Type, 12}}
  }};
  EXPECT_TRUE(IsStructValue(two_scalars));
  EXPECT_TRUE(two_scalars.HasField("signed"));
  EXPECT_TRUE(two_scalars.HasField("unsigned"));
  EXPECT_FALSE(two_scalars.HasField("absent"));
  EXPECT_FALSE(two_scalars.HasField("signed.absent"));
  EXPECT_FALSE(two_scalars.HasField("signed.[0]"));
  EXPECT_FALSE(two_scalars.HasField("signed[0]"));
}

TEST(AnyValueFieldTest, NestedStruct)
{
  const std::string nested_name = "nested_struct";
  AnyValue two_scalars = {{
    {"signed", {SignedInteger8Type, 1}},
    {"unsigned", {UnsignedInteger8Type, 12}}
  }};
  AnyValue nested_val{{
    {"scalars", two_scalars},
    {"single", {
      {"first", {SignedInteger8Type, 0}},
      {"second", {SignedInteger8Type, 5}}
    }}
  }, nested_name};
  EXPECT_TRUE(IsStructValue(nested_val));
  EXPECT_TRUE(nested_val.HasField("scalars"));
  EXPECT_TRUE(nested_val.HasField("scalars.signed"));
  EXPECT_TRUE(nested_val.HasField("scalars.unsigned"));
  EXPECT_TRUE(nested_val.HasField("single"));
  EXPECT_TRUE(nested_val.HasField("single.first"));
  EXPECT_TRUE(nested_val.HasField("single.second"));
  EXPECT_FALSE(nested_val.HasField("absent"));
  EXPECT_FALSE(nested_val.HasField("scalars.absent"));
  EXPECT_FALSE(nested_val.HasField("scalars.[0]"));
  EXPECT_FALSE(nested_val.HasField("scalars[0]"));
  EXPECT_FALSE(nested_val.HasField("scalars.signed.absent"));
  EXPECT_FALSE(nested_val.HasField("scalars.signed.[0]"));
  EXPECT_FALSE(nested_val.HasField("scalars.signed[0]"));
}

TEST(AnyValueFieldTest, SimpleArray)
{
  AnyValue array_val = ArrayValue({{UnsignedInteger16Type, 0}, 10 ,20 ,30});
  EXPECT_TRUE(IsArrayValue(array_val));
  EXPECT_TRUE(array_val.HasField("[0]"));
  EXPECT_TRUE(array_val.HasField("[3]"));
  EXPECT_FALSE(array_val.HasField("[4]"));
  EXPECT_FALSE(array_val.HasField("absent"));
  EXPECT_FALSE(array_val.HasField("[0].absent"));
  EXPECT_FALSE(array_val.HasField("[0]absent"));
}

TEST(AnyValueFieldTest, ArrayOfStruct)
{
  AnyValue two_scalars = {{
    {"first", {UnsignedInteger16Type, 1}},
    {"second", {UnsignedInteger16Type, 2}}
  }};
  AnyValue array_val = ArrayValue({ two_scalars, two_scalars, two_scalars }, "array_of_structs");
  EXPECT_TRUE(IsArrayValue(array_val));
  EXPECT_TRUE(array_val.HasField("[0]"));
  EXPECT_TRUE(array_val.HasField("[2]"));
  EXPECT_TRUE(array_val.HasField("[0]first"));
  EXPECT_TRUE(array_val.HasField("[0].second"));
  EXPECT_FALSE(array_val.HasField("[4]"));
  EXPECT_FALSE(array_val.HasField("[0]absent"));
  EXPECT_FALSE(array_val.HasField("[0].absent"));
  EXPECT_FALSE(array_val.HasField("absent"));
}

TEST(AnyValueFieldTest, ParseFailure)
{
  AnyValue array_val = ArrayValue({{UnsignedInteger16Type, 0}, 10 ,20 ,30});
  EXPECT_TRUE(IsArrayValue(array_val));
  EXPECT_TRUE(array_val.HasField("[0]"));
  EXPECT_TRUE(array_val.HasField("[3]"));
  EXPECT_FALSE(array_val.HasField("[0"));
  EXPECT_FALSE(array_val.HasField("]"));
  EXPECT_FALSE(array_val.HasField(".absent"));
}
