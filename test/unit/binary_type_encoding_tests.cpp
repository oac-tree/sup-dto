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

#include <sup/dto/anytype.h>
#include <sup/dto/anytype_helper.h>
#include <sup/dto/anyvalue_exceptions.h>

#include <sup/dto/serialize/binary_tokens.h>

using namespace sup::dto;

class BinaryTypeEncodingTests : public ::testing::Test
{
};

//! Empty buffer parsing throws.
TEST_F(BinaryTypeEncodingTests, EmptyBuffer)
{
  std::vector<uint8> buffer;
  EXPECT_THROW(AnyTypeFromBinary(buffer), ParseException);
}

//! Incomplete buffer parsing throws.
TEST_F(BinaryTypeEncodingTests, IncompleteBuffer)
{
  {
    // Scalar representation missing scalar token
    AnyType anytype{UnsignedInteger64Type};
    auto representation = AnyTypeToBinary(anytype);
    ASSERT_TRUE(representation.size() > 1);
    representation.pop_back();
    EXPECT_THROW(AnyTypeFromBinary(representation), ParseException);
  }
  {
    // Structure representation missing last byte
    AnyType anytype = {{
      {"signed", {SignedInteger32Type}
      }}, "my_struct"};
    auto representation = AnyTypeToBinary(anytype);
    ASSERT_TRUE(representation.size() > 1);
    representation.pop_back();
    EXPECT_THROW(AnyTypeFromBinary(representation), ParseException);
  }
}

//! Structure with unnamed field throws.
TEST_F(BinaryTypeEncodingTests, StructWithUnnamedField)
{
  AnyType anytype = {{"a", {SignedInteger32Type}}};
  auto representation = AnyTypeToBinary(anytype);
  ASSERT_EQ(representation.size(), 9);
  auto fieldname_start = representation.begin() + 4;
  auto fieldname_end = representation.begin() + 7;
  representation.erase(fieldname_start, fieldname_end);
  EXPECT_THROW(AnyTypeFromBinary(representation), ParseException);
}

//! Encode/decode empty anytypeue.
TEST_F(BinaryTypeEncodingTests, EmptyType)
{
  AnyType anytype;
  auto representation = AnyTypeToBinary(anytype);
  EXPECT_TRUE(representation.size() > 1);
  auto read_back = AnyTypeFromBinary(representation);
  EXPECT_EQ(read_back, anytype);
}

