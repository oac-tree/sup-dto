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
 * Copyright (c) : 2010-2024 ITER Organization,
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

#include <sup/dto/parse/anytype_builder.h>
#include <sup/dto/parse/anytype_buildnode.h>
#include <sup/dto/parse/anytype_root_buildnode.h>
#include <sup/dto/parse/membertype_buildnode.h>
#include <sup/dto/parse/membertype_array_buildnode.h>

#include <sup/dto/anytype.h>
#include <sup/dto/anytype_registry.h>
#include <sup/dto/anyvalue_exceptions.h>

using namespace sup::dto;

class AnyTypeBuilderTest : public ::testing::Test
{
protected:
  AnyTypeBuilderTest();
  virtual ~AnyTypeBuilderTest();
};

TEST_F(AnyTypeBuilderTest, AnyTypeBuilderMethods)
{
  AnyTypeRegistry anytype_registry;
  AnyTypeBuilder builder{&anytype_registry};

  // Most methods throw when the current node contained is still an AnyTypeRootBuildNode:
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
  EXPECT_THROW(builder.StartArray(), ParseException);
  EXPECT_THROW(builder.EndArray(1), ParseException);
  EXPECT_THROW(builder.EndObject(0), ParseException);

  // Retrieving the AnyType throws when the current node is not the root node:
  EXPECT_TRUE(builder.StartObject());
  EXPECT_THROW(builder.MoveAnyType(), ParseException);

  // Can't properly end object when type was not specified:
  EXPECT_THROW(builder.EndObject(0), ParseException);
}

TEST_F(AnyTypeBuilderTest, AnyTypeBuildNodeMethods)
{
  AnyTypeRegistry anytype_registry;
  AnyTypeBuildNode node(&anytype_registry, nullptr);
  EXPECT_THROW(node.Int32(-1), ParseException);
  EXPECT_THROW(node.Int32(1), ParseException);
  EXPECT_THROW(node.Int64(-1), ParseException);
  EXPECT_THROW(node.Int64(1), ParseException);
  EXPECT_THROW(node.Uint32(1), ParseException);
  EXPECT_THROW(node.Uint64(1), ParseException);
  EXPECT_THROW(node.String("wrong moment to pass a string"), ParseException);
}

TEST_F(AnyTypeBuilderTest, AnyTypeRootBuildNodeMethods)
{
  AnyTypeRegistry anytype_registry;
  AnyTypeRootBuildNode node(&anytype_registry, nullptr);
  EXPECT_THROW(node.PopStructureNode(), ParseException);
  auto child = node.GetStructureNode();
  EXPECT_NE(child, nullptr);
  EXPECT_THROW(node.GetStructureNode(), ParseException);
}

TEST_F(AnyTypeBuilderTest, MemberTypeBuildNodeMethods)
{
  AnyTypeRegistry anytype_registry;
  MemberTypeBuildNode node(&anytype_registry, nullptr);
  EXPECT_TRUE(node.Member("membername"));
  EXPECT_THROW(node.Member("othermembername"), ParseException);
  EXPECT_THROW(node.GetArrayNode(), ParseException);
  EXPECT_THROW(node.PopArrayNode(), ParseException);
  EXPECT_THROW(node.PopStructureNode(), ParseException);
  auto child = node.GetStructureNode();
  EXPECT_NE(child, nullptr);
  EXPECT_THROW(node.GetStructureNode(), ParseException);
  // still throws because it can't move the underlying type (not enough information)
  EXPECT_THROW(node.PopStructureNode(), ParseException);
}

TEST_F(AnyTypeBuilderTest, MemberTypeArrayBuildNodeMethods)
{
  AnyTypeRegistry anytype_registry;
  MemberTypeArrayBuildNode node(&anytype_registry, nullptr);
  EXPECT_THROW(node.Member("membername"), ParseException);
  EXPECT_THROW(node.GetArrayNode(), ParseException);
  EXPECT_THROW(node.PopArrayNode(), ParseException);
  EXPECT_THROW(node.PopStructureNode(), ParseException);
  auto child = node.GetStructureNode();
  EXPECT_NE(child, nullptr);
  EXPECT_THROW(node.GetStructureNode(), ParseException);
  // still throws because it can't move the uninitialized type
  EXPECT_THROW(node.PopStructureNode(), ParseException);
}

AnyTypeBuilderTest::AnyTypeBuilderTest() = default;

AnyTypeBuilderTest::~AnyTypeBuilderTest() = default;

static std::string ScalarTypeRepresentation(const std::string& scalar_type_name)
{
  std::string result = R"RAW({"type":")RAW" + scalar_type_name + R"RAW("})RAW";
  return result;
}
