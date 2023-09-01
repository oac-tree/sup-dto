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

#include "sup/dto/composer/anyvalue_composer_components.h"

#include <gtest/gtest.h>
#include <sup/dto/anyvalue_exceptions.h>

using namespace sup::dto;

//! Tests for classes in anyvalue_

class AnyValueComposerComponentsTests : public ::testing::Test
{
};

TEST_F(AnyValueComposerComponentsTests, ValueComposerComponentProcess)
{
  ValueComposerComponent node(sup::dto::AnyValue{sup::dto::SignedInteger32Type, 42});
  EXPECT_EQ(node.GetComponentType(), AbstractValueComposerComponent::Type::kValue);

  // processing empty stack
  std::stack<AbstractValueComposerComponent::component_t> stack;
  EXPECT_TRUE(node.Process(stack));

  // processing stack containing another value
  stack.push(std::unique_ptr<ValueComposerComponent>(
      new ValueComposerComponent(sup::dto::AnyValue{sup::dto::SignedInteger32Type, 42})));
  EXPECT_THROW(node.Process(stack), sup::dto::ParseException);

  // processing stack containing a field
  stack.push(
      std::unique_ptr<StartFieldValueComposerComponent>(new StartFieldValueComposerComponent("field_name")));
  EXPECT_TRUE(node.Process(stack));

  // expected value
  sup::dto::AnyValue expected{sup::dto::SignedInteger32Type, 42};
  auto result = node.MoveAnyValue();
  EXPECT_EQ(result, expected);
}

TEST_F(AnyValueComposerComponentsTests, StartStructComposerComponentProcess)
{
  StartStructValueComposerComponent node("struct_name");
  EXPECT_EQ(node.GetComponentType(), AbstractValueComposerComponent::Type::kStartStruct);

  // processing empty stack
  std::stack<AbstractValueComposerComponent::component_t> stack;
  EXPECT_TRUE(node.Process(stack));

  // processing stack containing another struct
  stack.push(std::unique_ptr<StartStructValueComposerComponent>(
      new StartStructValueComposerComponent(std::string())));
  EXPECT_THROW(node.Process(stack), sup::dto::ParseException);

  // processing stack containing a field
  stack.push(
      std::unique_ptr<StartFieldValueComposerComponent>(new StartFieldValueComposerComponent("field_name")));
  EXPECT_TRUE(node.Process(stack));

  // expected value
  auto expected = ::sup::dto::EmptyStruct("struct_name");
  auto result = node.MoveAnyValue();
  EXPECT_EQ(result, expected);
}

TEST_F(AnyValueComposerComponentsTests, StartStructBuildNodeProcessAddMember)
{
  StartStructValueComposerComponent node("struct_name");

  // adding a field to struct
  EXPECT_NO_THROW(
      node.AddMember("field_name", sup::dto::AnyValue{sup::dto::SignedInteger32Type, 42}));

  // expected value
  sup::dto::AnyValue expected_anyvalue = {{{"field_name", {sup::dto::SignedInteger32Type, 42}}},
                                          "struct_name"};
  auto result = node.MoveAnyValue();
  EXPECT_EQ(result, expected_anyvalue);
}

TEST_F(AnyValueComposerComponentsTests, StartFieldComposerComponentProcess)
{
  StartFieldValueComposerComponent node("field_name");
  EXPECT_EQ(node.GetFieldName(), std::string("field_name"));
  EXPECT_EQ(node.GetComponentType(), AbstractValueComposerComponent::Type::kStartField);

  // processing of empty stack is not allowed
  std::stack<AbstractValueComposerComponent::component_t> stack;
  EXPECT_THROW(node.Process(stack), sup::dto::ParseException);

  // stack is possible to process if it contains StartStructBuildNode
  stack.push(std::unique_ptr<StartStructValueComposerComponent>(
      new StartStructValueComposerComponent(std::string())));
  EXPECT_TRUE(node.Process(stack));

  // field name should be set
  node.SetFieldName("");
  EXPECT_THROW(node.Process(stack), sup::dto::ParseException);
}

