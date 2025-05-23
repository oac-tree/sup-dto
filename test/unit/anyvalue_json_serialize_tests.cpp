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

#include <sup/dto/anyvalue_helper.h>
#include <sup/dto/anyvalue.h>

using namespace sup::dto;

static const std::string json_empty_val = "null";
static const std::string json_true_val = "true";

static const std::string json_simple_struct =
    R"RAW({"id":"my_id","number":1729,"weight":50.25})RAW";

static const std::string json_simple_struct_full =
    R"RAW([{"encoding":"sup-dto/v1.0/JSON"},{"datatype":{"type":"","attributes":[{"id":{"type":"string"}},{"number":{"type":"int32"}},{"weight":{"type":"float64"}}]}},{"instance":{"id":"my_id","number":1729,"weight":50.25}}])RAW";

static const std::string json_simple_array =
    R"RAW([0,20,40,60,80])RAW";

static const std::string json_empty_array =
    R"RAW([])RAW";

static const std::string json_simple_array_full =
    R"RAW([{"encoding":"sup-dto/v1.0/JSON"},{"datatype":{"type":"","multiplicity":5,"element":{"type":"int32"}}},{"instance":[0,20,40,60,80]}])RAW";

static const std::string json_empty_dynamic_array_full =
    R"RAW([{"encoding":"sup-dto/v1.0/JSON"},{"datatype":{"type":"","element":{"type":"uint64"}}},{"instance":[]}])RAW";

static const std::string json_complex_val =
    R"RAW({"array":[{"id":"","number":23},{"id":"second_id","number":0}],"nested":{"id":"","number":0},"validated":false})RAW";

static const std::string pretty_json_simple_struct =
R"RAW([
  {
    "encoding": "sup-dto/v1.0/JSON"
  },
  {
    "datatype": {
      "type": "",
      "attributes": [
        {
          "id": {
            "type": "string"
          }
        },
        {
          "number": {
            "type": "int32"
          }
        },
        {
          "weight": {
            "type": "float64"
          }
        }
      ]
    }
  },
  {
    "instance": {
      "id": "my_id",
      "number": 1729,
      "weight": 50.25
    }
  }
])RAW";

class AnyValueJSONSerializeTest : public ::testing::Test
{
protected:
  AnyValueJSONSerializeTest();
  virtual ~AnyValueJSONSerializeTest();
};

// TODO: all these tests are better performed in conjunction with json parsing, so as not to depend
// on the specific representation in json (e.g. 90.0 vs 9e1 or pretty printing)
TEST_F(AnyValueJSONSerializeTest, EmptyValue)
{
  AnyValue empty{};
  auto json_string = ValuesToJSONString(empty);
  EXPECT_EQ(json_string, json_empty_val);
}

TEST_F(AnyValueJSONSerializeTest, BooleanValue)
{
  AnyValue bool_val = true;
  auto json_string = ValuesToJSONString(bool_val);
  EXPECT_EQ(json_string, json_true_val);
}

TEST_F(AnyValueJSONSerializeTest, Char8Value)
{
  AnyValue char8_val = 'a';
  auto json_string = ValuesToJSONString(char8_val);
  std::string expected = "97";
  EXPECT_EQ(json_string, expected);
}

TEST_F(AnyValueJSONSerializeTest, Int8Value)
{
  AnyValue int8_val = {SignedInteger8Type, -7};
  auto json_string = ValuesToJSONString(int8_val);
  std::string expected = "-7";
  EXPECT_EQ(json_string, expected);
}

TEST_F(AnyValueJSONSerializeTest, UInt8Value)
{
  AnyValue uint8_val = {UnsignedInteger8Type, 240};
  auto json_string = ValuesToJSONString(uint8_val);
  std::string expected = "240";
  EXPECT_EQ(json_string, expected);
}

TEST_F(AnyValueJSONSerializeTest, Int16Value)
{
  AnyValue int16_val = {SignedInteger16Type, -300};
  auto json_string = ValuesToJSONString(int16_val);
  std::string expected = "-300";
  EXPECT_EQ(json_string, expected);
}

TEST_F(AnyValueJSONSerializeTest, UInt16Value)
{
  AnyValue uint16_val = {UnsignedInteger16Type, 4008};
  auto json_string = ValuesToJSONString(uint16_val);
  std::string expected = "4008";
  EXPECT_EQ(json_string, expected);
}

TEST_F(AnyValueJSONSerializeTest, Int32Value)
{
  AnyValue int32_val = {SignedInteger32Type, -300001};
  auto json_string = ValuesToJSONString(int32_val);
  std::string expected = "-300001";
  EXPECT_EQ(json_string, expected);
}