//! Encode/decode single scalars.
TEST_F(BinaryTypeEncodingTests, Scalars)
{
  {
    // boolean
    AnyType anytype{BooleanType};
    auto representation = AnyTypeToBinary(anytype);
    EXPECT_TRUE(representation.size() > 1);
    auto read_back = AnyTypeFromBinary(representation);
    EXPECT_EQ(read_back, anytype);
  }
  {
    // char8
    AnyType anytype{Character8Type};
    auto representation = AnyTypeToBinary(anytype);
    EXPECT_TRUE(representation.size() > 1);
    auto read_back = AnyTypeFromBinary(representation);
    EXPECT_EQ(read_back, anytype);
  }
  {
    // int8
    AnyType anytype{SignedInteger8Type};
    auto representation = AnyTypeToBinary(anytype);
    EXPECT_TRUE(representation.size() > 1);
    auto read_back = AnyTypeFromBinary(representation);
    EXPECT_EQ(read_back, anytype);
  }
  {
    // uint8
    AnyType anytype{UnsignedInteger8Type};
    auto representation = AnyTypeToBinary(anytype);
    EXPECT_TRUE(representation.size() > 1);
    auto read_back = AnyTypeFromBinary(representation);
    EXPECT_EQ(read_back, anytype);
  }
  {
    // int16
    AnyType anytype{SignedInteger16Type};
    auto representation = AnyTypeToBinary(anytype);
    EXPECT_TRUE(representation.size() > 1);
    auto read_back = AnyTypeFromBinary(representation);
    EXPECT_EQ(read_back, anytype);
  }
  {
    // uint16
    AnyType anytype{UnsignedInteger16Type};
    auto representation = AnyTypeToBinary(anytype);
    EXPECT_TRUE(representation.size() > 1);
    auto read_back = AnyTypeFromBinary(representation);
    EXPECT_EQ(read_back, anytype);
  }
  {
    // int32
    AnyType anytype{SignedInteger32Type};
    auto representation = AnyTypeToBinary(anytype);
    EXPECT_TRUE(representation.size() > 1);
    auto read_back = AnyTypeFromBinary(representation);
    EXPECT_EQ(read_back, anytype);
  }
  {
    // uint32
    AnyType anytype{UnsignedInteger32Type};
    auto representation = AnyTypeToBinary(anytype);
    EXPECT_TRUE(representation.size() > 1);
    auto read_back = AnyTypeFromBinary(representation);
    EXPECT_EQ(read_back, anytype);
  }
  {
    // int64
    AnyType anytype{SignedInteger64Type};
    auto representation = AnyTypeToBinary(anytype);
    EXPECT_TRUE(representation.size() > 1);
    auto read_back = AnyTypeFromBinary(representation);
    EXPECT_EQ(read_back, anytype);
  }
  {
    // uint64
    AnyType anytype{UnsignedInteger64Type};
    auto representation = AnyTypeToBinary(anytype);
    EXPECT_TRUE(representation.size() > 1);
    auto read_back = AnyTypeFromBinary(representation);
    EXPECT_EQ(read_back, anytype);
  }
  {
    // float32
    AnyType anytype{Float32Type};
    auto representation = AnyTypeToBinary(anytype);
    EXPECT_TRUE(representation.size() > 1);
    auto read_back = AnyTypeFromBinary(representation);
    EXPECT_EQ(read_back, anytype);
  }
  {
    // float64
    AnyType anytype{Float64Type};
    auto representation = AnyTypeToBinary(anytype);
    EXPECT_TRUE(representation.size() > 1);
    auto read_back = AnyTypeFromBinary(representation);
    EXPECT_EQ(read_back, anytype);
  }
  {
    // string
    AnyType anytype{StringType};
    auto representation = AnyTypeToBinary(anytype);
    EXPECT_TRUE(representation.size() > 1);
    auto read_back = AnyTypeFromBinary(representation);
    EXPECT_EQ(read_back, anytype);
  }
}

//! Empty structure.
TEST_F(BinaryTypeEncodingTests, EmptyStruct)
{
  AnyType anytype = EmptyStructType("struct_name");
  auto representation = AnyTypeToBinary(anytype);
  EXPECT_TRUE(representation.size() > 1);
  auto read_back = AnyTypeFromBinary(representation);
  EXPECT_EQ(read_back, anytype);
}

//! Structure with a single field.
TEST_F(BinaryTypeEncodingTests, StructWithSingleField)
{
  AnyType anytype = {{"signed", {SignedInteger32Type}}};
  auto representation = AnyTypeToBinary(anytype);
  EXPECT_TRUE(representation.size() > 1);
  auto read_back = AnyTypeFromBinary(representation);
  EXPECT_EQ(read_back, anytype);
}

//! Structure with two fields.
TEST_F(BinaryTypeEncodingTests, StructWithTwoFields)
{
  AnyType anytype = {
    {"signed", {SignedInteger32Type}},
    {"bool", {BooleanType}}
  };
  auto representation = AnyTypeToBinary(anytype);
  EXPECT_TRUE(representation.size() > 1);
  auto read_back = AnyTypeFromBinary(representation);
  EXPECT_EQ(read_back, anytype);
}

//! Structure with another struct in it.
TEST_F(BinaryTypeEncodingTests, StructWithNestedStructWithField)
{
  AnyType two_scalars = {
    {"signed", {SignedInteger32Type}},
    {"bool", {BooleanType}}
  };
  AnyType anytype = {{"scalars", two_scalars}};
  auto representation = AnyTypeToBinary(anytype);
  EXPECT_TRUE(representation.size() > 1);
  auto read_back = AnyTypeFromBinary(representation);
  EXPECT_EQ(read_back, anytype);
}

//! Structure containing two structures.
TEST_F(BinaryTypeEncodingTests, StructWithTwoNestedStructs)
{
  AnyType two_scalars = {{
    {"signed", {SignedInteger32Type}},
    {"bool", {BooleanType}}}, "internal_struct"
  };
  AnyType anytype = {{
    {"struct1", two_scalars},
    {"struct2", {
      {"first", {SignedInteger8Type}},
      {"second", {UnsignedInteger8Type}}
      }}},
    "struct_name"
  };
  auto representation = AnyTypeToBinary(anytype);
  EXPECT_TRUE(representation.size() > 1);
  auto read_back = AnyTypeFromBinary(representation);
  EXPECT_EQ(read_back, anytype);
}

