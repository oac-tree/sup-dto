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
 * SPDX-License-Identifier: MIT
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file LICENSE located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include <gtest/gtest.h>

#include <sup/dto/anyvalue.h>
#include <sup/dto/anyvalue_operations.h>

using namespace sup::dto;

class AnyValueComparisonTests : public ::testing::Test
{
protected:
  AnyValueComparisonTests();
  ~AnyValueComparisonTests();
};

TEST_F(AnyValueComparisonTests, NonNumericTypes)
{
  const AnyValue f32_av{12.0f};
  const AnyValue f64_av{5.5};
  const AnyValue i32{-8};
  const AnyValue ui32{50u};
  {
    // Empty types cannot be compared, not even with itself
    AnyValue empty{};
    EXPECT_EQ(Compare(empty, f32_av), CompareResult::Unordered);
    EXPECT_EQ(Compare(f32_av, empty), CompareResult::Unordered);
    EXPECT_EQ(Compare(empty, f64_av), CompareResult::Unordered);
    EXPECT_EQ(Compare(f64_av, empty), CompareResult::Unordered);
    EXPECT_EQ(Compare(empty, i32), CompareResult::Unordered);
    EXPECT_EQ(Compare(i32, empty), CompareResult::Unordered);
    EXPECT_EQ(Compare(empty, ui32), CompareResult::Unordered);
    EXPECT_EQ(Compare(ui32, empty), CompareResult::Unordered);
    EXPECT_EQ(Compare(empty, empty), CompareResult::Unordered);
  }
  {
    // Bool types cannot be compared, not even with itself
    AnyValue bool_av{true};
    EXPECT_EQ(Compare(bool_av, f32_av), CompareResult::Unordered);
    EXPECT_EQ(Compare(f32_av, bool_av), CompareResult::Unordered);
    EXPECT_EQ(Compare(bool_av, f64_av), CompareResult::Unordered);
    EXPECT_EQ(Compare(f64_av, bool_av), CompareResult::Unordered);
    EXPECT_EQ(Compare(bool_av, i32), CompareResult::Unordered);
    EXPECT_EQ(Compare(i32, bool_av), CompareResult::Unordered);
    EXPECT_EQ(Compare(bool_av, ui32), CompareResult::Unordered);
    EXPECT_EQ(Compare(ui32, bool_av), CompareResult::Unordered);
    EXPECT_EQ(Compare(bool_av, bool_av), CompareResult::Unordered);
  }
  {
    // String types cannot be compared, not even with itself
    AnyValue str_av{"some string"};
    EXPECT_EQ(Compare(str_av, f32_av), CompareResult::Unordered);
    EXPECT_EQ(Compare(f32_av, str_av), CompareResult::Unordered);
    EXPECT_EQ(Compare(str_av, f64_av), CompareResult::Unordered);
    EXPECT_EQ(Compare(f64_av, str_av), CompareResult::Unordered);
    EXPECT_EQ(Compare(str_av, i32), CompareResult::Unordered);
    EXPECT_EQ(Compare(i32, str_av), CompareResult::Unordered);
    EXPECT_EQ(Compare(str_av, ui32), CompareResult::Unordered);
    EXPECT_EQ(Compare(ui32, str_av), CompareResult::Unordered);
    EXPECT_EQ(Compare(str_av, str_av), CompareResult::Unordered);
  }
  {
    // Structure types cannot be compared, not even with itself
    AnyValue struct_av = {
      {"fieldname", { UnsignedInteger16Type, 2}}};
    EXPECT_EQ(Compare(struct_av, f32_av), CompareResult::Unordered);
    EXPECT_EQ(Compare(f32_av, struct_av), CompareResult::Unordered);
    EXPECT_EQ(Compare(struct_av, f64_av), CompareResult::Unordered);
    EXPECT_EQ(Compare(f64_av, struct_av), CompareResult::Unordered);
    EXPECT_EQ(Compare(struct_av, i32), CompareResult::Unordered);
    EXPECT_EQ(Compare(i32, struct_av), CompareResult::Unordered);
    EXPECT_EQ(Compare(struct_av, ui32), CompareResult::Unordered);
    EXPECT_EQ(Compare(ui32, struct_av), CompareResult::Unordered);
    EXPECT_EQ(Compare(struct_av, struct_av), CompareResult::Unordered);
  }
  {
    // Array types cannot be compared, not even with itself
    AnyValue arr_av{2, StringType};
    EXPECT_EQ(Compare(arr_av, f32_av), CompareResult::Unordered);
    EXPECT_EQ(Compare(f32_av, arr_av), CompareResult::Unordered);
    EXPECT_EQ(Compare(arr_av, f64_av), CompareResult::Unordered);
    EXPECT_EQ(Compare(f64_av, arr_av), CompareResult::Unordered);
    EXPECT_EQ(Compare(arr_av, i32), CompareResult::Unordered);
    EXPECT_EQ(Compare(i32, arr_av), CompareResult::Unordered);
    EXPECT_EQ(Compare(arr_av, ui32), CompareResult::Unordered);
    EXPECT_EQ(Compare(ui32, arr_av), CompareResult::Unordered);
    EXPECT_EQ(Compare(arr_av, arr_av), CompareResult::Unordered);
  }
}

