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

#include <sup/dto/parse/anyvalue_array_buildnode.h>
#include <sup/dto/parse/anyvalue_builder.h>
#include <sup/dto/parse/anyvalue_buildnode.h>
#include <sup/dto/parse/anyvalue_encodingelement_buildnode.h>
#include <sup/dto/parse/anyvalue_root_buildnode.h>
#include <sup/dto/parse/anyvalue_typeelement_buildnode.h>
#include <sup/dto/parse/anyvalue_valueelement_buildnode.h>
#include <sup/dto/parse/arrayvalue_buildnode.h>
#include <sup/dto/parse/serialization_constants.h>

#include <sup/dto/anytype_registry.h>
#include <sup/dto/anyvalue.h>

using namespace sup::dto;

class AnyValueBuilderTest : public ::testing::Test
{
protected:
  AnyValueBuilderTest();
  virtual ~AnyValueBuilderTest();
};

TEST_F(AnyValueBuilderTest, AnyValueBuilderMethods)
{
  AnyTypeRegistry anytype_registry;
  AnyValueBuilder builder{&anytype_registry};

    // Most methods throw when the current node contained is still an AnyValueRootBuildNode:
  EXPECT_THROW(builder.Null(), ParseException);
  EXPECT_THROW(builder.Bool(true), ParseException);
  EXPECT_THROW(builder.Int(5), ParseException);
  EXPECT_THROW(builder.Uint(5), ParseException);
  EXPECT_THROW(builder.Int64(5), ParseException);
  EXPECT_THROW(builder.Uint64(5), ParseException);
  EXPECT_THROW(builder.Double(1.0), ParseException);
  EXPECT_THROW(builder.RawNumber("20", 2, true), ParseException);
  EXPECT_THROW(builder.String("text", 2, true), ParseException);
  EXPECT_THROW(builder.Key("key", 2, true), ParseException);
  EXPECT_THROW(builder.StartObject(), ParseException);
  EXPECT_THROW(builder.EndObject(1), ParseException);
  EXPECT_THROW(builder.EndArray(0), ParseException);

  // Retrieving the AnyValue throws when the current node is not the root node:
  EXPECT_TRUE(builder.StartArray());
  EXPECT_THROW(builder.MoveAnyValue(), ParseException);
}

TEST_F(AnyValueBuilderTest, AnyValueBuildNodeMethods)
{
  // Exceptions:
  AnyTypeRegistry anytype_registry;
  AnyValue val;
  EXPECT_THROW(AnyValueBuildNode invalid_node(nullptr, nullptr, val), InvalidOperationException);
  AnyValueBuildNode node(&anytype_registry, nullptr, val);
  EXPECT_THROW(node.Bool(bool(-1)), ParseException);
  EXPECT_THROW(node.Int32(-1), ParseException);
  EXPECT_THROW(node.Int64(-1), ParseException);
  EXPECT_THROW(node.Uint32(1), ParseException);
  EXPECT_THROW(node.Uint64(1), ParseException);
  EXPECT_THROW(node.Double(1.0), ParseException);
  EXPECT_THROW(node.String("wrong moment to pass a string"), ParseException);
  EXPECT_THROW(node.GetStructureNode(), ParseException);
  EXPECT_THROW(node.GetArrayNode(), ParseException);
  EXPECT_THROW(node.PopStructureNode(), ParseException);
  EXPECT_THROW(node.PopArrayNode(), ParseException);
  EXPECT_TRUE(node.Member("membername"));
  EXPECT_THROW(node.Member("othermembername"), ParseException);

  // Populate scalar member:
  AnyValue struct_val = {{
    {"flag", false},
    {"a", 0},
    {"b", 0},
    {"c", 0},
    {"d", 0},
    {"e", 0.0},
    {"f", ""}
  }};
  AnyValueBuildNode struct_node(&anytype_registry, nullptr, struct_val);
  EXPECT_TRUE(struct_node.Member("flag"));
  EXPECT_TRUE(struct_node.Bool(true));
  EXPECT_TRUE(struct_node.Member("a"));
  EXPECT_TRUE(struct_node.Int32(-1));
  EXPECT_TRUE(struct_node.Member("b"));
  EXPECT_TRUE(struct_node.Uint32(2));
  EXPECT_TRUE(struct_node.Member("c"));
  EXPECT_TRUE(struct_node.Int64(-3));
  EXPECT_TRUE(struct_node.Member("d"));
  EXPECT_TRUE(struct_node.Uint64(4));
  EXPECT_TRUE(struct_node.Member("e"));
  EXPECT_TRUE(struct_node.Double(7.5));
  EXPECT_TRUE(struct_node.Member("f"));
  EXPECT_TRUE(struct_node.String("text"));
}

