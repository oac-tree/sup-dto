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
    std::stack<AbstractComposerComponent::component_t> stack;
    stack.push(std::unique_ptr<T>(new T((args)...)));
    return CanAddValueComponent(stack);
  }

  template <typename T, typename... Args>
  void ValidateCompletedValueComponent(Args&&... args)
  {
    std::stack<AbstractComposerComponent::component_t> stack;
    stack.push(std::unique_ptr<T>(new T((args)...)));
    ValidateIfValueComponentIsComplete(stack);
  }
};

//! Unit tests for CanAddValueComponent utility function.

TEST_F(AnyValueComposerHelperTests, CanAddValueComponent)
{
  {  // it is possible to add value node to empty stack
    std::stack<AbstractComposerComponent::component_t> stack;
    EXPECT_TRUE(CanAddValueComponent(stack));
  }

  // it is possible to add value node if the last node is one of the following
  EXPECT_TRUE(CheckAddValueComponent<StartFieldComposerComponent>("name"));
  EXPECT_TRUE(CheckAddValueComponent<StartArrayElementComposerComponent>());

  // it is not possible to add value node if the last node in the stack is one of the following
  EXPECT_FALSE(CheckAddValueComponent<StartStructComposerComponent>("name"));
  EXPECT_FALSE(CheckAddValueComponent<StartArrayComposerComponent>("name"));
  EXPECT_FALSE(CheckAddValueComponent<EndStructComposerComponent>());
  EXPECT_FALSE(CheckAddValueComponent<EndArrayComposerComponent>());
  EXPECT_FALSE(CheckAddValueComponent<EndFieldComposerComponent>());
  EXPECT_FALSE(CheckAddValueComponent<EndArrayElementComposerComponent>());
}

//! Unit tests for ValidateAddValueComponent utility function.

TEST_F(AnyValueComposerHelperTests, ValidateAddValueComponent)
{
  {  // it is possible to add value node to empty stack
    std::stack<AbstractComposerComponent::component_t> stack;
    EXPECT_NO_THROW(ValidateAddValueComponent(stack));
  }

  {  // it is not possible to add value node if stack contains StartStructComposerComponent
    std::stack<AbstractComposerComponent::component_t> stack;
    stack.push(
        std::unique_ptr<StartStructComposerComponent>(new StartStructComposerComponent("name")));
    EXPECT_THROW(ValidateAddValueComponent(stack), std::runtime_error);
  }

  // More tests above in CanAddValueComponent::CanAddValueComponent.
}

//! Unit tests for ValidateLastComponent utility function.

TEST_F(AnyValueComposerHelperTests, ValidateLastComponent)
{
  std::stack<AbstractComposerComponent::component_t> stack;
  EXPECT_THROW(ValidateLastComponent(stack, AbstractComposerComponent::Type::kStartArray),
               std::runtime_error);

  stack.push(
      std::unique_ptr<StartStructComposerComponent>(new StartStructComposerComponent("name")));
  EXPECT_NO_THROW(ValidateLastComponent(stack, AbstractComposerComponent::Type::kStartStruct));
  EXPECT_THROW(ValidateLastComponent(stack, AbstractComposerComponent::Type::kStartArray),
               std::runtime_error);
}

//! Unit tests for ValidateIfValueComponentIsComplete utility function.

TEST_F(AnyValueComposerHelperTests, ValidateIfValueComponentIsComplete)
{
  std::stack<AbstractComposerComponent::component_t> stack;
  EXPECT_THROW(ValidateIfValueComponentIsComplete(stack), std::runtime_error);

  EXPECT_NO_THROW(CheckAddValueComponent<EndStructComposerComponent>());
  EXPECT_NO_THROW(CheckAddValueComponent<EndArrayComposerComponent>());
}
