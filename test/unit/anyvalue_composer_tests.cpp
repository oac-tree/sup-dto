/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : SUP - DTO
 *
 * Description   : Unit test code
 *
 * Author        : Gennady Pospelov (IO)
 *
 * Copyright (c) : 2010-2023 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include "sup/dto/anyvalue_composer.h"

#include <sup/dto/anytype.h>
#include <sup/dto/anytype_helper.h>
#include <sup/dto/anyvalue.h>
#include <sup/dto/anyvalue_helper.h>

#include <gtest/gtest.h>

using namespace sup::dto;

class AnyValueComposerTests : public ::testing::Test
{
};

//! Checking that the builder returns an empty value.

TEST_F(AnyValueComposerTests, InitialState)
{
  AnyValueComposer builder;
  EXPECT_EQ(builder.GetStackSize(), 0);
  auto value = builder.MoveAnyValue();
  EXPECT_TRUE(IsEmptyValue(value));
}

//! Creation of AnyValue scalar.

TEST_F(AnyValueComposerTests, Scalar)
{
  AnyValueComposer builder;

  builder.Int32(42);

  EXPECT_EQ(builder.GetStackSize(), 1);

  auto value = builder.MoveAnyValue();
  EXPECT_EQ(value.GetType(), SignedInteger32Type);
  EXPECT_TRUE(IsScalarValue(value));
  EXPECT_EQ(value.As<int32>(), 42);
}

//! Creation of AnyValue scalar via AddMember method with empty name.

TEST_F(AnyValueComposerTests, ScalarViaAddValue)
{
  AnyValueComposer builder;

  AnyValue expected_anyvalue{StringType, std::string("abc")};

  // By passing an empty member name we tell the builder that this will be the scalar.
  builder.AddValue(expected_anyvalue);

  EXPECT_EQ(builder.GetStackSize(), 1);

  auto value = builder.MoveAnyValue();
  EXPECT_EQ(value, expected_anyvalue);
}

//! Empty structure.

TEST_F(AnyValueComposerTests, EmptyStruct)
{
  AnyValueComposer builder;

  builder.StartStruct("struct_name");
  builder.EndStruct();

  auto value = builder.MoveAnyValue();
  EXPECT_EQ(value, EmptyStruct("struct_name"));
}

//! Creation of AnyValue containing a struct with single field.

TEST_F(AnyValueComposerTests, StructWithSingleField)
{
  AnyType expected_anytype = {{"signed", {SignedInteger32Type}}};

  AnyValueComposer builder;

  builder.StartStruct();
  builder.StartField("signed");
  builder.Int32(42);
  builder.EndField();
  builder.EndStruct();

  EXPECT_EQ(builder.GetStackSize(), 1);

  auto value = builder.MoveAnyValue();
  EXPECT_EQ(value.GetType(), expected_anytype);
  EXPECT_TRUE(IsStructValue(value));
  EXPECT_EQ(value["signed"].As<int32>(), 42);
}

//! Creation of AnyValue containing a struct with two fields.

TEST_F(AnyValueComposerTests, StructWithTwoFields)
{
  AnyType expected_anytype = {{"signed", {SignedInteger32Type}}, {"bool", {BooleanType}}};

  AnyValueComposer builder;

  builder.StartStruct();
  builder.StartField("signed");
  builder.Int32(42);
  builder.EndField();
  builder.StartField("bool");
  builder.Bool(true);
  builder.EndField();
  builder.EndStruct();

  EXPECT_EQ(builder.GetStackSize(), 1);

  auto value = builder.MoveAnyValue();
  EXPECT_EQ(value.GetType(), expected_anytype);
  EXPECT_TRUE(IsStructValue(value));
  EXPECT_EQ(value["signed"].As<int32>(), 42);
  EXPECT_EQ(value["bool"].As<boolean>(), true);
}

//! Creation of AnyValue containing a struct with two fields.
//! Same as before using method AddScalar and pre-constructed AnyValue scalars

TEST_F(AnyValueComposerTests, StructWithTwoFieldsViaAddValue)
{
  AnyType expected_anytype = {{"signed", {SignedInteger32Type}}, {"bool", {BooleanType}}};

  AnyValueComposer builder;

  builder.StartStruct();
  auto value1 = AnyValue(SignedInteger32Type, 42);
  builder.StartField("signed");
  builder.AddValue(value1);
  builder.EndField();
  auto value2 = AnyValue(BooleanType, true);
  builder.StartField("bool");
  builder.AddValue(value2);
  builder.EndField();
  builder.EndStruct();

  EXPECT_EQ(builder.GetStackSize(), 1);

  auto value = builder.MoveAnyValue();
  EXPECT_EQ(value.GetType(), expected_anytype);
  EXPECT_EQ(value.NumberOfMembers(), 2);
  EXPECT_TRUE(IsStructValue(value));
  EXPECT_EQ(value["signed"].As<int32>(), 42);
  EXPECT_EQ(value["bool"].As<boolean>(), true);
}

