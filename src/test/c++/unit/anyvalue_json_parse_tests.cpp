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
#include <sup/dto/anyvalue_helper.h>

using namespace sup::dto;

static const std::string json_simple_struct_full =
    R"RAW([{"encoding":"sup-dto/v1.0/JSON"},{"datatype":{"type":"","attributes":[{"id":{"type":"string"}},{"number":{"type":"int32"}},{"weight":{"type":"float64"}}]}},{"instance":{"id":"my_id","number":1729,"weight":50.25}}])RAW";

static const std::string json_simple_array_full =
    R"RAW([{"encoding":"sup-dto/v1.0/JSON"},{"datatype":{"type":"","multiplicity":5,"element":{"type":"int32"}}},{"instance":[0,20,40,60,80]}])RAW";

static const std::string json_dynamic_array_full =
    R"RAW([{"encoding":"sup-dto/v1.0/JSON"},{"datatype":{"type":"","element":{"type":"uint64"}}},{"instance":[11,22,33]}])RAW";

static const std::string json_empty_array_full =
    R"RAW([{"encoding":"sup-dto/v1.0/JSON"},{"datatype":{"type":"","element":{"type":"float32"}}},{"instance":[]}])RAW";

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

static const std::string json_ntenum_full =
R"RAW([
  {
    "encoding": "sup-dto/v1.0/JSON"
  },
  {
    "datatype":
    {
      "type": "epics:nt/NTEnum:1.0",
      "attributes": [
      {
        "value":
        {
          "type": "enum_t",
          "attributes": [
          {
            "index":
            {
              "type":"int32"
            }
          },
          {
            "choices":
            {
              "type":"string[]",
              "element":
              {
                "type":"string"
              },
              "multiplicity": 0
            }
          }]
        }
      }]
    }
  },
  {
    "instance":
    {
      "value":
      {
        "index": 0,
        "choices": ["Off", "Idle", "Running", "Fault"]
      }
    }
  }
])RAW";

static const std::string json_dynamic_array_of_struct =
R"RAW([
  {
    "encoding": "sup-dto/v1.0/JSON"
  },
  {
    "datatype": {
      "type": "",
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
    "instance": [
      {
        "id": "MyId",
        "number": 14
      }
    ]
  }
])RAW";

