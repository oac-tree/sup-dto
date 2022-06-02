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

#include "sup/dto/anytype_helper.h"
#include "sup/dto/anytype.h"
#include "TestSerializers.h"

using namespace sup::dto;

class AnyTypeSerializeTest : public ::testing::Test
{
protected:
  AnyTypeSerializeTest();
  virtual ~AnyTypeSerializeTest();

  SimpleAnyTypeSerializer serializer;
};

TEST_F(AnyTypeSerializeTest, EmptyType)
{
  AnyType empty = EmptyType;
  SerializeAnyType(empty, serializer);
  std::string expected = "E()E";
  EXPECT_EQ(serializer.GetRepresentation(), expected);
}

TEST_F(AnyTypeSerializeTest, BooleanType)
{
  AnyType bool_type = Boolean;
  SerializeAnyType(bool_type, serializer);
  std::string expected = BOOLEAN_TYPE_NAME;
  EXPECT_EQ(serializer.GetRepresentation(), expected);
}

TEST_F(AnyTypeSerializeTest, SimpleStructType)
{
  AnyType simple_struct_type({
    {"id", String},
    {"number", SignedInteger32},
    {"weight", Float64}
  });
  SerializeAnyType(simple_struct_type, serializer);
  std::string expected = "S{M(id:" + STRING_TYPE_NAME + ")M,"
                       + "M(number:" + INT32_TYPE_NAME + ")M,"
                       + "M(weight:" + FLOAT64_TYPE_NAME + ")M}S";
  EXPECT_EQ(serializer.GetRepresentation(), expected);
}

TEST_F(AnyTypeSerializeTest, SimpleArrayType)
{
  AnyType simple_array_type(5, Character8);
  SerializeAnyType(simple_array_type, serializer);
  std::string expected = "A[5|" + CHAR8_TYPE_NAME + "]A";
  EXPECT_EQ(serializer.GetRepresentation(), expected);
}

TEST_F(AnyTypeSerializeTest, UnboundedArrayType)
{
  AnyType unbounded_array_type(AnyType::unbounded_array_tag, Character8);
  SerializeAnyType(unbounded_array_type, serializer);
  std::string expected = "U[" + CHAR8_TYPE_NAME + "]U";
  EXPECT_EQ(serializer.GetRepresentation(), expected);
}

TEST_F(AnyTypeSerializeTest, ComplexStructType)
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
  SerializeAnyType(complex_struct_type, serializer);
  std::string simple_expected = "S{M(id:" + STRING_TYPE_NAME + ")M,"
                              + "M(number:" + UINT64_TYPE_NAME + ")M}S";
  std::string expected = "S{M(array:A[4|" + simple_expected + "]A)M,"
                       + "M(nested:" + simple_expected + ")M,"
                       + "M(validated:" + BOOLEAN_TYPE_NAME + ")M}S";
  EXPECT_EQ(serializer.GetRepresentation(), expected);
}

AnyTypeSerializeTest::AnyTypeSerializeTest()
  : serializer{}
{}

AnyTypeSerializeTest::~AnyTypeSerializeTest() = default;

