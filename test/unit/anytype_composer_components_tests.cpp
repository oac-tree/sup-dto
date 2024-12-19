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
 * Copyright (c) : 2010-2024 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include "sup/dto/composer/anytype_composer_components.h"

#include <gtest/gtest.h>
#include <sup/dto/anyvalue_exceptions.h>

using namespace sup::dto;

class AnyTypeComposerComponentsTests : public ::testing::Test
{};

TEST_F(AnyTypeComposerComponentsTests, LeafTypeComposerComponent_Process)
{
  LeafTypeComposerComponent node{sup::dto::SignedInteger32Type};
  EXPECT_EQ(node.GetComponentType(), AbstractTypeComposerComponent::Type::kLeafType);

  // processing empty stack
  std::stack<AbstractTypeComposerComponent::component_t> stack;
  EXPECT_TRUE(node.Process(stack));

  // processing stack containing another value
  stack.push(std::make_unique<LeafTypeComposerComponent>(sup::dto::SignedInteger32Type));
  EXPECT_THROW(node.Process(stack), sup::dto::ParseException);

  // processing stack containing a field
  stack.push(std::make_unique<StartFieldTypeComposerComponent>("field_name"));
  EXPECT_TRUE(node.Process(stack));

  // expected type
  sup::dto::AnyType expected{sup::dto::SignedInteger32Type};
  auto result = node.MoveAnyType();
  EXPECT_EQ(result, expected);
}

TEST_F(AnyTypeComposerComponentsTests, StartStructTypeComposerComponent_Process)
{
  StartStructTypeComposerComponent node("struct_name");
  EXPECT_EQ(node.GetComponentType(), AbstractTypeComposerComponent::Type::kStartStruct);

  // processing empty stack
  std::stack<AbstractTypeComposerComponent::component_t> stack;
  EXPECT_TRUE(node.Process(stack));

  // processing stack containing another struct
  stack.push(std::make_unique<StartStructTypeComposerComponent>(std::string()));
  EXPECT_THROW(node.Process(stack), sup::dto::ParseException);

  // processing stack containing a field
  stack.push(std::make_unique<StartFieldTypeComposerComponent>("field_name"));
  EXPECT_TRUE(node.Process(stack));

  // expected type
  auto expected = ::sup::dto::EmptyStructType("struct_name");
  auto result = node.MoveAnyType();
  EXPECT_EQ(result, expected);
}

TEST_F(AnyTypeComposerComponentsTests, StartStructTypeComposerComponent_AddMember)
{
  StartStructTypeComposerComponent node("struct_name");

  // adding a field to struct
  EXPECT_NO_THROW(node.AddMember("field_name", sup::dto::SignedInteger32Type));

  // expected type
  sup::dto::AnyType expected = {{
    {"field_name", sup::dto::SignedInteger32Type}
  }, "struct_name"};
  auto result = node.MoveAnyType();
  EXPECT_EQ(result, expected);
}

TEST_F(AnyTypeComposerComponentsTests, StartFieldTypeComposerComponent_Process)
{
  StartFieldTypeComposerComponent node("field_name");
  EXPECT_EQ(node.GetFieldName(), std::string("field_name"));
  EXPECT_EQ(node.GetComponentType(), AbstractTypeComposerComponent::Type::kStartField);

  // processing of empty stack is not allowed
  std::stack<AbstractTypeComposerComponent::component_t> stack;
  EXPECT_THROW(node.Process(stack), sup::dto::ParseException);

  // stack is possible to process if it contains StartStructTypeComposerComponent
  stack.push(std::make_unique<StartStructTypeComposerComponent>(std::string()));
  EXPECT_TRUE(node.Process(stack));
}

