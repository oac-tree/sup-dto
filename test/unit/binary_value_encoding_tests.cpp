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
#include <sup/dto/anyvalue_exceptions.h>
#include <sup/dto/anyvalue_helper.h>

#include <sup/dto/serialize/binary_tokens.h>

#include <cmath>
#include <limits>

using namespace sup::dto;

class BinaryValueEncodingTests : public ::testing::Test
{
};

//! Empty buffer parsing throws.
TEST_F(BinaryValueEncodingTests, EmptyBuffer)
{
  std::vector<sup::dto::uint8> buffer;
  EXPECT_THROW(AnyValueFromBinary(buffer), ParseException);
}

//! Incomplete buffer parsing throws.
TEST_F(BinaryValueEncodingTests, IncompleteBuffer)
{
  {
    // Scalar representation missing last byte
    AnyValue val{sup::dto::UnsignedInteger64Type, 571};
    auto representation = AnyValueToBinary(val);
    ASSERT_TRUE(representation.size() > 1);
    representation.pop_back();
    EXPECT_THROW(AnyValueFromBinary(representation), ParseException);
  }
  {
    // Structure representation missing last byte
    AnyValue val = {{"signed", {sup::dto::SignedInteger32Type, 42}}};
    auto representation = AnyValueToBinary(val);
    ASSERT_TRUE(representation.size() > 1);
    representation.pop_back();
    EXPECT_THROW(AnyValueFromBinary(representation), ParseException);
  }
}

//! Structure with unnamed field throws.
TEST_F(BinaryValueEncodingTests, StructWithUnnamedField)
{
  AnyValue val = {{"a", {sup::dto::SignedInteger32Type, 42}}};
  auto representation = AnyValueToBinary(val);
  ASSERT_EQ(representation.size(), 14);
  auto fieldname_start = representation.begin() + 4;
  auto fieldname_end = representation.begin() + 7;
  representation.erase(fieldname_start, fieldname_end);
  EXPECT_THROW(AnyValueFromBinary(representation), ParseException);
}

//! Encode/decode empty value.
TEST_F(BinaryValueEncodingTests, EmptyValue)
{
  AnyValue val;
  auto representation = AnyValueToBinary(val);
  EXPECT_TRUE(representation.size() > 1);
  auto read_back = AnyValueFromBinary(representation);
  EXPECT_EQ(read_back, val);
}

