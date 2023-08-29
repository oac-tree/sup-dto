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

#include <gtest/gtest.h>
#include <sup/dto/anytype.h>
#include <sup/dto/anytype_helper.h>
#include <sup/dto/anyvalue.h>
#include <sup/dto/anyvalue_helper.h>

using namespace sup::dto;

class AnyValueComposerTests : public ::testing::Test
{
};

//! Checking that the builder returns an empty value.

TEST_F(AnyValueComposerTests, InitialState)
{
  AnyValueComposer builder;
  auto value = builder.MoveAnyValue();

  EXPECT_EQ(builder.GetStackSize(), 0);

  EXPECT_TRUE(::sup::dto::IsEmptyValue(value));
}

//! Creation of AnyValue scalar.

TEST_F(AnyValueComposerTests, Scalar)
{
  AnyValueComposer builder;

  builder.Int32(42);

  EXPECT_EQ(builder.GetStackSize(), 1);

  auto value = builder.MoveAnyValue();
  EXPECT_EQ(value.GetType(), sup::dto::SignedInteger32Type);
  EXPECT_TRUE(::sup::dto::IsScalarValue(value));
  EXPECT_EQ(value.As<sup::dto::int32>(), 42);
}

//! Creation of AnyValue scalar via AddMember method with empty name.

TEST_F(AnyValueComposerTests, ScalarViaAddValue)
{
  AnyValueComposer builder;

  sup::dto::AnyValue expected_anyvalue{sup::dto::StringType, std::string("abc")};

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
  EXPECT_EQ(value, sup::dto::EmptyStruct("struct_name"));
}

//! Creation of AnyValue containing a struct with single field.

TEST_F(AnyValueComposerTests, StructWithSingleField)
{
  sup::dto::AnyType expected_anytype = {{"signed", {sup::dto::SignedInteger32Type}}};

  AnyValueComposer builder;

  builder.StartStruct();
  builder.StartField("signed");
  builder.Int32(42);
  builder.EndField();
  builder.EndStruct();

  EXPECT_EQ(builder.GetStackSize(), 1);

  auto value = builder.MoveAnyValue();
  EXPECT_EQ(value.GetType(), expected_anytype);
  EXPECT_TRUE(::sup::dto::IsStructValue(value));
  EXPECT_EQ(value["signed"].As<sup::dto::int32>(), 42);
}

//! Creation of AnyValue containing a struct with two fields.

TEST_F(AnyValueComposerTests, StructWithTwoFields)
{
  sup::dto::AnyType expected_anytype = {{"signed", {sup::dto::SignedInteger32Type}},
                                        {"bool", {sup::dto::BooleanType}}};

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
  EXPECT_TRUE(::sup::dto::IsStructValue(value));
  EXPECT_EQ(value["signed"].As<sup::dto::int32>(), 42);
  EXPECT_EQ(value["bool"].As<sup::dto::boolean>(), true);
}

//! Creation of AnyValue containing a struct with two fields.
//! Same as before using method AddScalar and pre-constructed AnyValue scalars

TEST_F(AnyValueComposerTests, StructWithTwoFieldsViaAddValue)
{
  sup::dto::AnyType expected_anytype = {{"signed", {sup::dto::SignedInteger32Type}},
                                        {"bool", {sup::dto::BooleanType}}};

  AnyValueComposer builder;

  builder.StartStruct();
  auto value1 = ::sup::dto::AnyValue(::sup::dto::SignedInteger32Type, 42);
  builder.StartField("signed");
  builder.AddValue(value1);
  builder.EndField();
  auto value2 = ::sup::dto::AnyValue(::sup::dto::BooleanType, true);
  builder.StartField("bool");
  builder.AddValue(value2);
  builder.EndField();
  builder.EndStruct();

  EXPECT_EQ(builder.GetStackSize(), 1);

  auto value = builder.MoveAnyValue();
  EXPECT_EQ(value.GetType(), expected_anytype);
  EXPECT_EQ(value.NumberOfMembers(), 2);
  EXPECT_TRUE(::sup::dto::IsStructValue(value));
  EXPECT_EQ(value["signed"].As<sup::dto::int32>(), 42);
  EXPECT_EQ(value["bool"].As<sup::dto::boolean>(), true);
}