TEST_F(AnyTypeComposerComponentsTests, EndFieldTypeComposerComponent_Process)
{
  EndFieldTypeComposerComponent node;
  EXPECT_EQ(node.GetComponentType(), AbstractTypeComposerComponent::Type::kEndField);
  {
    // processing of empty stack is not allowed
    std::stack<AbstractTypeComposerComponent::component_t> stack;
    EXPECT_THROW(node.Process(stack), sup::dto::ParseException);
  }
  {
    std::stack<AbstractTypeComposerComponent::component_t> stack;
    stack.push(std::make_unique<StartStructTypeComposerComponent>("struct_name"));
    stack.push(std::make_unique<StartFieldTypeComposerComponent>("field_name"));
    stack.push(std::make_unique<LeafTypeComposerComponent>(sup::dto::EmptyType));

    EXPECT_FALSE(node.Process(stack));

    EXPECT_EQ(stack.size(), 1);

    sup::dto::AnyType expected = {{
      {"field_name", sup::dto::EmptyType}
    }, "struct_name"};
    auto result = stack.top()->MoveAnyType();
    EXPECT_EQ(result, expected);
  }
}

TEST_F(AnyTypeComposerComponentsTests, EndStructTypeComposerComponent_Process)
{
  EndStructTypeComposerComponent node;
  EXPECT_EQ(node.GetComponentType(), AbstractTypeComposerComponent::Type::kEndStruct);
  {  // processing of empty stack is not allowed
    std::stack<AbstractTypeComposerComponent::component_t> stack;
    EXPECT_THROW(node.Process(stack), sup::dto::ParseException);
  }
  {
    std::stack<AbstractTypeComposerComponent::component_t> stack;
    stack.push(std::make_unique<StartStructTypeComposerComponent>("struct_name"));

    // as a result of stack processing, the StartStructTypeComposerComponent should be removed and
    // its type consumed
    EXPECT_TRUE(node.Process(stack));
    EXPECT_EQ(stack.size(), 0);

    // expected type
    auto expected = ::sup::dto::EmptyStructType("struct_name");
    auto result = node.MoveAnyType();
    EXPECT_EQ(result, expected);
  }
}

TEST_F(AnyTypeComposerComponentsTests, StartArrayTypeComposerComponent_Process)
{
  StartArrayTypeComposerComponent node("array_name", 4);
  EXPECT_EQ(node.GetComponentType(), AbstractTypeComposerComponent::Type::kStartArray);

  // processing empty stack
  std::stack<AbstractTypeComposerComponent::component_t> stack;
  EXPECT_TRUE(node.Process(stack));

  // processing stack containing another struct is not possible
  stack.push(std::make_unique<StartStructTypeComposerComponent>(std::string()));
  EXPECT_THROW(node.Process(stack), sup::dto::ParseException);

  // processing stack containing a field
  stack.push(std::make_unique<StartFieldTypeComposerComponent>("field_name"));
  EXPECT_TRUE(node.Process(stack));

  // at the beginning, StartArrayTypeComposerComponent doesn't contain valid AnyType since it
  // waits for a single element
  auto result = node.MoveAnyType();
  EXPECT_TRUE(sup::dto::IsEmptyType(result));
}

//! Testing StartArrayTypeComposerComponent_::AddElement method.
TEST_F(AnyTypeComposerComponentsTests, StartArrayTypeComposerComponent_AddElement)
{
  StartArrayTypeComposerComponent node("array_name", 4);
  EXPECT_EQ(node.GetComponentType(), AbstractTypeComposerComponent::Type::kStartArray);

  // adding an element to the array
  EXPECT_NO_THROW(node.AddElement(sup::dto::SignedInteger32Type));
  EXPECT_THROW(node.AddElement(sup::dto::SignedInteger32Type), ParseException);

  auto expected = sup::dto::AnyType(4, sup::dto::SignedInteger32Type, "array_name");
  auto result = node.MoveAnyType();
  EXPECT_EQ(result, expected);
}

