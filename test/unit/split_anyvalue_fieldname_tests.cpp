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
#include <sup/dto/anyvalue_exceptions.h>

using namespace sup::dto;

class SplitAnyValueFieldnameTest : public ::testing::Test
{
protected:
  SplitAnyValueFieldnameTest() = default;
  ~SplitAnyValueFieldnameTest() = default;
};

TEST_F(SplitAnyValueFieldnameTest, SingleField)
{
  {
    // Single field denoting struct member
    const std::string fieldname{"name"};
    const std::deque<std::string> expected_names{ "name" };
    auto names = SplitAnyValueFieldname(fieldname);
    ASSERT_EQ(names.size(), 1u);
    EXPECT_EQ(names, expected_names);
  }
  {
    // Single field denoting array element
    const std::string fieldname{"[42]"};
    const std::deque<std::string> expected_names{ "[42]" };
    auto names = SplitAnyValueFieldname(fieldname);
    ASSERT_EQ(names.size(), 1u);
    EXPECT_EQ(names, expected_names);
  }
}

TEST_F(SplitAnyValueFieldnameTest, TwoFieldsOfArrays)
{
  {
    // Array element type of array element type (1)
    const std::string fieldname{"[42][43]"};
    const std::deque<std::string> expected_names{ "[42]", "[43]" };
    auto names = SplitAnyValueFieldname(fieldname);
    ASSERT_EQ(names.size(), 2u);
    EXPECT_EQ(names, expected_names);
  }
  {
    // Array element type of array element type (2)
    const std::string fieldname{"[42].[43]"};
    const std::deque<std::string> expected_names{ "[42]", "[43]" };
    auto names = SplitAnyValueFieldname(fieldname);
    ASSERT_EQ(names.size(), 2u);
    EXPECT_EQ(names, expected_names);
  }
  {
    // Array element type of array element type (3)
    const std::string fieldname{"[42][43]."};
    const std::deque<std::string> expected_names{ "[42]", "[43]" };
    auto names = SplitAnyValueFieldname(fieldname);
    ASSERT_EQ(names.size(), 2u);
    EXPECT_EQ(names, expected_names);
  }
  {
    // Array element type of array element type (4)
    const std::string fieldname{"[42].[43]."};
    const std::deque<std::string> expected_names{ "[42]", "[43]" };
    auto names = SplitAnyValueFieldname(fieldname);
    ASSERT_EQ(names.size(), 2u);
    EXPECT_EQ(names, expected_names);
  }
}

TEST_F(SplitAnyValueFieldnameTest, TwoFieldsOfStructOfArray)
{
  {
    // Array element type of struct member type (1)
    const std::string fieldname{"mem[1729]"};
    const std::deque<std::string> expected_names{ "mem", "[1729]" };
    auto names = SplitAnyValueFieldname(fieldname);
    ASSERT_EQ(names.size(), 2u);
    EXPECT_EQ(names, expected_names);
  }
  {
    // Array element type of struct member type (2)
    const std::string fieldname{"mem[1729]."};
    const std::deque<std::string> expected_names{ "mem", "[1729]" };
    auto names = SplitAnyValueFieldname(fieldname);
    ASSERT_EQ(names.size(), 2u);
    EXPECT_EQ(names, expected_names);
  }
  {
    // Array element type of struct member type (3)
    const std::string fieldname{"mem.[1729]"};
    const std::deque<std::string> expected_names{ "mem", "[1729]" };
    auto names = SplitAnyValueFieldname(fieldname);
    ASSERT_EQ(names.size(), 2u);
    EXPECT_EQ(names, expected_names);
  }
  {
    // Array element type of struct member type (4)
    const std::string fieldname{"mem.[1729]."};
    const std::deque<std::string> expected_names{ "mem", "[1729]" };
    auto names = SplitAnyValueFieldname(fieldname);
    ASSERT_EQ(names.size(), 2u);
    EXPECT_EQ(names, expected_names);
  }
}

TEST_F(SplitAnyValueFieldnameTest, TwoFieldsOfArrayOfStruct)
{
  {
    // Struct member type of array element type (1)
    const std::string fieldname{"[0]mem"};
    const std::deque<std::string> expected_names{ "[0]", "mem" };
    auto names = SplitAnyValueFieldname(fieldname);
    ASSERT_EQ(names.size(), 2u);
    EXPECT_EQ(names, expected_names);
  }
  {
    // Struct member type of array element type (2)
    const std::string fieldname{"[0].mem"};
    const std::deque<std::string> expected_names{ "[0]", "mem" };
    auto names = SplitAnyValueFieldname(fieldname);
    ASSERT_EQ(names.size(), 2u);
    EXPECT_EQ(names, expected_names);
  }
  {
    // Fieldname can never start with .
    const std::string fieldname{".[0]mem"};
    EXPECT_THROW(SplitAnyValueFieldname(fieldname), InvalidOperationException);
  }
}

