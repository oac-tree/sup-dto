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

#include <sup/dto/anytype.h>

using namespace sup::dto;

TEST(AnyTypeFieldTest, SimpleStruct)
{
  AnyType two_scalars = {{
    {"signed", SignedInteger8Type},
    {"unsigned", UnsignedInteger8Type}
  }};
  EXPECT_TRUE(IsStructType(two_scalars));
  EXPECT_TRUE(two_scalars.HasMember("signed"));
  EXPECT_TRUE(two_scalars.HasMember("unsigned"));
  EXPECT_FALSE(two_scalars.HasMember("absent"));
  EXPECT_FALSE(two_scalars.HasMember("signed.absent"));
  EXPECT_FALSE(two_scalars.HasMember("signed.[]"));
  EXPECT_FALSE(two_scalars.HasMember("signed[]"));
}

TEST(AnyTypeFieldTest, NestedStruct)
{
  const std::string nested_name = "nested_struct";
  AnyType two_scalars = {{
    {"signed", SignedInteger8Type},
    {"unsigned", UnsignedInteger8Type}
  }};
  AnyType nested_val{{
    {"scalars", two_scalars},
    {"single", {
      {"first", SignedInteger8Type},
      {"second", SignedInteger8Type}
    }}
  }, nested_name};
  EXPECT_TRUE(IsStructType(nested_val));
  EXPECT_TRUE(nested_val.HasMember("scalars"));
  EXPECT_TRUE(nested_val.HasMember("scalars.signed"));
  EXPECT_TRUE(nested_val.HasMember("scalars.unsigned"));
  EXPECT_TRUE(nested_val.HasMember("single"));
  EXPECT_TRUE(nested_val.HasMember("single.first"));
  EXPECT_TRUE(nested_val.HasMember("single.second"));
  EXPECT_FALSE(nested_val.HasMember("absent"));
  EXPECT_FALSE(nested_val.HasMember("scalars.absent"));
  EXPECT_FALSE(nested_val.HasMember("scalars.[]"));
  EXPECT_FALSE(nested_val.HasMember("scalars[]"));
  EXPECT_FALSE(nested_val.HasMember("scalars.signed.absent"));
  EXPECT_FALSE(nested_val.HasMember("scalars.signed.[]"));
  EXPECT_FALSE(nested_val.HasMember("scalars.signed[]"));
}

TEST(AnyTypeFieldTest, SimpleArray)
{
  AnyType array_type(3, UnsignedInteger16Type);
  EXPECT_TRUE(IsArrayType(array_type));
  EXPECT_TRUE(array_type.HasMember("[]"));
  EXPECT_FALSE(array_type.HasMember("[0]"));
  EXPECT_FALSE(array_type.HasMember("absent"));
  EXPECT_FALSE(array_type.HasMember("[].absent"));
  EXPECT_FALSE(array_type.HasMember("[]absent"));
}

TEST(AnyTypeFieldTest, ArrayOfStruct)
{
  AnyType two_scalars = {{
    {"first", UnsignedInteger16Type},
    {"second", UnsignedInteger16Type}
  }};
  AnyType array_type(2, two_scalars, "array_of_structs");
  EXPECT_TRUE(IsArrayType(array_type));
  EXPECT_TRUE(array_type.HasMember("[]"));
  EXPECT_TRUE(array_type.HasMember("[]first"));
  EXPECT_TRUE(array_type.HasMember("[].second"));
  EXPECT_FALSE(array_type.HasMember("[1]"));
  EXPECT_FALSE(array_type.HasMember("[]absent"));
  EXPECT_FALSE(array_type.HasMember("[].absent"));
  EXPECT_FALSE(array_type.HasMember("absent"));
}