//! Creation of AnyValue containing a struct with two fields.
//! Same as before using method AddScalar and pre-constructed AnyValue scalars

TEST_F(AnyValueComposerTests, StructWithTwoFieldsViaAddMember)
{
  AnyType expected_anytype = {{"signed", {SignedInteger32Type}}, {"bool", {BooleanType}}};

  AnyValueComposer builder;

  builder.StartStruct();
  builder.AddMember("signed", AnyValue(SignedInteger32Type, 42));
  builder.AddMember("bool", AnyValue(BooleanType, true));
  builder.EndStruct();

  EXPECT_EQ(builder.GetStackSize(), 1);

  auto value = builder.MoveAnyValue();
  EXPECT_EQ(value.GetType(), expected_anytype);
  EXPECT_EQ(value.NumberOfMembers(), 2);
  EXPECT_TRUE(IsStructValue(value));
  EXPECT_EQ(value["signed"].As<int32>(), 42);
  EXPECT_EQ(value["bool"].As<boolean>(), true);
}

//! Creation of AnyValue containing a struct with another struct in it.

TEST_F(AnyValueComposerTests, StructWithNestedStructWithField)
{
  AnyType two_scalars = {{"signed", {SignedInteger32Type}}, {"bool", {BooleanType}}};
  AnyType expected_anytype = {{"scalars", two_scalars}};

  AnyValueComposer builder;

  builder.StartStruct();
  builder.StartField("scalars");

  builder.StartStruct();
  builder.StartField("signed");
  builder.Int32(42);
  builder.EndField();
  builder.StartField("bool");
  builder.Bool(true);
  builder.EndField();
  builder.EndStruct();

  builder.EndField();
  builder.EndStruct();

  EXPECT_EQ(builder.GetStackSize(), 1);

  auto value = builder.MoveAnyValue();
  EXPECT_EQ(value.GetType(), expected_anytype);
  EXPECT_TRUE(IsStructValue(value));
  EXPECT_TRUE(IsStructValue(value["scalars"]));
  EXPECT_EQ(value["scalars.signed"].As<int32>(), 42);
  EXPECT_EQ(value["scalars.bool"].As<boolean>(), true);
}

//! Creation of AnyValue containing two structures.

TEST_F(AnyValueComposerTests, StructWithTwoNestedStructs)
{
  const std::string struct_name = "struct_name";
  AnyType two_scalars = {{{"signed", {SignedInteger32Type}}, {"bool", {BooleanType}}},
                         "internal_struct"};

  AnyType expected_anytype{
      {{"struct1", two_scalars},
       {"struct2", {{"first", {SignedInteger8Type}}, {"second", {UnsignedInteger8Type}}}}},
      struct_name};

  AnyValueComposer builder;

  builder.StartStruct(struct_name);
  builder.StartField("struct1");

  builder.StartStruct("internal_struct");
  builder.StartField("signed");
  builder.Int32(42);
  builder.EndField();
  builder.StartField("bool");
  builder.Bool(true);
  builder.EndField();
  builder.EndStruct();

  builder.EndField();
  builder.StartField("struct2");

  builder.StartStruct();
  builder.StartField("first");
  builder.Int8(-43);
  builder.EndField();
  builder.StartField("second");
  builder.UInt8(44);
  builder.EndField();
  builder.EndStruct();

  builder.EndField();

  builder.EndStruct();

  auto value = builder.MoveAnyValue();
  EXPECT_EQ(value.GetType(), expected_anytype);
  EXPECT_TRUE(IsStructValue(value));
  EXPECT_TRUE(IsStructValue(value["struct1"]));
  EXPECT_TRUE(IsStructValue(value["struct2"]));
  EXPECT_EQ(value["struct1.signed"].As<int32>(), 42);
  EXPECT_EQ(value["struct1.bool"].As<boolean>(), true);
  EXPECT_EQ(value["struct2.first"].As<int8>(), -43);
  EXPECT_EQ(value["struct2.second"].As<uint8>(), 44);
}

//! Same test as before when internal structs are added via AddValue method

