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
#include "AnyValueExceptions.h"

using namespace sup::dto;

TEST(ArrayTypeTest, ArrayType)
{
  // test scalar array
  AnyType scalar_array(64, UnsignedInteger32);
  EXPECT_FALSE(IsEmptyType(scalar_array));
  EXPECT_FALSE(IsStructType(scalar_array));
  EXPECT_TRUE(IsArrayType(scalar_array));
  EXPECT_FALSE(IsScalarType(scalar_array));
  EXPECT_EQ(scalar_array.GetTypeCode(), TypeCode::Array);
  EXPECT_EQ(scalar_array.GetTypeName(), "");
  EXPECT_EQ(scalar_array.ElementType(), UnsignedInteger32);
  EXPECT_EQ(scalar_array.NumberOfElements(), 64);
  EXPECT_EQ(scalar_array["[]"], UnsignedInteger32);
  EXPECT_THROW(scalar_array["[2]"], KeyNotAllowedException);
  EXPECT_THROW(scalar_array["[]signed"], KeyNotAllowedException);
  EXPECT_EQ(scalar_array["[]."], UnsignedInteger32);

  AnyType scalar_array_diff_elem(64, SignedInteger32);
  EXPECT_NE(scalar_array_diff_elem, scalar_array);
  AnyType scalar_array_diff_size(60, UnsignedInteger32);
  EXPECT_NE(scalar_array_diff_size, scalar_array);
  AnyType scalar_array_diff_name(64, UnsignedInteger32, "custom name");
  EXPECT_NE(scalar_array_diff_name, scalar_array);

  // test array of structures
  AnyType two_scalars{{
    {"signed", SignedInteger8},
    {"unsigned", UnsignedInteger8}
  }};
  std::string array_name = "two_scalar_array";
  AnyType array_of_struct{2, two_scalars, array_name};
  EXPECT_FALSE(IsEmptyType(array_of_struct));
  EXPECT_FALSE(IsStructType(array_of_struct));
  EXPECT_TRUE(IsArrayType(array_of_struct));
  EXPECT_FALSE(IsScalarType(array_of_struct));
  EXPECT_EQ(array_of_struct.GetTypeCode(), TypeCode::Array);
  EXPECT_EQ(array_of_struct.GetTypeName(), array_name);
  EXPECT_EQ(array_of_struct.ElementType(), two_scalars);
  EXPECT_EQ(array_of_struct.NumberOfElements(), 2);
  EXPECT_EQ(array_of_struct["[]"], two_scalars);
  EXPECT_EQ(array_of_struct["[]signed"], SignedInteger8);
  EXPECT_EQ(array_of_struct["[].unsigned"], UnsignedInteger8);
  EXPECT_THROW(array_of_struct["[2]"], KeyNotAllowedException);

  AnyType copy = array_of_struct;
  EXPECT_EQ(copy, array_of_struct);
  EXPECT_FALSE(IsEmptyType(copy));
  EXPECT_FALSE(IsStructType(copy));
  EXPECT_TRUE(IsArrayType(copy));
  EXPECT_FALSE(IsScalarType(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::Array);
  EXPECT_EQ(copy.GetTypeName(), array_name);
  EXPECT_EQ(copy.ElementType(), two_scalars);
  EXPECT_EQ(copy.NumberOfElements(), 2);
  EXPECT_EQ(copy["[]"], two_scalars);
  EXPECT_EQ(copy["[]signed"], SignedInteger8);
  EXPECT_EQ(copy["[].unsigned"], UnsignedInteger8);
  EXPECT_THROW(copy["[2]"], KeyNotAllowedException);
}

TEST(ArrayTypeTest, ArrayMethods)
{
  // test array methods for structured type
  AnyType two_scalars{{
    {"signed", SignedInteger8},
    {"unsigned", UnsignedInteger8}
  }};
  EXPECT_THROW(two_scalars.ElementType(), InvalidOperationException);
  EXPECT_EQ(two_scalars.NumberOfElements(), 0);

  // test array methods for empty type
  AnyType empty_type = EmptyType;
  EXPECT_THROW(empty_type.ElementType(), InvalidOperationException);
  EXPECT_EQ(empty_type.NumberOfElements(), 0);

  // test array methods for scalar type
  AnyType scalar_type = Float32;
  EXPECT_THROW(scalar_type.ElementType(), InvalidOperationException);
  EXPECT_EQ(scalar_type.NumberOfElements(), 0);
}
