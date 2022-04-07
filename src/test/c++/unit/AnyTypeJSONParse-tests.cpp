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
#include "AnyTypeHelper.h"
#include "AnyTypeBuilder.h"
#include "AnyValueExceptions.h"

using namespace sup::dto;

static std::string ScalarTypeRepresentation(const std::string &scalar_type_name);

static const std::string json_simple_struct =
    R"RAW({"type":"","attributes":[{"id":{"type":"string"}},{"number":{"type":"int32"}},{"weight":{"type":"float64"}}]})RAW";

static const std::string json_simple_array =
    R"RAW({"type":"","multiplicity":5,"element":{"type":"char8"}})RAW";

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

class AnyTypeJSONParseTest : public ::testing::Test
{
protected:
  AnyTypeJSONParseTest();
  virtual ~AnyTypeJSONParseTest();
};

TEST_F(AnyTypeJSONParseTest, EmptyType)
{
  auto json_string = ScalarTypeRepresentation(EMPTY_TYPE_NAME);
  auto parsed_type = AnyTypeFromJSONString(json_string);
  AnyType expected = EmptyType;
  EXPECT_EQ(parsed_type, expected);
}

TEST_F(AnyTypeJSONParseTest, BooleanType)
{
  auto json_string = ScalarTypeRepresentation(BOOLEAN_TYPE_NAME);
  auto parsed_type = AnyTypeFromJSONString(json_string);
  AnyType expected = Boolean;
  EXPECT_EQ(parsed_type, expected);
}

TEST_F(AnyTypeJSONParseTest, SimpleStructType)
{
  auto parsed_type = AnyTypeFromJSONString(json_simple_struct);
  AnyType expected_type({
    {"id", String},
    {"number", SignedInteger32},
    {"weight", Float64}
  });
  EXPECT_EQ(parsed_type, expected_type);
}

TEST_F(AnyTypeJSONParseTest, SimpleArrayType)
{
  auto parsed_type = AnyTypeFromJSONString(json_simple_array);
  AnyType expected_type(5, Character8);
  EXPECT_EQ(parsed_type, expected_type);
}

TEST_F(AnyTypeJSONParseTest, ComplexStructType)
{
  auto parsed_type = AnyTypeFromJSONString(json_complex_type);
  AnyType simple_struct_type({
    {"id", String},
    {"number", UnsignedInteger64}
  });
  AnyType array_of_struct_type(4, simple_struct_type);
  AnyType expected_type({
    {"array", array_of_struct_type},
    {"nested", simple_struct_type},
    {"validated", Boolean}
  });
  EXPECT_EQ(parsed_type, expected_type);
}

TEST_F(AnyTypeJSONParseTest, PrettyPrintedType)
{
  auto parsed_type = AnyTypeFromJSONString(pretty_json_complex_type);
  AnyType simple_struct_type({
    {"id", String},
    {"number", UnsignedInteger64}
  });
  AnyType array_of_struct_type(4, simple_struct_type);
  AnyType expected_type({
    {"array", array_of_struct_type},
    {"nested", simple_struct_type},
    {"validated", Boolean}
  });
  EXPECT_EQ(parsed_type, expected_type);
}

TEST_F(AnyTypeJSONParseTest, ParseErrorsBuildNode)
{
  const std::string int_in_wrong_place = R"RAW({"type":3})RAW";
  EXPECT_THROW(AnyTypeFromJSONString(int_in_wrong_place), ParseException);
  const std::string int_negative = R"RAW({"type":"","multiplicity":-5})RAW";
  EXPECT_THROW(AnyTypeFromJSONString(int_negative), ParseException);
  const std::string string_for_non_type_field = R"RAW({"type":"","multiplicity":"5"})RAW";
  EXPECT_THROW(AnyTypeFromJSONString(string_for_non_type_field), ParseException);
  const std::string member_in_wrong_place = R"RAW({"type","multiplicity":"5"})RAW";
  EXPECT_THROW(AnyTypeFromJSONString(string_for_non_type_field), ParseException);
  const std::string structure_in_wrong_place = R"RAW({"type":{"id":5}})RAW";
  EXPECT_THROW(AnyTypeFromJSONString(structure_in_wrong_place), ParseException);
  const std::string array_in_wrong_place = R"RAW({"type":["id"]})RAW";
  EXPECT_THROW(AnyTypeFromJSONString(array_in_wrong_place), ParseException);
  const std::string unknown_scalar_type = R"RAW({"type":"unknown"})RAW";
  EXPECT_THROW(AnyTypeFromJSONString(unknown_scalar_type), ParseException);
}

TEST_F(AnyTypeJSONParseTest, AnyTypeBuilderExceptions)
{
  AnyTypeBuilder builder{};
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
}

AnyTypeJSONParseTest::AnyTypeJSONParseTest() = default;

AnyTypeJSONParseTest::~AnyTypeJSONParseTest() = default;

static std::string ScalarTypeRepresentation(const std::string& scalar_type_name)
{
  std::string result = R"RAW({"type":")RAW" + scalar_type_name + R"RAW("})RAW";
  return result;
}
