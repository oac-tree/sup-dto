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

#include <sup/dto/anyvalue.h>
#include <sup/dto/anyvalue_helper.h>
#include <sup/dto/json_value_parser.h>

#include <limits>

using namespace sup::dto;

const std::string json_simple_struct_full =
    R"RAW([{"encoding":"sup-dto/v1.0/JSON"},{"datatype":{"type":"","attributes":[{"id":{"type":"string"}},{"number":{"type":"int32"}},{"weight":{"type":"float64"}}]}},{"instance":{"id":"my_id","number":1729,"weight":50.25}}])RAW";

const std::string json_simple_array_full =
    R"RAW([{"encoding":"sup-dto/v1.0/JSON"},{"datatype":{"type":"","multiplicity":5,"element":{"type":"int32"}}},{"instance":[0,20,40,60,80]}])RAW";

const std::string json_dynamic_array_full =
    R"RAW([{"encoding":"sup-dto/v1.0/JSON"},{"datatype":{"type":"","element":{"type":"uint64"}}},{"instance":[11,22,33]}])RAW";

const std::string json_empty_array_full =
    R"RAW([{"encoding":"sup-dto/v1.0/JSON"},{"datatype":{"type":"","element":{"type":"float32"}}},{"instance":[]}])RAW";

const std::string pretty_json_simple_struct =
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

const std::string json_ntenum_full =
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

const std::string json_dynamic_array_of_struct =
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

const std::string json_dynamic_array_of_array =
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

const std::string json_unknown_struct_type =
    R"RAW([{"encoding":"sup-dto/v1.0/JSON"},{"datatype":{"type":"UNKNOWN"}},{"instance":{"id":"my_id","number":1729,"weight":50.25}}])RAW";

