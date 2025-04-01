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
 * Copyright (c) : 2010-2025 ITER Organization,
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
#include <sup/dto/anyvalue_operations.h>

#include <limits>

using namespace sup::dto;

class AnyValueDecrementTests : public ::testing::Test
{
protected:
  AnyValueDecrementTests();
  ~AnyValueDecrementTests();
};

TEST_F(AnyValueDecrementTests, NonNumericTypes)
{
  AnyValue empty{};
  EXPECT_FALSE(Decrement(empty));
  AnyValue bool_av{true};
  EXPECT_FALSE(Decrement(bool_av));
  AnyValue char_av{'z'};
  EXPECT_FALSE(Decrement(char_av));
  AnyValue str_av{"some string"};
  EXPECT_FALSE(Decrement(str_av));
  AnyValue struct_av = {
    {"fieldname", { UnsignedInteger16Type, 2}}};
  EXPECT_FALSE(Decrement(struct_av));
  AnyValue arr_av{2, StringType};
  EXPECT_FALSE(Decrement(arr_av));
}

TEST_F(AnyValueDecrementTests, FloatTypes)
{
  // 32 bit floats
  AnyValue f32{Float32Type, 90.5f};
  EXPECT_TRUE(Decrement(f32));
  EXPECT_EQ(f32.As<float32>(), 89.5f);
  // 64 bit floats
  AnyValue f64{Float64Type, 90.5};
  EXPECT_TRUE(Decrement(f64));
  EXPECT_EQ(f64.As<float64>(), 89.5);
}

TEST_F(AnyValueDecrementTests, SignedIntegerTypes)
{
  {
    // Values 'in the middle'
    AnyValue i8{SignedInteger8Type, 5};
    EXPECT_TRUE(Decrement(i8));
    EXPECT_EQ(i8.As<int8>(), 4);
    AnyValue i16{SignedInteger16Type, -30};
    EXPECT_TRUE(Decrement(i16));
    EXPECT_EQ(i16.As<int16>(), -31);
    AnyValue i32{SignedInteger32Type, 0};
    EXPECT_TRUE(Decrement(i32));
    EXPECT_EQ(i32.As<int32>(), -1);
    AnyValue i64{SignedInteger64Type, 1};
    EXPECT_TRUE(Decrement(i64));
    EXPECT_EQ(i64.As<int64>(), 0);
  }
  {
    // Values that wrap around
    AnyValue i8{SignedInteger8Type, std::numeric_limits<int8>::min()};
    EXPECT_TRUE(Decrement(i8));
    EXPECT_EQ(i8.As<int8>(), std::numeric_limits<int8>::max());
    AnyValue i16{SignedInteger16Type, std::numeric_limits<int16>::min()};
    EXPECT_TRUE(Decrement(i16));
    EXPECT_EQ(i16.As<int16>(), std::numeric_limits<int16>::max());
    AnyValue i32{SignedInteger32Type, std::numeric_limits<int32>::min()};
    EXPECT_TRUE(Decrement(i32));
    EXPECT_EQ(i32.As<int32>(), std::numeric_limits<int32>::max());
    AnyValue i64{SignedInteger64Type, std::numeric_limits<int64>::min()};
    EXPECT_TRUE(Decrement(i64));
    EXPECT_EQ(i64.As<int64>(), std::numeric_limits<int64>::max());
  }
}

TEST_F(AnyValueDecrementTests, UnsignedIntegerTypes)
{
  {
    // Values 'in the middle'
    AnyValue ui8{UnsignedInteger8Type, 5};
    EXPECT_TRUE(Decrement(ui8));
    EXPECT_EQ(ui8.As<uint8>(), 4);
    AnyValue ui16{UnsignedInteger16Type, 30};
    EXPECT_TRUE(Decrement(ui16));
    EXPECT_EQ(ui16.As<uint16>(), 29);
    AnyValue ui32{UnsignedInteger32Type, 1};
    EXPECT_TRUE(Decrement(ui32));
    EXPECT_EQ(ui32.As<uint32>(), 0);
    AnyValue ui64{UnsignedInteger64Type, 1000001ull};
    EXPECT_TRUE(Decrement(ui64));
    EXPECT_EQ(ui64.As<uint64>(), 1000000ul);
  }
  {
    // Values that wrap around
    AnyValue ui8{UnsignedInteger8Type, 0};
    EXPECT_TRUE(Decrement(ui8));
    EXPECT_EQ(ui8.As<uint8>(), std::numeric_limits<uint8>::max());
    AnyValue ui16{UnsignedInteger16Type, 0};
    EXPECT_TRUE(Decrement(ui16));
    EXPECT_EQ(ui16.As<uint16>(), std::numeric_limits<uint16>::max());
    AnyValue ui32{UnsignedInteger32Type, 0};
    EXPECT_TRUE(Decrement(ui32));
    EXPECT_EQ(ui32.As<uint32>(), std::numeric_limits<uint32>::max());
    AnyValue ui64{UnsignedInteger64Type, 0};
    EXPECT_TRUE(Decrement(ui64));
    EXPECT_EQ(ui64.As<uint64>(), std::numeric_limits<uint64>::max());
  }
}

AnyValueDecrementTests::AnyValueDecrementTests() = default;

AnyValueDecrementTests::~AnyValueDecrementTests() = default;