TEST_F(AnyValueComparisonTests, FloatTypes)
{
  const AnyValue f32_neg{-12.0f};
  const AnyValue f64_neg(-3.4);
  const AnyValue f32_pos{2.5f};
  const AnyValue f64_pos{8.5};
  {
    // Float types that compare with result 'Less'
    EXPECT_EQ(Compare(f32_neg, f64_neg), CompareResult::Less);
    EXPECT_EQ(Compare(f32_neg, f32_pos), CompareResult::Less);
    EXPECT_EQ(Compare(f32_neg, f64_pos), CompareResult::Less);
    EXPECT_EQ(Compare(f64_neg, f32_pos), CompareResult::Less);
    EXPECT_EQ(Compare(f64_neg, f64_pos), CompareResult::Less);
    EXPECT_EQ(Compare(f32_pos, f64_pos), CompareResult::Less);
  }
  {
    // Float types that compare with result 'Equivalent'
    EXPECT_EQ(Compare(f32_neg, f32_neg), CompareResult::Equivalent);
    EXPECT_EQ(Compare(f64_neg, f64_neg), CompareResult::Equivalent);
    EXPECT_EQ(Compare(f32_pos, f32_pos), CompareResult::Equivalent);
    EXPECT_EQ(Compare(f64_pos, f64_pos), CompareResult::Equivalent);
    const AnyValue f32_neg_as64{-12.0};
    EXPECT_EQ(Compare(f32_neg, f32_neg_as64), CompareResult::Equivalent);
    const AnyValue f64_pos_as32{8.5f};
    EXPECT_EQ(Compare(f64_pos, f64_pos_as32), CompareResult::Equivalent);
  }
  {
    // Float types that compare with result 'Greater'
    EXPECT_EQ(Compare(f64_pos, f32_pos), CompareResult::Greater);
    EXPECT_EQ(Compare(f64_pos, f64_neg), CompareResult::Greater);
    EXPECT_EQ(Compare(f64_pos, f32_neg), CompareResult::Greater);
    EXPECT_EQ(Compare(f32_pos, f64_neg), CompareResult::Greater);
    EXPECT_EQ(Compare(f32_pos, f32_neg), CompareResult::Greater);
    EXPECT_EQ(Compare(f64_neg, f32_neg), CompareResult::Greater);
  }
}

