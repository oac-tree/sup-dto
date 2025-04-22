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
 * Copyright (c) : 2010-2025 ITER Organization,
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

#include "anyvalue_meta.h"

#include <gtest/gtest.h>

#include <sup/dto/anyvalue.h>

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
  EXPECT_TRUE(copy.HasField("scalars"));
  EXPECT_TRUE(copy.HasField("single"));
  EXPECT_FALSE(copy.HasField("index"));

  copy.AddMember("index", {UnsignedInteger64Type, 2022});
  EXPECT_NE(copy, nested_val);
  EXPECT_TRUE(IsStructValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(copy.GetTypeName(), nested_name);
  EXPECT_TRUE(copy.HasField("scalars"));
  EXPECT_TRUE(copy.HasField("single"));
  EXPECT_TRUE(copy.HasField("index"));
}

TEST(AnyValueTest, PointerConstruction)
{
  // valid constructor argument types (without conversion)
  EXPECT_TRUE(IsValidAnyValueConstructorArgument<boolean>::value);
  EXPECT_TRUE(IsValidAnyValueConstructorArgument<char8>::value);
  EXPECT_TRUE(IsValidAnyValueConstructorArgument<int8>::value);
  EXPECT_TRUE(IsValidAnyValueConstructorArgument<uint8>::value);
  EXPECT_TRUE(IsValidAnyValueConstructorArgument<int16>::value);
  EXPECT_TRUE(IsValidAnyValueConstructorArgument<uint16>::value);
  EXPECT_TRUE(IsValidAnyValueConstructorArgument<int32>::value);
  EXPECT_TRUE(IsValidAnyValueConstructorArgument<uint32>::value);
  EXPECT_TRUE(IsValidAnyValueConstructorArgument<int64>::value);
  EXPECT_TRUE(IsValidAnyValueConstructorArgument<uint64>::value);
  EXPECT_TRUE(IsValidAnyValueConstructorArgument<float32>::value);
  EXPECT_TRUE(IsValidAnyValueConstructorArgument<float64>::value);
  EXPECT_TRUE(IsValidAnyValueConstructorArgument<const std::string&>::value);
  EXPECT_TRUE(IsValidAnyValueConstructorArgument<const char*>::value);

  // valid constructor argument types (with conversion)
  EXPECT_TRUE(IsValidAnyValueConstructorArgument<std::string>::value);
  EXPECT_TRUE(IsValidAnyValueConstructorArgument<const std::string>::value);

  // invalid constructor argument types
  EXPECT_FALSE(IsValidAnyValueConstructorArgument<std::nullptr_t>::value);
  EXPECT_FALSE(IsValidAnyValueConstructorArgument<int*>::value);
  EXPECT_FALSE(IsValidAnyValueConstructorArgument<char*>::value);
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
  EXPECT_TRUE(copy.HasField("scalars"));
  EXPECT_TRUE(copy.HasField("single"));
  EXPECT_FALSE(copy.HasField("index"));

  copy.AddMember("index", {UnsignedInteger64Type, 2022});
  EXPECT_NE(copy, nested_val);
  EXPECT_TRUE(IsStructValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(copy.GetTypeName(), nested_name);
  EXPECT_TRUE(copy.HasField("scalars"));
  EXPECT_TRUE(copy.HasField("single"));
  EXPECT_TRUE(copy.HasField("index"));

  AnyValue copy_again{copy.GetType()};
  copy_again = copy;
  EXPECT_EQ(copy_again, copy);
  EXPECT_TRUE(IsStructValue(copy_again));
  EXPECT_EQ(copy_again.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(copy_again.GetTypeName(), nested_name);
  EXPECT_TRUE(copy_again.HasField("scalars"));
  EXPECT_TRUE(copy_again.HasField("single"));
  EXPECT_TRUE(copy_again.HasField("index"));
}

TEST(AnyValueTest, MoveConstruction)
{
  {
    // Move ctor of nested structure
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
    EXPECT_TRUE(moved.HasField("scalars"));
    EXPECT_TRUE(moved.HasField("single"));
    EXPECT_FALSE(moved.HasField("index"));

    moved.AddMember("index", {UnsignedInteger64Type, 2022});
    EXPECT_NE(moved, nested_val);
    EXPECT_TRUE(IsStructValue(moved));
    EXPECT_EQ(moved.GetTypeCode(), TypeCode::Struct);
    EXPECT_EQ(moved.GetTypeName(), nested_name);
    EXPECT_TRUE(moved.HasField("scalars"));
    EXPECT_TRUE(moved.HasField("single"));
    EXPECT_TRUE(moved.HasField("index"));
  }
  {
    // Move construction of locked value
    AnyType two_scalars_t = {{
      {"signed", SignedInteger8Type },
      {"unsigned", UnsignedInteger8Type }
    }};
    AnyValue array{2, two_scalars_t};
    AnyValue el_1{std::move(array[0])};
    EXPECT_EQ(el_1.GetType(), two_scalars_t);
    EXPECT_THROW(array[0].AddMember("test", true), InvalidOperationException);
    EXPECT_NO_THROW(el_1.AddMember("test", true));
    EXPECT_TRUE(el_1.HasField("test"));
  }
}

TEST(AnyValueTest, MoveAssignment)
{
  {
    // Move assignment of nested structure
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
    EXPECT_TRUE(moved.HasField("scalars"));
    EXPECT_TRUE(moved.HasField("single"));
    EXPECT_FALSE(moved.HasField("index"));

    moved.AddMember("index", {UnsignedInteger64Type, 2022});
    EXPECT_NE(moved, nested_val);
    EXPECT_TRUE(IsStructValue(moved));
    EXPECT_EQ(moved.GetTypeCode(), TypeCode::Struct);
    EXPECT_EQ(moved.GetTypeName(), nested_name);
    EXPECT_TRUE(moved.HasField("scalars"));
    EXPECT_TRUE(moved.HasField("single"));
    EXPECT_TRUE(moved.HasField("index"));

    AnyValue moved_again{moved.GetType()};
    moved_again = std::move(moved);
    EXPECT_NE(moved_again, moved);
    EXPECT_TRUE(IsStructValue(moved_again));
    EXPECT_EQ(moved_again.GetTypeCode(), TypeCode::Struct);
    EXPECT_EQ(moved_again.GetTypeName(), nested_name);
    EXPECT_TRUE(moved_again.HasField("scalars"));
    EXPECT_TRUE(moved_again.HasField("single"));
    EXPECT_TRUE(moved_again.HasField("index"));
  }
  {
    // Move assignment of locked value
    AnyType two_scalars_t = {{
      {"signed", SignedInteger8Type },
      {"unsigned", UnsignedInteger8Type }
    }};
    AnyValue array{2, two_scalars_t};
    AnyValue el_1;
    el_1 = std::move(array[0]);
    EXPECT_EQ(el_1.GetType(), two_scalars_t);
    EXPECT_THROW(array[0].AddMember("test", true), InvalidOperationException);
    EXPECT_NO_THROW(el_1.AddMember("test", true));
    EXPECT_TRUE(el_1.HasField("test"));
  }
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
  EXPECT_TRUE(copy.HasField("scalars"));
  EXPECT_TRUE(copy.HasField("single"));
  EXPECT_FALSE(copy.HasField("index"));

  copy.AddMember("index", {UnsignedInteger64Type, 2022});
  EXPECT_NE(copy, nested_val);
  EXPECT_TRUE(IsStructValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(copy.GetTypeName(), nested_name);
  EXPECT_TRUE(copy.HasField("scalars"));
  EXPECT_TRUE(copy.HasField("single"));
  EXPECT_TRUE(copy.HasField("index"));
}

TEST(AnyValueTest, CreateEmptyFields)
{
  // Allow creating a structure value with an empty value as member
  EXPECT_NO_THROW(AnyValue({
                 {"number", {SignedInteger16Type, 8765}},
                 {"empty", AnyValue{}}
               }, "EmptyMemberStruct"));
  AnyValue my_struct = EmptyStruct("MyStruct");
  EXPECT_NO_THROW(my_struct.AddMember("number", 0));
  EXPECT_NO_THROW(my_struct.AddMember("empty", AnyValue{}));

  // Do not allow creating an array of empty types
  EXPECT_THROW(AnyValue(12, EmptyType), InvalidOperationException);
}

TEST(AnyValueTest, AssignEmptyFields)
{
  // Allow assigning the empty value to an empty value
  AnyValue empty{};
  EXPECT_NO_THROW(empty = AnyValue{});

  // Allow assigning an empty value to a scalar value
  AnyValue my_scalar = {StringType, "scalarname"};
  EXPECT_NO_THROW(my_scalar = AnyValue{});

  // Allow assigning an empty value to a member
  AnyValue my_struct({
    {"number", {SignedInteger16Type, -99}},
    {"other", false}
  }, "MyStruct");
  EXPECT_NO_THROW(my_struct["other"] = AnyValue{});

  // Do not allow assignment to an array element if that changes its type
  AnyValue my_array(4, UnsignedInteger64Type);
  EXPECT_THROW(my_array[0] = AnyValue{}, InvalidConversionException);
}
