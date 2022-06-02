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

#include "sup/dto/anytype_registry.h"
#include "sup/dto/anyvalue_exceptions.h"

using namespace sup::dto;

TEST(AnyTypeRegistryTest, Default)
{
  AnyTypeRegistry registry{};
  EXPECT_FALSE(registry.HasType("Unknown"));
  EXPECT_TRUE(registry.HasType(EMPTY_TYPE_NAME));
  EXPECT_TRUE(registry.HasType(BOOLEAN_TYPE_NAME));
  EXPECT_TRUE(registry.HasType(CHAR8_TYPE_NAME));
  EXPECT_TRUE(registry.HasType(INT8_TYPE_NAME));
  EXPECT_TRUE(registry.HasType(UINT8_TYPE_NAME));
  EXPECT_TRUE(registry.HasType(INT16_TYPE_NAME));
  EXPECT_TRUE(registry.HasType(UINT16_TYPE_NAME));
  EXPECT_TRUE(registry.HasType(INT32_TYPE_NAME));
  EXPECT_TRUE(registry.HasType(UINT32_TYPE_NAME));
  EXPECT_TRUE(registry.HasType(INT64_TYPE_NAME));
  EXPECT_TRUE(registry.HasType(UINT64_TYPE_NAME));
  EXPECT_TRUE(registry.HasType(FLOAT32_TYPE_NAME));
  EXPECT_TRUE(registry.HasType(FLOAT64_TYPE_NAME));
  EXPECT_TRUE(registry.HasType(STRING_TYPE_NAME));
  EXPECT_THROW(registry.GetType("Unknown"), InvalidOperationException);
  EXPECT_EQ(registry.GetType(EMPTY_TYPE_NAME), EmptyType);
  EXPECT_EQ(registry.GetType(BOOLEAN_TYPE_NAME), Boolean);
  EXPECT_EQ(registry.GetType(CHAR8_TYPE_NAME), Character8);
  EXPECT_EQ(registry.GetType(INT8_TYPE_NAME), SignedInteger8);
  EXPECT_EQ(registry.GetType(UINT8_TYPE_NAME), UnsignedInteger8);
  EXPECT_EQ(registry.GetType(INT16_TYPE_NAME), SignedInteger16);
  EXPECT_EQ(registry.GetType(UINT16_TYPE_NAME), UnsignedInteger16);
  EXPECT_EQ(registry.GetType(INT32_TYPE_NAME), SignedInteger32);
  EXPECT_EQ(registry.GetType(UINT32_TYPE_NAME), UnsignedInteger32);
  EXPECT_EQ(registry.GetType(INT64_TYPE_NAME), SignedInteger64);
  EXPECT_EQ(registry.GetType(UINT64_TYPE_NAME), UnsignedInteger64);
  EXPECT_EQ(registry.GetType(FLOAT32_TYPE_NAME), Float32);
  EXPECT_EQ(registry.GetType(FLOAT64_TYPE_NAME), Float64);
  EXPECT_EQ(registry.GetType(STRING_TYPE_NAME), String);
}

