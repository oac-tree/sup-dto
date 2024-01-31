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

#include <gtest/gtest.h>

#include <sup/dto/anyvalue.h>
#include <sup/dto/anyvalue_helper.h>
#include <sup/dto/json_value_parser.h>

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

class JSONValueParserTest : public ::testing::Test
{
protected:
  JSONValueParserTest();
  virtual ~JSONValueParserTest();

  JSONAnyValueParser m_parser;
};

TEST_F(JSONValueParserTest, EmptyValue)
{
  AnyValue empty{};
  auto json_string = AnyValueToJSONString(empty);
  EXPECT_TRUE(m_parser.ParseString(json_string));
  auto parsed_val = m_parser.MoveAnyValue();
  EXPECT_EQ(empty, parsed_val);

  auto json_value_string = ValuesToJSONString(empty);
  EXPECT_TRUE(m_parser.TypedParseString(EmptyType, json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(empty, parsed_from_type);
}

TEST_F(JSONValueParserTest, BooleanValue)
{
  AnyValue bool_val = true;
  auto json_string = AnyValueToJSONString(bool_val);
  EXPECT_TRUE(m_parser.ParseString(json_string));
  auto parsed_val = m_parser.MoveAnyValue();
  EXPECT_EQ(bool_val, parsed_val);

  auto json_value_string = ValuesToJSONString(bool_val);
  EXPECT_TRUE(m_parser.TypedParseString(BooleanType, json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(bool_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, Char8Value)
{
  AnyValue char8_val = 'a';
  auto json_string = AnyValueToJSONString(char8_val);
  EXPECT_TRUE(m_parser.ParseString(json_string));
  auto parsed_val = m_parser.MoveAnyValue();
  EXPECT_EQ(char8_val, parsed_val);

  auto json_value_string = ValuesToJSONString(char8_val);
  EXPECT_TRUE(m_parser.TypedParseString(Character8Type, json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(char8_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, Int8Value)
{
  AnyValue int8_val = {SignedInteger8Type, -7};
  auto json_string = AnyValueToJSONString(int8_val);
  EXPECT_TRUE(m_parser.ParseString(json_string));
  auto parsed_val = m_parser.MoveAnyValue();
  EXPECT_EQ(int8_val, parsed_val);

  auto json_value_string = ValuesToJSONString(int8_val);
  EXPECT_TRUE(m_parser.TypedParseString(SignedInteger8Type, json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(int8_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, UInt8Value)
{
  AnyValue uint8_val = {UnsignedInteger8Type, 240};
  auto json_string = AnyValueToJSONString(uint8_val);
  EXPECT_TRUE(m_parser.ParseString(json_string));
  auto parsed_val = m_parser.MoveAnyValue();
  EXPECT_EQ(uint8_val, parsed_val);

  auto json_value_string = ValuesToJSONString(uint8_val);
  EXPECT_TRUE(m_parser.TypedParseString(UnsignedInteger8Type, json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(uint8_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, Int16Value)
{
  AnyValue int16_val = {SignedInteger16Type, -300};
  auto json_string = AnyValueToJSONString(int16_val);
  EXPECT_TRUE(m_parser.ParseString(json_string));
  auto parsed_val = m_parser.MoveAnyValue();
  EXPECT_EQ(int16_val, parsed_val);

  auto json_value_string = ValuesToJSONString(int16_val);
  EXPECT_TRUE(m_parser.TypedParseString(SignedInteger16Type, json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(int16_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, UInt16Value)
{
  AnyValue uint16_val = {UnsignedInteger16Type, 4008};
  auto json_string = AnyValueToJSONString(uint16_val);
  EXPECT_TRUE(m_parser.ParseString(json_string));
  auto parsed_val = m_parser.MoveAnyValue();
  EXPECT_EQ(uint16_val, parsed_val);

  auto json_value_string = ValuesToJSONString(uint16_val);
  EXPECT_TRUE(m_parser.TypedParseString(UnsignedInteger16Type, json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(uint16_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, Int32Value)
{
  AnyValue int32_val = {SignedInteger32Type, -300001};
  auto json_string = AnyValueToJSONString(int32_val);
  EXPECT_TRUE(m_parser.ParseString(json_string));
  auto parsed_val = m_parser.MoveAnyValue();
  EXPECT_EQ(int32_val, parsed_val);

  auto json_value_string = ValuesToJSONString(int32_val);
  EXPECT_TRUE(m_parser.TypedParseString(SignedInteger32Type, json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(int32_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, UInt32Value)
{
  AnyValue uint32_val = {UnsignedInteger32Type, 123456};
  auto json_string = AnyValueToJSONString(uint32_val);
  EXPECT_TRUE(m_parser.ParseString(json_string));
  auto parsed_val = m_parser.MoveAnyValue();
  EXPECT_EQ(uint32_val, parsed_val);

  auto json_value_string = ValuesToJSONString(uint32_val);
  EXPECT_TRUE(m_parser.TypedParseString(UnsignedInteger32Type, json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(uint32_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, Int64Value)
{
  AnyValue int64_val = {SignedInteger64Type, -5001002003004};
  auto json_string = AnyValueToJSONString(int64_val);
  EXPECT_TRUE(m_parser.ParseString(json_string));
  auto parsed_val = m_parser.MoveAnyValue();
  EXPECT_EQ(int64_val, parsed_val);

  auto json_value_string = ValuesToJSONString(int64_val);
  EXPECT_TRUE(m_parser.TypedParseString(SignedInteger64Type, json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(int64_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, UInt64Value)
{
  AnyValue uint64_val = {UnsignedInteger64Type, 2001002003004005};
  auto json_string = AnyValueToJSONString(uint64_val);
  EXPECT_TRUE(m_parser.ParseString(json_string));
  auto parsed_val = m_parser.MoveAnyValue();
  EXPECT_EQ(uint64_val, parsed_val);

  auto json_value_string = ValuesToJSONString(uint64_val);
  EXPECT_TRUE(m_parser.TypedParseString(UnsignedInteger64Type, json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(uint64_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, Float32Value)
{
  AnyValue float32_val = {Float32Type, 90};
  auto json_string = AnyValueToJSONString(float32_val);
  EXPECT_TRUE(m_parser.ParseString(json_string));
  auto parsed_val = m_parser.MoveAnyValue();
  EXPECT_EQ(float32_val, parsed_val);

  auto json_value_string = ValuesToJSONString(float32_val);
  EXPECT_TRUE(m_parser.TypedParseString(Float32Type, json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(float32_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, Float64Value)
{
  AnyValue float64_val = {Float64Type, -777.125};
  auto json_string = AnyValueToJSONString(float64_val);
  EXPECT_TRUE(m_parser.ParseString(json_string));
  auto parsed_val = m_parser.MoveAnyValue();
  EXPECT_EQ(float64_val, parsed_val);

  auto json_value_string = ValuesToJSONString(float64_val);
  EXPECT_TRUE(m_parser.TypedParseString(Float64Type, json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(float64_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, SimpleStructValue)
{
  AnyValue simple_struct_val({
    {"id", {StringType, "my_id"}},
    {"number", {SignedInteger32Type, 1729}},
    {"weight", {Float64Type, 50.25}}
  });
  auto json_string = AnyValueToJSONString(simple_struct_val);
  EXPECT_TRUE(m_parser.ParseString(json_string));
  auto parsed_val = m_parser.MoveAnyValue();
  EXPECT_EQ(simple_struct_val, parsed_val);
  EXPECT_TRUE(m_parser.ParseString(json_simple_struct_full));
  auto parsed_val2 = m_parser.MoveAnyValue();
  EXPECT_EQ(simple_struct_val, parsed_val2);

  auto json_value_string = ValuesToJSONString(simple_struct_val);
  EXPECT_TRUE(m_parser.TypedParseString(simple_struct_val.GetType(), json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(simple_struct_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, PrettySimpleStructValue)
{
  AnyValue simple_struct_val({
    {"id", {StringType, "my_id"}},
    {"number", {SignedInteger32Type, 1729}},
    {"weight", {Float64Type, 50.25}}
  });
  EXPECT_TRUE(m_parser.ParseString(pretty_json_simple_struct));
  auto parsed_val = m_parser.MoveAnyValue();
  EXPECT_EQ(simple_struct_val, parsed_val);

  auto json_value_string = ValuesToJSONString(simple_struct_val, true);
  EXPECT_TRUE(m_parser.TypedParseString(simple_struct_val.GetType(), json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(simple_struct_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, NTEnumValue)
{
  AnyType string_array_type(4, StringType, "string[]");
  AnyType enum_t_type({
    {"index", SignedInteger32Type},
    {"choices", string_array_type}
  }, "enum_t");
  AnyType ntenum_type({{"value", enum_t_type}}, "epics:nt/NTEnum:1.0");
  AnyValue ntenum_val(ntenum_type);
  ntenum_val["value.choices"] = ArrayValue({"Off", "Idle", "Running", "Fault"}, "string[]");
  EXPECT_TRUE(m_parser.ParseString(json_ntenum_full));
  auto parsed_val = m_parser.MoveAnyValue();
  EXPECT_EQ(ntenum_val, parsed_val);

  auto json_value_string = ValuesToJSONString(ntenum_val);
  EXPECT_TRUE(m_parser.TypedParseString(ntenum_type, json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(ntenum_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, SimpleArrayValue)
{
  AnyValue simple_array_val(5, SignedInteger32Type);
  for (int i=0; i<5; ++i)
  {
    simple_array_val[i] = 20*i;
  }
  auto json_string = AnyValueToJSONString(simple_array_val);
  EXPECT_TRUE(m_parser.ParseString(json_string));
  auto parsed_val = m_parser.MoveAnyValue();
  EXPECT_EQ(simple_array_val, parsed_val);
  EXPECT_TRUE(m_parser.ParseString(json_simple_array_full));
  auto parsed_val2 = m_parser.MoveAnyValue();
  EXPECT_EQ(simple_array_val, parsed_val2);

  auto json_value_string = ValuesToJSONString(simple_array_val);
  EXPECT_TRUE(m_parser.TypedParseString(simple_array_val.GetType(), json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(simple_array_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, DynamicArrayValue)
{
  AnyValue dynamic_array_val(0, UnsignedInteger64Type);
  for (int i=1; i<4; ++i)
  {
    dynamic_array_val.AddElement(11*i);
  }
  auto json_string = AnyValueToJSONString(dynamic_array_val);
  EXPECT_TRUE(m_parser.ParseString(json_string));
  auto parsed_val = m_parser.MoveAnyValue();
  EXPECT_EQ(dynamic_array_val, parsed_val);
  EXPECT_TRUE(m_parser.ParseString(json_dynamic_array_full));
  auto parsed_val2 = m_parser.MoveAnyValue();
  EXPECT_EQ(dynamic_array_val, parsed_val2);

  auto json_value_string = ValuesToJSONString(dynamic_array_val);
  EXPECT_TRUE(m_parser.TypedParseString(dynamic_array_val.GetType(), json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(dynamic_array_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, EmptyDynamicArrayValue)
{
  AnyValue empty_dynamic_array_val(0, Float32Type);
  auto json_string = AnyValueToJSONString(empty_dynamic_array_val);
  EXPECT_TRUE(m_parser.ParseString(json_string));
  auto parsed_val = m_parser.MoveAnyValue();
  EXPECT_EQ(empty_dynamic_array_val, parsed_val);
  EXPECT_TRUE(m_parser.ParseString(json_empty_array_full));
  auto parsed_val2 = m_parser.MoveAnyValue();
  EXPECT_EQ(empty_dynamic_array_val, parsed_val2);

  auto json_value_string = ValuesToJSONString(empty_dynamic_array_val);
  EXPECT_TRUE(m_parser.TypedParseString(empty_dynamic_array_val.GetType(), json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(empty_dynamic_array_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, ComplexStructValue)
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
  EXPECT_TRUE(m_parser.ParseString(json_string));
  auto parsed_val = m_parser.MoveAnyValue();
  EXPECT_EQ(complex_struct_val, parsed_val);

  auto json_value_string = ValuesToJSONString(complex_struct_val);
  EXPECT_TRUE(m_parser.TypedParseString(complex_struct_type, json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(complex_struct_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, DynamicArrayOfStructValue)
{
  AnyValue simple_struct_val({
    {"id", {StringType, "MyId"}},
    {"number", {UnsignedInteger64Type, 14}}
  });
  AnyType array_of_struct_type(0, simple_struct_val.GetType());
  AnyValue array_of_struct_val(array_of_struct_type);
  array_of_struct_val.AddElement(simple_struct_val);
  auto json_string = AnyValueToJSONString(array_of_struct_val);
  EXPECT_TRUE(m_parser.ParseString(json_string));
  auto parsed_val = m_parser.MoveAnyValue();
  EXPECT_EQ(array_of_struct_val, parsed_val);
  EXPECT_TRUE(m_parser.ParseString(json_dynamic_array_of_struct));
  auto parsed_val_2 = m_parser.MoveAnyValue();
  EXPECT_EQ(array_of_struct_val, parsed_val_2);

  auto json_value_string = ValuesToJSONString(array_of_struct_val);
  EXPECT_TRUE(m_parser.TypedParseString(array_of_struct_type, json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(array_of_struct_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, EmptyDynamicArrayOfStructValue)
{
  AnyType simple_struct_type({
    {"id", StringType},
    {"number", UnsignedInteger64Type}
  });
  AnyValue empty_array_of_struct_val(0, simple_struct_type);
  auto json_string = AnyValueToJSONString(empty_array_of_struct_val);
  EXPECT_TRUE(m_parser.ParseString(json_string));
  auto parsed_val = m_parser.MoveAnyValue();
  EXPECT_EQ(empty_array_of_struct_val, parsed_val);

  auto json_value_string = ValuesToJSONString(empty_array_of_struct_val);
  EXPECT_TRUE(m_parser.TypedParseString(empty_array_of_struct_val.GetType(), json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(empty_array_of_struct_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, DynamicArrayOfArrayValue)
{
  AnyValue simple_array_val = ArrayValue({
    {UnsignedInteger8Type, 2}, 4, 6, 8
  });
  AnyType array_of_array_type(0, simple_array_val.GetType());
  AnyValue array_of_array_val(array_of_array_type);
  array_of_array_val.AddElement(simple_array_val);
  auto json_string = AnyValueToJSONString(array_of_array_val);
  EXPECT_TRUE(m_parser.ParseString(json_string));
  auto parsed_val = m_parser.MoveAnyValue();
  EXPECT_EQ(array_of_array_val, parsed_val);
  EXPECT_TRUE(m_parser.ParseString(json_dynamic_array_of_array));
  auto parsed_val_2 = m_parser.MoveAnyValue();
  EXPECT_EQ(array_of_array_val, parsed_val_2);

  auto json_value_string = ValuesToJSONString(array_of_array_val);
  EXPECT_TRUE(m_parser.TypedParseString(array_of_array_type, json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(array_of_array_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, EmptyDynamicArrayOfArrayValue)
{
  AnyType simple_array_type(4, SignedInteger16Type);
  AnyValue empty_array_of_array_val(0, simple_array_type);
  auto json_string = AnyValueToJSONString(empty_array_of_array_val);
  EXPECT_TRUE(m_parser.ParseString(json_string));
  auto parsed_val = m_parser.MoveAnyValue();
  EXPECT_EQ(empty_array_of_array_val, parsed_val);

  auto json_value_string = ValuesToJSONString(empty_array_of_array_val);
  EXPECT_TRUE(m_parser.TypedParseString(empty_array_of_array_val.GetType(), json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(empty_array_of_array_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, EmptyMember)
{
  // See COA-741
  {
    // Using direct initialization
    AnyValue anyvalue{{
      {"a", {} }
    }};
    const auto json = AnyValueToJSONString(anyvalue);
    ASSERT_FALSE(json.empty());
    std::cout << "json: " << json << std::endl;
    JSONAnyValueParser parser;
    ASSERT_TRUE(parser.ParseString(json));
    auto readback = parser.MoveAnyValue();
    std::cout << "readback: " << AnyValueToJSONString(readback) << std::endl;
    EXPECT_EQ(anyvalue, readback);
  }
  {
    // Using added empty member
    AnyValue anyvalue = EmptyStruct();
    anyvalue.AddMember("a", {});
    const auto json = AnyValueToJSONString(anyvalue);
    ASSERT_FALSE(json.empty());
    JSONAnyValueParser parser;
    ASSERT_TRUE(parser.ParseString(json));
    auto readback = parser.MoveAnyValue();
    EXPECT_EQ(anyvalue, readback);
  }
}

JSONValueParserTest::JSONValueParserTest() = default;

JSONValueParserTest::~JSONValueParserTest() = default;
