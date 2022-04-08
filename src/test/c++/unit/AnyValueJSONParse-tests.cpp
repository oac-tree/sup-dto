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

#include "AnyValueHelper.h"
#include "AnyValue.h"
#include "AnyValueBuilder.h"
#include "AnyValueBuildNode.h"
#include "AnyValueRootBuildNode.h"
#include "AnyValueArrayBuildNode.h"
#include "SerializationConstants.h"

using namespace sup::dto;

static const std::string json_simple_struct_full =
    R"RAW([{"encoding":"sup-dto/v1.0/JSON"},{"datatype":{"type":"","attributes":[{"id":{"type":"string"}},{"number":{"type":"int32"}},{"weight":{"type":"float64"}}]}},{"instance":{"id":"my_id","number":1729,"weight":50.25}}])RAW";

static const std::string json_simple_array_full =
    R"RAW([{"encoding":"sup-dto/v1.0/JSON"},{"datatype":{"type":"","multiplicity":5,"element":{"type":"int32"}}},{"instance":[0,20,40,60,80]}])RAW";

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

class AnyValueJSONParseTest : public ::testing::Test
{
protected:
  AnyValueJSONParseTest();
  virtual ~AnyValueJSONParseTest();
};

TEST_F(AnyValueJSONParseTest, EmptyValue)
{
  AnyValue empty{};
  auto json_string = AnyValueToJSONString(empty);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(empty, parsed_val);
}

TEST_F(AnyValueJSONParseTest, BooleanValue)
{
  AnyValue bool_val = true;
  auto json_string = AnyValueToJSONString(bool_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(bool_val, parsed_val);
}

TEST_F(AnyValueJSONParseTest, Char8Value)
{
  AnyValue char8_val = 'a';
  auto json_string = AnyValueToJSONString(char8_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(char8_val, parsed_val);
}

TEST_F(AnyValueJSONParseTest, Int8Value)
{
  AnyValue int8_val = {SignedInteger8, -7};
  auto json_string = AnyValueToJSONString(int8_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(int8_val, parsed_val);
}

TEST_F(AnyValueJSONParseTest, UInt8Value)
{
  AnyValue uint8_val = {UnsignedInteger8, 240};
  auto json_string = AnyValueToJSONString(uint8_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(uint8_val, parsed_val);
}

TEST_F(AnyValueJSONParseTest, Int16Value)
{
  AnyValue int16_val = {SignedInteger16, -300};
  auto json_string = AnyValueToJSONString(int16_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(int16_val, parsed_val);
}

TEST_F(AnyValueJSONParseTest, UInt16Value)
{
  AnyValue uint16_val = {UnsignedInteger16, 4008};
  auto json_string = AnyValueToJSONString(uint16_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(uint16_val, parsed_val);
}

TEST_F(AnyValueJSONParseTest, Int32Value)
{
  AnyValue int32_val = {SignedInteger32, -300001};
  auto json_string = AnyValueToJSONString(int32_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(int32_val, parsed_val);
}

TEST_F(AnyValueJSONParseTest, UInt32Value)
{
  AnyValue uint32_val = {UnsignedInteger32, 123456};
  auto json_string = AnyValueToJSONString(uint32_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(uint32_val, parsed_val);
}

TEST_F(AnyValueJSONParseTest, Int64Value)
{
  AnyValue int64_val = {SignedInteger64, -5001002003004};
  auto json_string = AnyValueToJSONString(int64_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(int64_val, parsed_val);
}

TEST_F(AnyValueJSONParseTest, UInt64Value)
{
  AnyValue uint64_val = {UnsignedInteger64, 2001002003004005};
  auto json_string = AnyValueToJSONString(uint64_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(uint64_val, parsed_val);
}

TEST_F(AnyValueJSONParseTest, Float32Value)
{
  AnyValue float32_val = {Float32, 90};
  auto json_string = AnyValueToJSONString(float32_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(float32_val, parsed_val);
}

TEST_F(AnyValueJSONParseTest, Float64Value)
{
  AnyValue float64_val = {Float64, -777.125};
  auto json_string = AnyValueToJSONString(float64_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(float64_val, parsed_val);
}

TEST_F(AnyValueJSONParseTest, SimpleStructValue)
{
  AnyValue simple_struct_val({
    {"id", {String, "my_id"}},
    {"number", {SignedInteger32, 1729}},
    {"weight", {Float64, 50.25}}
  });
  auto json_string = AnyValueToJSONString(simple_struct_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(simple_struct_val, parsed_val);
  auto parsed_val2 = AnyValueFromJSONString(json_simple_struct_full);
  EXPECT_EQ(simple_struct_val, parsed_val2);
}

TEST_F(AnyValueJSONParseTest, PrettySimpleStructValue)
{
  AnyValue simple_struct_val({
    {"id", {String, "my_id"}},
    {"number", {SignedInteger32, 1729}},
    {"weight", {Float64, 50.25}}
  });
  auto parsed_val = AnyValueFromJSONString(pretty_json_simple_struct);
  EXPECT_EQ(simple_struct_val, parsed_val);
}

TEST_F(AnyValueJSONParseTest, SimpleArrayValue)
{
  AnyValue simple_array_val(5, SignedInteger32);
  for (int i=0; i<5; ++i)
  {
    simple_array_val[i] = 20*i;
  }
  auto json_string = AnyValueToJSONString(simple_array_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(simple_array_val, parsed_val);
  auto parsed_val2 = AnyValueFromJSONString(json_simple_array_full);
  EXPECT_EQ(simple_array_val, parsed_val2);
}

TEST_F(AnyValueJSONParseTest, ComplexStructValue)
{
  AnyType simple_struct_type({
    {"id", String},
    {"number", UnsignedInteger64}
  });
  AnyType array_of_struct_type(2, simple_struct_type);
  AnyType complex_struct_type({
    {"array", array_of_struct_type},
    {"nested", simple_struct_type},
    {"validated", Boolean}
  });
  AnyValue complex_struct_val(complex_struct_type);
  complex_struct_val["array[1].id"] = "second_id";
  complex_struct_val["array[0].number"] = 23;
  complex_struct_val["validated"] = false;
  auto json_string = AnyValueToJSONString(complex_struct_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(complex_struct_val, parsed_val);
}

TEST_F(AnyValueJSONParseTest, AnyValueBuilderMethods)
{
  AnyValueBuilder builder{};

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

TEST_F(AnyValueJSONParseTest, AnyValueBuildNodeMethods)
{
  // Exceptions:
  AnyValue val;
  AnyValueBuildNode node(nullptr, val);
  EXPECT_THROW(node.Bool(-1), ParseException);
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
  AnyValueBuildNode struct_node(nullptr, struct_val);
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

TEST_F(AnyValueJSONParseTest, AnyValueRootBuildNodeMethods)
{
  AnyValueRootBuildNode node(nullptr);
  EXPECT_THROW(node.PopArrayNode(), ParseException);
  auto child = node.GetArrayNode();
  EXPECT_NE(child, nullptr);
  EXPECT_THROW(node.GetArrayNode(), ParseException);
}

TEST_F(AnyValueJSONParseTest, AnyValueArrayBuildNodeMethods)
{
  AnyValueArrayBuildNode node(nullptr);
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
  EXPECT_TRUE(type_node->String(FLOAT32_TYPE_NAME));
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

AnyValueJSONParseTest::AnyValueJSONParseTest() = default;

AnyValueJSONParseTest::~AnyValueJSONParseTest() = default;