class JSONValueParserTest : public ::testing::Test
{
protected:
  JSONValueParserTest();
  ~JSONValueParserTest() override;

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

TEST_F(JSONValueParserTest, Float64MaxValueRoundTrip)
{
  AnyValue max_val = {Float64Type, std::numeric_limits<float64>::max()};
  auto json_value_string = ValuesToJSONString(max_val);
  EXPECT_TRUE(m_parser.TypedParseString(Float64Type, json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(max_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, Float64MinValueRoundTrip)
{
  AnyValue min_val = {Float64Type, std::numeric_limits<float64>::min()};
  auto json_value_string = ValuesToJSONString(min_val);
  EXPECT_TRUE(m_parser.TypedParseString(Float64Type, json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(min_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, Float64DenormMinValueRoundTrip)
{
  AnyValue denorm_min_val = {Float64Type, std::numeric_limits<float64>::denorm_min()};
  auto json_value_string = ValuesToJSONString(denorm_min_val);
  EXPECT_TRUE(m_parser.TypedParseString(Float64Type, json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(denorm_min_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, NegativeZeroFloat64ValueRoundTrip)
{
  AnyValue negzero_val = {Float64Type, -0.0};
  auto json_value_string = ValuesToJSONString(negzero_val);
  EXPECT_TRUE(m_parser.TypedParseString(Float64Type, json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(negzero_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, Float64LargeExponentRoundTrip)
{
  AnyValue large_val = {Float64Type, 1e300};
  auto json_value_string = ValuesToJSONString(large_val);
  EXPECT_TRUE(m_parser.TypedParseString(Float64Type, json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(large_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, Float64SmallExponentRoundTripPrecisionLoss)
{
  // Known issue: the vendored RapidJSON (1.1) uses the plain Grisu2 double-to-string
  // algorithm without a Dragon4/correctness fallback. Grisu2 has a documented small but
  // nonzero rate of producing output that does not round-trip to the exact original
  // double. This value is a concrete example: it comes back one ULP off.
  AnyValue small_val = {Float64Type, 1.5e-300};
  auto json_value_string = ValuesToJSONString(small_val);
  EXPECT_TRUE(m_parser.TypedParseString(Float64Type, json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_NE(small_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, Float64HighPrecisionRoundTripPrecisionLoss)
{
  // Same Grisu2 round-trip limitation as Float64SmallExponentRoundTripPrecisionLoss,
  // triggered here by a value that needs the full 17 significant digits.
  AnyValue precise_val = {Float64Type, 123456789.12345679};
  auto json_value_string = ValuesToJSONString(precise_val);
  EXPECT_TRUE(m_parser.TypedParseString(Float64Type, json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_NE(precise_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, Float64RoundTripNonConvergentCycle)
{
  // Distinct from the two precision-loss cases above, which each drift once and then
  // settle at a fixed point: this value drifts to its immediate neighbor and then cycles
  // back to the exact original on the next round trip, forever, rather than converging.
  AnyValue original = {Float64Type, 3.6268083521793005e-184};

  auto json_after_zero = ValuesToJSONString(original);
  ASSERT_TRUE(m_parser.TypedParseString(Float64Type, json_after_zero));
  auto after_one_trip = m_parser.MoveAnyValue();
  EXPECT_NE(after_one_trip, original);

  auto json_after_one = ValuesToJSONString(after_one_trip);
  ASSERT_TRUE(m_parser.TypedParseString(Float64Type, json_after_one));
  auto after_two_trips = m_parser.MoveAnyValue();
  EXPECT_EQ(after_two_trips, original);
}

TEST_F(JSONValueParserTest, Float32MinValueRoundTrip)
{
  AnyValue min_val = {Float32Type, std::numeric_limits<float32>::min()};
  auto json_value_string = ValuesToJSONString(min_val);
  EXPECT_TRUE(m_parser.TypedParseString(Float32Type, json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(min_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, Float32MaxValueRoundTrip)
{
  // Float32 values are written by promoting to double (see
  // AnyValueJSONSerializeTest.Float32MaxValue) before applying the same Grisu2
  // algorithm, which can produce a JSON number that numerically exceeds
  // static_cast<float64>(FLT_MAX). This still round-trips correctly: the narrowing
  // conversion back to float32 (see low_level/scalar_conversion.h) rounds to nearest
  // instead of rejecting anything past the exact bound, so it correctly rounds back down
  // to FLT_MAX instead of overflowing.
  AnyValue max_val = {Float32Type, std::numeric_limits<float32>::max()};
  auto json_value_string = ValuesToJSONString(max_val);
  EXPECT_TRUE(m_parser.TypedParseString(Float32Type, json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(max_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, Float32MinValueNegatedRoundTrip)
{
  // Same as Float32MaxValueRoundTrip, mirrored to the negative side (the destination
  // range's lower bound rather than its upper one).
  AnyValue min_val = {Float32Type, -std::numeric_limits<float32>::max()};
  auto json_value_string = ValuesToJSONString(min_val);
  EXPECT_TRUE(m_parser.TypedParseString(Float32Type, json_value_string));
  auto parsed_from_type = m_parser.MoveAnyValue();
  EXPECT_EQ(min_val, parsed_from_type);
}

TEST_F(JSONValueParserTest, Float64ParseScientificNotationString)
{
  EXPECT_TRUE(m_parser.TypedParseString(Float64Type, "1.5e10"));
  auto parsed_val = m_parser.MoveAnyValue();
  AnyValue expected = {Float64Type, 1.5e10};
  EXPECT_EQ(expected, parsed_val);
}

// The following tests start from a hand-written JSON number literal, rather than from a
// C++ float/double value that is first serialized. This exercises the JSON->AnyValue parsing
// path directly and complements the value->JSON->value round trips above.

TEST_F(JSONValueParserTest, Float64OverflowLiteralRejected)
{
  // A decimal literal outside double range is gracefully rejected (the reader's
  // overflow-to-infinity is caught by the same conversion check that rejects
  // std::numeric_limits<float64>::infinity(), see
  // AnyValueJSONSerializeTest.PositiveInfinityConstructionThrows).
  EXPECT_FALSE(m_parser.TypedParseString(Float64Type, "1e400"));
  EXPECT_FALSE(m_parser.TypedParseString(Float64Type, "-1e400"));
}

TEST_F(JSONValueParserTest, Float64UnderflowLiteralParsesToZero)
{
  EXPECT_TRUE(m_parser.TypedParseString(Float64Type, "1e-400"));
  auto parsed_val = m_parser.MoveAnyValue();
  AnyValue expected = {Float64Type, 0.0};
  EXPECT_EQ(expected, parsed_val);
}

TEST_F(JSONValueParserTest, Float64LeadingZeroLiteralRejected)
{
  // "00.1" is not a valid JSON number (leading zeros are disallowed by the grammar).
  EXPECT_FALSE(m_parser.TypedParseString(Float64Type, "00.1"));
}

TEST_F(JSONValueParserTest, Float64NaNLiteralRejected)
{
  // The literal token "NaN" is not valid JSON syntax and is cleanly rejected while
  // parsing -- independently of ScalarValueTest.Float64InvalidValues, which rejects NaN
  // at the AnyValue level regardless of where the value comes from.
  EXPECT_FALSE(m_parser.TypedParseString(Float64Type, "NaN"));
}

TEST_F(JSONValueParserTest, Float64InfinityLiteralRejected)
{
  EXPECT_FALSE(m_parser.TypedParseString(Float64Type, "Infinity"));
  EXPECT_FALSE(m_parser.TypedParseString(Float64Type, "-Infinity"));
}

TEST_F(JSONValueParserTest, Float64IntegerLiteralParsesAsFloat)
{
  EXPECT_TRUE(m_parser.TypedParseString(Float64Type, "42"));
  auto parsed_val = m_parser.MoveAnyValue();
  AnyValue expected = {Float64Type, 42.0};
  EXPECT_EQ(expected, parsed_val);
}

TEST_F(JSONValueParserTest, Float64HighPrecisionLiteralRoundTripPrecisionLoss)
{
  // Same Grisu2 limitation as the value->JSON->value tests above (see
  // Float64SmallExponentRoundTripPrecisionLoss), now demonstrated starting from a JSON
  // literal instead of a C++ double. "1.0000000000000002220446049250313080847263336181640625"
  // is the exact decimal expansion of the double just above 1.0 and parses to it correctly,
  // but reserializing that double and reparsing it lands on a different double one ULP away.
  ASSERT_TRUE(m_parser.TypedParseString(
      Float64Type, "1.0000000000000002220446049250313080847263336181640625"));
  auto parsed_val = m_parser.MoveAnyValue();
  auto json_value_string = ValuesToJSONString(parsed_val);
  ASSERT_TRUE(m_parser.TypedParseString(Float64Type, json_value_string));
  auto reparsed_val = m_parser.MoveAnyValue();
  EXPECT_NE(parsed_val, reparsed_val);
}

TEST_F(JSONValueParserTest, Float64ThreeTenthsLiteralRoundTripPrecisionLoss)
{
  // Same known issue as Float64HighPrecisionLiteralRoundTripPrecisionLoss, triggered by
  // the classic 0.1+0.2 double artifact.
  ASSERT_TRUE(m_parser.TypedParseString(Float64Type, "0.30000000000000004"));
  auto parsed_val = m_parser.MoveAnyValue();
  auto json_value_string = ValuesToJSONString(parsed_val);
  ASSERT_TRUE(m_parser.TypedParseString(Float64Type, json_value_string));
  auto reparsed_val = m_parser.MoveAnyValue();
  EXPECT_NE(parsed_val, reparsed_val);
}

TEST_F(JSONValueParserTest, Float32CorrectlyRoundedMaxLiteralAccepted)
{
  // "3.4028235e38" is the textbook correctly-rounded decimal representation of
  // std::numeric_limits<float32>::max() (verified against strtof, which resolves it to
  // exactly FLT_MAX). The JSON reader parses every floating-point literal as a float64
  // first and then narrows to the target type; that intermediate float64 (3.4028235e38)
  // is numerically larger than static_cast<float64>(FLT_MAX), but the narrowing
  // conversion rounds to nearest instead of rejecting anything past the exact bound (see
  // low_level/scalar_conversion.h), so it correctly rounds down to FLT_MAX, same as
  // strtof.
  ASSERT_TRUE(m_parser.TypedParseString(Float32Type, "3.4028235e38"));
  auto parsed_val = m_parser.MoveAnyValue();
  AnyValue expected = {Float32Type, std::numeric_limits<float32>::max()};
  EXPECT_EQ(expected, parsed_val);
}

TEST_F(JSONValueParserTest, Float32CorrectlyRoundedNegatedMaxLiteralAccepted)
{
  // Mirrors Float32CorrectlyRoundedMaxLiteralAccepted on the negative side.
  ASSERT_TRUE(m_parser.TypedParseString(Float32Type, "-3.4028235e38"));
  auto parsed_val = m_parser.MoveAnyValue();
  AnyValue expected = {Float32Type, -std::numeric_limits<float32>::max()};
  EXPECT_EQ(expected, parsed_val);
}

TEST_F(JSONValueParserTest, Float32GenuineOverflowLiteralRejected)
{
  // Past the correct-rounding threshold, values are still rejected rather than silently
  // clamped -- both this one and Float32CorrectlyRoundedMaxLiteralAccepted's
  // "3.4028235e38" bracket the true halfway point to infinity.
  EXPECT_FALSE(m_parser.TypedParseString(Float32Type, "3.4028236e38"));
  EXPECT_FALSE(m_parser.TypedParseString(Float32Type, "-3.4028236e38"));
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
    JSONAnyValueParser parser;
    ASSERT_TRUE(parser.ParseString(json));
    auto readback = parser.MoveAnyValue();
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

TEST_F(JSONValueParserTest, UnknownType)
{
  EXPECT_FALSE(m_parser.ParseString(json_unknown_struct_type));
}

JSONValueParserTest::JSONValueParserTest() = default;

JSONValueParserTest::~JSONValueParserTest() = default;