static const std::string json_dynamic_array_of_array =
R"RAW([
  {
    "encoding": "sup-dto/v1.0/JSON"
  },
  {
    "datatype": {
      "type": "",
      "element": {
        "type": "",
        "element": {
          "type": "uint8"
        },
        "multiplicity": 4
      }
    }
  },
  {
    "instance": [
      [2, 4, 6, 8]
    ]
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
  AnyValue int8_val = {SignedInteger8Type, -7};
  auto json_string = AnyValueToJSONString(int8_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(int8_val, parsed_val);
}

TEST_F(AnyValueJSONParseTest, UInt8Value)
{
  AnyValue uint8_val = {UnsignedInteger8Type, 240};
  auto json_string = AnyValueToJSONString(uint8_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(uint8_val, parsed_val);
}

TEST_F(AnyValueJSONParseTest, Int16Value)
{
  AnyValue int16_val = {SignedInteger16Type, -300};
  auto json_string = AnyValueToJSONString(int16_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(int16_val, parsed_val);
}

TEST_F(AnyValueJSONParseTest, UInt16Value)
{
  AnyValue uint16_val = {UnsignedInteger16Type, 4008};
  auto json_string = AnyValueToJSONString(uint16_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(uint16_val, parsed_val);
}

TEST_F(AnyValueJSONParseTest, Int32Value)
{
  AnyValue int32_val = {SignedInteger32Type, -300001};
  auto json_string = AnyValueToJSONString(int32_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(int32_val, parsed_val);
}

TEST_F(AnyValueJSONParseTest, UInt32Value)
{
  AnyValue uint32_val = {UnsignedInteger32Type, 123456};
  auto json_string = AnyValueToJSONString(uint32_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(uint32_val, parsed_val);
}

TEST_F(AnyValueJSONParseTest, Int64Value)
{
  AnyValue int64_val = {SignedInteger64Type, -5001002003004};
  auto json_string = AnyValueToJSONString(int64_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(int64_val, parsed_val);
}

TEST_F(AnyValueJSONParseTest, UInt64Value)
{
  AnyValue uint64_val = {UnsignedInteger64Type, 2001002003004005};
  auto json_string = AnyValueToJSONString(uint64_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(uint64_val, parsed_val);
}

TEST_F(AnyValueJSONParseTest, Float32Value)
{
  AnyValue float32_val = {Float32Type, 90};
  auto json_string = AnyValueToJSONString(float32_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(float32_val, parsed_val);
}

TEST_F(AnyValueJSONParseTest, Float64Value)
{
  AnyValue float64_val = {Float64Type, -777.125};
  auto json_string = AnyValueToJSONString(float64_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(float64_val, parsed_val);
}

TEST_F(AnyValueJSONParseTest, SimpleStructValue)
{
  AnyValue simple_struct_val({
    {"id", {StringType, "my_id"}},
    {"number", {SignedInteger32Type, 1729}},
    {"weight", {Float64Type, 50.25}}
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
    {"id", {StringType, "my_id"}},
    {"number", {SignedInteger32Type, 1729}},
    {"weight", {Float64Type, 50.25}}
  });
  auto parsed_val = AnyValueFromJSONString(pretty_json_simple_struct);
  EXPECT_EQ(simple_struct_val, parsed_val);
}

TEST_F(AnyValueJSONParseTest, NTEnumValue)
{
  AnyType string_array_type(4, StringType, "string[]");
  AnyType enum_t_type({
    {"index", SignedInteger32Type},
    {"choices", string_array_type}
  }, "enum_t");
  AnyType ntenum_type({{"value", enum_t_type}}, "epics:nt/NTEnum:1.0");
  AnyValue ntenum_val(ntenum_type);
  ntenum_val["value.choices"] = ArrayValue({"Off", "Idle", "Running", "Fault"});
  auto parsed_val = AnyValueFromJSONString(json_ntenum_full);
  EXPECT_EQ(ntenum_val, parsed_val);
}

TEST_F(AnyValueJSONParseTest, SimpleArrayValue)
{
  AnyValue simple_array_val(5, SignedInteger32Type);
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

TEST_F(AnyValueJSONParseTest, DynamicArrayValue)
{
  AnyValue dynamic_array_val(0, UnsignedInteger64Type);
  for (int i=1; i<4; ++i)
  {
    dynamic_array_val.AddElement(11*i);
  }
  auto json_string = AnyValueToJSONString(dynamic_array_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(dynamic_array_val, parsed_val);
  auto parsed_val2 = AnyValueFromJSONString(json_dynamic_array_full);
  EXPECT_EQ(dynamic_array_val, parsed_val2);
}

TEST_F(AnyValueJSONParseTest, EmptyDynamicArrayValue)
{
  AnyValue empty_dynamic_array_val(0, Float32Type);
  auto json_string = AnyValueToJSONString(empty_dynamic_array_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(empty_dynamic_array_val, parsed_val);
  auto parsed_val2 = AnyValueFromJSONString(json_empty_array_full);
  EXPECT_EQ(empty_dynamic_array_val, parsed_val2);
}

TEST_F(AnyValueJSONParseTest, ComplexStructValue)
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
  auto json_string = AnyValueToJSONString(complex_struct_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(complex_struct_val, parsed_val);
}

TEST_F(AnyValueJSONParseTest, DynamicArrayOfStructValue)
{
  AnyValue simple_struct_val({
    {"id", {StringType, "MyId"}},
    {"number", {UnsignedInteger64Type, 14}}
  });
  AnyType array_of_struct_type(0, simple_struct_val.GetType());
  AnyValue array_of_struct_val(array_of_struct_type);
  array_of_struct_val.AddElement(simple_struct_val);
  auto json_string = AnyValueToJSONString(array_of_struct_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(array_of_struct_val, parsed_val);
  auto parsed_val_2 = AnyValueFromJSONString(json_dynamic_array_of_struct);
  EXPECT_EQ(array_of_struct_val, parsed_val_2);
}

TEST_F(AnyValueJSONParseTest, EmptyDynamicArrayOfStructValue)
{
  AnyType simple_struct_type({
    {"id", StringType},
    {"number", UnsignedInteger64Type}
  });
  AnyValue empty_array_of_struct_val(0, simple_struct_type);
  auto json_string = AnyValueToJSONString(empty_array_of_struct_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(empty_array_of_struct_val, parsed_val);
}

TEST_F(AnyValueJSONParseTest, DynamicArrayOfArrayValue)
{
  AnyValue simple_array_val = ArrayValue({
    {UnsignedInteger8Type, 2}, 4, 6, 8
  });
  AnyType array_of_array_type(0, simple_array_val.GetType());
  AnyValue array_of_array_val(array_of_array_type);
  array_of_array_val.AddElement(simple_array_val);
  auto json_string = AnyValueToJSONString(array_of_array_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(array_of_array_val, parsed_val);
  auto parsed_val_2 = AnyValueFromJSONString(json_dynamic_array_of_array);
  EXPECT_EQ(array_of_array_val, parsed_val_2);
}

TEST_F(AnyValueJSONParseTest, EmptyDynamicArrayOfArrayValue)
{
  AnyType simple_array_type(4, SignedInteger16Type);
  AnyValue empty_array_of_array_val(0, simple_array_type);
  auto json_string = AnyValueToJSONString(empty_array_of_array_val);
  auto parsed_val = AnyValueFromJSONString(json_string);
  EXPECT_EQ(empty_array_of_array_val, parsed_val);
}

TEST_F(AnyValueJSONParseTest, AnyValueBuilderMethods)
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

TEST_F(AnyValueJSONParseTest, AnyValueBuildNodeMethods)
{
  // Exceptions:
  AnyTypeRegistry anytype_registry;
  AnyValue val;
  EXPECT_THROW(AnyValueBuildNode invalid_node(nullptr, nullptr, val), InvalidOperationException);
  AnyValueBuildNode node(&anytype_registry, nullptr, val);
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

TEST_F(AnyValueJSONParseTest, AnyValueRootBuildNodeMethods)
{
  AnyTypeRegistry anytype_registry;
  EXPECT_THROW(AnyValueRootBuildNode invalid_node(nullptr, nullptr), InvalidOperationException);
  AnyValueRootBuildNode node(&anytype_registry, nullptr);
  EXPECT_THROW(node.PopArrayNode(), ParseException);
  auto child = node.GetArrayNode();
  EXPECT_NE(child, nullptr);
  EXPECT_THROW(node.GetArrayNode(), ParseException);
}

TEST_F(AnyValueJSONParseTest, AnyValueArrayBuildNodeMethods)
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

TEST_F(AnyValueJSONParseTest, AnyValueEncodingElementBuildNodeMethods)
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

TEST_F(AnyValueJSONParseTest, AnyValueTypeElementBuildNodeMethods)
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

TEST_F(AnyValueJSONParseTest, AnyValueValueElementBuildNodeMethods)
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

TEST_F(AnyValueJSONParseTest, ArrayValueBuildNodeMethods)
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

AnyValueJSONParseTest::AnyValueJSONParseTest() = default;

AnyValueJSONParseTest::~AnyValueJSONParseTest() = default;
