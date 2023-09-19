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
 * Copyright (c) : 2010-2023 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include "anyvalue_meta.h"

#include <gtest/gtest.h>

#include <sup/dto/anyvalue.h>

using namespace sup::dto;

TEST(AnyValueAssignTest, Structures)
{
  const std::string nested_name = "nested_struct";
  AnyValue two_scalars = {{
    {"signed", {SignedInteger8Type, 1}},
    {"unsigned", {UnsignedInteger8Type, 12}}
  }};
  AnyValue nested_val{{
    {"scalars", two_scalars},
    {"single", {
      {"first", {SignedInteger8Type, 0}},
      {"second", {SignedInteger8Type, 5}}
    }}
  }, nested_name};
  AnyValue copy = nested_val;
  EXPECT_EQ(copy, nested_val);
  AnyValue scalar{UnsignedInteger64Type, 2u};
  EXPECT_NE(scalar, nested_val);
  EXPECT_NO_THROW(scalar = copy);
  EXPECT_EQ(scalar, nested_val);
  EXPECT_NO_THROW(nested_val["scalars.signed"] = AnyValue(SignedInteger32Type, -1));
  EXPECT_NE(copy, nested_val);
  EXPECT_EQ(scalar, copy);
  EXPECT_NO_THROW(copy["single"].AddMember("third", {SignedInteger8Type, 10}));
  EXPECT_NE(scalar, copy);
}

TEST(AnyValueAssignTest, Arrays)
{
  AnyValue two_scalars = {{
    {"signed", {SignedInteger8Type, 1}},
    {"unsigned", {UnsignedInteger8Type, 12}}
  }};
  AnyValue array_val = ArrayValue({two_scalars, two_scalars});
  AnyValue copy = array_val;
  EXPECT_EQ(copy, array_val);
  AnyValue scalar{UnsignedInteger64Type, 2u};
  EXPECT_NE(scalar, array_val);
  EXPECT_NO_THROW(scalar = copy);
  EXPECT_EQ(scalar, array_val);
  // Assigment works if the value can be converted:
  EXPECT_NO_THROW(array_val["[1].signed"] = AnyValue(SignedInteger32Type, -1));
  EXPECT_THROW(array_val["[0].unsigned"] = AnyValue{}, InvalidConversionException);
  EXPECT_NE(copy, array_val);
  EXPECT_EQ(copy.GetType(), array_val.GetType());
  EXPECT_THROW(copy["[0]"].AddMember("third", {SignedInteger8Type, 10}), InvalidOperationException);
}
