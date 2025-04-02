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

class AnyValueIncrementTests : public ::testing::Test
{
protected:
  AnyValueIncrementTests();
  ~AnyValueIncrementTests();
};

TEST_F(AnyValueIncrementTests, NonNumericTypes)
{
  AnyValue empty{};
  EXPECT_FALSE(Increment(empty));
  AnyValue bool_av{true};
  EXPECT_FALSE(Increment(bool_av));
  AnyValue char_av{'z'};
  EXPECT_FALSE(Increment(char_av));
  AnyValue str_av{"some string"};
  EXPECT_FALSE(Increment(str_av));
  AnyValue struct_av = {
    {"fieldname", { UnsignedInteger16Type, 2}}};
  EXPECT_FALSE(Increment(struct_av));
  AnyValue arr_av{2, StringType};
  EXPECT_FALSE(Increment(arr_av));
}

TEST_F(AnyValueIncrementTests, FloatTypes)
{
  // 32 bit floats
  AnyValue f32{Float32Type, 90.5f};
  EXPECT_TRUE(Increment(f32));
  EXPECT_EQ(f32.As<float32>(), 91.5f);
  // 64 bit floats
  AnyValue f64{Float64Type, 90.5};
  EXPECT_TRUE(Increment(f64));
  EXPECT_EQ(f64.As<float64>(), 91.5);
}

TEST_F(AnyValueIncrementTests, SignedIntegerTypes)
{
  {
    // Values 'in the middle'
    AnyValue i8{SignedInteger8Type, 5};
    EXPECT_TRUE(Increment(i8));
    EXPECT_EQ(i8.As<int8>(), 6);
    AnyValue i16{SignedInteger16Type, -30};
    EXPECT_TRUE(Increment(i16));
    EXPECT_EQ(i16.As<int16>(), -29);
    AnyValue i32{SignedInteger32Type, 0};
    EXPECT_TRUE(Increment(i32));
    EXPECT_EQ(i32.As<int32>(), 1);
    AnyValue i64{SignedInteger64Type, -1};
    EXPECT_TRUE(Increment(i64));
    EXPECT_EQ(i64.As<int64>(), 0);
  }
  {
    // Values that wrap around
    AnyValue i8{SignedInteger8Type, std::numeric_limits<int8>::max()};
    EXPECT_TRUE(Increment(i8));
    EXPECT_EQ(i8.As<int8>(), std::numeric_limits<int8>::min());
    AnyValue i16{SignedInteger16Type, std::numeric_limits<int16>::max()};
    EXPECT_TRUE(Increment(i16));
    EXPECT_EQ(i16.As<int16>(), std::numeric_limits<int16>::min());
    AnyValue i32{SignedInteger32Type, std::numeric_limits<int32>::max()};
    EXPECT_TRUE(Increment(i32));
    EXPECT_EQ(i32.As<int32>(), std::numeric_limits<int32>::min());
    AnyValue i64{SignedInteger64Type, std::numeric_limits<int64>::max()};
    EXPECT_TRUE(Increment(i64));
    EXPECT_EQ(i64.As<int64>(), std::numeric_limits<int64>::min());
  }
}

TEST_F(AnyValueIncrementTests, UnsignedIntegerTypes)
{
  {
    // Values 'in the middle'
    AnyValue ui8{UnsignedInteger8Type, 5};
    EXPECT_TRUE(Increment(ui8));
    EXPECT_EQ(ui8.As<uint8>(), 6);
    AnyValue ui16{UnsignedInteger16Type, 30};
    EXPECT_TRUE(Increment(ui16));
    EXPECT_EQ(ui16.As<uint16>(), 31);
    AnyValue ui32{UnsignedInteger32Type, 0};
    EXPECT_TRUE(Increment(ui32));
    EXPECT_EQ(ui32.As<uint32>(), 1);
    AnyValue ui64{UnsignedInteger64Type, uint64(1000000ull)};
    EXPECT_TRUE(Increment(ui64));
    EXPECT_EQ(ui64.As<uint64>(), 1000001ul);
  }
  {
    // Values that wrap around
    AnyValue ui8{UnsignedInteger8Type, std::numeric_limits<uint8>::max()};
    EXPECT_TRUE(Increment(ui8));
    EXPECT_EQ(ui8.As<int8>(), 0);
    AnyValue ui16{UnsignedInteger16Type, std::numeric_limits<uint16>::max()};
    EXPECT_TRUE(Increment(ui16));
    EXPECT_EQ(ui16.As<int16>(), 0);
    AnyValue ui32{UnsignedInteger32Type, std::numeric_limits<uint32>::max()};
    EXPECT_TRUE(Increment(ui32));
    EXPECT_EQ(ui32.As<int32>(), 0);
    AnyValue ui64{UnsignedInteger64Type, std::numeric_limits<uint64>::max()};
    EXPECT_TRUE(Increment(ui64));
    EXPECT_EQ(ui64.As<int64>(), 0);
  }
}

AnyValueIncrementTests::AnyValueIncrementTests() = default;

AnyValueIncrementTests::~AnyValueIncrementTests() = default;
