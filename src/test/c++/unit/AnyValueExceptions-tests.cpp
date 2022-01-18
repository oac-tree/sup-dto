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

#include "AnyValueExceptions.h"

using namespace sup::dto;

TEST(AnyValueExceptions, EmptyValue)
{
  std::string message = "Custom message";
  auto exception1 = DuplicateKeyException(message);
  auto exception2 = KeyNotAllowedException(message);
  auto exception3 = EmptyKeyException(message);
  auto exception4 = UnknownKeyException(message);
  auto exception5 = InvalidConversionException(message);
  auto exception6 = InvalidOperationException(message);

  EXPECT_EQ(std::string(exception1.what()), message);
  EXPECT_EQ(std::string(exception2.what()), message);
  EXPECT_EQ(std::string(exception3.what()), message);
  EXPECT_EQ(std::string(exception4.what()), message);
  EXPECT_EQ(std::string(exception5.what()), message);
  EXPECT_EQ(std::string(exception6.what()), message);
}