//! Testing StartArrayElementTypeComposerComponent and its Process method.
TEST_F(AnyTypeComposerComponentsTests, StartArrayElementTypeComposerComponent_Process)
{
  StartArrayElementTypeComposerComponent node;
  EXPECT_EQ(node.GetComponentType(), AbstractTypeComposerComponent::Type::kStartArrayElement);

  // processing of empty stack is not allowed
  std::stack<AbstractTypeComposerComponent::component_t> stack;
  EXPECT_THROW(node.Process(stack), sup::dto::ParseException);

  // stack is possible to process if it contains StartArrayBuildNode
  stack.push(std::make_unique<StartArrayTypeComposerComponent>(std::string(), 0));
  EXPECT_TRUE(node.Process(stack));
}

//! Testing EndArrayElementTypeComposerComponent and its Process method.
TEST_F(AnyTypeComposerComponentsTests, EndArrayElementTypeComposerComponent_Process)
{
  EndArrayElementTypeComposerComponent node;
  EXPECT_EQ(node.GetComponentType(), AbstractTypeComposerComponent::Type::kEndArrayElement);

  // processing of empty stack is not allowed
  {
    std::stack<AbstractTypeComposerComponent::component_t> stack;
    EXPECT_THROW(node.Process(stack), sup::dto::ParseException);
  }
  // stack should contain proper nodes for processing
  {
    std::stack<AbstractTypeComposerComponent::component_t> stack;

    stack.push(std::make_unique<StartArrayTypeComposerComponent>("array_name", 0));
    stack.push(std::make_unique<StartArrayElementTypeComposerComponent>());
    stack.push(std::make_unique<LeafTypeComposerComponent>(sup::dto::SignedInteger32Type));

    // processing should return false since EndArrayElementTypeComposerComponent doesn't want to be
    // in the stack
    EXPECT_FALSE(node.Process(stack));

    // stack should contain StartArrayTypeComposerComponent
    EXPECT_EQ(stack.size(), 1);

    // expected type should be array with zero elements of type SignedInteger32Type
    auto expected = sup::dto::AnyType(0,sup::dto::SignedInteger32Type, "array_name");
    auto result = stack.top()->MoveAnyType();
    EXPECT_EQ(result, expected);
  }
}

TEST_F(AnyTypeComposerComponentsTests, EndArrayTypeComposerComponent_Process)
{
  EndArrayTypeComposerComponent node;
  EXPECT_EQ(node.GetComponentType(), AbstractTypeComposerComponent::Type::kEndArray);

  {  // processing of empty stack is not allowed
    std::stack<AbstractTypeComposerComponent::component_t> stack;
    EXPECT_THROW(node.Process(stack), sup::dto::ParseException);
  }
  {
    // processing of array without element being defined
    std::stack<AbstractTypeComposerComponent::component_t> stack;
    stack.push(std::make_unique<StartArrayTypeComposerComponent>("array_name", 1));

    // as a result of stack processing, the StartArrayTypeComposerComponent should be removed and
    // its value consumed
    EXPECT_THROW(node.Process(stack), sup::dto::ParseException);
  }
  {
    std::stack<AbstractTypeComposerComponent::component_t> stack;
    stack.push(std::make_unique<StartArrayTypeComposerComponent>("array_name", 1));
    stack.push(std::make_unique<StartArrayElementTypeComposerComponent>());
    stack.push(std::make_unique<LeafTypeComposerComponent>(sup::dto::SignedInteger32Type));
    EndArrayElementTypeComposerComponent end_element_node;
    EXPECT_FALSE(end_element_node.Process(stack));

    // as a result of stack processing, the StartArrayTypeComposerComponent should be removed and
    // its value consumed
    EXPECT_TRUE(node.Process(stack));
    EXPECT_EQ(stack.size(), 0);

    // as a result we should get an array type with one element of type SignedInteger32Type
    auto expected = sup::dto::AnyType(1, sup::dto::SignedInteger32Type, "array_name");
    auto result = node.MoveAnyType();
    EXPECT_EQ(result, expected);
  }
}