TEST(AnyTypeRegistryTest, RegisterSuccess)
{
  AnyTypeRegistry registry{};
  auto registered_typenames = registry.RegisteredAnyTypeNames();
  auto number_of_leaf_types = registered_typenames.size();

  // Register type with acceptable name or provide name explicitly
  std::string one_scalar_name = "OneScalar";
  AnyType one_scalar{{
    {"value", Float64}
  }, one_scalar_name};
  std::string two_scalars_name = "TwoScalars";
  AnyType two_scalars{{
    {"signed", SignedInteger8},
    {"unsigned", UnsignedInteger8}
  }};
  EXPECT_NO_THROW(registry.RegisterType(one_scalar));
  EXPECT_NO_THROW(registry.RegisterType(two_scalars_name, two_scalars));
  EXPECT_TRUE(registry.HasType(one_scalar_name));
  EXPECT_TRUE(registry.HasType(two_scalars_name));
  EXPECT_EQ(registry.GetType(one_scalar_name), one_scalar);
  EXPECT_EQ(registry.GetType(two_scalars_name), two_scalars);
  registered_typenames = registry.RegisteredAnyTypeNames();
  ASSERT_EQ(registered_typenames.size(), number_of_leaf_types + 2);

  // Register the same type again with the same name
  EXPECT_NO_THROW(registry.RegisterType(one_scalar));
  EXPECT_NO_THROW(registry.RegisterType(two_scalars_name, two_scalars));
  EXPECT_TRUE(registry.HasType(one_scalar_name));
  EXPECT_TRUE(registry.HasType(two_scalars_name));
  EXPECT_EQ(registry.GetType(one_scalar_name), one_scalar);
  EXPECT_EQ(registry.GetType(two_scalars_name), two_scalars);
  registered_typenames = registry.RegisteredAnyTypeNames();
  ASSERT_EQ(registered_typenames.size(), number_of_leaf_types + 2);
}

TEST(AnyTypeRegistryTest, RegisterFailure)
{
  AnyTypeRegistry registry{};
  auto registered_typenames = registry.RegisteredAnyTypeNames();
  auto number_of_leaf_types = registered_typenames.size();

  // Register type with empty name or provide empty name explicitly
  std::string one_scalar_name = "OneScalar";
  AnyType one_scalar{{
    {"value", Float64}
  }, one_scalar_name};
  std::string two_scalars_name = "TwoScalars";
  AnyType two_scalars{{
    {"signed", SignedInteger8},
    {"unsigned", UnsignedInteger8}
  }};
  EXPECT_THROW(registry.RegisterType("", one_scalar), InvalidOperationException);
  EXPECT_THROW(registry.RegisterType(two_scalars), InvalidOperationException);
  EXPECT_FALSE(registry.HasType(one_scalar_name));
  EXPECT_FALSE(registry.HasType(two_scalars_name));
  registered_typenames = registry.RegisteredAnyTypeNames();
  ASSERT_EQ(registered_typenames.size(), number_of_leaf_types);

  // Try to register a type with an existing scalar typename
  EXPECT_THROW(registry.RegisterType(EMPTY_TYPE_NAME, one_scalar), InvalidOperationException);
  EXPECT_THROW(registry.RegisterType(BOOLEAN_TYPE_NAME, one_scalar), InvalidOperationException);
  EXPECT_THROW(registry.RegisterType(CHAR8_TYPE_NAME, one_scalar), InvalidOperationException);
  EXPECT_THROW(registry.RegisterType(INT8_TYPE_NAME, one_scalar), InvalidOperationException);
  EXPECT_THROW(registry.RegisterType(UINT8_TYPE_NAME, one_scalar), InvalidOperationException);
  EXPECT_THROW(registry.RegisterType(INT16_TYPE_NAME, one_scalar), InvalidOperationException);
  EXPECT_THROW(registry.RegisterType(UINT16_TYPE_NAME, one_scalar), InvalidOperationException);
  EXPECT_THROW(registry.RegisterType(INT32_TYPE_NAME, one_scalar), InvalidOperationException);
  EXPECT_THROW(registry.RegisterType(UINT32_TYPE_NAME, one_scalar), InvalidOperationException);
  EXPECT_THROW(registry.RegisterType(INT64_TYPE_NAME, one_scalar), InvalidOperationException);
  EXPECT_THROW(registry.RegisterType(UINT64_TYPE_NAME, one_scalar), InvalidOperationException);
  EXPECT_THROW(registry.RegisterType(FLOAT32_TYPE_NAME, one_scalar), InvalidOperationException);
  EXPECT_THROW(registry.RegisterType(FLOAT64_TYPE_NAME, one_scalar), InvalidOperationException);
  EXPECT_THROW(registry.RegisterType(STRING_TYPE_NAME, one_scalar), InvalidOperationException);
}