TEST_F(AnyValueBuilderTest, AnyValueRootBuildNodeMethods)
{
  AnyTypeRegistry anytype_registry;
  EXPECT_THROW(AnyValueRootBuildNode invalid_node(nullptr, nullptr), InvalidOperationException);
  AnyValueRootBuildNode node(&anytype_registry, nullptr);
  EXPECT_THROW(node.PopArrayNode(), ParseException);
  auto child = node.GetArrayNode();
  EXPECT_NE(child, nullptr);
  EXPECT_THROW(node.GetArrayNode(), ParseException);
}

TEST_F(AnyValueBuilderTest, AnyValueArrayBuildNodeMethods)
{
  AnyTypeRegistry anytype_registry;
  EXPECT_THROW(AnyValueArrayBuildNode invalid_node(nullptr, nullptr), InvalidOperationException);
  AnyValueArrayBuildNode node(&anytype_registry, nullptr);
  EXPECT_THROW(node.Null(), ParseException);
  EXPECT_THROW(node.Bool(true), ParseException);
  EXPECT_THROW(node.Int32(-1), ParseException);
  EXPECT_THROW(node.Uint32(1), ParseException);
  EXPECT_THROW(node.Int64(-1), ParseException);
  EXPECT_THROW(node.Uint64(1), ParseException);
  EXPECT_THROW(node.Double(1.0), ParseException);
  EXPECT_THROW(node.String("text"), ParseException);
  EXPECT_THROW(node.Member("membername"), ParseException);
  EXPECT_THROW(node.GetArrayNode(), ParseException);
  EXPECT_THROW(node.PopArrayNode(), ParseException);
  EXPECT_THROW(node.PopStructureNode(), ParseException);

  // First child node: encoding node
  auto child = node.GetStructureNode();
  ASSERT_NE(child, nullptr);
  EXPECT_TRUE(child->Member(serialization::ENCODING_KEY));
  EXPECT_TRUE(child->String(serialization::JSON_ENCODING_1_0));
  EXPECT_THROW(node.GetStructureNode(), ParseException);
  EXPECT_TRUE(node.PopStructureNode());
  EXPECT_THROW(node.PopStructureNode(), ParseException);

  // Second child node: type node
  child = node.GetStructureNode();
  ASSERT_NE(child, nullptr);
  EXPECT_TRUE(child->Member(serialization::DATATYPE_KEY));
  auto type_node = child->GetStructureNode();
  ASSERT_NE(type_node, nullptr);
  EXPECT_TRUE(type_node->Member(serialization::TYPE_KEY));
  EXPECT_TRUE(type_node->String(kFloat32TypeName));
  EXPECT_TRUE(child->PopStructureNode());
  EXPECT_THROW(node.GetStructureNode(), ParseException);
  EXPECT_TRUE(node.PopStructureNode());
  EXPECT_THROW(node.PopStructureNode(), ParseException);

  // Third child node: value node
  child = node.GetStructureNode();
  ASSERT_NE(child, nullptr);
  EXPECT_TRUE(child->Member(serialization::INSTANCE_KEY));
  EXPECT_TRUE(child->Double(1.2e9));
  EXPECT_THROW(node.GetStructureNode(), ParseException);
  EXPECT_TRUE(node.PopStructureNode());
  EXPECT_THROW(node.PopStructureNode(), ParseException);

  // No more child nodes allowed
  EXPECT_THROW(node.GetStructureNode(), ParseException);
}

