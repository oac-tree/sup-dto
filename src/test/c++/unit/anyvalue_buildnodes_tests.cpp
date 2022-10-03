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

#include "sup/dto/builder/anyvalue_buildnodes.h"

#include <gtest/gtest.h>

using namespace sup::dto;

//! Tests for classes in anyvalue_

class AnyValueBuildNodesTests : public ::testing::Test
{
};

TEST_F(AnyValueBuildNodesTests, AnyValueBuildNodeProcess)
{
  AnyValueBuildNode node(sup::dto::AnyValue{sup::dto::SignedInteger32Type, 42});
  EXPECT_EQ(node.GetNodeType(), AbstractComposerComponent::NodeType::kValue);

  // processing empty stack
  std::stack<AbstractComposerComponent::node_t> stack;
  EXPECT_TRUE(node.Process(stack));

  // processing stack containing another value
  stack.push(std::unique_ptr<AnyValueBuildNode>(
      new AnyValueBuildNode(sup::dto::AnyValue{sup::dto::SignedInteger32Type, 42})));
  EXPECT_THROW(node.Process(stack), std::runtime_error);

  // processing stack containing a field
  stack.push(std::unique_ptr<StartFieldBuildNode>(new StartFieldBuildNode("field_name")));
  EXPECT_TRUE(node.Process(stack));

  // expected value
  sup::dto::AnyValue expected{sup::dto::SignedInteger32Type, 42};
  auto result = node.MoveAnyValue();
  EXPECT_EQ(result, expected);
}

TEST_F(AnyValueBuildNodesTests, StartStructBuildNodeProcess)
{
  StartStructBuildNode node("struct_name");
  EXPECT_EQ(node.GetNodeType(), AbstractComposerComponent::NodeType::kStartStruct);

  // processing empty stack
  std::stack<AbstractComposerComponent::node_t> stack;
  EXPECT_TRUE(node.Process(stack));

  // processing stack containing another struct
  stack.push(std::unique_ptr<StartStructBuildNode>(new StartStructBuildNode(std::string())));
  EXPECT_THROW(node.Process(stack), std::runtime_error);

  // processing stack containing a field
  stack.push(std::unique_ptr<StartFieldBuildNode>(new StartFieldBuildNode("field_name")));
  EXPECT_TRUE(node.Process(stack));

  // expected value
  auto expected = ::sup::dto::EmptyStruct("struct_name");
  auto result = node.MoveAnyValue();
  EXPECT_EQ(result, expected);
}

TEST_F(AnyValueBuildNodesTests, StartStructBuildNodeProcessAddMember)
{
  StartStructBuildNode node("struct_name");

  // adding a field to struct
  EXPECT_NO_THROW(
      node.AddMember("field_name", sup::dto::AnyValue{sup::dto::SignedInteger32Type, 42}));

  // expected value
  sup::dto::AnyValue expected_anyvalue = {{{"field_name", {sup::dto::SignedInteger32Type, 42}}},
                                          "struct_name"};
  auto result = node.MoveAnyValue();
  EXPECT_EQ(result, expected_anyvalue);
}

TEST_F(AnyValueBuildNodesTests, StartFieldBuildNodeProcess)
{
  StartFieldBuildNode node("field_name");
  EXPECT_EQ(node.GetFieldName(), std::string("field_name"));
  EXPECT_EQ(node.GetNodeType(), AbstractComposerComponent::NodeType::kStartField);

  // processing of empty stack is not allowed
  std::stack<AbstractComposerComponent::node_t> stack;
  EXPECT_THROW(node.Process(stack), std::runtime_error);

  // stack is possible to process if it contains StartStructBuildNode
  stack.push(std::unique_ptr<StartStructBuildNode>(new StartStructBuildNode(std::string())));
  EXPECT_TRUE(node.Process(stack));

  // field name should be set
  node.SetFieldName("");
  EXPECT_THROW(node.Process(stack), std::runtime_error);
}

TEST_F(AnyValueBuildNodesTests, EndFieldBuildNodeProcess)
{
  EndFieldBuildNode node;
  EXPECT_EQ(node.GetNodeType(), AbstractComposerComponent::NodeType::kEndField);

  {
    // processing of empty stack is not allowed
    std::stack<AbstractComposerComponent::node_t> stack;
    EXPECT_THROW(node.Process(stack), std::runtime_error);
  }

  {
    std::stack<AbstractComposerComponent::node_t> stack;
    stack.push(std::unique_ptr<StartStructBuildNode>(new StartStructBuildNode("struct_name")));
    stack.push(std::unique_ptr<StartFieldBuildNode>(new StartFieldBuildNode("field_name")));
    stack.push(std::unique_ptr<AnyValueBuildNode>(
        new AnyValueBuildNode(sup::dto::AnyValue{sup::dto::SignedInteger32Type, 42})));

    EXPECT_FALSE(node.Process(stack));

    EXPECT_EQ(stack.size(), 1);

    sup::dto::AnyValue expected_anyvalue = {{{"field_name", {sup::dto::SignedInteger32Type, 42}}},
                                            "struct_name"};
    auto result = stack.top()->MoveAnyValue();
    EXPECT_EQ(result, expected_anyvalue);
  }
}

