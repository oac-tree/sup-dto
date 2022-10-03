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

#include "sup/dto/composer/anyvalue_buildnode_utils.h"

#include <gtest/gtest.h>
#include <sup/dto/composer/anyvalue_composer_components.h>

#include <stdexcept>

using namespace sup::dto;

class AnyValueBuildNodeUtilsTests : public ::testing::Test
{
public:
  //! Utility function that creates a stack and put there one build node of given type.
  //! It returns the value reported by CanAddValueNode for this stack.
  template <typename T, typename... Args>
  bool CheckAddValueNode(Args&&... args)
  {
    std::stack<AbstractComposerComponent::node_t> stack;
    stack.push(std::unique_ptr<T>(new T((args)...)));
    return CanAddValueNode(stack);
  }

  template <typename T, typename... Args>
  void ValidateCompletedValueNode(Args&&... args)
  {
    std::stack<AbstractComposerComponent::node_t> stack;
    stack.push(std::unique_ptr<T>(new T((args)...)));
    ValidateIfValueNodeIsComplete(stack);
  }
};

//! Unit tests for CanAddValueNode utility function.

TEST_F(AnyValueBuildNodeUtilsTests, CanAddValueNode)
{
  {  // it is possible to add value node to empty stack
    std::stack<AbstractComposerComponent::node_t> stack;
    EXPECT_TRUE(CanAddValueNode(stack));
  }

  // it is possible to add value node if the last node is one of the following
  EXPECT_TRUE(CheckAddValueNode<StartFieldComposerComponent>("name"));
  EXPECT_TRUE(CheckAddValueNode<StartArrayElementComposerComponent>());

  // it is not possible to add value node if the last node in the stack is one of the following
  EXPECT_FALSE(CheckAddValueNode<StartStructComposerComponent>("name"));
  EXPECT_FALSE(CheckAddValueNode<StartArrayComposerComponent>("name"));
  EXPECT_FALSE(CheckAddValueNode<EndStructComposerComponent>());
  EXPECT_FALSE(CheckAddValueNode<EndArrayComposerComponent>());
  EXPECT_FALSE(CheckAddValueNode<EndFieldComposerComponent>());
  EXPECT_FALSE(CheckAddValueNode<EndArrayElementBuildNode>());
}

//! Unit tests for ValidateAddValueNode utility function.

TEST_F(AnyValueBuildNodeUtilsTests, ValidateAddValueNode)
{
  {  // it is possible to add value node to empty stack
    std::stack<AbstractComposerComponent::node_t> stack;
    EXPECT_NO_THROW(ValidateAddValueNode(stack));
  }

  {  // it is not possible to add value node if stack contains StartStructBuildNode
    std::stack<AbstractComposerComponent::node_t> stack;
    stack.push(
        std::unique_ptr<StartStructComposerComponent>(new StartStructComposerComponent("name")));
    EXPECT_THROW(ValidateAddValueNode(stack), std::runtime_error);
  }

  // More tests above in AnyValueBuildNodeUtilsTests::CanAddValueNode.
}

//! Unit tests for ValidateAddValueNode utility function.

TEST_F(AnyValueBuildNodeUtilsTests, ValidateLastNode)
{
  std::stack<AbstractComposerComponent::node_t> stack;
  EXPECT_THROW(ValidateLastNode(stack, AbstractComposerComponent::NodeType::kStartArray),
               std::runtime_error);

  stack.push(
      std::unique_ptr<StartStructComposerComponent>(new StartStructComposerComponent("name")));
  EXPECT_NO_THROW(ValidateLastNode(stack, AbstractComposerComponent::NodeType::kStartStruct));
  EXPECT_THROW(ValidateLastNode(stack, AbstractComposerComponent::NodeType::kStartArray),
               std::runtime_error);
}

//! Unit tests for ValidateIfValueNodeIsComplete utility function.

TEST_F(AnyValueBuildNodeUtilsTests, ValidateIfValueNodeIsComplete)
{
  std::stack<AbstractComposerComponent::node_t> stack;
  EXPECT_THROW(ValidateIfValueNodeIsComplete(stack), std::runtime_error);

  EXPECT_NO_THROW(CheckAddValueNode<EndStructComposerComponent>());
  EXPECT_NO_THROW(CheckAddValueNode<EndArrayComposerComponent>());
}