//! Encode/decode single scalars.
TEST_F(BinaryValueEncodingTests, Scalars)
{
  {
    // boolean
    AnyValue val{sup::dto::BooleanType, true};
    auto representation = AnyValueToBinary(val);
    EXPECT_TRUE(representation.size() > 1);
    auto read_back = AnyValueFromBinary(representation);
    EXPECT_EQ(read_back, val);
  }
  {
    // char8
    AnyValue val{sup::dto::Character8Type, 'a'};
    auto representation = AnyValueToBinary(val);
    EXPECT_TRUE(representation.size() > 1);
    auto read_back = AnyValueFromBinary(representation);
    EXPECT_EQ(read_back, val);
  }
  {
    // int8
    AnyValue val{sup::dto::SignedInteger8Type, -1};
    auto representation = AnyValueToBinary(val);
    EXPECT_TRUE(representation.size() > 1);
    auto read_back = AnyValueFromBinary(representation);
    EXPECT_EQ(read_back, val);
  }
  {
    // uint8
    AnyValue val{sup::dto::UnsignedInteger8Type, 17};
    auto representation = AnyValueToBinary(val);
    EXPECT_TRUE(representation.size() > 1);
    auto read_back = AnyValueFromBinary(representation);
    EXPECT_EQ(read_back, val);
  }
  {
    // int16
    AnyValue val{sup::dto::SignedInteger16Type, -317};
    auto representation = AnyValueToBinary(val);
    EXPECT_TRUE(representation.size() > 1);
    auto read_back = AnyValueFromBinary(representation);
    EXPECT_EQ(read_back, val);
  }
  {
    // uint16
    AnyValue val{sup::dto::UnsignedInteger16Type, 571};
    auto representation = AnyValueToBinary(val);
    EXPECT_TRUE(representation.size() > 1);
    auto read_back = AnyValueFromBinary(representation);
    EXPECT_EQ(read_back, val);
  }
  {
    // int32
    AnyValue val{sup::dto::SignedInteger32Type, -317};
    auto representation = AnyValueToBinary(val);
    EXPECT_TRUE(representation.size() > 1);
    auto read_back = AnyValueFromBinary(representation);
    EXPECT_EQ(read_back, val);
  }
  {
    // uint32
    AnyValue val{sup::dto::UnsignedInteger32Type, 571};
    auto representation = AnyValueToBinary(val);
    EXPECT_TRUE(representation.size() > 1);
    auto read_back = AnyValueFromBinary(representation);
    EXPECT_EQ(read_back, val);
  }
  {
    // int64
    AnyValue val{sup::dto::SignedInteger64Type, -317};
    auto representation = AnyValueToBinary(val);
    EXPECT_TRUE(representation.size() > 1);
    auto read_back = AnyValueFromBinary(representation);
    EXPECT_EQ(read_back, val);
  }
  {
    // uint64
    AnyValue val{sup::dto::UnsignedInteger64Type, 571};
    auto representation = AnyValueToBinary(val);
    EXPECT_TRUE(representation.size() > 1);
    auto read_back = AnyValueFromBinary(representation);
    EXPECT_EQ(read_back, val);
  }
  {
    // float32
    AnyValue val{sup::dto::Float32Type, 3.14};
    auto representation = AnyValueToBinary(val);
    EXPECT_TRUE(representation.size() > 1);
    auto read_back = AnyValueFromBinary(representation);
    EXPECT_EQ(read_back, val);
  }
  {
    // float64
    AnyValue val{sup::dto::Float64Type, -3.14};
    auto representation = AnyValueToBinary(val);
    EXPECT_TRUE(representation.size() > 1);
    auto read_back = AnyValueFromBinary(representation);
    EXPECT_EQ(read_back, val);
  }
  {
    // short string
    AnyValue val{sup::dto::StringType, "Short string"};
    auto representation = AnyValueToBinary(val);
    EXPECT_TRUE(representation.size() > 1);
    auto read_back = AnyValueFromBinary(representation);
    EXPECT_EQ(read_back, val);
  }
  {
    // long string
    std::string str(10 * SHORT_SIZE_LIMIT, 'x');
    AnyValue val{str};
    auto representation = AnyValueToBinary(val);
    EXPECT_TRUE(representation.size() > 1);
    auto read_back = AnyValueFromBinary(representation);
    EXPECT_EQ(read_back, val);
  }
}

//! Round trips of float/double edge cases that are known to lose precision or fail
//! outright through the JSON path (see doc/floating_point_json_notes.md and
//! anyvalue_json_serialize_tests.cpp / json_value_parser_tests.cpp). Unlike JSON, the
//! binary format copies the underlying IEEE-754 bytes directly with no decimal string
//! conversion involved, so none of the same issues are expected here. Note that NaN and
//! Infinity are out of scope here: they are rejected at AnyValue construction time (see
//! ScalarValueTest.Float64InvalidValues), before any serializer -- binary included -- is
//! ever involved.

TEST_F(BinaryValueEncodingTests, NegativeZeroFloat64RoundTrip)
{
  AnyValue val{Float64Type, -0.0};
  auto representation = AnyValueToBinary(val);
  auto read_back = AnyValueFromBinary(representation);
  EXPECT_EQ(read_back, val);
  EXPECT_TRUE(std::signbit(read_back.As<float64>()));
}

TEST_F(BinaryValueEncodingTests, Float64MaxValueRoundTrip)
{
  AnyValue val{Float64Type, std::numeric_limits<float64>::max()};
  auto representation = AnyValueToBinary(val);
  auto read_back = AnyValueFromBinary(representation);
  EXPECT_EQ(read_back, val);
}

TEST_F(BinaryValueEncodingTests, Float64MinValueRoundTrip)
{
  AnyValue val{Float64Type, std::numeric_limits<float64>::min()};
  auto representation = AnyValueToBinary(val);
  auto read_back = AnyValueFromBinary(representation);
  EXPECT_EQ(read_back, val);
}

TEST_F(BinaryValueEncodingTests, Float64DenormMinValueRoundTrip)
{
  AnyValue val{Float64Type, std::numeric_limits<float64>::denorm_min()};
  auto representation = AnyValueToBinary(val);
  auto read_back = AnyValueFromBinary(representation);
  EXPECT_EQ(read_back, val);
}

