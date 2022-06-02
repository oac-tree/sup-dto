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
  EXPECT_TRUE(registry.HasType(kEmptyTypeName));
  EXPECT_TRUE(registry.HasType(kBooleanTypeName));
  EXPECT_TRUE(registry.HasType(kChar8TypeName));
  EXPECT_TRUE(registry.HasType(kInt8TypeName));
  EXPECT_TRUE(registry.HasType(kUInt8TypeName));
  EXPECT_TRUE(registry.HasType(kInt16TypeName));
  EXPECT_TRUE(registry.HasType(kUInt16TypeName));
  EXPECT_TRUE(registry.HasType(kInt32TypeName));
  EXPECT_TRUE(registry.HasType(kUInt32TypeName));
  EXPECT_TRUE(registry.HasType(kInt64TypeName));
  EXPECT_TRUE(registry.HasType(kUInt64TypeName));
  EXPECT_TRUE(registry.HasType(kFloat32TypeName));
  EXPECT_TRUE(registry.HasType(kFloat64TypeName));
  EXPECT_TRUE(registry.HasType(kStringTypeName));
  EXPECT_THROW(registry.GetType("Unknown"), InvalidOperationException);
  EXPECT_EQ(registry.GetType(kEmptyTypeName), EmptyType);
  EXPECT_EQ(registry.GetType(kBooleanTypeName), Boolean);
  EXPECT_EQ(registry.GetType(kChar8TypeName), Character8);
  EXPECT_EQ(registry.GetType(kInt8TypeName), SignedInteger8);
  EXPECT_EQ(registry.GetType(kUInt8TypeName), UnsignedInteger8);
  EXPECT_EQ(registry.GetType(kInt16TypeName), SignedInteger16);
  EXPECT_EQ(registry.GetType(kUInt16TypeName), UnsignedInteger16);
  EXPECT_EQ(registry.GetType(kInt32TypeName), SignedInteger32);
  EXPECT_EQ(registry.GetType(kUInt32TypeName), UnsignedInteger32);
  EXPECT_EQ(registry.GetType(kInt64TypeName), SignedInteger64);
  EXPECT_EQ(registry.GetType(kUInt64TypeName), UnsignedInteger64);
  EXPECT_EQ(registry.GetType(kFloat32TypeName), Float32);
  EXPECT_EQ(registry.GetType(kFloat64TypeName), Float64);
  EXPECT_EQ(registry.GetType(kStringTypeName), String);
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
  EXPECT_THROW(registry.RegisterType(kEmptyTypeName, one_scalar), InvalidOperationException);
  EXPECT_THROW(registry.RegisterType(kBooleanTypeName, one_scalar), InvalidOperationException);
  EXPECT_THROW(registry.RegisterType(kChar8TypeName, one_scalar), InvalidOperationException);
  EXPECT_THROW(registry.RegisterType(kInt8TypeName, one_scalar), InvalidOperationException);
  EXPECT_THROW(registry.RegisterType(kUInt8TypeName, one_scalar), InvalidOperationException);
  EXPECT_THROW(registry.RegisterType(kInt16TypeName, one_scalar), InvalidOperationException);
  EXPECT_THROW(registry.RegisterType(kUInt16TypeName, one_scalar), InvalidOperationException);
  EXPECT_THROW(registry.RegisterType(kInt32TypeName, one_scalar), InvalidOperationException);
  EXPECT_THROW(registry.RegisterType(kUInt32TypeName, one_scalar), InvalidOperationException);
  EXPECT_THROW(registry.RegisterType(kInt64TypeName, one_scalar), InvalidOperationException);
  EXPECT_THROW(registry.RegisterType(kUInt64TypeName, one_scalar), InvalidOperationException);
  EXPECT_THROW(registry.RegisterType(kFloat32TypeName, one_scalar), InvalidOperationException);
  EXPECT_THROW(registry.RegisterType(kFloat64TypeName, one_scalar), InvalidOperationException);
  EXPECT_THROW(registry.RegisterType(kStringTypeName, one_scalar), InvalidOperationException);
}
