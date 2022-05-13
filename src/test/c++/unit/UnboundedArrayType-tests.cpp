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

#include "sup/dto/AnyType.h"
#include "sup/dto/AnyValueExceptions.h"

using namespace sup::dto;

TEST(UnboundedArrayTypeTest, EmptyElementType)
{
  EXPECT_THROW(UnboundedArrayType(EmptyType), InvalidOperationException);
}

TEST(UnboundedArrayTypeTest, ArrayType)
{
  // test scalar array
  AnyType scalar_array = UnboundedArrayType(UnsignedInteger32);
  EXPECT_FALSE(IsEmptyType(scalar_array));
  EXPECT_FALSE(IsStructType(scalar_array));
  EXPECT_FALSE(IsArrayType(scalar_array));
  EXPECT_TRUE(IsUnboundedArrayType(scalar_array));
  EXPECT_FALSE(IsScalarType(scalar_array));
  EXPECT_EQ(scalar_array.GetTypeCode(), TypeCode::UnboundedArray);
  EXPECT_EQ(scalar_array.GetTypeName(), "");
  EXPECT_EQ(scalar_array.ElementType(), UnsignedInteger32);
  EXPECT_EQ(scalar_array.NumberOfElements(), 0);
  EXPECT_EQ(scalar_array["[]"], UnsignedInteger32);
  EXPECT_THROW(scalar_array["[2]"], InvalidOperationException);
  EXPECT_THROW(scalar_array["[]signed"], InvalidOperationException);
  EXPECT_EQ(scalar_array["[]."], UnsignedInteger32);

  AnyType scalar_array_diff_elem = UnboundedArrayType(SignedInteger32);
  EXPECT_NE(scalar_array_diff_elem, scalar_array);
  AnyType scalar_array_fixed_size(5, UnsignedInteger32);
  EXPECT_NE(scalar_array_fixed_size, scalar_array);
  AnyType scalar_array_diff_name = UnboundedArrayType(UnsignedInteger32, "custom name");
  EXPECT_NE(scalar_array_diff_name, scalar_array);

  // test array of structures
  AnyType two_scalars{{
    {"signed", SignedInteger8},
    {"unsigned", UnsignedInteger8}
  }};
  std::string array_name = "two_scalar_array";
  AnyType array_of_struct = UnboundedArrayType(two_scalars, array_name);
  EXPECT_FALSE(IsEmptyType(array_of_struct));
  EXPECT_FALSE(IsStructType(array_of_struct));
  EXPECT_FALSE(IsArrayType(array_of_struct));
  EXPECT_TRUE(IsUnboundedArrayType(array_of_struct));
  EXPECT_FALSE(IsScalarType(array_of_struct));
  EXPECT_EQ(array_of_struct.GetTypeCode(), TypeCode::UnboundedArray);
  EXPECT_EQ(array_of_struct.GetTypeName(), array_name);
  EXPECT_EQ(array_of_struct.ElementType(), two_scalars);
  EXPECT_EQ(array_of_struct.NumberOfElements(), 0);
  EXPECT_EQ(array_of_struct["[]"], two_scalars);
  EXPECT_EQ(array_of_struct["[]signed"], SignedInteger8);
  EXPECT_EQ(array_of_struct["[].unsigned"], UnsignedInteger8);
  EXPECT_THROW(array_of_struct["[2]"], InvalidOperationException);

  AnyType copy = array_of_struct;
  EXPECT_EQ(copy, array_of_struct);
  EXPECT_FALSE(IsEmptyType(copy));
  EXPECT_FALSE(IsStructType(copy));
  EXPECT_FALSE(IsArrayType(copy));
  EXPECT_TRUE(IsUnboundedArrayType(copy));
  EXPECT_FALSE(IsScalarType(copy));
  EXPECT_EQ(copy.GetTypeCode(), TypeCode::UnboundedArray);
  EXPECT_EQ(copy.GetTypeName(), array_name);
  EXPECT_EQ(copy.ElementType(), two_scalars);
  EXPECT_EQ(copy.NumberOfElements(), 0);
  EXPECT_EQ(copy["[]"], two_scalars);
  EXPECT_EQ(copy["[]signed"], SignedInteger8);
  EXPECT_EQ(copy["[].unsigned"], UnsignedInteger8);
  EXPECT_THROW(copy["[2]"], InvalidOperationException);
}
