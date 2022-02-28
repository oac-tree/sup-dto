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

#include "AnyTypeHelper.h"
#include "AnyType.h"

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

class AnyTypeJSONSerializeTest : public ::testing::Test
{
protected:
  AnyTypeJSONSerializeTest();
  virtual ~AnyTypeJSONSerializeTest();
};

TEST_F(AnyTypeJSONSerializeTest, EmptyType)
{
  AnyType empty = EmptyType;
  auto json_string = ToJSONString(empty);
  EXPECT_EQ(json_string, ScalarTypeRepresentation(EMPTY_TYPE_NAME));
}

TEST_F(AnyTypeJSONSerializeTest, BooleanType)
{
  AnyType bool_type = Boolean;
  auto json_string = ToJSONString(bool_type);
  EXPECT_EQ(json_string, ScalarTypeRepresentation(BOOLEAN_TYPE_NAME));
}

TEST_F(AnyTypeJSONSerializeTest, SimpleStructType)
{
  AnyType simple_struct_type({
    {"id", String},
    {"number", SignedInteger32},
    {"weight", Float64}
  });
  auto json_string = ToJSONString(simple_struct_type);
  EXPECT_EQ(json_string, json_simple_struct);
}

TEST_F(AnyTypeJSONSerializeTest, SimpleArrayType)
{
  AnyType simple_array_type(5, Character8);
  auto json_string = ToJSONString(simple_array_type);
  EXPECT_EQ(json_string, json_simple_array);
}

TEST_F(AnyTypeJSONSerializeTest, ComplexStructType)
{
  AnyType simple_struct_type({
    {"id", String},
    {"number", UnsignedInteger64}
  });
  AnyType array_of_struct_type(4, simple_struct_type);
  AnyType complex_struct_type({
    {"array", array_of_struct_type},
    {"nested", simple_struct_type},
    {"validated", Boolean}
  });
  auto json_string = ToJSONString(complex_struct_type);
  EXPECT_EQ(json_string, json_complex_type);
}

TEST_F(AnyTypeJSONSerializeTest, PrettyPrinting)
{
  AnyType simple_struct_type({
    {"id", String},
    {"number", UnsignedInteger64}
  });
  AnyType array_of_struct_type(4, simple_struct_type);
  AnyType complex_struct_type({
    {"array", array_of_struct_type},
    {"nested", simple_struct_type},
    {"validated", Boolean}
  });
  auto json_string = ToPrettyJSONString(complex_struct_type);
  EXPECT_EQ(json_string, pretty_json_complex_type);
}

AnyTypeJSONSerializeTest::AnyTypeJSONSerializeTest() = default;

AnyTypeJSONSerializeTest::~AnyTypeJSONSerializeTest() = default;

static std::string ScalarTypeRepresentation(const std::string& scalar_type_name)
{
  std::string result = R"RAW({"type":")RAW" + scalar_type_name + R"RAW("})RAW";
  return result;
}