TEST_F(AnyValueJSONSerializeTest, UInt32Value)
{
  AnyValue uint32_val = {UnsignedInteger32Type, 123456};
  auto json_string = ValuesToJSONString(uint32_val);
  std::string expected = "123456";
  EXPECT_EQ(json_string, expected);
}

TEST_F(AnyValueJSONSerializeTest, Int64Value)
{
  AnyValue int64_val = {SignedInteger64Type, -5001002003004};
  auto json_string = ValuesToJSONString(int64_val);
  std::string expected = "-5001002003004";
  EXPECT_EQ(json_string, expected);
}

TEST_F(AnyValueJSONSerializeTest, UInt64Value)
{
  AnyValue uint64_val = {UnsignedInteger64Type, 2001002003004005};
  auto json_string = ValuesToJSONString(uint64_val);
  std::string expected = "2001002003004005";
  EXPECT_EQ(json_string, expected);
}

TEST_F(AnyValueJSONSerializeTest, Float32Value)
{
  AnyValue float32_val = {Float32Type, 90};
  auto json_string = ValuesToJSONString(float32_val);
  std::string expected = "90.0";
  EXPECT_EQ(json_string, expected);
}

TEST_F(AnyValueJSONSerializeTest, Float64Value)
{
  AnyValue float64_val = {Float64Type, -777.125};
  auto json_string = ValuesToJSONString(float64_val);
  std::string expected = "-777.125";
  EXPECT_EQ(json_string, expected);
}

TEST_F(AnyValueJSONSerializeTest, SimpleStructValue)
{
  AnyValue simple_struct_val({
    {"id", {StringType, "my_id"}},
    {"number", {SignedInteger32Type, 1729}},
    {"weight", {Float64Type, 50.25}}
  });
  auto json_string = ValuesToJSONString(simple_struct_val);
  EXPECT_EQ(json_string, json_simple_struct);
  auto json_full = AnyValueToJSONString(simple_struct_val);
  EXPECT_EQ(json_full, json_simple_struct_full);
}

TEST_F(AnyValueJSONSerializeTest, PrettySimpleStructValue)
{
  AnyValue simple_struct_val({
    {"id", {StringType, "my_id"}},
    {"number", {SignedInteger32Type, 1729}},
    {"weight", {Float64Type, 50.25}}
  });
  auto json_string = AnyValueToJSONString(simple_struct_val, true);
  EXPECT_EQ(json_string, pretty_json_simple_struct);
}

TEST_F(AnyValueJSONSerializeTest, SimpleArrayValue)
{
  AnyValue simple_array_val(5, SignedInteger32Type);
  for (int i=0; i<5; ++i)
  {
    simple_array_val[i] = 20*i;
  }
  auto json_string = ValuesToJSONString(simple_array_val);
  EXPECT_EQ(json_string, json_simple_array);
  auto json_full = AnyValueToJSONString(simple_array_val);
  EXPECT_EQ(json_full, json_simple_array_full);
}

TEST_F(AnyValueJSONSerializeTest, DynamicArrayValue)
{
  AnyValue dynamic_array_val(0, SignedInteger32Type);
  for (int i=0; i<5; ++i)
  {
    dynamic_array_val.AddElement(20*i);
  }
  auto json_string = ValuesToJSONString(dynamic_array_val);
  EXPECT_EQ(json_string, json_simple_array);
  auto json_full = AnyValueToJSONString(dynamic_array_val);
  EXPECT_EQ(json_full, json_simple_array_full);
}

TEST_F(AnyValueJSONSerializeTest, EmptyDynamicArrayValue)
{
  AnyValue empty_dynamic_array_val(0, UnsignedInteger64Type);
  auto json_string = ValuesToJSONString(empty_dynamic_array_val);
  EXPECT_EQ(json_string, json_empty_array);
  auto json_full = AnyValueToJSONString(empty_dynamic_array_val);
  EXPECT_EQ(json_full, json_empty_dynamic_array_full);
}

TEST_F(AnyValueJSONSerializeTest, ComplexStructValue)
{
  AnyType simple_struct_type({
    {"id", StringType},
    {"number", UnsignedInteger64Type}
  });
  AnyType array_of_struct_type(2, simple_struct_type);
  AnyType complex_struct_type({
    {"array", array_of_struct_type},
    {"nested", simple_struct_type},
    {"validated", BooleanType}
  });
  AnyValue complex_struct_val(complex_struct_type);
  complex_struct_val["array[1].id"] = "second_id";
  complex_struct_val["array[0].number"] = 23;
  complex_struct_val["validated"] = false;
  auto json_string = ValuesToJSONString(complex_struct_val);
  EXPECT_EQ(json_string, json_complex_val);
}

AnyValueJSONSerializeTest::AnyValueJSONSerializeTest() = default;

AnyValueJSONSerializeTest::~AnyValueJSONSerializeTest() = default;

