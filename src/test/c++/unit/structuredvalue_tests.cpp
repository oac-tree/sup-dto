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
#include <sup/dto/anyvalue_exceptions.h>

using namespace sup::dto;

TEST(StructuredValueTest, StructValue)
{
  AnyValue my_struct{{
    {"index", {UnsignedInteger64Type, 1}},
    {"coordinates", {{
      {"x", 0},
      {"y", 5}
    }, "coord_t"}},
    {"enabled", true}
  }, "my_struct_t"};
  EXPECT_EQ(my_struct["index"], 1);
  EXPECT_EQ(my_struct["coordinates.x"], 0);
  EXPECT_EQ(my_struct["coordinates.y"], 5);
  EXPECT_EQ(my_struct["enabled"], true);
  my_struct["coordinates.x"] = 23;
  EXPECT_EQ(my_struct["coordinates.x"], 23);
}

TEST(StructuredValueTest, InvalidMemberFieldName)
{
  AnyValue two_scalars{{
    {"signed", {SignedInteger8Type, -5}},
    {"unsigned", {UnsignedInteger8Type, 22}}
  }};
  EXPECT_THROW(two_scalars.AddMember("", true), InvalidOperationException);
  EXPECT_THROW(two_scalars.AddMember("signed.subfield", true), InvalidOperationException);
  EXPECT_THROW(two_scalars.AddMember("signed", true), InvalidOperationException);
}

TEST(StructuredValueTest, StructEqualityName)
{
  AnyValue two_scalars{{
    {"signed", {SignedInteger8Type, -5}},
    {"unsigned", {UnsignedInteger8Type, 22}}
  }};
  AnyValue other(two_scalars);
  EXPECT_EQ(two_scalars, other);
  two_scalars.AddMember("status", true);
  EXPECT_NE(two_scalars, other);
  EXPECT_NE(other, two_scalars);
}

TEST(StructuredValueTest, InvalidStructAssign)
{
  AnyValue two_scalars{{
    {"signed", {SignedInteger8Type, -5}},
    {"unsigned", {UnsignedInteger8Type, 22}}
  }};
  AnyValue other(two_scalars);
  EXPECT_EQ(two_scalars, other);
  two_scalars.AddMember("status", true);
  EXPECT_NE(two_scalars, other);

  EXPECT_THROW(two_scalars = other, InvalidConversionException);
  EXPECT_NE(two_scalars, other);

  AnyValue index{UnsignedInteger64Type, 1};
  EXPECT_THROW(two_scalars = index, InvalidConversionException);
  EXPECT_NE(two_scalars, index);
}

TEST(StructuredValueTest, MemberAccess)
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
  EXPECT_EQ(nested_val.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(nested_val.GetTypeName(), nested_name);

  AnyType nested_type{{
    {"scalars", two_scalars.GetType()},
    {"single", {
      {"first", SignedInteger8Type},
      {"second", SignedInteger8Type}
    }}
  }, nested_name};
  EXPECT_EQ(nested_val.GetType(), nested_type);

  EXPECT_TRUE(nested_val.HasMember("scalars"));
  EXPECT_TRUE(nested_val.HasMember("single"));
  EXPECT_FALSE(nested_val.HasMember("index"));
  auto member_fields = nested_val.MemberNames();
  EXPECT_EQ(member_fields.size(), 2);
  EXPECT_EQ(nested_val.NumberOfMembers(), 2);
  EXPECT_EQ(member_fields[0], "scalars");
  EXPECT_EQ(member_fields[1], "single");
  nested_val.AddMember("index", {UnsignedInteger64Type, 2022});
  EXPECT_TRUE(nested_val.HasMember("index"));
  member_fields = nested_val.MemberNames();
  EXPECT_EQ(member_fields.size(), 3);
  EXPECT_EQ(nested_val.NumberOfMembers(), 3);
  EXPECT_EQ(member_fields[0], "scalars");
  EXPECT_EQ(member_fields[1], "single");
  EXPECT_EQ(member_fields[2], "index");

  // test presence of composite field indices
  EXPECT_TRUE(nested_val.HasMember("scalars.signed"));
  EXPECT_FALSE(nested_val.HasMember("scalars.unknown"));

  // test values of fields
  EXPECT_EQ(nested_val["scalars.signed"], 1);
  EXPECT_EQ(nested_val["scalars.unsigned"], 12);
  EXPECT_EQ(nested_val["single.first"], 0);
  EXPECT_EQ(nested_val["single.second"], 5);
  EXPECT_EQ(nested_val["index"], 2022);

  // test member access for empty value
  AnyValue empty_value;
  EXPECT_THROW(empty_value.AddMember("throws", true), InvalidOperationException);
  EXPECT_FALSE(empty_value.HasMember("throws"));
  EXPECT_EQ(empty_value.MemberNames().size(), 0);
  EXPECT_EQ(empty_value.NumberOfMembers(), 0);

  // test member access for scalar value
  AnyValue scalar_value(Float32Type);
  EXPECT_THROW(scalar_value.AddMember("throws", 1.0), InvalidOperationException);
  EXPECT_FALSE(scalar_value.HasMember("throws"));
  EXPECT_EQ(scalar_value.MemberNames().size(), 0);
  EXPECT_EQ(scalar_value.NumberOfMembers(), 0);
}