TEST_F(AnyValueComposerComponentsTests, EndFieldComposerComponentProcess)
{
  EndFieldValueComposerComponent node;
  EXPECT_EQ(node.GetComponentType(), AbstractValueComposerComponent::Type::kEndField);

  {
    // processing of empty stack is not allowed
    std::stack<AbstractValueComposerComponent::component_t> stack;
    EXPECT_THROW(node.Process(stack), sup::dto::ParseException);
  }

  {
    std::stack<AbstractValueComposerComponent::component_t> stack;
    stack.push(std::unique_ptr<StartStructValueComposerComponent>(
        new StartStructValueComposerComponent("struct_name")));
    stack.push(std::unique_ptr<StartFieldValueComposerComponent>(
        new StartFieldValueComposerComponent("field_name")));
    stack.push(std::unique_ptr<ValueComposerComponent>(
        new ValueComposerComponent(sup::dto::AnyValue{sup::dto::SignedInteger32Type, 42})));

    EXPECT_FALSE(node.Process(stack));

    EXPECT_EQ(stack.size(), 1);

    sup::dto::AnyValue expected_anyvalue = {{{"field_name", {sup::dto::SignedInteger32Type, 42}}},
                                            "struct_name"};
    auto result = stack.top()->MoveAnyValue();
    EXPECT_EQ(result, expected_anyvalue);
  }
}

TEST_F(AnyValueComposerComponentsTests, EndStructComposerComponentProcess)
{
  EndStructValueComposerComponent node;
  EXPECT_EQ(node.GetComponentType(), AbstractValueComposerComponent::Type::kEndStruct);

  {  // processing of empty stack is not allowed
    std::stack<AbstractValueComposerComponent::component_t> stack;
    EXPECT_THROW(node.Process(stack), sup::dto::ParseException);
  }

  {
    std::stack<AbstractValueComposerComponent::component_t> stack;
    stack.push(std::unique_ptr<StartStructValueComposerComponent>(
        new StartStructValueComposerComponent("struct_name")));

    // as a result of stack processing, the StartStructBuildNode should be removed, it's value
    // consumed
    EXPECT_TRUE(node.Process(stack));
    EXPECT_EQ(stack.size(), 0);

    // expected value
    auto expected = ::sup::dto::EmptyStruct("struct_name");
    auto result = node.MoveAnyValue();
    EXPECT_EQ(result, expected);
  }
}

TEST_F(AnyValueComposerComponentsTests, StartArrayComposerComponentProcess)
{
  StartArrayValueComposerComponent node("array_name");
  EXPECT_EQ(node.GetComponentType(), AbstractValueComposerComponent::Type::kStartArray);

  // processing empty stack
  std::stack<AbstractValueComposerComponent::component_t> stack;
  EXPECT_TRUE(node.Process(stack));

  // processing stack containing another struct is not possible
  stack.push(std::unique_ptr<StartStructValueComposerComponent>(
      new StartStructValueComposerComponent(std::string())));
  EXPECT_THROW(node.Process(stack), sup::dto::ParseException);

  // processing stack containing a field
  stack.push(
      std::unique_ptr<StartFieldValueComposerComponent>(new StartFieldValueComposerComponent("field_name")));
  EXPECT_TRUE(node.Process(stack));

  // at the beginning, StartArrayBuildNode doesn't contain valid AnyValue since it waits the first
  // element
  auto result = node.MoveAnyValue();
  EXPECT_TRUE(sup::dto::IsEmptyValue(result));
}