TEST_F(AnyValueComparisonTests, FloatWithIntegerTypes)
{
  {
    // Float comparison with signed integers
    const AnyValue i8{SignedInteger8Type, -2};
    const AnyValue i16{SignedInteger16Type, 0};
    const AnyValue i32{SignedInteger32Type, 5};
    const AnyValue i64{SignedInteger64Type, -12000};
    EXPECT_EQ(Compare(AnyValue{-3.0}, i8), CompareResult::Less);
    EXPECT_EQ(Compare(AnyValue{-2.0}, i8), CompareResult::Equivalent);
    EXPECT_EQ(Compare(AnyValue{0.0}, i8), CompareResult::Greater);
    EXPECT_EQ(Compare(AnyValue{-3.0f}, i16), CompareResult::Less);
    EXPECT_EQ(Compare(AnyValue{0.0f}, i16), CompareResult::Equivalent);
    EXPECT_EQ(Compare(AnyValue{3.0f}, i16), CompareResult::Greater);
    EXPECT_EQ(Compare(AnyValue{-3.0}, i32), CompareResult::Less);
    EXPECT_EQ(Compare(AnyValue{5.0}, i32), CompareResult::Equivalent);
    EXPECT_EQ(Compare(AnyValue{8.5}, i32), CompareResult::Greater);
    EXPECT_EQ(Compare(AnyValue{-13000.0f}, i64), CompareResult::Less);
    EXPECT_EQ(Compare(AnyValue{-12000.0f}, i64), CompareResult::Equivalent);
    EXPECT_EQ(Compare(AnyValue{0.0f}, i64), CompareResult::Greater);
  }
  {
    // Float comparison with unsigned integers
    const AnyValue ui8{UnsignedInteger8Type, 10};
    const AnyValue ui16{UnsignedInteger16Type, 55};
    const AnyValue ui32{UnsignedInteger32Type, 0};
    const AnyValue ui64{UnsignedInteger64Type, 12000};
    EXPECT_EQ(Compare(AnyValue{-3.0}, ui8), CompareResult::Less);
    EXPECT_EQ(Compare(AnyValue{10.0}, ui8), CompareResult::Equivalent);
    EXPECT_EQ(Compare(AnyValue{55.0}, ui8), CompareResult::Greater);
    EXPECT_EQ(Compare(AnyValue{-3.0f}, ui16), CompareResult::Less);
    EXPECT_EQ(Compare(AnyValue{55.0f}, ui16), CompareResult::Equivalent);
    EXPECT_EQ(Compare(AnyValue{320.0f}, ui16), CompareResult::Greater);
    EXPECT_EQ(Compare(AnyValue{0.0}, ui32), CompareResult::Equivalent);
    EXPECT_EQ(Compare(AnyValue{8.5}, ui32), CompareResult::Greater);
    EXPECT_EQ(Compare(AnyValue{11999.9f}, ui64), CompareResult::Less);
    EXPECT_EQ(Compare(AnyValue{12000.0f}, ui64), CompareResult::Equivalent);
    EXPECT_EQ(Compare(AnyValue{12000.1f}, ui64), CompareResult::Greater);
  }
}

TEST_F(AnyValueComparisonTests, SignedIntegerTypes)
{
  {
    // Positive signed integers
    EXPECT_EQ(Compare(AnyValue{SignedInteger8Type, 120},
                      AnyValue{SignedInteger8Type, 121}), CompareResult::Less);
    EXPECT_EQ(Compare(AnyValue{SignedInteger8Type, 120},
                      AnyValue{SignedInteger16Type, 30000}), CompareResult::Less);
    EXPECT_EQ(Compare(AnyValue{SignedInteger64Type, 120},
                      AnyValue{SignedInteger32Type, 1000000}), CompareResult::Less);
    EXPECT_EQ(Compare(AnyValue{SignedInteger8Type, 120},
                      AnyValue{SignedInteger64Type, int64(4000000000ll)}), CompareResult::Less);
    EXPECT_EQ(Compare(AnyValue{SignedInteger8Type, 121},
                      AnyValue{SignedInteger8Type, 121}), CompareResult::Equivalent);
    EXPECT_EQ(Compare(AnyValue{SignedInteger8Type, 120},
                      AnyValue{SignedInteger16Type, 120}), CompareResult::Equivalent);
    EXPECT_EQ(Compare(AnyValue{SignedInteger64Type, 1000000},
                      AnyValue{SignedInteger32Type, 1000000}), CompareResult::Equivalent);
    EXPECT_EQ(Compare(AnyValue{SignedInteger8Type, 120},
                      AnyValue{SignedInteger64Type, int64(120ll)}), CompareResult::Equivalent);
    EXPECT_EQ(Compare(AnyValue{SignedInteger8Type, 122},
                      AnyValue{SignedInteger8Type, 121}), CompareResult::Greater);
    EXPECT_EQ(Compare(AnyValue{SignedInteger8Type, 127},
                      AnyValue{SignedInteger16Type, 120}), CompareResult::Greater);
    EXPECT_EQ(Compare(AnyValue{SignedInteger64Type, 1000001},
                      AnyValue{SignedInteger32Type, 1000000}), CompareResult::Greater);
    EXPECT_EQ(Compare(AnyValue{SignedInteger8Type, 120},
                      AnyValue{SignedInteger64Type, int64(119ll)}), CompareResult::Greater);
  }
  {
    // Negative and positive signed integers
    EXPECT_EQ(Compare(AnyValue{SignedInteger8Type, -120},
                      AnyValue{SignedInteger8Type, 121}), CompareResult::Less);
    EXPECT_EQ(Compare(AnyValue{SignedInteger8Type, -120},
                      AnyValue{SignedInteger16Type, 30000}), CompareResult::Less);
    EXPECT_EQ(Compare(AnyValue{SignedInteger64Type, 0},
                      AnyValue{SignedInteger32Type, 1000000}), CompareResult::Less);
    EXPECT_EQ(Compare(AnyValue{SignedInteger8Type, -120},
                      AnyValue{SignedInteger64Type, int64(4000000000ll)}), CompareResult::Less);
    EXPECT_EQ(Compare(AnyValue{SignedInteger8Type, -121},
                      AnyValue{SignedInteger8Type, -121}), CompareResult::Equivalent);
    EXPECT_EQ(Compare(AnyValue{SignedInteger8Type, -120},
                      AnyValue{SignedInteger16Type, -120}), CompareResult::Equivalent);
    EXPECT_EQ(Compare(AnyValue{SignedInteger64Type, 0},
                      AnyValue{SignedInteger32Type, 0}), CompareResult::Equivalent);
    EXPECT_EQ(Compare(AnyValue{SignedInteger8Type, -120},
                      AnyValue{SignedInteger64Type, int64(-120ll)}), CompareResult::Equivalent);
    EXPECT_EQ(Compare(AnyValue{SignedInteger8Type, 122},
                      AnyValue{SignedInteger8Type, -121}), CompareResult::Greater);
    EXPECT_EQ(Compare(AnyValue{SignedInteger8Type, 127},
                      AnyValue{SignedInteger16Type, 0}), CompareResult::Greater);
    EXPECT_EQ(Compare(AnyValue{SignedInteger64Type, -1000000},
                      AnyValue{SignedInteger32Type, -1000001}), CompareResult::Greater);
    EXPECT_EQ(Compare(AnyValue{SignedInteger8Type, -119},
                      AnyValue{SignedInteger64Type, int64(-20000ll)}), CompareResult::Greater);
  }
}

