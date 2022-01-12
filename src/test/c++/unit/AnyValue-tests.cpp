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

#include "AnyValue.h"
#include "AnyValueExceptions.h"

using namespace sup::dto;

class AnyValueTest : public ::testing::Test
{
protected:
  AnyValueTest();
  virtual ~AnyValueTest();
};

TEST_F(AnyValueTest, EmptyValue)
{
  AnyValue empty_value{};
  EXPECT_EQ(empty_value.GetType(), EmptyType);
  EXPECT_NE(empty_value.GetType(), SignedInteger8);
  EXPECT_TRUE(IsEmptyValue(empty_value));
  EXPECT_FALSE(IsStructValue(empty_value));
  EXPECT_FALSE(IsArrayValue(empty_value));
  EXPECT_FALSE(IsScalarValue(empty_value));
  EXPECT_EQ(empty_value.GetTypeCode(), TypeCode::Empty);
  EXPECT_EQ(empty_value.GetTypeName(), EMPTY_TYPE_NAME);
  EXPECT_THROW(empty_value["field"], KeyNotAllowedException);

  const AnyValue copy = empty_value;
  EXPECT_TRUE(IsEmptyValue(copy));
  EXPECT_EQ(copy, empty_value);
  EXPECT_FALSE(IsStructValue(copy));
  EXPECT_FALSE(IsArrayValue(copy));
  EXPECT_FALSE(IsScalarValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Empty);
  EXPECT_EQ(copy.GetTypeName(), EMPTY_TYPE_NAME);
  EXPECT_THROW(copy["field"], KeyNotAllowedException);

  AnyValue moved = std::move(empty_value);
  EXPECT_TRUE(IsEmptyValue(empty_value)); // Moved from value is always empty
  EXPECT_EQ(empty_value.GetType(), EmptyType);
  EXPECT_TRUE(IsEmptyValue(moved));
  EXPECT_EQ(moved, copy);
  EXPECT_FALSE(IsStructValue(moved));
  EXPECT_FALSE(IsArrayValue(moved));
  EXPECT_FALSE(IsScalarValue(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Empty);
  EXPECT_EQ(moved.GetTypeName(), EMPTY_TYPE_NAME);
  EXPECT_THROW(moved["field"], KeyNotAllowedException);
}

TEST_F(AnyValueTest, BooleanValue)
{
  AnyValue boolean_value{Boolean};
  EXPECT_EQ(boolean_value.GetType(), Boolean);
  EXPECT_NE(boolean_value.GetType(), SignedInteger8);
  EXPECT_FALSE(IsEmptyValue(boolean_value));
  EXPECT_FALSE(IsStructValue(boolean_value));
  EXPECT_FALSE(IsArrayValue(boolean_value));
  EXPECT_TRUE(IsScalarValue(boolean_value));
  EXPECT_EQ(boolean_value.GetTypeCode(), TypeCode::Bool);
  EXPECT_EQ(boolean_value.GetTypeName(), BOOLEAN_TYPE_NAME);
  EXPECT_THROW(boolean_value["field"], KeyNotAllowedException);
  EXPECT_EQ(boolean_value.As<boolean>(), false);
  boolean_value = true;
  EXPECT_EQ(boolean_value.As<boolean>(), true);

  const AnyValue copy = boolean_value;
  EXPECT_TRUE(IsScalarValue(copy));
  EXPECT_EQ(copy, boolean_value);
  EXPECT_FALSE(IsEmptyValue(copy));
  EXPECT_FALSE(IsStructValue(copy));
  EXPECT_FALSE(IsArrayValue(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Bool);
  EXPECT_EQ(copy.GetTypeName(), BOOLEAN_TYPE_NAME);
  EXPECT_THROW(copy["field"], KeyNotAllowedException);
  EXPECT_EQ(copy.As<boolean>(), true);

  AnyValue moved = std::move(boolean_value);
  EXPECT_TRUE(IsEmptyValue(boolean_value)); // Moved from value is always empty
  EXPECT_EQ(boolean_value.GetType(), EmptyType);
  EXPECT_TRUE(IsScalarValue(moved));
  EXPECT_EQ(moved, copy);
  EXPECT_FALSE(IsEmptyValue(moved));
  EXPECT_FALSE(IsStructValue(moved));
  EXPECT_FALSE(IsArrayValue(moved));
  EXPECT_EQ(moved.GetTypeCode(), TypeCode::Bool);
  EXPECT_EQ(moved.GetTypeName(), BOOLEAN_TYPE_NAME);
  EXPECT_THROW(moved["field"], KeyNotAllowedException);
  EXPECT_EQ(moved.As<boolean>(), true);

  AnyValue boolean_from_literal = true;
  EXPECT_EQ(boolean_from_literal.GetType(), Boolean);
  EXPECT_NE(boolean_from_literal.GetType(), SignedInteger8);
  EXPECT_FALSE(IsEmptyValue(boolean_from_literal));
  EXPECT_FALSE(IsStructValue(boolean_from_literal));
  EXPECT_FALSE(IsArrayValue(boolean_from_literal));
  EXPECT_TRUE(IsScalarValue(boolean_from_literal));
  EXPECT_EQ(boolean_from_literal.GetTypeCode(), TypeCode::Bool);
  EXPECT_EQ(boolean_from_literal.GetTypeName(), BOOLEAN_TYPE_NAME);
  EXPECT_THROW(boolean_from_literal["field"], KeyNotAllowedException);
  EXPECT_EQ(boolean_from_literal.As<boolean>(), true);
  boolean_from_literal = false;
  EXPECT_EQ(boolean_from_literal.As<boolean>(), false);

  int8 init = 9;
  AnyValue boolean_from_typed_literal = {Boolean, init};
  EXPECT_EQ(boolean_from_typed_literal.GetType(), Boolean);
  EXPECT_NE(boolean_from_typed_literal.GetType(), SignedInteger8);
  EXPECT_FALSE(IsEmptyValue(boolean_from_typed_literal));
  EXPECT_FALSE(IsStructValue(boolean_from_typed_literal));
  EXPECT_FALSE(IsArrayValue(boolean_from_typed_literal));
  EXPECT_TRUE(IsScalarValue(boolean_from_typed_literal));
  EXPECT_EQ(boolean_from_typed_literal.GetTypeCode(), TypeCode::Bool);
  EXPECT_EQ(boolean_from_typed_literal.GetTypeName(), BOOLEAN_TYPE_NAME);
  EXPECT_THROW(boolean_from_typed_literal["field"], KeyNotAllowedException);
  EXPECT_EQ(boolean_from_typed_literal.As<boolean>(), true);
  boolean_from_typed_literal = false;
  EXPECT_EQ(boolean_from_typed_literal.As<boolean>(), false);
}

AnyValueTest::AnyValueTest() = default;

AnyValueTest::~AnyValueTest() = default;