//! Creation of AnyValue containing a struct with two fields.
//! Same as before using method AddScalar and pre-constructed AnyValue scalars

TEST_F(AnyValueComposerTests, StructWithTwoFieldsViaAddMember)
{
  sup::dto::AnyType expected_anytype = {{"signed", {sup::dto::SignedInteger32Type}},
                                        {"bool", {sup::dto::BooleanType}}};

  AnyValueComposer builder;

  builder.StartStruct();
  builder.AddMember("signed", ::sup::dto::AnyValue(::sup::dto::SignedInteger32Type, 42));
  builder.AddMember("bool", ::sup::dto::AnyValue(::sup::dto::BooleanType, true));
  builder.EndStruct();

  EXPECT_EQ(builder.GetStackSize(), 1);

  auto value = builder.MoveAnyValue();
  EXPECT_EQ(value.GetType(), expected_anytype);
  EXPECT_EQ(value.NumberOfMembers(), 2);
  EXPECT_TRUE(::sup::dto::IsStructValue(value));
  EXPECT_EQ(value["signed"].As<sup::dto::int32>(), 42);
  EXPECT_EQ(value["bool"].As<sup::dto::boolean>(), true);
}

//! Creation of AnyValue containing a struct with another struct in it.

TEST_F(AnyValueComposerTests, StructWithNestedStructWithField)
{
  sup::dto::AnyType two_scalars = {{"signed", {sup::dto::SignedInteger32Type}},
                                   {"bool", {sup::dto::BooleanType}}};
  sup::dto::AnyType expected_anytype = {{"scalars", two_scalars}};

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
  EXPECT_TRUE(::sup::dto::IsStructValue(value));
  EXPECT_TRUE(::sup::dto::IsStructValue(value["scalars"]));
  EXPECT_EQ(value["scalars.signed"].As<sup::dto::int32>(), 42);
  EXPECT_EQ(value["scalars.bool"].As<sup::dto::boolean>(), true);
}

//! Creation of AnyValue containing two structures.

