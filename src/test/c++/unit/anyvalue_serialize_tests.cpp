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

#include "sup/dto/anyvalue_helper.h"
#include "sup/dto/anyvalue.h"
#include "test_serializers.h"

using namespace sup::dto;

class AnyValueSerializeTest : public ::testing::Test
{
protected:
  AnyValueSerializeTest();
  virtual ~AnyValueSerializeTest();

  SimpleAnyValueSerializer serializer;
};

TEST_F(AnyValueSerializeTest, EmptyValue)
{
  AnyValue empty{};
  SerializeAnyValue(empty, serializer);
  std::string expected = "E()E";
  EXPECT_EQ(serializer.GetRepresentation(), expected);
}

TEST_F(AnyValueSerializeTest, BooleanValue)
{
  AnyValue bool_value{Boolean};
  SerializeAnyValue(bool_value, serializer);
  std::string expected = kBooleanTypeName;
  EXPECT_EQ(serializer.GetRepresentation(), expected);
}

TEST_F(AnyValueSerializeTest, SimpleStructValue)
{
  AnyValue simple_struct_value({
    {"id", {String, "MyID"}},
    {"number", {SignedInteger32, 10}},
    {"weight", {Float64, 4.75}}
  });
  SerializeAnyValue(simple_struct_value, serializer);
  std::string expected = "S{M(id:" + kStringTypeName + ")M,"
                       + "M(number:" + kInt32TypeName + ")M,"
                       + "M(weight:" + kFloat64TypeName + ")M}S";
  EXPECT_EQ(serializer.GetRepresentation(), expected);
}

TEST_F(AnyValueSerializeTest, SimpleArrayValue)
{
  AnyValue simple_array_value(3, Character8);
  SerializeAnyValue(simple_array_value, serializer);
  std::string expected = "A[3|" + kChar8TypeName + ","
                                + kChar8TypeName + ","
                                + kChar8TypeName + "]A";
  EXPECT_EQ(serializer.GetRepresentation(), expected);
}

TEST_F(AnyValueSerializeTest, UnboundedArrayValue)
{
  AnyValue unbounded_array_value = UnboundedArrayValue({
    {Character8, 1}, 2, 3
  });
  SerializeAnyValue(unbounded_array_value, serializer);
  std::string expected = "U[" + kChar8TypeName + ","
                                + kChar8TypeName + ","
                                + kChar8TypeName + "]U";
  EXPECT_EQ(serializer.GetRepresentation(), expected);
}

TEST_F(AnyValueSerializeTest, ComplexStructValue)
{
  AnyValue simple_struct_value({
    {"id", {String, "MyID"}},
    {"number", {UnsignedInteger64, 23}}
  });
  AnyValue array_of_struct_value(2, simple_struct_value.GetType());
  AnyValue complex_struct_value({
    {"array", array_of_struct_value},
    {"nested", simple_struct_value},
    {"validated", {Boolean, true}}
  });
  SerializeAnyValue(complex_struct_value, serializer);
  std::string simple_expected = "S{M(id:" + kStringTypeName + ")M,"
                              + "M(number:" + kUInt64TypeName + ")M}S";
  std::string expected = "S{M(array:A[2|" + simple_expected + ","
                                          + simple_expected + "]A)M,"
                       + "M(nested:" + simple_expected + ")M,"
                       + "M(validated:" + kBooleanTypeName + ")M}S";
  EXPECT_EQ(serializer.GetRepresentation(), expected);
}

AnyValueSerializeTest::AnyValueSerializeTest()
  : serializer{}
{}

AnyValueSerializeTest::~AnyValueSerializeTest() = default;