TEST_F(AnyValueBuilderTest, AnyValueEncodingElementBuildNodeMethods)
{
  AnyTypeRegistry anytype_registry;
  EXPECT_THROW(AnyValueEncodingElementBuildNode invalid_node(nullptr, nullptr),
               InvalidOperationException);
  AnyValueEncodingElementBuildNode node(&anytype_registry, nullptr);
  EXPECT_THROW(node.Null(), ParseException);
  EXPECT_THROW(node.Bool(true), ParseException);
  EXPECT_THROW(node.Int32(-1), ParseException);
  EXPECT_THROW(node.Uint32(1), ParseException);
  EXPECT_THROW(node.Int64(-1), ParseException);
  EXPECT_THROW(node.Uint64(1), ParseException);
  EXPECT_THROW(node.Double(1.0), ParseException);
  EXPECT_THROW(node.String("text"), ParseException);
  EXPECT_THROW(node.Member("wrong_key"), ParseException);
  EXPECT_THROW(node.GetArrayNode(), ParseException);
  EXPECT_THROW(node.PopArrayNode(), ParseException);
  EXPECT_THROW(node.GetStructureNode(), ParseException);
  EXPECT_THROW(node.PopStructureNode(), ParseException);
}

TEST_F(AnyValueBuilderTest, AnyValueTypeElementBuildNodeMethods)
{
  AnyTypeRegistry anytype_registry;
  EXPECT_THROW(AnyValueTypeElementBuildNode invalid_node(nullptr, nullptr),
               InvalidOperationException);
  AnyValueTypeElementBuildNode node(&anytype_registry, nullptr);
  EXPECT_THROW(node.Null(), ParseException);
  EXPECT_THROW(node.Bool(true), ParseException);
  EXPECT_THROW(node.Int32(-1), ParseException);
  EXPECT_THROW(node.Uint32(1), ParseException);
  EXPECT_THROW(node.Int64(-1), ParseException);
  EXPECT_THROW(node.Uint64(1), ParseException);
  EXPECT_THROW(node.Double(1.0), ParseException);
  EXPECT_THROW(node.String("text"), ParseException);
  EXPECT_THROW(node.Member("wrong_key"), ParseException);
  EXPECT_THROW(node.GetArrayNode(), ParseException);
  EXPECT_THROW(node.PopArrayNode(), ParseException);
  // Throws when the correct key was not set:
  EXPECT_THROW(node.GetStructureNode(), ParseException);
  EXPECT_THROW(node.PopStructureNode(), ParseException);
}

TEST_F(AnyValueBuilderTest, AnyValueValueElementBuildNodeMethods)
{
  AnyTypeRegistry anytype_registry;
  AnyValue empty{StringType};
  EXPECT_THROW(AnyValueValueElementBuildNode invalid_node(nullptr, nullptr, empty),
               InvalidOperationException);
  AnyValueValueElementBuildNode node(&anytype_registry, nullptr, empty);
  EXPECT_THROW(node.Null(), ParseException);
  EXPECT_THROW(node.Bool(true), ParseException);
  EXPECT_THROW(node.Int32(-1), ParseException);
  EXPECT_THROW(node.Uint32(1), ParseException);
  EXPECT_THROW(node.Int64(-1), ParseException);
  EXPECT_THROW(node.Uint64(1), ParseException);
  EXPECT_THROW(node.Double(1.0), ParseException);
  EXPECT_THROW(node.String("text"), ParseException);
  EXPECT_THROW(node.Member("wrong_key"), ParseException);
  EXPECT_THROW(node.GetArrayNode(), ParseException);
  EXPECT_THROW(node.PopArrayNode(), ParseException);
  EXPECT_THROW(node.GetStructureNode(), ParseException);
  EXPECT_THROW(node.PopStructureNode(), ParseException);

  // Correct parsing
  EXPECT_TRUE(node.Member(serialization::INSTANCE_KEY));
  EXPECT_TRUE(node.String("Text"));
}