//! Testing StartArrayBuildNode::AddElement method.
TEST_F(AnyValueComposerComponentsTests, StartArrayBuildNodeAddElement)
{
  StartArrayValueComposerComponent node("array_name");
  EXPECT_EQ(node.GetComponentType(), AbstractValueComposerComponent::Type::kStartArray);

  // adding an element to the array
  EXPECT_NO_THROW(node.AddElement(sup::dto::AnyValue{sup::dto::SignedInteger32Type, 42}));
  EXPECT_NO_THROW(node.AddElement(sup::dto::AnyValue{sup::dto::SignedInteger32Type, 43}));

  auto expected = sup::dto::ArrayValue({{sup::dto::SignedInteger32Type, 42}, 43}, "array_name");
  auto result = node.MoveAnyValue();
  EXPECT_EQ(result, expected);
}

//! Testing StartArrayElementBuildNode and its Process method.
TEST_F(AnyValueComposerComponentsTests, StartArrayElementComposerComponentProcess)
{
  StartArrayElementValueComposerComponent node;
  EXPECT_EQ(node.GetComponentType(), AbstractValueComposerComponent::Type::kStartArrayElement);

  // processing of empty stack is not allowed
  std::stack<AbstractValueComposerComponent::component_t> stack;
  EXPECT_THROW(node.Process(stack), sup::dto::ParseException);

  // stack is possible to process if it contains StartArrayBuildNode
  stack.push(
      std::unique_ptr<StartArrayValueComposerComponent>(new StartArrayValueComposerComponent(std::string())));
  EXPECT_TRUE(node.Process(stack));
}

//! Testing EndArrayElementBuildNode and its Process method.
TEST_F(AnyValueComposerComponentsTests, EndArrayElementComposerComponentProcess)
{
  EndArrayElementValueComposerComponent node;
  EXPECT_EQ(node.GetComponentType(), AbstractValueComposerComponent::Type::kEndArrayElement);

  // processing of empty stack is not allowed
  {
    std::stack<AbstractValueComposerComponent::component_t> stack;
    EXPECT_THROW(node.Process(stack), sup::dto::ParseException);
  }

  // stack should contains proper nodes for processing
  {
    std::stack<AbstractValueComposerComponent::component_t> stack;

    stack.push(std::unique_ptr<StartArrayValueComposerComponent>(
        new StartArrayValueComposerComponent("array_name")));
    stack.push(std::unique_ptr<StartArrayElementValueComposerComponent>(
        new StartArrayElementValueComposerComponent()));
    stack.push(std::unique_ptr<ValueComposerComponent>(
        new ValueComposerComponent(sup::dto::AnyValue{sup::dto::SignedInteger32Type, 42})));

    // processing should return false since EndArrayElementBuildNode doesn't want to be in the stack
    EXPECT_FALSE(node.Process(stack));

    // stack should contain StartArrayBuildNode
    EXPECT_EQ(stack.size(), 1);

    // expected value should be array with single element
    auto expected = sup::dto::ArrayValue({{sup::dto::SignedInteger32Type, 42}}, "array_name");
    auto result = stack.top()->MoveAnyValue();
    EXPECT_EQ(result, expected);
  }
}

TEST_F(AnyValueComposerComponentsTests, EndArrayComposerComponentProcess)
{
  EndArrayValueComposerComponent node;
  EXPECT_EQ(node.GetComponentType(), AbstractValueComposerComponent::Type::kEndArray);

  {  // processing of empty stack is not allowed
    std::stack<AbstractValueComposerComponent::component_t> stack;
    EXPECT_THROW(node.Process(stack), sup::dto::ParseException);
  }

  {
    std::stack<AbstractValueComposerComponent::component_t> stack;
    stack.push(std::unique_ptr<StartArrayValueComposerComponent>(
        new StartArrayValueComposerComponent("array_name")));

    // as a result of stack processing, the StartStructBuildNode should be removed, it's value
    // consumed
    EXPECT_TRUE(node.Process(stack));
    EXPECT_EQ(stack.size(), 0);

    // as a result we should give empty AnyValues, since array is defined only after the first added
    // element
    auto result = node.MoveAnyValue();
    EXPECT_TRUE(sup::dto::IsEmptyValue(result));
  }
}
