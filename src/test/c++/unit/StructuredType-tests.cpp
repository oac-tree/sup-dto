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

#include "AnyType.h"
#include "AnyValueExceptions.h"

using namespace sup::dto;

TEST(StructuredTypeTest, StructOfScalarType)
{
  const std::string two_scalar_name = "scalar_pair";
  AnyType two_scalars{{
    {"signed", SignedInteger8},
    {"unsigned", UnsignedInteger8}
  }, two_scalar_name};
  EXPECT_FALSE(IsEmptyType(two_scalars));
  EXPECT_TRUE(IsStructType(two_scalars));
  EXPECT_FALSE(IsArrayType(two_scalars));
  EXPECT_FALSE(IsUnboundedArrayType(two_scalars));
  EXPECT_FALSE(IsScalarType(two_scalars));
  EXPECT_EQ(two_scalars.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(two_scalars.GetTypeName(), two_scalar_name);
  EXPECT_THROW(two_scalars[""], InvalidOperationException);
  EXPECT_THROW(two_scalars["unknownfield"], InvalidOperationException);
  auto& signed_type = two_scalars["signed"];
  auto& unsigned_type = two_scalars["unsigned"];
  EXPECT_EQ(signed_type.GetTypeCode(), TypeCode::Int8);
  EXPECT_EQ(unsigned_type.GetTypeCode(), TypeCode::UInt8);

  AnyType copy = two_scalars;
  EXPECT_EQ(copy, two_scalars);

  // Creation of non-scalar types using typecode throws
  EXPECT_THROW(AnyType{TypeCode::Struct}, InvalidOperationException);
}

TEST(StructuredTypeTest, StructOfStructType)
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
  EXPECT_FALSE(IsEmptyType(nested_type));
  EXPECT_TRUE(IsStructType(nested_type));
  EXPECT_FALSE(IsArrayType(nested_type));
  EXPECT_FALSE(IsUnboundedArrayType(nested_type));
  EXPECT_FALSE(IsScalarType(nested_type));
  EXPECT_EQ(nested_type.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(nested_type.GetTypeName(), nested_name);
  EXPECT_THROW(nested_type[""], InvalidOperationException);
  EXPECT_THROW(nested_type["unknownfield"], InvalidOperationException);
  auto& scalars_type = nested_type["scalars"];
  auto& signed_type = nested_type["single.first"];
  EXPECT_EQ(scalars_type.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(scalars_type.GetTypeName(), "");
  EXPECT_EQ(signed_type.GetTypeCode(), TypeCode::Int8);

  const std::string nested_with_name_name = "nested_struct_with_name";
  const std::string embedded_name = "embedded_name";
  AnyType nested_type_with_name{{
    {"scalars", two_scalars},
    {"single", {{
      {"first", SignedInteger8},
      {"second", SignedInteger8}
    }, embedded_name}}
  }, nested_with_name_name};
  EXPECT_NE(nested_type_with_name, nested_type); // struct names are different
  EXPECT_FALSE(IsEmptyType(nested_type_with_name));
  EXPECT_TRUE(IsStructType(nested_type_with_name));
  EXPECT_FALSE(IsArrayType(nested_type_with_name));
  EXPECT_FALSE(IsUnboundedArrayType(nested_type_with_name));
  EXPECT_FALSE(IsScalarType(nested_type_with_name));
  EXPECT_EQ(nested_type_with_name.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(nested_type_with_name.GetTypeName(), nested_with_name_name);
  EXPECT_THROW(nested_type_with_name[""], InvalidOperationException);
  EXPECT_THROW(nested_type_with_name["unknownfield"], InvalidOperationException);
  auto& single_type = nested_type_with_name["single"];
  auto& signed_type2 = nested_type_with_name["scalars.signed"];
  EXPECT_EQ(single_type.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(single_type.GetTypeName(), embedded_name);
  EXPECT_EQ(signed_type2.GetTypeCode(), TypeCode::Int8);
}

TEST(StructuredTypeTest, InvalidMemberFieldName)
{
  AnyType two_scalars{{
    {"signed", SignedInteger8},
    {"unsigned", UnsignedInteger8}
  }};
  EXPECT_THROW(two_scalars.AddMember("", Boolean), InvalidOperationException);
  EXPECT_THROW(two_scalars.AddMember("signed.subfield", Boolean), InvalidOperationException);
  EXPECT_THROW(two_scalars.AddMember("signed", Boolean), InvalidOperationException);
}

TEST(StructuredTypeTest, MemberAccess)
{
  const std::string nested_name = "nested_struct";
  AnyType two_scalars{{
    {"signed", SignedInteger8},
    {"unsigned", UnsignedInteger8}
  }};
  AnyType nested_type = (EmptyStructType(nested_name)
                            .AddMember("scalars", two_scalars)
                            .AddMember("single", EmptyStructType()
                                .AddMember("first", SignedInteger8)
                                .AddMember("second", SignedInteger8)));
  EXPECT_TRUE(IsStructType(nested_type));
  EXPECT_EQ(nested_type.GetTypeCode(), TypeCode::Struct);
  EXPECT_EQ(nested_type.GetTypeName(), nested_name);
  EXPECT_TRUE(nested_type.HasMember("scalars"));
  EXPECT_TRUE(nested_type.HasMember("single"));
  EXPECT_FALSE(nested_type.HasMember("index"));
  auto member_fields = nested_type.MemberNames();
  EXPECT_EQ(member_fields.size(), 2);
  EXPECT_EQ(nested_type.NumberOfMembers(), 2);
  EXPECT_EQ(member_fields[0], "scalars");
  EXPECT_EQ(member_fields[1], "single");
  nested_type.AddMember("index", UnsignedInteger64);
  EXPECT_TRUE(nested_type.HasMember("index"));
  member_fields = nested_type.MemberNames();
  EXPECT_EQ(member_fields.size(), 3);
  EXPECT_EQ(nested_type.NumberOfMembers(), 3);
  EXPECT_EQ(member_fields[0], "scalars");
  EXPECT_EQ(member_fields[1], "single");
  EXPECT_EQ(member_fields[2], "index");

  // test presence of composite field indices
  EXPECT_TRUE(nested_type.HasMember("scalars.signed"));
  EXPECT_FALSE(nested_type.HasMember("scalars.unknown"));

  // test member access for empty type
  AnyType empty_type = EmptyType;
  EXPECT_THROW(empty_type.AddMember("throws", Boolean), InvalidOperationException);
  EXPECT_FALSE(empty_type.HasMember("throws"));
  EXPECT_EQ(empty_type.MemberNames().size(), 0);
  EXPECT_EQ(empty_type.NumberOfMembers(), 0);

  // test member access for scalar type
  AnyType scalar_type = Float32;
  EXPECT_THROW(scalar_type.AddMember("throws", SignedInteger64), InvalidOperationException);
  EXPECT_FALSE(scalar_type.HasMember("throws"));
  EXPECT_EQ(scalar_type.MemberNames().size(), 0);
  EXPECT_EQ(scalar_type.NumberOfMembers(), 0);
}