TEST_F(AnyValueBuildNodesTests, EndStructBuildNodeProcess)
{
  EndStructBuildNode node;
  EXPECT_EQ(node.GetNodeType(), AbstractComposerComponent::NodeType::kEndStruct);

  {  // processing of empty stack is not allowed
    std::stack<AbstractComposerComponent::node_t> stack;
    EXPECT_THROW(node.Process(stack), std::runtime_error);
  }

  {
    std::stack<AbstractComposerComponent::node_t> stack;
    stack.push(std::unique_ptr<StartStructBuildNode>(new StartStructBuildNode("struct_name")));

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

TEST_F(AnyValueBuildNodesTests, StartArrayBuildNodeProcess)
{
  StartArrayBuildNode node("array_name");
  EXPECT_EQ(node.GetNodeType(), AbstractComposerComponent::NodeType::kStartArray);

  // processing empty stack
  std::stack<AbstractComposerComponent::node_t> stack;
  EXPECT_TRUE(node.Process(stack));

  // processing stack containing another struct is not possible
  stack.push(std::unique_ptr<StartStructBuildNode>(new StartStructBuildNode(std::string())));
  EXPECT_THROW(node.Process(stack), std::runtime_error);

  // processing stack containing a field
  stack.push(std::unique_ptr<StartFieldBuildNode>(new StartFieldBuildNode("field_name")));
  EXPECT_TRUE(node.Process(stack));

  // at the beginning, StartArrayBuildNode doesn't contain valid AnyValue since it waits the first
  // element
  auto result = node.MoveAnyValue();
  EXPECT_TRUE(sup::dto::IsEmptyValue(result));
}

//! Testing StartArrayBuildNode::AddElement method.
TEST_F(AnyValueBuildNodesTests, StartArrayBuildNodeAddElement)
{
  StartArrayBuildNode node("array_name");
  EXPECT_EQ(node.GetNodeType(), AbstractComposerComponent::NodeType::kStartArray);

  // adding an element to the array
  EXPECT_NO_THROW(node.AddElement(sup::dto::AnyValue{sup::dto::SignedInteger32Type, 42}));
  EXPECT_NO_THROW(node.AddElement(sup::dto::AnyValue{sup::dto::SignedInteger32Type, 43}));

  auto expected = sup::dto::ArrayValue({{sup::dto::SignedInteger32Type, 42}, 43}, "array_name");
  auto result = node.MoveAnyValue();
  EXPECT_EQ(result, expected);
}

//! Testing StartArrayElementBuildNode and its Process method.
TEST_F(AnyValueBuildNodesTests, StartArrayElementBuildNodeProcess)
{
  StartArrayElementBuildNode node;
  EXPECT_EQ(node.GetNodeType(), AbstractComposerComponent::NodeType::kStartArrayElement);

  // processing of empty stack is not allowed
  std::stack<AbstractComposerComponent::node_t> stack;
  EXPECT_THROW(node.Process(stack), std::runtime_error);

  // stack is possible to process if it contains StartArrayBuildNode
  stack.push(std::unique_ptr<StartArrayBuildNode>(new StartArrayBuildNode(std::string())));
  EXPECT_TRUE(node.Process(stack));
}

//! Testing EndArrayElementBuildNode and its Process method.
TEST_F(AnyValueBuildNodesTests, EndArrayElementBuildNodeProcess)
{
  EndArrayElementBuildNode node;
  EXPECT_EQ(node.GetNodeType(), AbstractComposerComponent::NodeType::kEndArrayElement);

  // processing of empty stack is not allowed
  {
    std::stack<AbstractComposerComponent::node_t> stack;
    EXPECT_THROW(node.Process(stack), std::runtime_error);
  }

  // stack should contains proper nodes for processing
  {
    std::stack<AbstractComposerComponent::node_t> stack;

    stack.push(std::unique_ptr<StartArrayBuildNode>(new StartArrayBuildNode("array_name")));
    stack.push(std::unique_ptr<StartArrayElementBuildNode>(new StartArrayElementBuildNode()));
    stack.push(std::unique_ptr<AnyValueBuildNode>(
        new AnyValueBuildNode(sup::dto::AnyValue{sup::dto::SignedInteger32Type, 42})));

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

TEST_F(AnyValueBuildNodesTests, EndArrayBuildNodeProcess)
{
  EndArrayBuildNode node;
  EXPECT_EQ(node.GetNodeType(), AbstractComposerComponent::NodeType::kEndArray);

  {  // processing of empty stack is not allowed
    std::stack<AbstractComposerComponent::node_t> stack;
    EXPECT_THROW(node.Process(stack), std::runtime_error);
  }

  {
    std::stack<AbstractComposerComponent::node_t> stack;
    stack.push(std::unique_ptr<StartArrayBuildNode>(new StartArrayBuildNode("array_name")));

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