TEST_F(AnyValueComposerTests, StructWithTwoNestedStructsViaAddValue)
{
  const std::string struct_name = "struct_name";
  AnyType two_scalars = {{{"signed", {SignedInteger32Type}}, {"bool", {BooleanType}}},
                         "internal_struct"};

  AnyType expected_anytype{
      {{"struct1", two_scalars},
       {"struct2", {{"first", {SignedInteger8Type}}, {"second", {UnsignedInteger8Type}}}}},
      struct_name};

  AnyValue struct1 = {{{"signed", {SignedInteger32Type, 42}}, {"bool", {BooleanType, true}}},
                      "internal_struct"};

  AnyValue struct2 = {{"first", {SignedInteger8Type, -43}}, {"second", {UnsignedInteger8Type, 44}}};

  AnyValueComposer builder;

  builder.StartStruct(struct_name);

  builder.StartField("struct1");
  builder.AddValue(struct1);
  builder.EndField();
  builder.StartField("struct2");
  builder.AddValue(struct2);
  builder.EndField();

  builder.EndStruct();

  auto value = builder.MoveAnyValue();
  EXPECT_EQ(value.GetType(), expected_anytype);
  EXPECT_TRUE(IsStructValue(value));
  EXPECT_TRUE(IsStructValue(value["struct1"]));
  EXPECT_TRUE(IsStructValue(value["struct2"]));
  EXPECT_EQ(value["struct1.signed"].As<int32>(), 42);
  EXPECT_EQ(value["struct1.bool"].As<boolean>(), true);
  EXPECT_EQ(value["struct2.first"].As<int8>(), -43);
  EXPECT_EQ(value["struct2.second"].As<uint8>(), 44);
}

//! Same test as before when internal structs are added via AddMember method

TEST_F(AnyValueComposerTests, StructWithTwoNestedStructsViaAddMember)
{
  const std::string struct_name = "struct_name";
  AnyType two_scalars = {{{"signed", {SignedInteger32Type}}, {"bool", {BooleanType}}},
                         "internal_struct"};

  AnyType expected_anytype{
      {{"struct1", two_scalars},
       {"struct2", {{"first", {SignedInteger8Type}}, {"second", {UnsignedInteger8Type}}}}},
      struct_name};

  AnyValue struct1 = {{{"signed", {SignedInteger32Type, 42}}, {"bool", {BooleanType, true}}},
                      "internal_struct"};

  AnyValue struct2 = {{"first", {SignedInteger8Type, -43}}, {"second", {UnsignedInteger8Type, 44}}};

  AnyValueComposer builder;

  builder.StartStruct(struct_name);
  builder.AddMember("struct1", struct1);
  builder.AddMember("struct2", struct2);
  builder.EndStruct();

  auto value = builder.MoveAnyValue();
  EXPECT_EQ(value.GetType(), expected_anytype);
  EXPECT_TRUE(IsStructValue(value));
  EXPECT_TRUE(IsStructValue(value["struct1"]));
  EXPECT_TRUE(IsStructValue(value["struct2"]));
  EXPECT_EQ(value["struct1.signed"].As<int32>(), 42);
  EXPECT_EQ(value["struct1.bool"].As<boolean>(), true);
  EXPECT_EQ(value["struct2.first"].As<int8>(), -43);
  EXPECT_EQ(value["struct2.second"].As<uint8>(), 44);
}

//! Validate array construction when no elements have been added.

TEST_F(AnyValueComposerTests, EmptyArray)
{
  AnyValueComposer builder;

  builder.StartArray("array_name");

  // current implementation doesn't allow building array AnyValue without adding at least one
  // element
  EXPECT_THROW(builder.EndArray(), sup::dto::ParseException);
}

//! Construction of scalar array with the name and two elements.

TEST_F(AnyValueComposerTests, ScalarArray)
{
  auto expected = ArrayValue({{SignedInteger32Type, 42}, 43}, "array_name");

  AnyValueComposer builder;

  builder.StartArray("array_name");
  builder.StartArrayElement();
  builder.Int32(42);
  builder.EndArrayElement();
  builder.StartArrayElement();
  builder.Int32(43);
  builder.EndArrayElement();
  builder.EndArray();

  auto value = builder.MoveAnyValue();
  EXPECT_EQ(value, expected);
}

//! Construction of scalar array with the name and two elements.
//! Using convenience AddArrayElement methods.

TEST_F(AnyValueComposerTests, ScalarArrayViaAddArrayElement)
{
  auto expected = ArrayValue({{SignedInteger32Type, 42}, 43}, "array_name");

  AnyValueComposer builder;

  builder.StartArray("array_name");
  builder.AddArrayElement(AnyValue(SignedInteger32Type, 42));
  builder.AddArrayElement(AnyValue(SignedInteger32Type, 43));
  builder.EndArray();

  auto value = builder.MoveAnyValue();
  EXPECT_EQ(value, expected);
}

//! Building a structure with scalar array as a single field.

