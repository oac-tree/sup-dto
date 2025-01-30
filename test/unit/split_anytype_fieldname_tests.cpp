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

#include <sup/dto/anytype.h>
#include <sup/dto/anyvalue_exceptions.h>

using namespace sup::dto;

class SplitAnyTypeFieldnameTest : public ::testing::Test
{
protected:
  SplitAnyTypeFieldnameTest() = default;
  ~SplitAnyTypeFieldnameTest() = default;
};

TEST_F(SplitAnyTypeFieldnameTest, SingleField)
{
  {
    // Single field denoting struct member
    const std::string fieldname{"name"};
    const std::deque<std::string> expected_names{ "name" };
    auto names = SplitAnyTypeFieldname(fieldname);
    ASSERT_EQ(names.size(), 1u);
    EXPECT_EQ(names, expected_names);
  }
  {
    // Single field denoting array element
    const std::string fieldname{"[]"};
    const std::deque<std::string> expected_names{ "[]" };
    auto names = SplitAnyTypeFieldname(fieldname);
    ASSERT_EQ(names.size(), 1u);
    EXPECT_EQ(names, expected_names);
  }
}

TEST_F(SplitAnyTypeFieldnameTest, TwoFieldsOfArrays)
{
  {
    // Array element type of array element type (1)
    const std::string fieldname{"[][]"};
    const std::deque<std::string> expected_names{ "[]", "[]" };
    auto names = SplitAnyTypeFieldname(fieldname);
    ASSERT_EQ(names.size(), 2u);
    EXPECT_EQ(names, expected_names);
  }
  {
    // Array element type of array element type (2)
    const std::string fieldname{"[].[]"};
    const std::deque<std::string> expected_names{ "[]", "[]" };
    auto names = SplitAnyTypeFieldname(fieldname);
    ASSERT_EQ(names.size(), 2u);
    EXPECT_EQ(names, expected_names);
  }
  {
    // Array element type of array element type (3)
    const std::string fieldname{"[][]."};
    const std::deque<std::string> expected_names{ "[]", "[]" };
    auto names = SplitAnyTypeFieldname(fieldname);
    ASSERT_EQ(names.size(), 2u);
    EXPECT_EQ(names, expected_names);
  }
  {
    // Array element type of array element type (4)
    const std::string fieldname{"[].[]."};
    const std::deque<std::string> expected_names{ "[]", "[]" };
    auto names = SplitAnyTypeFieldname(fieldname);
    ASSERT_EQ(names.size(), 2u);
    EXPECT_EQ(names, expected_names);
  }
}

TEST_F(SplitAnyTypeFieldnameTest, TwoFieldsOfStructOfArray)
{
  {
    // Array element type of struct member type (1)
    const std::string fieldname{"mem[]"};
    const std::deque<std::string> expected_names{ "mem", "[]" };
    auto names = SplitAnyTypeFieldname(fieldname);
    ASSERT_EQ(names.size(), 2u);
    EXPECT_EQ(names, expected_names);
  }
  {
    // Array element type of struct member type (2)
    const std::string fieldname{"mem[]."};
    const std::deque<std::string> expected_names{ "mem", "[]" };
    auto names = SplitAnyTypeFieldname(fieldname);
    ASSERT_EQ(names.size(), 2u);
    EXPECT_EQ(names, expected_names);
  }
  {
    // Array element type of struct member type (3)
    const std::string fieldname{"mem.[]"};
    const std::deque<std::string> expected_names{ "mem", "[]" };
    auto names = SplitAnyTypeFieldname(fieldname);
    ASSERT_EQ(names.size(), 2u);
    EXPECT_EQ(names, expected_names);
  }
  {
    // Array element type of struct member type (4)
    const std::string fieldname{"mem.[]."};
    const std::deque<std::string> expected_names{ "mem", "[]" };
    auto names = SplitAnyTypeFieldname(fieldname);
    ASSERT_EQ(names.size(), 2u);
    EXPECT_EQ(names, expected_names);
  }
}

