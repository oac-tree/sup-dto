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

#include "AnyTypeHelper.h"
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

AnyTypeSerializeTest::AnyTypeSerializeTest()
  : serializer{}
{}

AnyTypeSerializeTest::~AnyTypeSerializeTest() = default;

