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
 * Copyright (c) : 2010-2024 ITER Organization,
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

using namespace sup::dto;

TEST(AnyValueEqualityTest, BooleanEquality)
{
  // Arithmetic values representing 1 compare equal to true
  EXPECT_EQ(AnyValue(true), AnyValue(1));
  EXPECT_EQ(AnyValue(1), AnyValue(true));
  EXPECT_EQ(AnyValue(true), AnyValue(1u));
  EXPECT_EQ(AnyValue(1u), AnyValue(true));
  EXPECT_EQ(AnyValue(true), AnyValue(1.0));
  EXPECT_EQ(AnyValue(1.0), AnyValue(true));
  EXPECT_EQ(AnyValue(true), AnyValue(1.0f));
  EXPECT_EQ(AnyValue(1.0f), AnyValue(true));

  // Arithmetic values representing 0 compare equal to false
  EXPECT_EQ(AnyValue(false), AnyValue(0));
  EXPECT_EQ(AnyValue(0), AnyValue(false));
  EXPECT_EQ(AnyValue(false), AnyValue(0u));
  EXPECT_EQ(AnyValue(0u), AnyValue(false));
  EXPECT_EQ(AnyValue(false), AnyValue(0.0));
  EXPECT_EQ(AnyValue(0.0), AnyValue(false));
  EXPECT_EQ(AnyValue(false), AnyValue(0.0f));
  EXPECT_EQ(AnyValue(0.0f), AnyValue(false));
}

TEST(AnyValueEqualityTest, BooleanInequality)
{
  // Arithmetic values representing neither 0 nor 1 compare not equal to true
  EXPECT_NE(AnyValue(5), AnyValue(true));
  EXPECT_NE(AnyValue(true), AnyValue(5));
  EXPECT_NE(AnyValue(5u), AnyValue(true));
  EXPECT_NE(AnyValue(true), AnyValue(5u));
  EXPECT_NE(AnyValue(5.0), AnyValue(true));
  EXPECT_NE(AnyValue(true), AnyValue(5.0));
  EXPECT_NE(AnyValue(5.0f), AnyValue(true));
  EXPECT_NE(AnyValue(true), AnyValue(5.0f));

  // Arithmetic values representing neither 0 nor 1 compare not equal to false either
  EXPECT_NE(AnyValue(5), AnyValue(false));
  EXPECT_NE(AnyValue(false), AnyValue(5));
  EXPECT_NE(AnyValue(5u), AnyValue(false));
  EXPECT_NE(AnyValue(false), AnyValue(5u));
  EXPECT_NE(AnyValue(5.0), AnyValue(false));
  EXPECT_NE(AnyValue(false), AnyValue(5.0));
  EXPECT_NE(AnyValue(5.0f), AnyValue(false));
  EXPECT_NE(AnyValue(false), AnyValue(5.0f));
}

TEST(AnyValueEqualityTest, FloatEquality)
{
  // Exactly representable floating point values compare equal
  EXPECT_EQ(AnyValue(1.0), AnyValue(1.0f));
  EXPECT_EQ(AnyValue(1.5), AnyValue(1.5f));
  EXPECT_EQ(AnyValue(-1.0), AnyValue(-1.0f));
}

TEST(AnyValueEqualityTest, FloatInequality)
{
  // Non-exactly representable floating point values compare not equal
  EXPECT_NE(AnyValue(0.1), AnyValue(0.1f));
  EXPECT_NE(AnyValue(-0.1), AnyValue(-0.1f));
}
