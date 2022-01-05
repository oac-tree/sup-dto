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

#include "AnyType.h"

using namespace sup::dto;

class AnyTypeTest : public ::testing::Test
{
protected:
  AnyTypeTest();
  virtual ~AnyTypeTest();
};

TEST_F(AnyTypeTest, EmptyType)
{
  AnyType empty_type{};
  EXPECT_EQ(empty_type.GetTypeCode(), TypeCode::Empty);
}

AnyTypeTest::AnyTypeTest() = default;

AnyTypeTest::~AnyTypeTest() = default;
