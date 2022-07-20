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

#include "test_config.h"

#include <sup/dto/anytype.h>
#include <sup/dto/anytype_helper.h>
#include <sup/dto/anyvalue.h>
#include <sup/dto/anyvalue_helper.h>

#include <fstream>

using namespace sup::dto;

static std::string GetLocalFilename(const std::string& filename);

class JSONFileTest : public ::testing::Test
{
protected:
  JSONFileTest();
  virtual ~JSONFileTest();
};

TEST_F(JSONFileTest, AnyTypeToFromFile)
{
  AnyType simple_struct_type({
    {"id", StringType},
    {"number", UnsignedInteger64Type}
  });
  AnyType array_of_struct_type(4, simple_struct_type);
  AnyType complex_struct_type({
    {"array", array_of_struct_type},
    {"nested", simple_struct_type},
    {"validated", BooleanType}
  });
  auto filename = GetLocalFilename("complex_struct_type.json");
  EXPECT_NO_THROW(AnyTypeToJSONFile(complex_struct_type, filename));
  auto parsed_type = AnyTypeFromJSONFile(filename);
  EXPECT_EQ(parsed_type, complex_struct_type);

  auto filename_pretty = GetLocalFilename("complex_struct_type_pretty.json");
  EXPECT_NO_THROW(AnyTypeToJSONFile(complex_struct_type, filename_pretty, true));
  auto parsed_type_pretty = AnyTypeFromJSONFile(filename_pretty);
  EXPECT_EQ(parsed_type_pretty, complex_struct_type);
}

TEST_F(JSONFileTest, AnyValueToFromFile)
{
  AnyType simple_struct_type({
    {"id", StringType},
    {"number", UnsignedInteger64Type}
  });
  AnyType array_of_struct_type(2, simple_struct_type);
  AnyType complex_struct_type({
    {"array", array_of_struct_type},
    {"nested", simple_struct_type},
    {"validated", BooleanType}
  });
  AnyValue complex_struct_val(complex_struct_type);
  complex_struct_val["array[1].id"] = "second_id";
  complex_struct_val["array[0].number"] = 23;
  complex_struct_val["validated"] = false;

  auto filename = GetLocalFilename("complex_struct_value.json");
  EXPECT_NO_THROW(AnyValueToJSONFile(complex_struct_val, filename));
  auto parsed_value = AnyValueFromJSONFile(filename);
  EXPECT_EQ(parsed_value, complex_struct_val);

  auto filename_pretty = GetLocalFilename("complex_struct_value_pretty.json");
  EXPECT_NO_THROW(AnyValueToJSONFile(complex_struct_val, filename_pretty, true));
  auto parsed_value_pretty = AnyValueFromJSONFile(filename_pretty);
  EXPECT_EQ(parsed_value_pretty, complex_struct_val);
}

TEST_F(JSONFileTest, FailureToOpenFile)
{
  // Using a directory name as filename
  auto filename_dir = testconfig::CMakeBinaryDir();
  AnyType test_type({
    {"id", StringType},
    {"number", UnsignedInteger64Type}
  });
  AnyValue test_value(test_type);
  EXPECT_THROW(AnyTypeToJSONFile(test_type, filename_dir), SerializeException);
  EXPECT_THROW(AnyValueToJSONFile(test_value, filename_dir), SerializeException);
  EXPECT_THROW(AnyTypeFromJSONFile(filename_dir), ParseException);
  EXPECT_THROW(AnyValueFromJSONFile(filename_dir), ParseException);
}

JSONFileTest::JSONFileTest() = default;

JSONFileTest::~JSONFileTest() = default;

static std::string GetLocalFilename(const std::string& filename)
{
  std::string result = testconfig::CMakeBinaryDir() + "/" + filename;
  return result;
}
