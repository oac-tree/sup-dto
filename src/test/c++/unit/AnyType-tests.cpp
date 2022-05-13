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

#include "sup/dto/AnyType.h"
#include "sup/dto/AnyValueExceptions.h"

using namespace sup::dto;

TEST(AnyTypeTest, TypeCodes)
{
  EXPECT_TRUE(IsEmptyTypeCode(TypeCode::Empty));
  EXPECT_FALSE(IsStructTypeCode(TypeCode::Empty));
  EXPECT_FALSE(IsArrayTypeCode(TypeCode::Empty));
  EXPECT_FALSE(IsUnboundedArrayTypeCode(TypeCode::Empty));
  EXPECT_FALSE(IsScalarTypeCode(TypeCode::Empty));

  EXPECT_FALSE(IsEmptyTypeCode(TypeCode::Struct));
  EXPECT_TRUE(IsStructTypeCode(TypeCode::Struct));
  EXPECT_FALSE(IsArrayTypeCode(TypeCode::Struct));
  EXPECT_FALSE(IsUnboundedArrayTypeCode(TypeCode::Struct));
  EXPECT_FALSE(IsScalarTypeCode(TypeCode::Struct));

  EXPECT_FALSE(IsEmptyTypeCode(TypeCode::Array));
  EXPECT_FALSE(IsStructTypeCode(TypeCode::Array));
  EXPECT_TRUE(IsArrayTypeCode(TypeCode::Array));
  EXPECT_FALSE(IsUnboundedArrayTypeCode(TypeCode::Array));
  EXPECT_FALSE(IsScalarTypeCode(TypeCode::Array));

  EXPECT_FALSE(IsEmptyTypeCode(TypeCode::Int8));
  EXPECT_FALSE(IsStructTypeCode(TypeCode::Int8));
  EXPECT_FALSE(IsArrayTypeCode(TypeCode::Int8));
  EXPECT_FALSE(IsUnboundedArrayTypeCode(TypeCode::Int8));
  EXPECT_TRUE(IsScalarTypeCode(TypeCode::Int8));

  EXPECT_FALSE(IsEmptyTypeCode(TypeCode::UnboundedArray));
  EXPECT_FALSE(IsStructTypeCode(TypeCode::UnboundedArray));
  EXPECT_FALSE(IsArrayTypeCode(TypeCode::UnboundedArray));
  EXPECT_TRUE(IsUnboundedArrayTypeCode(TypeCode::UnboundedArray));
  EXPECT_FALSE(IsScalarTypeCode(TypeCode::UnboundedArray));

  EXPECT_FALSE(IsEmptyTypeCode(TypeCode::UInt8));
  EXPECT_FALSE(IsStructTypeCode(TypeCode::UInt8));
  EXPECT_FALSE(IsArrayTypeCode(TypeCode::UInt8));
  EXPECT_FALSE(IsUnboundedArrayTypeCode(TypeCode::UInt8));
  EXPECT_TRUE(IsScalarTypeCode(TypeCode::UInt8));
}

TEST(AnyTypeTest, CopyConstruction)
{
  const std::string nested_name = "nested_struct";
  AnyType two_scalars{{
    {"signed", SignedInteger8},
    {"unsigned", UnsignedInteger8}
  }};
  AnyType nested_type{{
    {"scalars", two_scalars},
    {"single", {
      {"first", SignedInteger8},
      {"second", SignedInteger8}
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
  EXPECT_TRUE(copy.HasMember("scalars"));
  EXPECT_TRUE(copy.HasMember("single"));
  EXPECT_FALSE(copy.HasMember("index"));

  copy.AddMember("index", UnsignedInteger64);
  EXPECT_NE(copy, nested_type);
  EXPECT_TRUE(IsStructType(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(copy.GetTypeName(), nested_name);
  EXPECT_TRUE(copy.HasMember("scalars"));
  EXPECT_TRUE(copy.HasMember("single"));
  EXPECT_TRUE(copy.HasMember("index"));
}

TEST(AnyTypeTest, CopyAssignment)
{
  const std::string nested_name = "nested_struct";
  AnyType two_scalars{{
    {"signed", SignedInteger8},
    {"unsigned", UnsignedInteger8}
  }};
  AnyType nested_type{{
    {"scalars", two_scalars},
    {"single", {
      {"first", SignedInteger8},
      {"second", SignedInteger8}
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

  copy.AddMember("index", UnsignedInteger64);
  EXPECT_NE(copy, nested_type);
  EXPECT_TRUE(IsStructType(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(copy.GetTypeName(), nested_name);
}

TEST(AnyTypeTest, MoveConstruction)
{
  const std::string nested_name = "nested_struct";
  AnyType two_scalars{{
    {"signed", SignedInteger8},
    {"unsigned", UnsignedInteger8}
  }};
  AnyType nested_type{{
    {"scalars", two_scalars},
    {"single", {
      {"first", SignedInteger8},
      {"second", SignedInteger8}
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
  EXPECT_TRUE(moved.HasMember("scalars"));
  EXPECT_TRUE(moved.HasMember("single"));
  EXPECT_FALSE(moved.HasMember("index"));

  moved.AddMember("index", UnsignedInteger64);
  EXPECT_NE(moved, nested_type);
  EXPECT_TRUE(IsStructType(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(moved.GetTypeName(), nested_name);
  EXPECT_TRUE(moved.HasMember("scalars"));
  EXPECT_TRUE(moved.HasMember("single"));
  EXPECT_TRUE(moved.HasMember("index"));
}

TEST(AnyTypeTest, MoveAssignment)
{
  const std::string nested_name = "nested_struct";
  AnyType two_scalars{{
    {"signed", SignedInteger8},
    {"unsigned", UnsignedInteger8}
  }};
  AnyType nested_type{{
    {"scalars", two_scalars},
    {"single", {
      {"first", SignedInteger8},
      {"second", SignedInteger8}
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
  EXPECT_TRUE(moved.HasMember("scalars"));
  EXPECT_TRUE(moved.HasMember("single"));
  EXPECT_FALSE(moved.HasMember("index"));

  moved.AddMember("index", UnsignedInteger64);
  EXPECT_NE(moved, nested_type);
  EXPECT_TRUE(IsStructType(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(moved.GetTypeName(), nested_name);
  EXPECT_TRUE(moved.HasMember("scalars"));
  EXPECT_TRUE(moved.HasMember("single"));
  EXPECT_TRUE(moved.HasMember("index"));
}

TEST(AnyTypeTest, CreateEmptyFields)
{
  // Do not allow creating a structure type with an empty type as member
  EXPECT_THROW(AnyType({
                 {"number", SignedInteger16},
                 {"empty", EmptyType}
               }, "EmptyMemberStruct"), InvalidOperationException);
  AnyType my_struct = EmptyStructType("MyStruct");
  EXPECT_NO_THROW(my_struct.AddMember("number", UnsignedInteger32));
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
  AnyType my_scalar = String;
  EXPECT_THROW(my_scalar = EmptyType, InvalidOperationException);

  // Do not allow assigning an empty type to a member
  AnyType my_struct({
    {"number", SignedInteger16},
    {"other", Boolean}
  }, "MyStruct");
  EXPECT_THROW(my_struct["other"] = EmptyType, InvalidOperationException);

  // Do not allow assigning the empty type as the element type of an array
  AnyType my_array(4, UnsignedInteger64);
  EXPECT_THROW(my_array["[]"] = EmptyType, InvalidOperationException);
}