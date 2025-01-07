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
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include "sup/dto/anytype_composer.h"

#include <sup/dto/anytype.h>
#include <sup/dto/anyvalue_exceptions.h>

#include <gtest/gtest.h>

using namespace sup::dto;

class AnyTypeComposerTests : public ::testing::Test
{};

//! Checking that the builder throws when no type was defined.
TEST_F(AnyTypeComposerTests, InitialState)
{
  AnyTypeComposer builder;
  EXPECT_EQ(builder.GetStackSize(), 0);
  EXPECT_THROW(builder.MoveAnyType(), ParseException);
}

//! Creation of scalar type.
TEST_F(AnyTypeComposerTests, Scalar)
{
  AnyTypeComposer builder;

  builder.Int32();

  EXPECT_EQ(builder.GetStackSize(), 1);

  auto anytype = builder.MoveAnyType();
  EXPECT_EQ(anytype, sup::dto::SignedInteger32Type);
}

//! Empty structure.
TEST_F(AnyTypeComposerTests, EmptyStruct)
{
  AnyTypeComposer builder;

  builder.StartStruct("struct_name");
  builder.EndStruct();

  auto anytype = builder.MoveAnyType();
  EXPECT_EQ(anytype, sup::dto::EmptyStructType("struct_name"));
}

//! Creation of AnyType containing a struct with single field.
TEST_F(AnyTypeComposerTests, StructWithSingleField)
{
  sup::dto::AnyType expected_anytype = {{"signed", {sup::dto::SignedInteger32Type}}};

  AnyTypeComposer builder;

  builder.StartStruct();
  builder.StartField("signed");
  builder.Int32();
  builder.EndField();
  builder.EndStruct();

  EXPECT_EQ(builder.GetStackSize(), 1);

  auto anytype = builder.MoveAnyType();
  EXPECT_EQ(anytype, expected_anytype);
}

//! Creation of AnyType containing a struct with two fields.
TEST_F(AnyTypeComposerTests, StructWithTwoFields)
{
  sup::dto::AnyType expected_anytype = {{"signed", {sup::dto::SignedInteger32Type}},
                                        {"bool", {sup::dto::BooleanType}}};

  AnyTypeComposer builder;

  builder.StartStruct();
  builder.StartField("signed");
  builder.Int32();
  builder.EndField();
  builder.StartField("bool");
  builder.Bool();
  builder.EndField();
  builder.EndStruct();

  EXPECT_EQ(builder.GetStackSize(), 1);

  auto anytype = builder.MoveAnyType();
  EXPECT_EQ(anytype, expected_anytype);
}

//! Creation of AnyType containing a struct with another struct in it.
TEST_F(AnyTypeComposerTests, StructWithNestedStructWithField)
{
  sup::dto::AnyType two_scalars = {{"signed", {sup::dto::SignedInteger32Type}},
                                   {"bool", {sup::dto::BooleanType}}};
  sup::dto::AnyType expected_anytype = {{{"scalars", two_scalars}}, "my_struct"};

  AnyTypeComposer builder;

  builder.StartStruct("my_struct");
  builder.StartField("scalars");

  builder.StartStruct();
  builder.StartField("signed");
  builder.Int32();
  builder.EndField();
  builder.StartField("bool");
  builder.Bool();
  builder.EndField();
  builder.EndStruct();

  builder.EndField();
  builder.EndStruct();

  EXPECT_EQ(builder.GetStackSize(), 1);

  auto anytype = builder.MoveAnyType();
  EXPECT_EQ(anytype, expected_anytype);
}

//! Creation of AnyType containing two structures.
TEST_F(AnyTypeComposerTests, StructWithTwoNestedStructs)
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

  AnyTypeComposer builder;

  builder.StartStruct(struct_name);
  builder.StartField("struct1");

  builder.StartStruct("internal_struct");
  builder.StartField("signed");
  builder.Int32();
  builder.EndField();
  builder.StartField("bool");
  builder.Bool();
  builder.EndField();
  builder.EndStruct();

  builder.EndField();
  builder.StartField("struct2");

  builder.StartStruct();
  builder.StartField("first");
  builder.Int8();
  builder.EndField();
  builder.StartField("second");
  builder.UInt8();
  builder.EndField();
  builder.EndStruct();

  builder.EndField();

  builder.EndStruct();

  auto anytype = builder.MoveAnyType();
  EXPECT_EQ(anytype, expected_anytype);
}

//! Array construction when no elements have beem added.
TEST_F(AnyTypeComposerTests, EmptyArray)
{
  AnyTypeComposer builder;

  builder.StartArray("array_name", 1);
  // current implementation expects at least one element to have array property initialised
  // attempt to build empty array leads to exception being thrown
  EXPECT_THROW(builder.EndArray(), ParseException);
}

//! Construction of scalar array type with a name and two elements.
TEST_F(AnyTypeComposerTests, ScalarArray)
{
  auto expected = sup::dto::AnyType(2, sup::dto::SignedInteger32Type, "array_name");

  AnyTypeComposer builder;

  builder.StartArray("array_name", 2);
  builder.StartArrayElement();
  builder.Int32();
  builder.EndArrayElement();
  builder.EndArray();

  auto anytype = builder.MoveAnyType();
  EXPECT_EQ(anytype, expected);
}