//! Float32Type's maximum round trips fine in binary: there is no float32-to-double
//! promotion involved at all (see JSONValueParserTest.Float32MaxValueRoundTrip for the
//! JSON equivalent, which round-trips too, but via a narrowing conversion that has to
//! correctly round back down to FLT_MAX).
TEST_F(BinaryValueEncodingTests, Float32MaxValueRoundTrip)
{
  AnyValue val{Float32Type, std::numeric_limits<float32>::max()};
  auto representation = AnyValueToBinary(val);
  auto read_back = AnyValueFromBinary(representation);
  EXPECT_EQ(read_back, val);
}

TEST_F(BinaryValueEncodingTests, Float32MinValueRoundTrip)
{
  AnyValue val{Float32Type, std::numeric_limits<float32>::min()};
  auto representation = AnyValueToBinary(val);
  auto read_back = AnyValueFromBinary(representation);
  EXPECT_EQ(read_back, val);
}

//! Unlike JSON (see JSONValueParserTest.Float64SmallExponentRoundTripPrecisionLoss),
//! this value round trips exactly in binary: no Grisu2 decimal formatting is involved.
TEST_F(BinaryValueEncodingTests, Float64SmallExponentRoundTrip)
{
  AnyValue val{Float64Type, 1.5e-300};
  auto representation = AnyValueToBinary(val);
  auto read_back = AnyValueFromBinary(representation);
  EXPECT_EQ(read_back, val);
}

//! Unlike JSON (see JSONValueParserTest.Float64HighPrecisionRoundTripPrecisionLoss),
//! this value round trips exactly in binary.
TEST_F(BinaryValueEncodingTests, Float64HighPrecisionRoundTrip)
{
  AnyValue val{Float64Type, 123456789.123456789};
  auto representation = AnyValueToBinary(val);
  auto read_back = AnyValueFromBinary(representation);
  EXPECT_EQ(read_back, val);
}

//! Empty structure.
TEST_F(BinaryValueEncodingTests, EmptyStruct)
{
  AnyValue val = sup::dto::EmptyStruct("struct_name");
  auto representation = AnyValueToBinary(val);
  EXPECT_TRUE(representation.size() > 1);
  auto read_back = AnyValueFromBinary(representation);
  EXPECT_EQ(read_back, val);
}

//! Structure with a single field.
TEST_F(BinaryValueEncodingTests, StructWithSingleField)
{
  AnyValue val = {{"signed", {sup::dto::SignedInteger32Type, 42}}};
  auto representation = AnyValueToBinary(val);
  EXPECT_TRUE(representation.size() > 1);
  auto read_back = AnyValueFromBinary(representation);
  EXPECT_EQ(read_back, val);
}

//! Structure with a single field.
TEST_F(BinaryValueEncodingTests, StructWithEmptyField)
{
  AnyValue val = EmptyStruct();
  val.AddMember("a", {});
  auto representation = AnyValueToBinary(val);
  EXPECT_TRUE(representation.size() > 1);
  auto read_back = AnyValueFromBinary(representation);
  EXPECT_EQ(read_back, val);
}

//! Structure with two fields.
TEST_F(BinaryValueEncodingTests, StructWithTwoFields)
{
  AnyValue val = {
    {"signed", {sup::dto::SignedInteger32Type, 42}},
    {"bool", {sup::dto::BooleanType, true}}
  };
  auto representation = AnyValueToBinary(val);
  EXPECT_TRUE(representation.size() > 1);
  auto read_back = AnyValueFromBinary(representation);
  EXPECT_EQ(read_back, val);
}

//! Structure with another struct in it.
TEST_F(BinaryValueEncodingTests, StructWithNestedStructWithField)
{
  AnyValue two_scalars = {
    {"signed", {sup::dto::SignedInteger32Type, 42}},
    {"bool", {sup::dto::BooleanType, true}}
  };
  AnyValue val = {{"scalars", two_scalars}};
  auto representation = AnyValueToBinary(val);
  EXPECT_TRUE(representation.size() > 1);
  auto read_back = AnyValueFromBinary(representation);
  EXPECT_EQ(read_back, val);
}

//! Structure containing two structures.
TEST_F(BinaryValueEncodingTests, StructWithTwoNestedStructs)
{
  AnyValue two_scalars = {{
    {"signed", {sup::dto::SignedInteger32Type, 42}},
    {"bool", {sup::dto::BooleanType, true}}}, "internal_struct"
  };
  AnyValue val = {{
    {"struct1", two_scalars},
    {"struct2", {
      {"first", {sup::dto::SignedInteger8Type, -43}},
      {"second", {sup::dto::UnsignedInteger8Type, 44}}
      }}},
    "struct_name"
  };
  auto representation = AnyValueToBinary(val);
  EXPECT_TRUE(representation.size() > 1);
  auto read_back = AnyValueFromBinary(representation);
  EXPECT_EQ(read_back, val);
}