TEST_F(AnyValueComparisonTests, UnsignedIntegerTypes)
{
  EXPECT_EQ(Compare(AnyValue{UnsignedInteger8Type, 120},
                    AnyValue{UnsignedInteger8Type, 121}), CompareResult::Less);
  EXPECT_EQ(Compare(AnyValue{UnsignedInteger8Type, 120},
                    AnyValue{UnsignedInteger16Type, 30000}), CompareResult::Less);
  EXPECT_EQ(Compare(AnyValue{UnsignedInteger64Type, 120},
                    AnyValue{UnsignedInteger32Type, 1000000}), CompareResult::Less);
  EXPECT_EQ(Compare(AnyValue{UnsignedInteger8Type, 0},
                    AnyValue{UnsignedInteger64Type, int64(4000000000ll)}), CompareResult::Less);
  EXPECT_EQ(Compare(AnyValue{UnsignedInteger8Type, 121},
                    AnyValue{UnsignedInteger8Type, 121}), CompareResult::Equivalent);
  EXPECT_EQ(Compare(AnyValue{UnsignedInteger8Type, 120},
                    AnyValue{UnsignedInteger16Type, 120}), CompareResult::Equivalent);
  EXPECT_EQ(Compare(AnyValue{UnsignedInteger64Type, 0},
                    AnyValue{UnsignedInteger32Type, 0}), CompareResult::Equivalent);
  EXPECT_EQ(Compare(AnyValue{UnsignedInteger8Type, 120},
                    AnyValue{UnsignedInteger64Type, int64(120ll)}), CompareResult::Equivalent);
  EXPECT_EQ(Compare(AnyValue{UnsignedInteger8Type, 122},
                    AnyValue{UnsignedInteger8Type, 121}), CompareResult::Greater);
  EXPECT_EQ(Compare(AnyValue{UnsignedInteger8Type, 127},
                    AnyValue{UnsignedInteger16Type, 0}), CompareResult::Greater);
  EXPECT_EQ(Compare(AnyValue{UnsignedInteger64Type, 1000001},
                    AnyValue{UnsignedInteger32Type, 1000000}), CompareResult::Greater);
  EXPECT_EQ(Compare(AnyValue{UnsignedInteger8Type, 120},
                    AnyValue{UnsignedInteger64Type, int64(119ll)}), CompareResult::Greater);
}