//! Construction of scalar array type with a name and zero elements.
TEST_F(AnyTypeComposerTests, ZeroSizeArray)
{
  auto expected = sup::dto::AnyType(0, sup::dto::SignedInteger32Type, "array_name");

  AnyTypeComposer builder;

  builder.StartArray("array_name", 0);
  builder.StartArrayElement();
  builder.Int32();
  builder.EndArrayElement();
  builder.EndArray();

  auto anytype = builder.MoveAnyType();
  EXPECT_EQ(anytype, expected);
}

//! Trying to build scalar array type with two element types (not allowed).
TEST_F(AnyTypeComposerTests, ArrayTwoElementTypes)
{
  AnyTypeComposer builder;

  builder.StartArray("array_name", 0);
  builder.StartArrayElement();
  builder.Int32();
  builder.EndArrayElement();
  builder.StartArrayElement();
  builder.Bool();
  EXPECT_THROW(builder.EndArrayElement(), ParseException);
}

//! Building a structure type with scalar array as a single field.
TEST_F(AnyTypeComposerTests, StructWithScalarArrayAsField)
{
  auto array_anytype = sup::dto::AnyType(2, sup::dto::SignedInteger32Type, "array_name");
  sup::dto::AnyType expected_struct_anytype = {{{"array_field", array_anytype}}, "struct_name"};

  AnyTypeComposer builder;

  builder.StartStruct("struct_name");
  builder.StartField("array_field");
  builder.StartArray("array_name", 2);
  builder.StartArrayElement();
  builder.Int32();
  builder.EndArrayElement();
  builder.EndArray();
  builder.EndField();
  builder.EndStruct();

  auto anytype = builder.MoveAnyType();
  EXPECT_EQ(anytype, expected_struct_anytype);
}

//! Building a structure with two scalar array as fields.

TEST_F(AnyTypeComposerTests, StructWithTwoScalarArrayAsField)
{
  auto array1 = sup::dto::AnyType(2, sup::dto::SignedInteger32Type, "array_name1");
  auto array2 = sup::dto::AnyType(3, sup::dto::SignedInteger32Type, "array_name2");
  sup::dto::AnyType expected_struct_anytype = {{{"field1", array1}, {"field2", array2}},
                                              "struct_name"};

  AnyTypeComposer builder;

  builder.StartStruct("struct_name");

  builder.StartField("field1");
  builder.StartArray("array_name1", 2);
  builder.StartArrayElement();
  builder.Int32();
  builder.EndArrayElement();
  builder.EndArray();
  builder.EndField();

  builder.StartField("field2");
  builder.StartArray("array_name2", 3);
  builder.StartArrayElement();
  builder.Int32();
  builder.EndArrayElement();
  builder.EndArray();
  builder.EndField();

  builder.EndStruct();

  auto anytype = builder.MoveAnyType();
  EXPECT_EQ(anytype, expected_struct_anytype);
}

//! Building an array type with two structure elements.

TEST_F(AnyTypeComposerTests, ArrayWithTwoStructureElements)
{
  sup::dto::AnyType struct_type = {{{"first", sup::dto::SignedInteger8Type},
                                 {"second", sup::dto::UnsignedInteger8Type}},
                                "struct_name"};

  auto expected_array_anytype = sup::dto::AnyType(2, struct_type, "array_name");

  AnyTypeComposer builder;

  builder.StartArray("array_name", 2);

  builder.StartArrayElement();
  builder.StartStruct("struct_name");
  builder.StartField("first");
  builder.Int8();
  builder.EndField();
  builder.StartField("second");
  builder.UInt8();
  builder.EndField();
  builder.EndStruct();
  builder.EndArrayElement();

  builder.EndArray();

  auto anytype = builder.MoveAnyType();
  EXPECT_EQ(anytype, expected_array_anytype);
}

//! Building a structure with array as a field with two structures.
TEST_F(AnyTypeComposerTests, StructureWithArrayWithStructure)
{
  sup::dto::AnyType struct_type = {{{"first", sup::dto::SignedInteger8Type},
                                {"second", sup::dto::UnsignedInteger8Type}},
                                "struct_name"};
  auto array_anytype = sup::dto::AnyType(2, struct_type, "array_name");
  sup::dto::AnyType expected_struct_anytype = {{{"field", array_anytype}}, "struct_name_outer"};

  AnyTypeComposer builder;

  builder.StartStruct("struct_name_outer");
  builder.StartField("field");

  builder.StartArray("array_name", 2);

  builder.StartArrayElement();
  builder.StartStruct("struct_name");
  builder.StartField("first");
  builder.Int8();
  builder.EndField();
  builder.StartField("second");
  builder.UInt8();
  builder.EndField();
  builder.EndStruct();
  builder.EndArrayElement();

  builder.EndArray();

  builder.EndField();
  builder.EndStruct();

  auto anytype = builder.MoveAnyType();
  EXPECT_EQ(anytype, expected_struct_anytype);
}
