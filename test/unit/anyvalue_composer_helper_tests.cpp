/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : SUP - DTO
 *
 * Description   : Unit test code
 *
 * Author        : Gennady Pospelov (IO)
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

#include "sup/dto/composer/anyvalue_composer_helper.h"

#include <gtest/gtest.h>
#include <sup/dto/composer/anyvalue_composer_components.h>

#include <stdexcept>

using namespace sup::dto;

class AnyValueComposerHelperTests : public ::testing::Test
{
public:
  //! Utility function that creates a stack and put there one build node of given type.
  //! It returns the value reported by CanAddValueNode for this stack.
  template <typename T, typename... Args>
  bool CheckAddValueComponent(Args&&... args)
  {
    std::stack<AbstractValueComposerComponent::component_t> stack;
    stack.push(std::make_unique<T>((args)...));
    return CanAddValueComponent(stack);
  }

  template <typename T, typename... Args>
  void ValidateCompletedValueComponent(Args&&... args)
  {
    std::stack<AbstractValueComposerComponent::component_t> stack;
    stack.push(std::make_unique<T>((args)...));
    ValidateIfValueComponentIsComplete(stack);
  }
};

//! Unit tests for CanAddValueComponent utility function.

TEST_F(AnyValueComposerHelperTests, CanAddValueComponent)
{
  {  // it is possible to add value node to empty stack
    std::stack<AbstractValueComposerComponent::component_t> stack;
    EXPECT_TRUE(CanAddValueComponent(stack));
  }

  // it is possible to add value node if the last node is one of the following
  EXPECT_TRUE(CheckAddValueComponent<StartFieldValueComposerComponent>("name"));
  EXPECT_TRUE(CheckAddValueComponent<StartArrayElementValueComposerComponent>());

  // it is not possible to add value node if the last node in the stack is one of the following
  EXPECT_FALSE(CheckAddValueComponent<StartStructValueComposerComponent>("name"));
  EXPECT_FALSE(CheckAddValueComponent<StartArrayValueComposerComponent>("name"));
  EXPECT_FALSE(CheckAddValueComponent<EndStructValueComposerComponent>());
  EXPECT_FALSE(CheckAddValueComponent<EndArrayValueComposerComponent>());
  EXPECT_FALSE(CheckAddValueComponent<EndFieldValueComposerComponent>());
  EXPECT_FALSE(CheckAddValueComponent<EndArrayElementValueComposerComponent>());
}

//! Unit tests for ValidateAddValueComponent utility function.

TEST_F(AnyValueComposerHelperTests, ValidateAddValueComponent)
{
  {  // it is possible to add value node to empty stack
    std::stack<AbstractValueComposerComponent::component_t> stack;
    EXPECT_NO_THROW(ValidateAddValueComponent(stack));
  }

  {  // it is not possible to add value node if stack contains StartStructValueComposerComponent
    std::stack<AbstractValueComposerComponent::component_t> stack;
    stack.push(std::make_unique<StartStructValueComposerComponent>("name"));
    EXPECT_THROW(ValidateAddValueComponent(stack), sup::dto::ParseException);
  }

  // More tests above in CanAddValueComponent::CanAddValueComponent.
}

//! Unit tests for ValidateLastComponent utility function.

TEST_F(AnyValueComposerHelperTests, ValidateLastComponent)
{
  std::stack<AbstractValueComposerComponent::component_t> stack;
  EXPECT_THROW(ValidateLastComponent(stack, AbstractValueComposerComponent::Type::kStartArray),
               sup::dto::ParseException);

  stack.push(std::make_unique<StartStructValueComposerComponent>("name"));
  EXPECT_NO_THROW(ValidateLastComponent(stack, AbstractValueComposerComponent::Type::kStartStruct));
  EXPECT_THROW(ValidateLastComponent(stack, AbstractValueComposerComponent::Type::kStartArray),
               sup::dto::ParseException);
}

//! Unit tests for ValidateIfValueComponentIsComplete utility function.

TEST_F(AnyValueComposerHelperTests, ValidateIfValueComponentIsComplete)
{
  std::stack<AbstractValueComposerComponent::component_t> stack;
  EXPECT_THROW(ValidateIfValueComponentIsComplete(stack), sup::dto::ParseException);

  EXPECT_NO_THROW(CheckAddValueComponent<EndStructValueComposerComponent>());
  EXPECT_NO_THROW(CheckAddValueComponent<EndArrayValueComposerComponent>());
}
