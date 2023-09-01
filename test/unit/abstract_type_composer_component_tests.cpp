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

#include "sup/dto/composer/abstract_type_composer_component.h"

#include <sup/dto/anyvalue_exceptions.h>

#include <gtest/gtest.h>

using namespace sup::dto;

class AbstractTypeComposerComponentTests : public ::testing::Test
{
public:
  class TestComponent : public AbstractTypeComposerComponent
  {
  public:
    TestComponent() = default;
    TestComponent(sup::dto::AnyType&& anytype) : AbstractTypeComposerComponent(std::move(anytype)) {}

    Type GetComponentType() const override { return Type::kLeafType; }
    bool Process(std::stack<component_t>&) override { return false; }
  };
};

//! Checking initial state of TestComponent class.
TEST_F(AbstractTypeComposerComponentTests, InitialState)
{
  TestComponent node;
  EXPECT_TRUE(node.GetFieldName().empty());

  std::stack<AbstractTypeComposerComponent::component_t> stack;
  EXPECT_FALSE(node.Process(stack));

  EXPECT_THROW(node.AddMember("name", sup::dto::EmptyType), sup::dto::ParseException);
  EXPECT_THROW(node.AddElement(sup::dto::EmptyType), sup::dto::ParseException);
}

TEST_F(AbstractTypeComposerComponentTests, MoveAnyType)
{
  TestComponent node{sup::dto::AnyType{sup::dto::SignedInteger32Type}};

  auto result = node.MoveAnyType();

  sup::dto::AnyType expected{sup::dto::SignedInteger32Type};
  EXPECT_EQ(result, expected);
}

TEST_F(AbstractTypeComposerComponentTests, SetFieldName)
{
  TestComponent node;
  node.SetFieldName("field_name");
  EXPECT_EQ(node.GetFieldName(), std::string("field_name"));
}