TEST_F(AnyValueComposerTests, StructWithTwoNestedStructs)
{
  const std::string struct_name = "struct_name";
  sup::dto::AnyType two_scalars = {
      {{"signed", {sup::dto::SignedInteger32Type}}, {"bool", {sup::dto::BooleanType}}},
      "internal_struct"};

  sup::dto::AnyType expected_anytype{
      {{"struct1", two_scalars},
       {"struct2",
        {{"first", {sup::dto::SignedInteger8Type}}, {"second", {sup::dto::UnsignedInteger8Type}}}}},
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
  EXPECT_TRUE(::sup::dto::IsStructValue(value));
  EXPECT_TRUE(::sup::dto::IsStructValue(value["struct1"]));
  EXPECT_TRUE(::sup::dto::IsStructValue(value["struct2"]));
  EXPECT_EQ(value["struct1.signed"].As<sup::dto::int32>(), 42);
  EXPECT_EQ(value["struct1.bool"].As<sup::dto::boolean>(), true);
  EXPECT_EQ(value["struct2.first"].As<sup::dto::int8>(), -43);
  EXPECT_EQ(value["struct2.second"].As<sup::dto::uint8>(), 44);
}

//! Same test as before when internal structs are added via AddValue method

TEST_F(AnyValueComposerTests, StructWithTwoNestedStructsViaAddValue)
{
  const std::string struct_name = "struct_name";
  sup::dto::AnyType two_scalars = {
      {{"signed", {sup::dto::SignedInteger32Type}}, {"bool", {sup::dto::BooleanType}}},
      "internal_struct"};

  sup::dto::AnyType expected_anytype{
      {{"struct1", two_scalars},
       {"struct2",
        {{"first", {sup::dto::SignedInteger8Type}}, {"second", {sup::dto::UnsignedInteger8Type}}}}},
      struct_name};

  sup::dto::AnyValue struct1 = {
      {{"signed", {sup::dto::SignedInteger32Type, 42}}, {"bool", {sup::dto::BooleanType, true}}},
      "internal_struct"};

  sup::dto::AnyValue struct2 = {{"first", {sup::dto::SignedInteger8Type, -43}},
                                {"second", {sup::dto::UnsignedInteger8Type, 44}}};

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
  EXPECT_TRUE(::sup::dto::IsStructValue(value));
  EXPECT_TRUE(::sup::dto::IsStructValue(value["struct1"]));
  EXPECT_TRUE(::sup::dto::IsStructValue(value["struct2"]));
  EXPECT_EQ(value["struct1.signed"].As<sup::dto::int32>(), 42);
  EXPECT_EQ(value["struct1.bool"].As<sup::dto::boolean>(), true);
  EXPECT_EQ(value["struct2.first"].As<sup::dto::int8>(), -43);
  EXPECT_EQ(value["struct2.second"].As<sup::dto::uint8>(), 44);
}

//! Same test as before when internal structs are added via AddMember method

TEST_F(AnyValueComposerTests, StructWithTwoNestedStructsViaAddMember)
{
  const std::string struct_name = "struct_name";
  sup::dto::AnyType two_scalars = {
      {{"signed", {sup::dto::SignedInteger32Type}}, {"bool", {sup::dto::BooleanType}}},
      "internal_struct"};

  sup::dto::AnyType expected_anytype{
      {{"struct1", two_scalars},
       {"struct2",
        {{"first", {sup::dto::SignedInteger8Type}}, {"second", {sup::dto::UnsignedInteger8Type}}}}},
      struct_name};

  sup::dto::AnyValue struct1 = {
      {{"signed", {sup::dto::SignedInteger32Type, 42}}, {"bool", {sup::dto::BooleanType, true}}},
      "internal_struct"};

  sup::dto::AnyValue struct2 = {{"first", {sup::dto::SignedInteger8Type, -43}},
                                {"second", {sup::dto::UnsignedInteger8Type, 44}}};

  AnyValueComposer builder;

  builder.StartStruct(struct_name);
  builder.AddMember("struct1", struct1);
  builder.AddMember("struct2", struct2);
  builder.EndStruct();

  auto value = builder.MoveAnyValue();
  EXPECT_EQ(value.GetType(), expected_anytype);
  EXPECT_TRUE(::sup::dto::IsStructValue(value));
  EXPECT_TRUE(::sup::dto::IsStructValue(value["struct1"]));
  EXPECT_TRUE(::sup::dto::IsStructValue(value["struct2"]));
  EXPECT_EQ(value["struct1.signed"].As<sup::dto::int32>(), 42);
  EXPECT_EQ(value["struct1.bool"].As<sup::dto::boolean>(), true);
  EXPECT_EQ(value["struct2.first"].As<sup::dto::int8>(), -43);
  EXPECT_EQ(value["struct2.second"].As<sup::dto::uint8>(), 44);
}

//! Validate array construction when no elements have beem added.

TEST_F(AnyValueComposerTests, EmptyArray)
{
  AnyValueComposer builder;

  builder.StartArray("array_name");
  builder.EndArray();

  // current implementation expects at least one element to have array property initialised
  // attempt to build empty array leads to empty AnyValue
  auto value = builder.MoveAnyValue();
  EXPECT_TRUE(sup::dto::IsEmptyValue(value));
}

//! Construction of scalar array with the name and two elements.

TEST_F(AnyValueComposerTests, ScalarArray)
{
  auto expected = sup::dto::ArrayValue({{sup::dto::SignedInteger32Type, 42}, 43}, "array_name");

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
  auto expected = sup::dto::ArrayValue({{sup::dto::SignedInteger32Type, 42}, 43}, "array_name");

  AnyValueComposer builder;

  builder.StartArray("array_name");
  builder.AddArrayElement(::sup::dto::AnyValue(::sup::dto::SignedInteger32Type, 42));
  builder.AddArrayElement(::sup::dto::AnyValue(::sup::dto::SignedInteger32Type, 43));
  builder.EndArray();

  auto value = builder.MoveAnyValue();
  EXPECT_EQ(value, expected);
}

//! Building a structure with scalar array as a single field.

TEST_F(AnyValueComposerTests, StructWithScalarArrayAsField)
{
  auto array_value = sup::dto::ArrayValue({{sup::dto::SignedInteger32Type, 42}, 43}, "array_name");
  sup::dto::AnyValue expected_struct_value = {{{"array_field", array_value}}, "struct_name"};

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
  auto array1 = sup::dto::ArrayValue({{sup::dto::SignedInteger32Type, 42}, 43}, "array_name1");
  auto array2 = sup::dto::ArrayValue({{sup::dto::SignedInteger32Type, 44}, 45, 46}, "array_name2");
  sup::dto::AnyValue expected_struct_value = {{{"field1", array1}, {"field2", array2}},
                                              "struct_name"};

  AnyValueComposer builder;

  builder.StartStruct("struct_name");

  builder.StartField("field1");
  builder.StartArray("array_name1");
  builder.AddArrayElement(::sup::dto::AnyValue(::sup::dto::SignedInteger32Type, 42));
  builder.AddArrayElement(::sup::dto::AnyValue(::sup::dto::SignedInteger32Type, 43));
  builder.EndArray();
  builder.EndField();

  builder.StartField("field2");
  builder.StartArray("array_name2");
  builder.AddArrayElement(::sup::dto::AnyValue(::sup::dto::SignedInteger32Type, 44));
  builder.AddArrayElement(::sup::dto::AnyValue(::sup::dto::SignedInteger32Type, 45));
  builder.AddArrayElement(::sup::dto::AnyValue(::sup::dto::SignedInteger32Type, 46));
  builder.EndArray();
  builder.EndField();

  builder.EndStruct();

  auto value = builder.MoveAnyValue();
  EXPECT_EQ(value, expected_struct_value);
}

//! Building an array with two structure elements.

TEST_F(AnyValueComposerTests, ArrayWithTwoStructureElements)
{
  sup::dto::AnyValue struct1 = {{{"first", {sup::dto::SignedInteger8Type, -43}},
                                 {"second", {sup::dto::UnsignedInteger8Type, 44}}},
                                "struct_name"};
  sup::dto::AnyValue struct2 = {{{"first", {sup::dto::SignedInteger8Type, 42}},
                                 {"second", {sup::dto::UnsignedInteger8Type, 43}}},
                                "struct_name"};

  auto expected_array_value = sup::dto::ArrayValue({struct1, struct2}, "array_name");

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
  builder.AddMember("first", ::sup::dto::AnyValue(::sup::dto::SignedInteger8Type, 42));
  builder.AddMember("second", ::sup::dto::AnyValue(::sup::dto::UnsignedInteger8Type, 43));
  builder.EndStruct();
  builder.EndArrayElement();

  builder.EndArray();

  auto value = builder.MoveAnyValue();
  EXPECT_EQ(value, expected_array_value);
}

//! Building a structure with array as a field with two structures.

TEST_F(AnyValueComposerTests, StructureWithArrayWithStructure)
{
  sup::dto::AnyValue struct1 = {{{"first", {sup::dto::SignedInteger8Type, -43}},
                                 {"second", {sup::dto::UnsignedInteger8Type, 44}}},
                                "struct_name"};
  sup::dto::AnyValue struct2 = {{{"first", {sup::dto::SignedInteger8Type, 42}},
                                 {"second", {sup::dto::UnsignedInteger8Type, 43}}},
                                "struct_name"};

  auto array_value = sup::dto::ArrayValue({{struct1}, struct2}, "array_name");

  sup::dto::AnyValue expected_struct_value = {{{"field", array_value}}, "struct_name2"};

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
  builder.AddMember("first", ::sup::dto::AnyValue(::sup::dto::SignedInteger8Type, 42));
  builder.AddMember("second", ::sup::dto::AnyValue(::sup::dto::UnsignedInteger8Type, 43));
  builder.EndStruct();
  builder.EndArrayElement();

  builder.EndArray();

  builder.EndField();
  builder.EndStruct();

  auto value = builder.MoveAnyValue();
  EXPECT_EQ(value, expected_struct_value);
}