//! Empty array
TEST_F(BinaryValueEncodingTests, EmptyArray)
{
  AnyValue val{0, sup::dto::Float64Type, "empty_array"};
  auto representation = AnyValueToBinary(val);
  EXPECT_TRUE(representation.size() > 1);
  auto read_back = AnyValueFromBinary(representation);
  EXPECT_TRUE(IsArrayValue(read_back));
  EXPECT_EQ(read_back, val);
}

//! Scalar array with a name and two elements.
TEST_F(BinaryValueEncodingTests, ScalarArray)
{
  AnyValue val = sup::dto::ArrayValue({{sup::dto::SignedInteger32Type, 42}, 43}, "array_name");
  auto representation = AnyValueToBinary(val);
  EXPECT_TRUE(representation.size() > 1);
  auto read_back = AnyValueFromBinary(representation);
  EXPECT_TRUE(IsArrayValue(read_back));
  EXPECT_EQ(read_back, val);
}

//! Structure with scalar array as a single field.
TEST_F(BinaryValueEncodingTests, StructWithScalarArrayAsField)
{
  auto array_value = sup::dto::ArrayValue({{sup::dto::SignedInteger32Type, 42}, 43}, "array_name");
  AnyValue val = {{{"array_field", array_value}}, "struct_name"};
  auto representation = AnyValueToBinary(val);
  EXPECT_TRUE(representation.size() > 1);
  auto read_back = AnyValueFromBinary(representation);
  EXPECT_EQ(read_back, val);
}

//! Structure with two scalar arrays as fields.
TEST_F(BinaryValueEncodingTests, StructWithTwoScalarArrayAsField)
{
  auto array1 = sup::dto::ArrayValue({{sup::dto::SignedInteger32Type, 42}, 43}, "array_name1");
  auto array2 = sup::dto::ArrayValue({{sup::dto::SignedInteger32Type, 44}, 45, 46}, "array_name2");
  AnyValue val = {{{"field1", array1}, {"field2", array2}}, "struct_name"};
  auto representation = AnyValueToBinary(val);
  EXPECT_TRUE(representation.size() > 1);
  auto read_back = AnyValueFromBinary(representation);
  EXPECT_EQ(read_back, val);
}

//! Array with two structure elements.
TEST_F(BinaryValueEncodingTests, ArrayWithTwoStructureElements)
{
  sup::dto::AnyValue struct1 = {{{"first", {sup::dto::SignedInteger8Type, -43}},
                                 {"second", {sup::dto::UnsignedInteger8Type, 44}}},
                                "struct_name"};
  sup::dto::AnyValue struct2 = {{{"first", {sup::dto::SignedInteger8Type, 42}},
                                 {"second", {sup::dto::UnsignedInteger8Type, 43}}},
                                "struct_name"};
  AnyValue val = sup::dto::ArrayValue({struct1, struct2}, "array_name");
  auto representation = AnyValueToBinary(val);
  EXPECT_TRUE(representation.size() > 1);
  auto read_back = AnyValueFromBinary(representation);
  EXPECT_EQ(read_back, val);
}

//! Structure with array with two structures.
TEST_F(BinaryValueEncodingTests, StructureWithArrayWithStructure)
{
  sup::dto::AnyValue struct1 = {{{"first", {sup::dto::SignedInteger8Type, -43}},
                                 {"second", {sup::dto::UnsignedInteger8Type, 44}}},
                                "struct_name"};
  sup::dto::AnyValue struct2 = {{{"first", {sup::dto::SignedInteger8Type, 42}},
                                 {"second", {sup::dto::UnsignedInteger8Type, 43}}},
                                "struct_name"};

  auto array_value = sup::dto::ArrayValue({{struct1}, struct2}, "array_name");
  AnyValue val = {{{"field", array_value}}, "struct_name2"};
  auto representation = AnyValueToBinary(val);
  EXPECT_TRUE(representation.size() > 1);
  auto read_back = AnyValueFromBinary(representation);
  EXPECT_EQ(read_back, val);
}
