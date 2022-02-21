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

using namespace sup::dto;

struct __attribute__((__packed__)) AddressType
{
  char street[STRING_MAX_LENGTH];
  uint16 number;
};

struct __attribute__((__packed__)) TwoScalarsType
{
  int8 signed_scalar;
  uint8 unsigned_scalar;
};

struct __attribute__((__packed__)) ArrayType
{
  uint32 elements[5];
};

TEST(AnyValueToCTypeTest, StringFields)
{
  // Valid string length
  AnyValue address = {{
    {"street", {String, "Main street"}},
    {"number", {UnsignedInteger16, 1033}}
  }};
  auto address_c = address.As<AddressType>();
  EXPECT_STREQ(address_c.street, "Main street");
  EXPECT_EQ(address_c.number, 1033);

  // String length too long
  address["street"] =
      "This streetname is too long to be used for conversion to C-types (75 chars)";
  EXPECT_FALSE(address.As(address_c));
  // Fields are unchanged
  EXPECT_STREQ(address_c.street, "Main street");
  EXPECT_EQ(address_c.number, 1033);
}

TEST(AnyValueToCTypeTest, Empty)
{
  // Empty AnyValue has empty byte array representation
  AnyValue empty{};
  auto byte_array = AnyValueToByteArray(empty);
  EXPECT_EQ(byte_array.size(), 0);
}

TEST(AnyValueToCTypeTest, Struct)
{
  AnyValue two_scalars = {{
    {"signed", {SignedInteger8, 1}},
    {"unsigned", {UnsignedInteger8, 12}}
  }};
  auto two_scalars_c = two_scalars.As<TwoScalarsType>();
  EXPECT_EQ(two_scalars_c.signed_scalar, 1);
  EXPECT_EQ(two_scalars_c.unsigned_scalar, 12);
}

TEST(AnyValueToCTypeTest, Array)
{
  // Empty AnyValue has empty byte array representation
  AnyValue my_array(5, UnsignedInteger32, "my_uint32_array");
  for (unsigned i=0; i<5; ++i)
  {
    my_array[i] = 10 * i;
  }
  auto my_array_c = my_array.As<ArrayType>();
  for (unsigned i=0; i<5; ++i)
  {
    EXPECT_EQ(my_array_c.elements[i], 10 * i);
  }
}