//! Empty array
TEST_F(BinaryTypeEncodingTests, EmptyArray)
{
  AnyType anytype{0, Float64Type, "empty_array"};
  auto representation = AnyTypeToBinary(anytype);
  EXPECT_TRUE(representation.size() > 1);
  auto read_back = AnyTypeFromBinary(representation);
  EXPECT_TRUE(IsArrayType(read_back));
  EXPECT_EQ(read_back, anytype);
}

//! Scalar array with a name and two elements.
TEST_F(BinaryTypeEncodingTests, ScalarArray)
{
  AnyType anytype{2, SignedInteger32Type, "array_name"};
  auto representation = AnyTypeToBinary(anytype);
  EXPECT_TRUE(representation.size() > 1);
  auto read_back = AnyTypeFromBinary(representation);
  EXPECT_TRUE(IsArrayType(read_back));
  EXPECT_EQ(read_back, anytype);
}

//! Structure with scalar array as a single field.
TEST_F(BinaryTypeEncodingTests, StructWithScalarArrayAsField)
{
  AnyType array_type{2, SignedInteger32Type, "array_name"};
  AnyType anytype = {{{"array_field", array_type}}, "struct_name"};
  auto representation = AnyTypeToBinary(anytype);
  EXPECT_TRUE(representation.size() > 1);
  auto read_back = AnyTypeFromBinary(representation);
  EXPECT_EQ(read_back, anytype);
}

//! Structure with two scalar arrays as fields.
TEST_F(BinaryTypeEncodingTests, StructWithTwoScalarArrayAsField)
{
  AnyType array1{2, SignedInteger32Type, "array_name1"};
  AnyType array2{3, SignedInteger32Type, "array_name2"};
  AnyType anytype = {{{"field1", array1}, {"field2", array2}}, "struct_name"};
  auto representation = AnyTypeToBinary(anytype);
  EXPECT_TRUE(representation.size() > 1);
  auto read_back = AnyTypeFromBinary(representation);
  EXPECT_EQ(read_back, anytype);
}

//! Array with two structure elements.
TEST_F(BinaryTypeEncodingTests, ArrayWithTwoStructureElements)
{
  AnyType struct_type = {{{"first", SignedInteger8Type},
                                    {"second", UnsignedInteger8Type}},
                                    "struct_name"};
  AnyType anytype{2, struct_type, "array_name"};
  auto representation = AnyTypeToBinary(anytype);
  EXPECT_TRUE(representation.size() > 1);
  auto read_back = AnyTypeFromBinary(representation);
  EXPECT_EQ(read_back, anytype);
}

//! Structure with array with two structures.
TEST_F(BinaryTypeEncodingTests, StructureWithArrayWithStructure)
{
  AnyType struct_type = {{{"first", SignedInteger8Type},
                                    {"second", UnsignedInteger8Type}},
                                    "struct_name"};

  AnyType array_type{2, struct_type, "array_name"};
  AnyType anytype = {{{"field", array_type}}, "struct_name2"};
  auto representation = AnyTypeToBinary(anytype);
  EXPECT_TRUE(representation.size() > 1);
  auto read_back = AnyTypeFromBinary(representation);
  EXPECT_EQ(read_back, anytype);
}

//! Check if duplucate typenames for arrays/structs do not cause conflicts
TEST_F(BinaryTypeEncodingTests, ParseDuplicateTypename)
{
  {
    // Use typename from EmptyType
    AnyType anytype{{
      {"x", Float32Type},
      {"y", Float32Type},
      {"z", Float32Type}
    }, kEmptyTypeName};
    auto bin_type = AnyTypeToBinary(anytype);
    ASSERT_FALSE(bin_type.empty());
    auto readback = AnyTypeFromBinary(bin_type);
    EXPECT_EQ(anytype, readback);
  }
  {
    // Use typename from BooleanType
    AnyType anytype{{
      {"x", Float32Type},
      {"y", Float32Type},
      {"z", Float32Type}
    }, kBooleanTypeName};
    auto bin_type = AnyTypeToBinary(anytype);
    ASSERT_FALSE(bin_type.empty());
    auto readback = AnyTypeFromBinary(bin_type);
    EXPECT_EQ(anytype, readback);
  }
}
