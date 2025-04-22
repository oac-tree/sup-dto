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
#include <sup/dto/anytype_registry.h>
#include <sup/dto/json_type_parser.h>

using namespace sup::dto;

static std::string ScalarTypeRepresentation(const std::string &scalar_type_name);

static const std::string json_simple_struct =
    R"RAW({"type":"","attributes":[{"id":{"type":"string"}},{"number":{"type":"int32"}},{"weight":{"type":"float64"}}]})RAW";

static const std::string json_simple_array =
    R"RAW({"type":"","multiplicity":5,"element":{"type":"char8"}})RAW";

static const std::string json_dynamic_array =
    R"RAW({"type":"","element":{"type":"uint64"}})RAW";

static const std::string json_complex_type =
    R"RAW({"type":"","attributes":[{"array":{"type":"","multiplicity":4,"element":{"type":"","attributes":[{"id":{"type":"string"}},{"number":{"type":"uint64"}}]}}},{"nested":{"type":"","attributes":[{"id":{"type":"string"}},{"number":{"type":"uint64"}}]}},{"validated":{"type":"bool"}}]})RAW";

static const std::string pretty_json_complex_type =
R"RAW({
  "type": "",
  "attributes": [
    {
      "array": {
        "type": "",
        "multiplicity": 4,
        "element": {
          "type": "",
          "attributes": [
            {
              "id": {
                "type": "string"
              }
            },
            {
              "number": {
                "type": "uint64"
              }
            }
          ]
        }
      }
    },
    {
      "nested": {
        "type": "",
        "attributes": [
          {
            "id": {
              "type": "string"
            }
          },
          {
            "number": {
              "type": "uint64"
            }
          }
        ]
      }
    },
    {
      "validated": {
        "type": "bool"
      }
    }
  ]
})RAW";

static const std::string json_alias_type = R"RAW({"type":"double"})RAW";

static const std::string json_registered_subtypes =
    R"RAW({"type":"","attributes":[{"value":{"type":"double"}},{"point":{"type":"point_t"}}]})RAW";

class JSONTypeParserTest : public ::testing::Test
{
protected:
  JSONTypeParserTest();
  virtual ~JSONTypeParserTest();

  JSONAnyTypeParser m_parser;
};

TEST_F(JSONTypeParserTest, EmptyType)
{
  auto json_string = ScalarTypeRepresentation(kEmptyTypeName);
  EXPECT_TRUE(m_parser.ParseString(json_string));
  auto parsed_type = m_parser.MoveAnyType();
  AnyType expected = EmptyType;
  EXPECT_EQ(parsed_type, expected);
}

TEST_F(JSONTypeParserTest, BooleanType)
{
  auto json_string = ScalarTypeRepresentation(kBooleanTypeName);
  EXPECT_TRUE(m_parser.ParseString(json_string));
  auto parsed_type = m_parser.MoveAnyType();
  AnyType expected = BooleanType;
  EXPECT_EQ(parsed_type, expected);
}

TEST_F(JSONTypeParserTest, SimpleStructType)
{
  EXPECT_TRUE(m_parser.ParseString(json_simple_struct));
  auto parsed_type = m_parser.MoveAnyType();
  AnyType expected_type({
    {"id", StringType},
    {"number", SignedInteger32Type},
    {"weight", Float64Type}
  });
  EXPECT_EQ(parsed_type, expected_type);
}

TEST_F(JSONTypeParserTest, SimpleArrayType)
{
  EXPECT_TRUE(m_parser.ParseString(json_simple_array));
  auto parsed_type = m_parser.MoveAnyType();
  AnyType expected_type(5, Character8Type);
  EXPECT_EQ(parsed_type, expected_type);
}

TEST_F(JSONTypeParserTest, DynamicArrayType)
{
  EXPECT_TRUE(m_parser.ParseString(json_dynamic_array));
  auto parsed_type = m_parser.MoveAnyType();
  AnyType expected_type(0, UnsignedInteger64Type);
  EXPECT_EQ(parsed_type, expected_type);
}