TEST_F(AnyValueComposerTests, StructWithScalarArrayAsField)
{
  auto array_value = ArrayValue({{SignedInteger32Type, 42}, 43}, "array_name");
  AnyValue expected_struct_value = {{{"array_field", array_value}}, "struct_name"};

  AnyValueComposer builder;

  builder.StartStruct("struct_name");
  builder.StartField("array_field");
  builder.StartArray("array_name");
  builder.StartArrayElement();
  builder.Int32(42);
  builder.EndArrayElement();
  builder.StartArrayElement();
  builder.Int32(43);
  builder.EndArrayElement();
  builder.EndArray();
  builder.EndField();
  builder.EndStruct();

  auto value = builder.MoveAnyValue();
  EXPECT_EQ(value, expected_struct_value);
}

//! Building a structure with two scalar array as fields.

TEST_F(AnyValueComposerTests, StructWithTwoScalarArrayAsField)
{
  auto array1 = ArrayValue({{SignedInteger32Type, 42}, 43}, "array_name1");
  auto array2 = ArrayValue({{SignedInteger32Type, 44}, 45, 46}, "array_name2");
  AnyValue expected_struct_value = {{{"field1", array1}, {"field2", array2}}, "struct_name"};

  AnyValueComposer builder;

  builder.StartStruct("struct_name");

  builder.StartField("field1");
  builder.StartArray("array_name1");
  builder.AddArrayElement(AnyValue(SignedInteger32Type, 42));
  builder.AddArrayElement(AnyValue(SignedInteger32Type, 43));
  builder.EndArray();
  builder.EndField();

  builder.StartField("field2");
  builder.StartArray("array_name2");
  builder.AddArrayElement(AnyValue(SignedInteger32Type, 44));
  builder.AddArrayElement(AnyValue(SignedInteger32Type, 45));
  builder.AddArrayElement(AnyValue(SignedInteger32Type, 46));
  builder.EndArray();
  builder.EndField();

  builder.EndStruct();

  auto value = builder.MoveAnyValue();
  EXPECT_EQ(value, expected_struct_value);
}

//! Building an array with two structure elements.

TEST_F(AnyValueComposerTests, ArrayWithTwoStructureElements)
{
  AnyValue struct1 = {
      {{"first", {SignedInteger8Type, -43}}, {"second", {UnsignedInteger8Type, 44}}},
      "struct_name"};
  AnyValue struct2 = {{{"first", {SignedInteger8Type, 42}}, {"second", {UnsignedInteger8Type, 43}}},
                      "struct_name"};

  auto expected_array_value = ArrayValue({struct1, struct2}, "array_name");

  AnyValueComposer builder;

  builder.StartArray("array_name");

  builder.StartArrayElement();
  builder.StartStruct("struct_name");
  builder.StartField("first");
  builder.Int8(-43);
  builder.EndField();
  builder.StartField("second");
  builder.UInt8(44);
  builder.EndField();
  builder.EndStruct();
  builder.EndArrayElement();

  builder.StartArrayElement();
  builder.StartStruct("struct_name");
  builder.AddMember("first", AnyValue(SignedInteger8Type, 42));
  builder.AddMember("second", AnyValue(UnsignedInteger8Type, 43));
  builder.EndStruct();
  builder.EndArrayElement();

  builder.EndArray();

  auto value = builder.MoveAnyValue();
  EXPECT_EQ(value, expected_array_value);
}

//! Building a structure with array as a field with two structures.

TEST_F(AnyValueComposerTests, StructureWithArrayWithStructure)
{
  AnyValue struct1 = {
      {{"first", {SignedInteger8Type, -43}}, {"second", {UnsignedInteger8Type, 44}}},
      "struct_name"};
  AnyValue struct2 = {{{"first", {SignedInteger8Type, 42}}, {"second", {UnsignedInteger8Type, 43}}},
                      "struct_name"};

  auto array_value = ArrayValue({{struct1}, struct2}, "array_name");

  AnyValue expected_struct_value = {{{"field", array_value}}, "struct_name2"};

  AnyValueComposer builder;

  builder.StartStruct("struct_name2");
  builder.StartField("field");

  builder.StartArray("array_name");

  builder.StartArrayElement();
  builder.StartStruct("struct_name");
  builder.StartField("first");
  builder.Int8(-43);
  builder.EndField();
  builder.StartField("second");
  builder.UInt8(44);
  builder.EndField();
  builder.EndStruct();
  builder.EndArrayElement();

  builder.StartArrayElement();
  builder.StartStruct("struct_name");
  builder.AddMember("first", AnyValue(SignedInteger8Type, 42));
  builder.AddMember("second", AnyValue(UnsignedInteger8Type, 43));
  builder.EndStruct();
  builder.EndArrayElement();

  builder.EndArray();

  builder.EndField();
  builder.EndStruct();

  auto value = builder.MoveAnyValue();
  EXPECT_EQ(value, expected_struct_value);
}
