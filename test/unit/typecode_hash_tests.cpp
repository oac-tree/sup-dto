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

#include <set>

using namespace sup::dto;

class TypeCodeHashTest : public ::testing::Test
{
protected:
  TypeCodeHashTest() = default;
  ~TypeCodeHashTest() = default;
};

TEST_F(TypeCodeHashTest, CheckUniqueness)
{
  // Check uniqueness of TypeCode hashes. Although not strictly necessary, this uniqueness
  // is likely to result in better performance for keys in hash maps
  std::vector<TypeCode> type_codes = {
    TypeCode::Empty, TypeCode::Bool, TypeCode::Char8, TypeCode::Int8, TypeCode::UInt8,
    TypeCode::Int16, TypeCode::UInt16, TypeCode::Int32, TypeCode::UInt32,
    TypeCode::Int64, TypeCode::UInt64, TypeCode::Float32, TypeCode::Float64,
    TypeCode::String, TypeCode::Struct, TypeCode::Array
  };
  std::set<std::size_t> hashes;
  for (const auto& type_code : type_codes)
  {
    hashes.insert(std::hash<TypeCode>{}(type_code));
  }
  EXPECT_EQ(hashes.size(), type_codes.size());
}