TEST_F(SplitAnyTypeFieldnameTest, TwoFieldsOfArrayOfStruct)
{
  {
    // Struct member type of array element type (1)
    const std::string fieldname{"[]mem"};
    const std::deque<std::string> expected_names{ "[]", "mem" };
    auto names = SplitAnyTypeFieldname(fieldname);
    ASSERT_EQ(names.size(), 2u);
    EXPECT_EQ(names, expected_names);
  }
  {
    // Struct member type of array element type (2)
    const std::string fieldname{"[].mem"};
    const std::deque<std::string> expected_names{ "[]", "mem" };
    auto names = SplitAnyTypeFieldname(fieldname);
    ASSERT_EQ(names.size(), 2u);
    EXPECT_EQ(names, expected_names);
  }
  {
    // Fieldname can never start with .
    const std::string fieldname{".[]mem"};
    EXPECT_THROW(SplitAnyTypeFieldname(fieldname), InvalidOperationException);
  }
}

TEST_F(SplitAnyTypeFieldnameTest, TwoFieldsOfStructOfStruct)
{
  {
    // Struct member type of struct member type
    const std::string fieldname{"mem1.mem2"};
    const std::deque<std::string> expected_names{ "mem1", "mem2" };
    auto names = SplitAnyTypeFieldname(fieldname);
    ASSERT_EQ(names.size(), 2u);
    EXPECT_EQ(names, expected_names);
  }
  {
    // Fieldname can never start with .
    const std::string fieldname{".mem1.mem2"};
    EXPECT_THROW(SplitAnyTypeFieldname(fieldname), InvalidOperationException);
  }
  {
    // Fieldname can never end with (unless the end is "[].")
    const std::string fieldname{"mem1.mem2."};
    EXPECT_THROW(SplitAnyTypeFieldname(fieldname), InvalidOperationException);
  }
}

TEST_F(SplitAnyTypeFieldnameTest, ComplexNestedNames)
{
  {
    // variation 1
    const std::string fieldname{"[].mem1[].mem2.mem3.[]"};
    const std::deque<std::string> expected_names{ "[]", "mem1", "[]", "mem2", "mem3", "[]" };
    auto names = SplitAnyTypeFieldname(fieldname);
    ASSERT_EQ(names.size(), 6u);
    EXPECT_EQ(names, expected_names);
  }
  {
    // variation 2
    const std::string fieldname{"[]mem1[]mem2.mem3[]."};
    const std::deque<std::string> expected_names{ "[]", "mem1", "[]", "mem2", "mem3", "[]" };
    auto names = SplitAnyTypeFieldname(fieldname);
    ASSERT_EQ(names.size(), 6u);
    EXPECT_EQ(names, expected_names);
  }
}

TEST_F(SplitAnyTypeFieldnameTest, Exceptions)
{
  {
    // Empty fieldname
    const std::string fieldname{};
    EXPECT_THROW(SplitAnyTypeFieldname(fieldname), InvalidOperationException);
  }
  {
    // Fieldname contains unpaired '['
    const std::string fieldname{"a[h"};
    EXPECT_THROW(SplitAnyTypeFieldname(fieldname), InvalidOperationException);
  }
  {
    // Fieldname starts with ]
    const std::string fieldname{"]rest"};
    EXPECT_THROW(SplitAnyTypeFieldname(fieldname), InvalidOperationException);
  }
  {
    // ] is not paired with [
    const std::string fieldname{"a]h"};
    EXPECT_THROW(SplitAnyTypeFieldname(fieldname), InvalidOperationException);
  }
  {
    // fieldname starts with .
    const std::string fieldname{".rest"};
    EXPECT_THROW(SplitAnyTypeFieldname(fieldname), InvalidOperationException);
  }
  {
    // fieldname ends with .
    const std::string fieldname{"rest."};
    EXPECT_THROW(SplitAnyTypeFieldname(fieldname), InvalidOperationException);
  }
}