TEST_F(AnyValueBuilderTest, ArrayValueBuildNodeMethods)
{

  // Exceptions
  AnyTypeRegistry anytype_registry;
  AnyValue empty;
  EXPECT_THROW(ArrayValueBuildNode invalid_node(nullptr, nullptr, empty),
               InvalidOperationException);
  EXPECT_THROW(ArrayValueBuildNode invalid_node_2(&anytype_registry, nullptr, empty),
               ParseException);
  AnyValue string_array(1, StringType);
  ArrayValueBuildNode node(&anytype_registry, nullptr, string_array);
  EXPECT_THROW(node.Null(), ParseException);
  EXPECT_THROW(node.Bool(true), ParseException);
  EXPECT_THROW(node.Int32(-1), ParseException);
  EXPECT_THROW(node.Uint32(1), ParseException);
  EXPECT_THROW(node.Int64(-1), ParseException);
  EXPECT_THROW(node.Uint64(1), ParseException);
  EXPECT_THROW(node.Double(1.0), ParseException);
  EXPECT_THROW(node.Member("not_supported"), ParseException);
  EXPECT_THROW(node.GetArrayNode(), ParseException);
  EXPECT_THROW(node.PopArrayNode(), ParseException);
  EXPECT_THROW(node.GetStructureNode(), ParseException);
  EXPECT_THROW(node.PopStructureNode(), ParseException);

  AnyValue int_array(2, SignedInteger16Type);
  ArrayValueBuildNode node_2(&anytype_registry, nullptr, int_array);
  EXPECT_THROW(node_2.GetArrayNode(), ParseException);
  EXPECT_THROW(node_2.String("text"), ParseException);

  // Boolean array
  {
    AnyType array_t(2, BooleanType);
    AnyValue array_v(array_t);
    ArrayValueBuildNode node(&anytype_registry, nullptr, array_v);
    EXPECT_TRUE(node.Bool(true));
    EXPECT_TRUE(node.Bool(true));
    EXPECT_THROW(node.Bool(true), ParseException);
    EXPECT_EQ(array_v[0], true);
    EXPECT_EQ(array_v[1], true);
  }

  // Signed integer array
  {
    AnyType array_t(2, SignedInteger32Type);
    AnyValue array_v(array_t);
    ArrayValueBuildNode node(&anytype_registry, nullptr, array_v);
    EXPECT_TRUE(node.Int32(-6));
    EXPECT_TRUE(node.Int64(1245));
    EXPECT_THROW(node.Int32(1), ParseException);
    EXPECT_EQ(array_v[0], -6);
    EXPECT_EQ(array_v[1], 1245);
  }

  // Unsigned integer array
  {
    AnyType array_t(2, UnsignedInteger8Type);
    AnyValue array_v(array_t);
    ArrayValueBuildNode node(&anytype_registry, nullptr, array_v);
    EXPECT_TRUE(node.Uint32(6));
    EXPECT_TRUE(node.Uint64(12));
    EXPECT_THROW(node.Uint32(1), ParseException);
    EXPECT_EQ(array_v[0], 6);
    EXPECT_EQ(array_v[1], 12);
  }

  // Double array
  {
    AnyType array_t(2, Float32Type);
    AnyValue array_v(array_t);
    ArrayValueBuildNode node(&anytype_registry, nullptr, array_v);
    EXPECT_TRUE(node.Double(1.0));
    EXPECT_TRUE(node.Double(2.0));
    EXPECT_THROW(node.Double(3.0), ParseException);
    EXPECT_EQ(array_v[0], 1.0);
    EXPECT_EQ(array_v[1], 2.0);
  }

  // String array
  {
    AnyType array_t(2, StringType);
    AnyValue array_v(array_t);
    ArrayValueBuildNode node(&anytype_registry, nullptr, array_v);
    EXPECT_TRUE(node.String("a"));
    EXPECT_TRUE(node.String("bc"));
    EXPECT_THROW(node.String("index error"), ParseException);
    EXPECT_EQ(array_v[0], "a");
    EXPECT_EQ(array_v[1], "bc");
  }

  // Array array
  {
    AnyType bool_array(2, BooleanType);
    AnyType array_t(1, bool_array);
    AnyValue array_v(array_t);
    ArrayValueBuildNode node(&anytype_registry, nullptr, array_v);
    auto child = node.GetArrayNode();
    ASSERT_NE(child, nullptr);
    EXPECT_TRUE(child->Bool(true));
    EXPECT_TRUE(child->Bool(true));
    EXPECT_THROW(child->Bool(true), ParseException);
    EXPECT_TRUE(node.PopArrayNode());
    EXPECT_EQ(array_v[0][0], true);
    EXPECT_EQ(array_v[0][1], true);
  }
}

AnyValueBuilderTest::AnyValueBuilderTest() = default;

AnyValueBuilderTest::~AnyValueBuilderTest() = default;
