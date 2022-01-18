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

#include "ScalarConversion.h"

using namespace sup::dto;

class ScalarConversionTest : public ::testing::Test
{
protected:
  ScalarConversionTest();
  virtual ~ScalarConversionTest();
};

TEST_F(ScalarConversionTest, Traits)
{
  EXPECT_FALSE(IsStrictlyInteger<boolean>::value);
  EXPECT_TRUE(IsStrictlyInteger<int8>::value);
  EXPECT_TRUE(IsStrictlyInteger<uint8>::value);
}

TEST_F(ScalarConversionTest, SuccessfulConversions)
{
  EXPECT_EQ((ConvertScalar<uint8, int8>(4)), 4u);
  EXPECT_EQ((ConvertScalar<int8, int8>(4)), 4);
  EXPECT_EQ((ConvertScalar<int8, uint8>(4)), 4);
  EXPECT_EQ((ConvertScalar<boolean, int8>(4)), true);
  EXPECT_EQ((ConvertScalar<int8, boolean>(true)), 1);
  EXPECT_EQ((ConvertScalar<int8, boolean>(false)), 0);
}

TEST_F(ScalarConversionTest, InvalidConversions)
{
  EXPECT_THROW(ConvertScalar<uint8>(260u), InvalidConversionException);
  EXPECT_THROW(ConvertScalar<uint32>(-4), InvalidConversionException);
  EXPECT_THROW(ConvertScalar<int16>(40000), InvalidConversionException);
  EXPECT_THROW(ConvertScalar<int8>(400u), InvalidConversionException);
  EXPECT_THROW(ConvertScalar<uint64>(-3.14), InvalidConversionException);
  EXPECT_THROW(ConvertScalar<int64>(1e19), InvalidConversionException);
}

ScalarConversionTest::ScalarConversionTest() = default;

ScalarConversionTest::~ScalarConversionTest() = default;