TEST_F(JSONTypeParserTest, ComplexStructType)
{
  EXPECT_TRUE(m_parser.ParseString(json_complex_type));
  auto parsed_type = m_parser.MoveAnyType();
  AnyType simple_struct_type({
    {"id", StringType},
    {"number", UnsignedInteger64Type}
  });
  AnyType array_of_struct_type(4, simple_struct_type);
  AnyType expected_type({
    {"array", array_of_struct_type},
    {"nested", simple_struct_type},
    {"validated", BooleanType}
  });
  EXPECT_EQ(parsed_type, expected_type);
}

TEST_F(JSONTypeParserTest, PrettyPrintedType)
{
  EXPECT_TRUE(m_parser.ParseString(pretty_json_complex_type));
  auto parsed_type = m_parser.MoveAnyType();
  AnyType simple_struct_type({
    {"id", StringType},
    {"number", UnsignedInteger64Type}
  });
  AnyType array_of_struct_type(4, simple_struct_type);
  AnyType expected_type({
    {"array", array_of_struct_type},
    {"nested", simple_struct_type},
    {"validated", BooleanType}
  });
  EXPECT_EQ(parsed_type, expected_type);
}

TEST_F(JSONTypeParserTest, ParseErrorsBuildNode)
{
  const std::string int_in_wrong_place = R"RAW({"type":3})RAW";
  EXPECT_FALSE(m_parser.ParseString(int_in_wrong_place));
  const std::string int_negative = R"RAW({"type":"","multiplicity":-5})RAW";
  EXPECT_FALSE(m_parser.ParseString(int_negative));
  const std::string string_for_non_type_field = R"RAW({"type":"","multiplicity":"5"})RAW";
  EXPECT_FALSE(m_parser.ParseString(string_for_non_type_field));
  const std::string member_in_wrong_place = R"RAW({"type","multiplicity":"5"})RAW";
  EXPECT_FALSE(m_parser.ParseString(member_in_wrong_place));
  const std::string structure_in_wrong_place = R"RAW({"type":{"id":5}})RAW";
  EXPECT_FALSE(m_parser.ParseString(structure_in_wrong_place));
  const std::string array_in_wrong_place = R"RAW({"type":["id"]})RAW";
  EXPECT_FALSE(m_parser.ParseString(array_in_wrong_place));
  const std::string unknown_scalar_type = R"RAW({"type":"unknown"})RAW";
  EXPECT_FALSE(m_parser.ParseString(unknown_scalar_type));
}

TEST_F(JSONTypeParserTest, ParseFromRegistry)
{
  AnyTypeRegistry anytype_registry;
  // Alias for Float64
  anytype_registry.RegisterType("double", Float64Type);
  // Define type for 3d point
  std::string point_typename("point_t");
  AnyType point_t{{
    {"x", Float32Type},
    {"y", Float32Type},
    {"z", Float32Type}
  }, point_typename};
  anytype_registry.RegisterType(point_t);
  // Define struct with point
  AnyType my_struct_t{{
    {"value", Float64Type},
    {"point", point_t}
  }};
  EXPECT_TRUE(m_parser.ParseString(json_alias_type, &anytype_registry));
  auto alias_type = m_parser.MoveAnyType();
  EXPECT_EQ(alias_type, Float64Type);
  EXPECT_TRUE(m_parser.ParseString(json_registered_subtypes, &anytype_registry));
  auto registered_subtypes = m_parser.MoveAnyType();
  EXPECT_EQ(registered_subtypes, my_struct_t);

  // Test failure of parsing with default registry
  AnyTypeRegistry default_registry;
  EXPECT_FALSE(m_parser.ParseString(json_alias_type, &default_registry));
  EXPECT_FALSE(m_parser.ParseString(json_registered_subtypes, &default_registry));
}

TEST_F(JSONTypeParserTest, ParseDuplicateTypename)
{
  {
    // Use typename from EmptyType
    AnyType anytype{{
      {"x", Float32Type},
      {"y", Float32Type},
      {"z", Float32Type}
    }, kEmptyTypeName};
    auto json_str = AnyTypeToJSONString(anytype);
    ASSERT_FALSE(json_str.empty());
    ASSERT_TRUE(m_parser.ParseString(json_str));
    auto readback = m_parser.MoveAnyType();
    EXPECT_EQ(anytype, readback);
  }
  {
    // Use typename from BooleanType
    AnyType anytype{{
      {"x", Float32Type},
      {"y", Float32Type},
      {"z", Float32Type}
    }, kBooleanTypeName};
    auto json_str = AnyTypeToJSONString(anytype);
    ASSERT_FALSE(json_str.empty());
    ASSERT_TRUE(m_parser.ParseString(json_str));
    auto readback = m_parser.MoveAnyType();
    EXPECT_EQ(anytype, readback);
  }
}

