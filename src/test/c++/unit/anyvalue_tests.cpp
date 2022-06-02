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

#include "sup/dto/anyvalue.h"

using namespace sup::dto;

TEST(AnyValueTest, CopyConstruction)
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

  AnyValue copy = nested_val;
  EXPECT_EQ(copy, nested_val);
  EXPECT_TRUE(IsStructValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(copy.GetTypeName(), nested_name);
  EXPECT_TRUE(copy.HasMember("scalars"));
  EXPECT_TRUE(copy.HasMember("single"));
  EXPECT_FALSE(copy.HasMember("index"));

  copy.AddMember("index", {UnsignedInteger64Type, 2022});
  EXPECT_NE(copy, nested_val);
  EXPECT_TRUE(IsStructValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(copy.GetTypeName(), nested_name);
  EXPECT_TRUE(copy.HasMember("scalars"));
  EXPECT_TRUE(copy.HasMember("single"));
  EXPECT_TRUE(copy.HasMember("index"));
}

TEST(AnyValueTest, CopyAssignment)
{
  const std::string nested_name = "nested_struct";
  AnyValue two_scalars = {{
    {"signed", {SignedInteger8Type, 1}},
    {"unsigned", {UnsignedInteger8Type, 12}}
  }};
  AnyValue nested_val = (EmptyStruct(nested_name)
                            .AddMember("scalars", two_scalars)
                            .AddMember("single", EmptyStruct()
                                .AddMember("first", {SignedInteger8Type, 0})
                                .AddMember("second", {SignedInteger8Type, 5})));
  EXPECT_TRUE(IsStructValue(nested_val));
  EXPECT_EQ(nested_val.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(nested_val.GetTypeName(), nested_name);

  AnyValue copy;
  copy = nested_val;
  EXPECT_EQ(copy, nested_val);
  EXPECT_TRUE(IsStructValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(copy.GetTypeName(), nested_name);
  EXPECT_TRUE(copy.HasMember("scalars"));
  EXPECT_TRUE(copy.HasMember("single"));
  EXPECT_FALSE(copy.HasMember("index"));

  copy.AddMember("index", {UnsignedInteger64Type, 2022});
  EXPECT_NE(copy, nested_val);
  EXPECT_TRUE(IsStructValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(copy.GetTypeName(), nested_name);
  EXPECT_TRUE(copy.HasMember("scalars"));
  EXPECT_TRUE(copy.HasMember("single"));
  EXPECT_TRUE(copy.HasMember("index"));

  AnyValue copy_again{copy.GetType()};
  copy_again = copy;
  EXPECT_EQ(copy_again, copy);
  EXPECT_TRUE(IsStructValue(copy_again));
  EXPECT_EQ(copy_again.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(copy_again.GetTypeName(), nested_name);
  EXPECT_TRUE(copy_again.HasMember("scalars"));
  EXPECT_TRUE(copy_again.HasMember("single"));
  EXPECT_TRUE(copy_again.HasMember("index"));
}

TEST(AnyValueTest, MoveConstruction)
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

  AnyValue moved = std::move(nested_val);
  EXPECT_NE(moved, nested_val);
  EXPECT_TRUE(IsStructValue(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(moved.GetTypeName(), nested_name);
  EXPECT_TRUE(moved.HasMember("scalars"));
  EXPECT_TRUE(moved.HasMember("single"));
  EXPECT_FALSE(moved.HasMember("index"));

  moved.AddMember("index", {UnsignedInteger64Type, 2022});
  EXPECT_NE(moved, nested_val);
  EXPECT_TRUE(IsStructValue(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(moved.GetTypeName(), nested_name);
  EXPECT_TRUE(moved.HasMember("scalars"));
  EXPECT_TRUE(moved.HasMember("single"));
  EXPECT_TRUE(moved.HasMember("index"));
}

TEST(AnyValueTest, MoveAssignment)
{
  const std::string nested_name = "nested_struct";
  AnyValue two_scalars = {{
    {"signed", {SignedInteger8Type, 1}},
    {"unsigned", {UnsignedInteger8Type, 12}}
  }};
  AnyValue nested_val = (EmptyStruct(nested_name)
                            .AddMember("scalars", two_scalars)
                            .AddMember("single", EmptyStruct()
                                .AddMember("first", {SignedInteger8Type, 0})
                                .AddMember("second", {SignedInteger8Type, 5})));
  EXPECT_TRUE(IsStructValue(nested_val));
  EXPECT_EQ(nested_val.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(nested_val.GetTypeName(), nested_name);

  AnyValue moved;
  moved = std::move(nested_val);
  EXPECT_NE(moved, nested_val);
  EXPECT_TRUE(IsStructValue(moved));
  EXPECT_TRUE(IsEmptyValue(nested_val));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(moved.GetTypeName(), nested_name);
  EXPECT_TRUE(moved.HasMember("scalars"));
  EXPECT_TRUE(moved.HasMember("single"));
  EXPECT_FALSE(moved.HasMember("index"));

  moved.AddMember("index", {UnsignedInteger64Type, 2022});
  EXPECT_NE(moved, nested_val);
  EXPECT_TRUE(IsStructValue(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(moved.GetTypeName(), nested_name);
  EXPECT_TRUE(moved.HasMember("scalars"));
  EXPECT_TRUE(moved.HasMember("single"));
  EXPECT_TRUE(moved.HasMember("index"));

  AnyValue moved_again{moved.GetType()};
  moved_again = std::move(moved);
  EXPECT_NE(moved_again, moved);
  EXPECT_TRUE(IsStructValue(moved_again));
  EXPECT_TRUE(IsEmptyValue(moved));
  EXPECT_EQ(moved_again.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(moved_again.GetTypeName(), nested_name);
  EXPECT_TRUE(moved_again.HasMember("scalars"));
  EXPECT_TRUE(moved_again.HasMember("single"));
  EXPECT_TRUE(moved_again.HasMember("index"));
}

TEST(AnyValueTest, CastToAnyValue)
{
  const std::string nested_name = "nested_struct";
  AnyValue two_scalars = {{
    {"signed", {SignedInteger8Type, 1}},
    {"unsigned", {UnsignedInteger8Type, 12}}
  }};
  AnyValue nested_val = (EmptyStruct(nested_name)
                            .AddMember("scalars", two_scalars)
                            .AddMember("single", EmptyStruct()
                                .AddMember("first", {SignedInteger8Type, 0})
                                .AddMember("second", {SignedInteger8Type, 5})));
  EXPECT_TRUE(IsStructValue(nested_val));
  EXPECT_EQ(nested_val.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(nested_val.GetTypeName(), nested_name);

  AnyValue copy = nested_val.As<AnyValue>();
  EXPECT_EQ(copy, nested_val);
  EXPECT_TRUE(IsStructValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(copy.GetTypeName(), nested_name);
  EXPECT_TRUE(copy.HasMember("scalars"));
  EXPECT_TRUE(copy.HasMember("single"));
  EXPECT_FALSE(copy.HasMember("index"));

  copy.AddMember("index", {UnsignedInteger64Type, 2022});
  EXPECT_NE(copy, nested_val);
  EXPECT_TRUE(IsStructValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(copy.GetTypeName(), nested_name);
  EXPECT_TRUE(copy.HasMember("scalars"));
  EXPECT_TRUE(copy.HasMember("single"));
  EXPECT_TRUE(copy.HasMember("index"));
}

TEST(AnyValueTest, CreateEmptyFields)
{
  // Do not allow creating a structure value with an empty value as member
  EXPECT_THROW(AnyValue({
                 {"number", {SignedInteger16Type, 8765}},
                 {"empty", AnyValue{}}
               }, "EmptyMemberStruct"), InvalidOperationException);
  AnyValue my_struct = EmptyStruct("MyStruct");
  EXPECT_NO_THROW(my_struct.AddMember("number", 0));
  EXPECT_THROW(my_struct.AddMember("empty", AnyValue{}), InvalidOperationException);

  // Do not allow creating an array of empty types
  EXPECT_THROW(AnyValue(12, EmptyType), InvalidOperationException);
}

TEST(AnyValueTest, AssignEmptyFields)
{
  // Allow assigning the empty value to an empty value
  AnyValue empty{};
  EXPECT_NO_THROW(empty = AnyValue{});

  // Do not allow assigning an empty value to a scalar value
  AnyValue my_scalar = {StringType, "scalarname"};
  EXPECT_THROW(my_scalar = AnyValue{}, InvalidConversionException);

  // Do not allow assigning an empty value to a member
  AnyValue my_struct({
    {"number", {SignedInteger16Type, -99}},
    {"other", false}
  }, "MyStruct");
  EXPECT_THROW(my_struct["other"] = AnyValue{}, InvalidConversionException);

  // Do not allow assigning the empty value as the element value of an array
  AnyValue my_array(4, UnsignedInteger64Type);
  EXPECT_THROW(my_array[0] = AnyValue{}, InvalidConversionException);
}