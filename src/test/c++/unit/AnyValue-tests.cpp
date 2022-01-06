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

AnyValueTest::AnyValueTest() = default;

AnyValueTest::~AnyValueTest() = default;