TEST_F(JSONTypeParserTest, EmptyMember)
{
  {
    // Use typename from EmptyType
    AnyType anytype{{
      {"a", EmptyType}
    }};
    const auto json_str = AnyTypeToJSONString(anytype);
    ASSERT_FALSE(json_str.empty());
    ASSERT_TRUE(m_parser.ParseString(json_str));
    auto readback = m_parser.MoveAnyType();
    EXPECT_EQ(anytype, readback);
  }
  {
    // Adding empty member
    AnyType anytype = EmptyStructType();
    anytype.AddMember("a", {});
    const auto json_str = AnyTypeToJSONString(anytype);
    ASSERT_FALSE(json_str.empty());
    ASSERT_TRUE(m_parser.ParseString(json_str));
    auto readback = m_parser.MoveAnyType();
    EXPECT_EQ(anytype, readback);
  }
}

TEST_F(JSONTypeParserTest, PermissiveParsing)
{
  // TODO: some of these permissive parsing cases should not be allowed, while others seem
  // natural.
  {
    // Scalar with multiplicity in JSON
    const std::string json_str =
    R"RAW({"type":"uint32","multiplicity":3})RAW";
    AnyType expected_type{UnsignedInteger32Type};
    ASSERT_TRUE(m_parser.ParseString(json_str));
    auto readback = m_parser.MoveAnyType();
    EXPECT_EQ(readback, expected_type);
  }
  {
    // Structure without type in JSON
    const std::string json_str =
    R"RAW({"attributes":[{"id":{"type":"string"}},{"number":{"type":"int32"}}]})RAW";
    AnyType expected_type{{
      {"id", StringType},
      {"number", SignedInteger32Type}
    }};
    ASSERT_TRUE(m_parser.ParseString(json_str));
    auto readback = m_parser.MoveAnyType();
    EXPECT_EQ(readback, expected_type);
  }
  {
    // Structure with multiplicity in JSON
    const std::string json_str =
    R"RAW({"type":"","multiplicity":3,"attributes":[{"id":{"type":"string"}},{"number":{"type":"int32"}}]})RAW";
    AnyType expected_type{{
      {"id", StringType},
      {"number", SignedInteger32Type}
    }};
    ASSERT_TRUE(m_parser.ParseString(json_str));
    auto readback = m_parser.MoveAnyType();
    EXPECT_EQ(readback, expected_type);
  }
  {
    // Array without type in JSON
    const std::string json_str =
    R"RAW({"multiplicity":5,"element":{"type":"char8"}})RAW";
    AnyType expected_type{5, Character8Type};
    ASSERT_TRUE(m_parser.ParseString(json_str));
    auto readback = m_parser.MoveAnyType();
    EXPECT_EQ(readback, expected_type);
  }
  {
    // Array with multiplicity after element in JSON
    const std::string json_str =
    R"RAW({"type":"","element":{"type":"char8"},"multiplicity":5})RAW";
    AnyType expected_type{5, Character8Type};
    ASSERT_TRUE(m_parser.ParseString(json_str));
    auto readback = m_parser.MoveAnyType();
    EXPECT_EQ(readback, expected_type);
  }
  {
    // Array without multiplicity in JSON
    const std::string json_str =
    R"RAW({"type":"","element":{"type":"char8"}})RAW";
    AnyType expected_type{0, Character8Type};
    ASSERT_TRUE(m_parser.ParseString(json_str));
    auto readback = m_parser.MoveAnyType();
    EXPECT_EQ(readback, expected_type);
  }
}

JSONTypeParserTest::JSONTypeParserTest() = default;

JSONTypeParserTest::~JSONTypeParserTest() = default;

static std::string ScalarTypeRepresentation(const std::string& scalar_type_name)
{
  std::string result = R"RAW({"type":")RAW" + scalar_type_name + R"RAW("})RAW";
  return result;
}
