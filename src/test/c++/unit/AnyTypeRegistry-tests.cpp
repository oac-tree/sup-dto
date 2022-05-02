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

#include "AnyTypeRegistry.h"
#include "AnyValueExceptions.h"

using namespace sup::dto;

TEST(AnyTypeRegistryTest, Empty)
{
  AnyTypeRegistry registry{};
  EXPECT_FALSE(registry.HasType("Unknown"));
  EXPECT_THROW(registry.RemoveType("Unknown"), InvalidOperationException);
  EXPECT_THROW(registry.GetType("Unknown"), InvalidOperationException);
  auto registered_typenames = registry.RegisteredAnyTypeNames();
  EXPECT_EQ(registered_typenames.size(), 0);

  AnyType two_scalars{{
    {"signed", SignedInteger8},
    {"unsigned", UnsignedInteger8}
  }};
  EXPECT_NO_THROW(registry.RegisterType("TwoScalars", two_scalars));
  EXPECT_TRUE(registry.HasType("TwoScalars"));
  auto registered_type = registry.GetType("TwoScalars");
  EXPECT_EQ(registered_type, two_scalars);
  registered_typenames = registry.RegisteredAnyTypeNames();
  ASSERT_EQ(registered_typenames.size(), 1);
  EXPECT_EQ(registered_typenames[0], "TwoScalars");
  EXPECT_NO_THROW(registry.RemoveType("TwoScalars"));
  registered_typenames = registry.RegisteredAnyTypeNames();
  EXPECT_EQ(registered_typenames.size(), 0);
}
