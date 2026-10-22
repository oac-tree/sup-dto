/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : SUP - DTO
 *
 * Description   : Data transfer objects for SUP
 *
 * Author        : Walter Van Herck (IO)
 *
 * Copyright (c) : 2010-2026 ITER Organization,
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

// The installed header comes first: it has to be usable on its own.
#include <sup/dto/type_code_helper.h>

#include <sup/dto/anyvalue.h>

#include <gtest/gtest.h>

#include <string>

using namespace sup::dto;

class TypeCodeHelperTest : public ::testing::Test
{
};

// The mapping is available at compile time
static_assert(TypeToCode<boolean>::code == TypeCode::Bool, "boolean");
static_assert(TypeToCode<char8>::code == TypeCode::Char8, "char8");
static_assert(TypeToCode<int8>::code == TypeCode::Int8, "int8");
static_assert(TypeToCode<uint8>::code == TypeCode::UInt8, "uint8");
static_assert(TypeToCode<int16>::code == TypeCode::Int16, "int16");
static_assert(TypeToCode<uint16>::code == TypeCode::UInt16, "uint16");
static_assert(TypeToCode<int32>::code == TypeCode::Int32, "int32");
static_assert(TypeToCode<uint32>::code == TypeCode::UInt32, "uint32");
static_assert(TypeToCode<int64>::code == TypeCode::Int64, "int64");
static_assert(TypeToCode<uint64>::code == TypeCode::UInt64, "uint64");
static_assert(TypeToCode<float32>::code == TypeCode::Float32, "float32");
static_assert(TypeToCode<float64>::code == TypeCode::Float64, "float64");
static_assert(TypeToCode<std::string>::code == TypeCode::String, "string");

// The code of a C++ type is the type code of an AnyValue holding such a value
template <typename T>
void ExpectMatchesAnyValue()
{
  EXPECT_EQ(TypeToCode<T>::code, AnyValue{T{}}.GetTypeCode());
  EXPECT_TRUE(IsScalarTypeCode(TypeToCode<T>::code));
}

TEST_F(TypeCodeHelperTest, TypeToCodeMatchesAnyValue)
{
  ExpectMatchesAnyValue<boolean>();
  ExpectMatchesAnyValue<char8>();
  ExpectMatchesAnyValue<int8>();
  ExpectMatchesAnyValue<uint8>();
  ExpectMatchesAnyValue<int16>();
  ExpectMatchesAnyValue<uint16>();
  ExpectMatchesAnyValue<int32>();
  ExpectMatchesAnyValue<uint32>();
  ExpectMatchesAnyValue<int64>();
  ExpectMatchesAnyValue<uint64>();
  ExpectMatchesAnyValue<float32>();
  ExpectMatchesAnyValue<float64>();
  ExpectMatchesAnyValue<std::string>();
}
