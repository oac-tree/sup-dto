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

#include <sup/dto/anyvalue.h>

using namespace sup::dto;

TEST(AnyValueFieldTest, SimpleStruct)
{
  AnyValue two_scalars = {{
    {"signed", {SignedInteger8Type, 1}},
    {"unsigned", {UnsignedInteger8Type, 12}}
  }};
  EXPECT_TRUE(IsStructValue(two_scalars));
  EXPECT_TRUE(two_scalars.HasMember("signed"));
  EXPECT_TRUE(two_scalars.HasMember("unsigned"));
  EXPECT_FALSE(two_scalars.HasMember("absent"));
  EXPECT_FALSE(two_scalars.HasMember("signed.absent"));
  EXPECT_FALSE(two_scalars.HasMember("signed.[0]"));
  EXPECT_FALSE(two_scalars.HasMember("signed[0]"));
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
  EXPECT_TRUE(nested_val.HasMember("scalars"));
  EXPECT_TRUE(nested_val.HasMember("scalars.signed"));
  EXPECT_TRUE(nested_val.HasMember("scalars.unsigned"));
  EXPECT_TRUE(nested_val.HasMember("single"));
  EXPECT_TRUE(nested_val.HasMember("single.first"));
  EXPECT_TRUE(nested_val.HasMember("single.second"));
  EXPECT_FALSE(nested_val.HasMember("absent"));
  EXPECT_FALSE(nested_val.HasMember("scalars.absent"));
  EXPECT_FALSE(nested_val.HasMember("scalars.[0]"));
  EXPECT_FALSE(nested_val.HasMember("scalars[0]"));
  EXPECT_FALSE(nested_val.HasMember("scalars.signed.absent"));
  EXPECT_FALSE(nested_val.HasMember("scalars.signed.[0]"));
  EXPECT_FALSE(nested_val.HasMember("scalars.signed[0]"));
}

TEST(AnyValueFieldTest, DISABLED_SimpleArray)
{
  AnyValue array_val = ArrayValue({{UnsignedInteger16Type, 0}, 10 ,20 ,30});
  EXPECT_TRUE(IsArrayValue(array_val));
  EXPECT_TRUE(array_val.HasMember("[0]"));
  EXPECT_TRUE(array_val.HasMember("[3]"));
  EXPECT_FALSE(array_val.HasMember("[4]"));
  EXPECT_FALSE(array_val.HasMember("absent"));
  EXPECT_FALSE(array_val.HasMember("[0].absent"));
  EXPECT_FALSE(array_val.HasMember("[0]absent"));
}