TEST_F(SplitAnyValueFieldnameTest, TwoFieldsOfStructOfStruct)
{
  {
    // Struct member type of struct member type
    const std::string fieldname{"mem1.mem2"};
    const std::deque<std::string> expected_names{ "mem1", "mem2" };
    auto names = SplitAnyValueFieldname(fieldname);
    ASSERT_EQ(names.size(), 2u);
    EXPECT_EQ(names, expected_names);
  }
  {
    // Fieldname can never start with .
    const std::string fieldname{".mem1.mem2"};
    EXPECT_THROW(SplitAnyValueFieldname(fieldname), InvalidOperationException);
  }
  {
    // Fieldname can never end with (unless the end is "[].")
    const std::string fieldname{"mem1.mem2."};
    EXPECT_THROW(SplitAnyValueFieldname(fieldname), InvalidOperationException);
  }
  {
    // Fieldname can never have a first part that contains ']'
    const std::string fieldname{"mem].mem2"};
    EXPECT_THROW(SplitAnyValueFieldname(fieldname), InvalidOperationException);
  }
}

TEST_F(SplitAnyValueFieldnameTest, ComplexNestedNames)
{
  {
    // variation 1
    const std::string fieldname{"[1].mem1[0].mem2.mem3.[42]"};
    const std::deque<std::string> expected_names{ "[1]", "mem1", "[0]", "mem2", "mem3", "[42]" };
    auto names = SplitAnyValueFieldname(fieldname);
    ASSERT_EQ(names.size(), 6u);
    EXPECT_EQ(names, expected_names);
  }
  {
    // variation 2
    const std::string fieldname{"[1]mem1[0]mem2.mem3[42]."};
    const std::deque<std::string> expected_names{ "[1]", "mem1", "[0]", "mem2", "mem3", "[42]" };
    auto names = SplitAnyValueFieldname(fieldname);
    ASSERT_EQ(names.size(), 6u);
    EXPECT_EQ(names, expected_names);
  }
}

TEST_F(SplitAnyValueFieldnameTest, Exceptions)
{
  {
    // Empty fieldname
    const std::string fieldname{};
    EXPECT_THROW(SplitAnyValueFieldname(fieldname), InvalidOperationException);
  }
  {
    // Fieldname contains unpaired '['
    const std::string fieldname{"a[h"};
    EXPECT_THROW(SplitAnyValueFieldname(fieldname), InvalidOperationException);
  }
  {
    // Fieldname starts with ]
    const std::string fieldname{"]rest"};
    EXPECT_THROW(SplitAnyValueFieldname(fieldname), InvalidOperationException);
  }
  {
    // ] is not paired with [
    const std::string fieldname{"a]h"};
    EXPECT_THROW(SplitAnyValueFieldname(fieldname), InvalidOperationException);
  }
  {
    // fieldname starts with .
    const std::string fieldname{".rest"};
    EXPECT_THROW(SplitAnyValueFieldname(fieldname), InvalidOperationException);
  }
  {
    // fieldname ends with .
    const std::string fieldname{"rest."};
    EXPECT_THROW(SplitAnyValueFieldname(fieldname), InvalidOperationException);
  }
  {
    // fieldname is index that cannot be parsed (1)
    const std::string fieldname{"[]"};
    EXPECT_THROW(SplitAnyValueFieldname(fieldname), InvalidOperationException);
  }
  {
    // fieldname is index that cannot be parsed (2)
    const std::string fieldname{"[one]"};
    EXPECT_THROW(SplitAnyValueFieldname(fieldname), InvalidOperationException);
  }
  {
    // fieldname is index that cannot be parsed (3)
    const std::string fieldname{"mem[]"};
    EXPECT_THROW(SplitAnyValueFieldname(fieldname), InvalidOperationException);
  }
  {
    // fieldname is index that cannot be parsed (4)
    const std::string fieldname{"mem[one]"};
    EXPECT_THROW(SplitAnyValueFieldname(fieldname), InvalidOperationException);
  }
  {
    // fieldname is index that cannot be parsed (5)
    const std::string fieldname{"[3 ]"};
    EXPECT_THROW(SplitAnyValueFieldname(fieldname), InvalidOperationException);
  }
  {
    // fieldname is index that cannot be parsed (6)
    const std::string fieldname{"[3b]"};
    EXPECT_THROW(SplitAnyValueFieldname(fieldname), InvalidOperationException);
  }
}