TEST_F(AnyValueComparisonTests, MixedSignIntegerTypes)
{
  // mixed int8 and uint8
  EXPECT_EQ(Compare(AnyValue{SignedInteger8Type, -1},
                    AnyValue{UnsignedInteger8Type, 0}), CompareResult::Less);
  EXPECT_EQ(Compare(AnyValue{SignedInteger8Type, std::numeric_limits<sup::dto::int8>::min()},
                    AnyValue{UnsignedInteger8Type, 4}), CompareResult::Less);
  EXPECT_EQ(Compare(AnyValue{SignedInteger8Type, std::numeric_limits<sup::dto::int8>::max()},
                    AnyValue{UnsignedInteger8Type, std::numeric_limits<sup::dto::uint8>::min()}),
                    CompareResult::Greater);
  EXPECT_EQ(Compare(AnyValue{SignedInteger8Type, std::numeric_limits<sup::dto::int8>::max()},
                    AnyValue{UnsignedInteger8Type, std::numeric_limits<sup::dto::uint8>::max()}),
                    CompareResult::Less);
  // mixed int16 and uint32
  EXPECT_EQ(Compare(AnyValue{SignedInteger16Type, -1},
                    AnyValue{UnsignedInteger32Type, 0}), CompareResult::Less);
  EXPECT_EQ(Compare(AnyValue{SignedInteger16Type, std::numeric_limits<sup::dto::int16>::min()},
                    AnyValue{UnsignedInteger32Type, 4}), CompareResult::Less);
  EXPECT_EQ(Compare(AnyValue{SignedInteger16Type, std::numeric_limits<sup::dto::int16>::max()},
                    AnyValue{UnsignedInteger32Type, std::numeric_limits<sup::dto::uint32>::min()}),
                    CompareResult::Greater);
  EXPECT_EQ(Compare(AnyValue{SignedInteger16Type, std::numeric_limits<sup::dto::int16>::max()},
                    AnyValue{UnsignedInteger32Type, std::numeric_limits<sup::dto::uint32>::max()}),
                    CompareResult::Less);
  // mixed int64 and uint32
  EXPECT_EQ(Compare(AnyValue{SignedInteger64Type, -1},
                    AnyValue{UnsignedInteger32Type, 0}), CompareResult::Less);
  EXPECT_EQ(Compare(AnyValue{SignedInteger64Type, std::numeric_limits<sup::dto::int64>::min()},
                    AnyValue{UnsignedInteger32Type, 4}), CompareResult::Less);
  EXPECT_EQ(Compare(AnyValue{SignedInteger64Type, std::numeric_limits<sup::dto::int64>::max()},
                    AnyValue{UnsignedInteger32Type, std::numeric_limits<sup::dto::uint32>::min()}),
                    CompareResult::Greater);
  EXPECT_EQ(Compare(AnyValue{SignedInteger64Type, std::numeric_limits<sup::dto::int64>::max()},
                    AnyValue{UnsignedInteger32Type, std::numeric_limits<sup::dto::uint32>::max()}),
                    CompareResult::Greater);
  // mixed uint64 and int32
  EXPECT_EQ(Compare(AnyValue{UnsignedInteger64Type, 0},
                    AnyValue{SignedInteger32Type, -1}), CompareResult::Greater);
  EXPECT_EQ(Compare(AnyValue{UnsignedInteger64Type, std::numeric_limits<sup::dto::uint64>::min()},
                    AnyValue{SignedInteger32Type, 4}), CompareResult::Less);
  EXPECT_EQ(Compare(AnyValue{UnsignedInteger64Type, std::numeric_limits<sup::dto::uint64>::max()},
                    AnyValue{SignedInteger32Type, std::numeric_limits<sup::dto::int32>::min()}),
                    CompareResult::Greater);
  EXPECT_EQ(Compare(AnyValue{UnsignedInteger64Type, std::numeric_limits<sup::dto::uint64>::max()},
                    AnyValue{SignedInteger32Type, std::numeric_limits<sup::dto::int32>::max()}),
                    CompareResult::Greater);
  // mixed uint16 and int32
  EXPECT_EQ(Compare(AnyValue{UnsignedInteger16Type, 0},
                    AnyValue{SignedInteger32Type, -1}), CompareResult::Greater);
  EXPECT_EQ(Compare(AnyValue{UnsignedInteger16Type, std::numeric_limits<sup::dto::uint16>::min()},
                    AnyValue{SignedInteger32Type, 4}), CompareResult::Less);
  EXPECT_EQ(Compare(AnyValue{UnsignedInteger16Type, std::numeric_limits<sup::dto::uint16>::max()},
                    AnyValue{SignedInteger32Type, std::numeric_limits<sup::dto::int32>::min()}),
                    CompareResult::Greater);
  EXPECT_EQ(Compare(AnyValue{UnsignedInteger16Type, std::numeric_limits<sup::dto::uint16>::max()},
                    AnyValue{SignedInteger32Type, std::numeric_limits<sup::dto::int32>::max()}),
                    CompareResult::Less);
}

AnyValueComparisonTests::AnyValueComparisonTests() = default;

AnyValueComparisonTests::~AnyValueComparisonTests() = default;
