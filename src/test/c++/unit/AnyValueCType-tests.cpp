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
#include "ByteParser.h"

#include <cstring>

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

struct __attribute__((__packed__)) SimpleStructType
{
  char id[STRING_MAX_LENGTH];
  uint64 number;
};

struct __attribute__((__packed__)) ComplexStructType
{
  SimpleStructType simple_array[2];
  SimpleStructType simple_val;
  bool validated;
};

TEST(AnyValueCTypeTest, ToStringFields)
{
  // Valid string length
  AnyValue address = {{
    {"street", {String, "Main street"}},
    {"number", {UnsignedInteger16, 1033}}
  }};
  auto address_c = address.As<AddressType>();
  EXPECT_STREQ(address_c.street, "Main street");
  EXPECT_EQ(address_c.number, 1033);

  // Non-matching size
  EXPECT_THROW(address.As<TwoScalarsType>(), InvalidConversionException);

  // String length too long
  address["street"] =
      "This streetname is too long to be used for conversion to C-types (75 chars)";
  EXPECT_FALSE(address.As(address_c));
  // Fields are unchanged
  EXPECT_STREQ(address_c.street, "Main street");
  EXPECT_EQ(address_c.number, 1033);
}

TEST(AnyValueCTypeTest, FromStringFields)
{
  // Init C type and AnyValue with correct type
  AddressType address_c;
  std::strcpy(address_c.street, "Fortune Road");
  address_c.number = 812;

  AnyType address_t = {{
    {"street", String},
    {"number", UnsignedInteger16}
  }};
  AnyValue address(address_t);

  // Assignment from C type
  EXPECT_NO_THROW(AssignFromCType(address, address_c));
  EXPECT_EQ(address["street"], "Fortune Road");
  EXPECT_EQ(address["number"], 812);

  // Non-throwing assignment
  std::strcpy(address_c.street, "Misery Alley");
  address_c.number = 7;
  EXPECT_TRUE(SafeAssignFromCType(address, address_c));
  EXPECT_EQ(address["street"], "Misery Alley");
  EXPECT_EQ(address["number"], 7);

  // Non-matching size
  TwoScalarsType two_scalars_c;
  EXPECT_THROW(AssignFromCType(address, two_scalars_c), ParseException);
  EXPECT_FALSE(SafeAssignFromCType(address, two_scalars_c));

  // Non null-terminated source string
  std::vector<char> buffer(STRING_MAX_LENGTH, 'a');
  std::memcpy(address_c.street, buffer.data(), STRING_MAX_LENGTH);
  EXPECT_THROW(AssignFromCType(address, address_c), ParseException);
  EXPECT_FALSE(SafeAssignFromCType(address, address_c));
}

TEST(AnyValueCTypeTest, ToEmpty)
{
  // Empty AnyValue has empty byte array representation
  AnyValue empty{};
  auto byte_array = ToBytes(empty);
  EXPECT_EQ(byte_array.size(), 0);
}

TEST(AnyValueCTypeTest, FromEmpty)
{
  // Empty AnyValue has empty byte array representation
  AnyValue empty{};
  uint8 a;
  EXPECT_NO_THROW(FromBytes(empty, &a, 0));
  EXPECT_THROW(FromBytes(empty, &a, 1), ParseException);
}

TEST(AnyValueCTypeTest, ToStruct)
{
  AnyValue two_scalars = {{
    {"signed", {SignedInteger8, 1}},
    {"unsigned", {UnsignedInteger8, 12}}
  }};
  auto two_scalars_c = two_scalars.As<TwoScalarsType>();
  EXPECT_EQ(two_scalars_c.signed_scalar, 1);
  EXPECT_EQ(two_scalars_c.unsigned_scalar, 12);
}

TEST(AnyValueCTypeTest, FromStruct)
{
  // Successful assignment
  TwoScalarsType two_scalars_c = { -3, 44 };
  AnyType two_scalars_t = {{
    {"signed", SignedInteger8},
    {"unsigned", UnsignedInteger8}
  }};
  AnyValue two_scalars(two_scalars_t);
  EXPECT_NO_THROW(AssignFromCType(two_scalars, two_scalars_c));
  EXPECT_EQ(two_scalars["signed"], -3);
  EXPECT_EQ(two_scalars["unsigned"], 44);

  // Non-matching size
  AddressType address_c;
  std::strcpy(address_c.street, "Fortune Road");
  address_c.number = 812;
  EXPECT_THROW(AssignFromCType(two_scalars, address_c), ParseException);
  EXPECT_FALSE(SafeAssignFromCType(two_scalars, address_c));
}

TEST(AnyValueCTypeTest, ToArray)
{
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

TEST(AnyValueCTypeTest, FromArray)
{
  // Successful assignment
  ArrayType my_array_c = { { 0, 7, 14 , 21, 28 }};
  AnyValue my_array(5, UnsignedInteger32, "my_uint32_array");
  EXPECT_NO_THROW(AssignFromCType(my_array, my_array_c));
  for (unsigned i=0; i<5; ++i)
  {
    EXPECT_EQ(my_array[i], 7 * i);
  }
}

TEST(AnyValueCTypeTest, RoundTrip)
{
  AnyType simple_struct_type({
    {"id", String},
    {"number", UnsignedInteger64}
  });
  AnyType array_of_struct_type(2, simple_struct_type);
  AnyType complex_struct_type({
    {"array", array_of_struct_type},
    {"nested", simple_struct_type},
    {"validated", Boolean}
  });
  AnyValue complex_struct_val(complex_struct_type);
  complex_struct_val["array[1].id"] = "second_id";
  complex_struct_val["array[0].number"] = 23;
  complex_struct_val["validated"] = true;
  AnyValue parsed_val(complex_struct_type);
  auto complex_struct_c = complex_struct_val.As<ComplexStructType>();
  EXPECT_NO_THROW(AssignFromCType(parsed_val, complex_struct_c));
  EXPECT_EQ(parsed_val["array[1].id"], "second_id");
  EXPECT_EQ(parsed_val["array[0].number"], 23);
  EXPECT_EQ(parsed_val["validated"], true);
}

TEST(AnyValueCTypeTest, ByteParser)
{
  AnyValue empty_value;
  uint8 a;
  ByteParser parser(&a, 1);
  EXPECT_THROW(parser.ScalarProlog(&empty_value), ParseException);
}
