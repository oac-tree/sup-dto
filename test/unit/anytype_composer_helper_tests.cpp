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

#include "sup/dto/composer/anytype_composer_helper.h"

#include <sup/dto/composer/anytype_composer_components.h>
#include <sup/dto/anyvalue_exceptions.h>

#include <gtest/gtest.h>

using namespace sup::dto;

class AnyTypeComposerHelperTests : public ::testing::Test
{
public:
  //! Utility function that creates a stack and put there one build node of given type.
  //! It returns the value reported by CanAddValueNode for this stack.
  template <typename T, typename... Args>
  bool CheckAddTypeComponent(Args&&... args)
  {
    std::stack<AbstractTypeComposerComponent::component_t> stack;
    stack.push(std::unique_ptr<T>(new T((args)...)));
    return CanAddTypeComponent(stack);
  }

  template <typename T, typename... Args>
  void ValidateCompletedTypeComponent(Args&&... args)
  {
    std::stack<AbstractTypeComposerComponent::component_t> stack;
    stack.push(std::unique_ptr<T>(new T((args)...)));
    ValidateIfTypeComponentIsComplete(stack);
  }
};

//! Unit tests for CanAddTypeComponent utility function.
TEST_F(AnyTypeComposerHelperTests, CanAddTypeComponent)
{
  {  // it is possible to add a type node to an empty stack
    std::stack<AbstractTypeComposerComponent::component_t> stack;
    EXPECT_TRUE(CanAddTypeComponent(stack));
  }

  // it is possible to add value node if the last node is one of the following
  EXPECT_TRUE(CheckAddTypeComponent<StartFieldTypeComposerComponent>("name"));
  EXPECT_TRUE(CheckAddTypeComponent<StartArrayElementTypeComposerComponent>());

  // it is not possible to add value node if the last node in the stack is one of the following
  EXPECT_FALSE(CheckAddTypeComponent<StartStructTypeComposerComponent>("name"));
  EXPECT_FALSE(CheckAddTypeComponent<StartArrayTypeComposerComponent>("name", 2));
  EXPECT_FALSE(CheckAddTypeComponent<EndStructTypeComposerComponent>());
  EXPECT_FALSE(CheckAddTypeComponent<EndArrayTypeComposerComponent>());
  EXPECT_FALSE(CheckAddTypeComponent<EndFieldTypeComposerComponent>());
  EXPECT_FALSE(CheckAddTypeComponent<EndArrayElementTypeComposerComponent>());
}

//! Unit tests for ValidateAddValueComponent utility function.
TEST_F(AnyTypeComposerHelperTests, ValidateAddTypeComponent)
{
  {  // it is possible to add value node to empty stack
    std::stack<AbstractTypeComposerComponent::component_t> stack;
    EXPECT_NO_THROW(ValidateAddTypeComponent(stack));
  }

  {  // it is not possible to add value node if stack contains StartStructTypeComposerComponent
    std::stack<AbstractTypeComposerComponent::component_t> stack;
    stack.push(std::unique_ptr<StartStructTypeComposerComponent>(
      new StartStructTypeComposerComponent("name")));
    EXPECT_THROW(ValidateAddTypeComponent(stack), sup::dto::ParseException);
  }
  // More tests above in CanAddTypeComponent.
}

//! Unit tests for ValidateLastTypeComponent utility function.
TEST_F(AnyTypeComposerHelperTests, ValidateLastTypeComponent)
{
  std::stack<AbstractTypeComposerComponent::component_t> stack;
  EXPECT_THROW(ValidateLastTypeComponent(stack, AbstractTypeComposerComponent::Type::kStartArray),
               sup::dto::ParseException);

  stack.push(std::unique_ptr<StartStructTypeComposerComponent>(
    new StartStructTypeComposerComponent("name")));
  EXPECT_NO_THROW(ValidateLastTypeComponent(
    stack, AbstractTypeComposerComponent::Type::kStartStruct));
  EXPECT_THROW(ValidateLastTypeComponent(stack, AbstractTypeComposerComponent::Type::kStartArray),
               sup::dto::ParseException);
}

//! Unit tests for ValidateIfTypeComponentIsComplete utility function.
TEST_F(AnyTypeComposerHelperTests, ValidateIfTypeComponentIsComplete)
{
  std::stack<AbstractTypeComposerComponent::component_t> stack;
  EXPECT_THROW(ValidateIfTypeComponentIsComplete(stack), sup::dto::ParseException);

  stack.push(std::unique_ptr<StartStructTypeComposerComponent>(
    new StartStructTypeComposerComponent("name")));
  EXPECT_THROW(ValidateIfTypeComponentIsComplete(stack), sup::dto::ParseException);
  stack.push(std::unique_ptr<EndStructTypeComposerComponent>(
    new EndStructTypeComposerComponent()));
  EXPECT_NO_THROW(ValidateIfTypeComponentIsComplete(stack));
}
