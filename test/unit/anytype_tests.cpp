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
#include <sup/dto/anyvalue_exceptions.h>

using namespace sup::dto;

TEST(AnyTypeTest, TypeCodes)
{
  EXPECT_TRUE(IsEmptyTypeCode(TypeCode::Empty));
  EXPECT_FALSE(IsStructTypeCode(TypeCode::Empty));
  EXPECT_FALSE(IsArrayTypeCode(TypeCode::Empty));
  EXPECT_FALSE(IsScalarTypeCode(TypeCode::Empty));

  EXPECT_FALSE(IsEmptyTypeCode(TypeCode::Struct));
  EXPECT_TRUE(IsStructTypeCode(TypeCode::Struct));
  EXPECT_FALSE(IsArrayTypeCode(TypeCode::Struct));
  EXPECT_FALSE(IsScalarTypeCode(TypeCode::Struct));

  EXPECT_FALSE(IsEmptyTypeCode(TypeCode::Array));
  EXPECT_FALSE(IsStructTypeCode(TypeCode::Array));
  EXPECT_TRUE(IsArrayTypeCode(TypeCode::Array));
  EXPECT_FALSE(IsScalarTypeCode(TypeCode::Array));

  EXPECT_FALSE(IsEmptyTypeCode(TypeCode::Int8));
  EXPECT_FALSE(IsStructTypeCode(TypeCode::Int8));
  EXPECT_FALSE(IsArrayTypeCode(TypeCode::Int8));
  EXPECT_TRUE(IsScalarTypeCode(TypeCode::Int8));

  EXPECT_FALSE(IsEmptyTypeCode(TypeCode::UInt8));
  EXPECT_FALSE(IsStructTypeCode(TypeCode::UInt8));
  EXPECT_FALSE(IsArrayTypeCode(TypeCode::UInt8));
  EXPECT_TRUE(IsScalarTypeCode(TypeCode::UInt8));
}

