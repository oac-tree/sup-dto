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

using namespace sup::dto;

static const std::string json_empty_val = "null";
static const std::string json_true_val = "true";

static const std::string json_simple_struct =
    R"RAW({"type":"","attributes":[{"id":{"type":"string"}},{"number":{"type":"int32"}},{"weight":{"type":"float64"}}]})RAW";

static const std::string json_simple_array =
    R"RAW({"type":"","multiplicity":5,"element":{"type":"char8"}})RAW";

static const std::string json_complex_val =
    R"RAW({"type":"","attributes":[{"array":{"type":"","multiplicity":4,"element":{"type":"","attributes":[{"id":{"type":"string"}},{"number":{"type":"uint64"}}]}}},{"nested":{"type":"","attributes":[{"id":{"type":"string"}},{"number":{"type":"uint64"}}]}},{"validated":{"type":"bool"}}]})RAW";

class AnyValueJSONSerializeTest : public ::testing::Test
{
protected:
  AnyValueJSONSerializeTest();
  virtual ~AnyValueJSONSerializeTest();
};

TEST_F(AnyValueJSONSerializeTest, EmptyValue)
{
  AnyValue empty{};
  auto json_string = ToJSONString(empty);
  EXPECT_EQ(json_string, json_empty_val);
}

TEST_F(AnyValueJSONSerializeTest, BooleanValue)
{
  AnyValue bool_val = true;
  auto json_string = ToJSONString(bool_val);
  EXPECT_EQ(json_string, json_true_val);
}

// TEST_F(AnyValueJSONSerializeTest, SimpleStructValue)
// {
//   AnyValue simple_struct_val({
//     {"id", String},
//     {"number", SignedInteger32},
//     {"weight", Float64}
//   });
//   auto json_string = ToJSONString(simple_struct_val);
//   EXPECT_EQ(json_string, json_simple_struct);
// }

// TEST_F(AnyValueJSONSerializeTest, SimpleArrayValue)
// {
//   AnyValue simple_array_val(5, Character8);
//   auto json_string = ToJSONString(simple_array_val);
//   EXPECT_EQ(json_string, json_simple_array);
// }

// TEST_F(AnyValueJSONSerializeTest, ComplexStructValue)
// {
//   AnyValue simple_struct_val({
//     {"id", String},
//     {"number", UnsignedInteger64}
//   });
//   AnyValue array_of_struct_val(4, simple_struct_val);
//   AnyValue complex_struct_val({
//     {"array", array_of_struct_val},
//     {"nested", simple_struct_val},
//     {"validated", Boolean}
//   });
//   auto json_string = ToJSONString(complex_struct_val);
//   EXPECT_EQ(json_string, json_complex_val);
// }

AnyValueJSONSerializeTest::AnyValueJSONSerializeTest() = default;

AnyValueJSONSerializeTest::~AnyValueJSONSerializeTest() = default;