TEST(AnyTypeTest, CopyConstruction)
{
  const std::string nested_name = "nested_struct";
  AnyType two_scalars{{
    {"signed", SignedInteger8Type},
    {"unsigned", UnsignedInteger8Type}
  }};
  AnyType nested_type{{
    {"scalars", two_scalars},
    {"single", {
      {"first", SignedInteger8Type},
      {"second", SignedInteger8Type}
    }}
  }, nested_name};
  EXPECT_TRUE(IsStructType(nested_type));
  EXPECT_EQ(nested_type.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(nested_type.GetTypeName(), nested_name);

  AnyType copy = nested_type;
  EXPECT_EQ(copy, nested_type);
  EXPECT_TRUE(IsStructType(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(copy.GetTypeName(), nested_name);
  EXPECT_TRUE(copy.HasField("scalars"));
  EXPECT_TRUE(copy.HasField("single"));
  EXPECT_FALSE(copy.HasField("index"));

  copy.AddMember("index", UnsignedInteger64Type);
  EXPECT_NE(copy, nested_type);
  EXPECT_TRUE(IsStructType(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(copy.GetTypeName(), nested_name);
  EXPECT_TRUE(copy.HasField("scalars"));
  EXPECT_TRUE(copy.HasField("single"));
  EXPECT_TRUE(copy.HasField("index"));
}

TEST(AnyTypeTest, CopyAssignment)
{
  const std::string nested_name = "nested_struct";
  AnyType two_scalars{{
    {"signed", SignedInteger8Type},
    {"unsigned", UnsignedInteger8Type}
  }};
  AnyType nested_type{{
    {"scalars", two_scalars},
    {"single", {
      {"first", SignedInteger8Type},
      {"second", SignedInteger8Type}
    }}
  }, nested_name};
  EXPECT_TRUE(IsStructType(nested_type));
  EXPECT_EQ(nested_type.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(nested_type.GetTypeName(), nested_name);

  AnyType copy;
  copy = nested_type;
  EXPECT_EQ(copy, nested_type);
  EXPECT_TRUE(IsStructType(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(copy.GetTypeName(), nested_name);

  copy.AddMember("index", UnsignedInteger64Type);
  EXPECT_NE(copy, nested_type);
  EXPECT_TRUE(IsStructType(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(copy.GetTypeName(), nested_name);
}

TEST(AnyTypeTest, MoveConstruction)
{
  const std::string nested_name = "nested_struct";
  AnyType two_scalars{{
    {"signed", SignedInteger8Type},
    {"unsigned", UnsignedInteger8Type}
  }};
  AnyType nested_type{{
    {"scalars", two_scalars},
    {"single", {
      {"first", SignedInteger8Type},
      {"second", SignedInteger8Type}
    }}
  }, nested_name};
  EXPECT_TRUE(IsStructType(nested_type));
  EXPECT_EQ(nested_type.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(nested_type.GetTypeName(), nested_name);

  AnyType moved = std::move(nested_type);
  EXPECT_NE(moved, nested_type);
  EXPECT_TRUE(IsEmptyType(nested_type));
  EXPECT_TRUE(IsStructType(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(moved.GetTypeName(), nested_name);
  EXPECT_TRUE(moved.HasField("scalars"));
  EXPECT_TRUE(moved.HasField("single"));
  EXPECT_FALSE(moved.HasField("index"));

  moved.AddMember("index", UnsignedInteger64Type);
  EXPECT_NE(moved, nested_type);
  EXPECT_TRUE(IsStructType(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(moved.GetTypeName(), nested_name);
  EXPECT_TRUE(moved.HasField("scalars"));
  EXPECT_TRUE(moved.HasField("single"));
  EXPECT_TRUE(moved.HasField("index"));
}

TEST(AnyTypeTest, MoveAssignment)
{
  const std::string nested_name = "nested_struct";
  AnyType two_scalars{{
    {"signed", SignedInteger8Type},
    {"unsigned", UnsignedInteger8Type}
  }};
  AnyType nested_type{{
    {"scalars", two_scalars},
    {"single", {
      {"first", SignedInteger8Type},
      {"second", SignedInteger8Type}
    }}
  }, nested_name};
  EXPECT_TRUE(IsStructType(nested_type));
  EXPECT_EQ(nested_type.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(nested_type.GetTypeName(), nested_name);

  AnyType moved;
  moved = std::move(nested_type);
  EXPECT_NE(moved, nested_type);
  EXPECT_TRUE(IsEmptyType(nested_type));
  EXPECT_TRUE(IsStructType(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(moved.GetTypeName(), nested_name);
  EXPECT_TRUE(moved.HasField("scalars"));
  EXPECT_TRUE(moved.HasField("single"));
  EXPECT_FALSE(moved.HasField("index"));

  moved.AddMember("index", UnsignedInteger64Type);
  EXPECT_NE(moved, nested_type);
  EXPECT_TRUE(IsStructType(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(moved.GetTypeName(), nested_name);
  EXPECT_TRUE(moved.HasField("scalars"));
  EXPECT_TRUE(moved.HasField("single"));
  EXPECT_TRUE(moved.HasField("index"));
}

TEST(AnyTypeTest, CreateEmptyFields)
{
  // Do not allow creating a structure type with an empty type as member
  EXPECT_THROW(AnyType({
                 {"number", SignedInteger16Type},
                 {"empty", EmptyType}
               }, "EmptyMemberStruct"), InvalidOperationException);
  AnyType my_struct = EmptyStructType("MyStruct");
  EXPECT_NO_THROW(my_struct.AddMember("number", UnsignedInteger32Type));
  EXPECT_THROW(my_struct.AddMember("empty", EmptyType), InvalidOperationException);

  // Do not allow creating an array of empty types
  EXPECT_THROW(AnyType(12, EmptyType), InvalidOperationException);
}

TEST(AnyTypeTest, AssignEmptyFields)
{
  // Allow assigning the empty type to an empty type
  AnyType empty{};
  EXPECT_NO_THROW(empty = EmptyType);

  // Do not allow assigning an empty type to a scalar type
  AnyType my_scalar = StringType;
  EXPECT_THROW(my_scalar = EmptyType, InvalidOperationException);

  // Do not allow assigning an empty type to a member
  AnyType my_struct({
    {"number", SignedInteger16Type},
    {"other", BooleanType}
  }, "MyStruct");
  EXPECT_THROW(my_struct["other"] = EmptyType, InvalidOperationException);

  // Do not allow assigning the empty type as the element type of an array
  AnyType my_array(4, UnsignedInteger64Type);
  EXPECT_THROW(my_array["[]"] = EmptyType, InvalidOperationException);
}