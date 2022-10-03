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

#include "sup/dto/composer/abstract_composer_component.h"

#include <gtest/gtest.h>
#include <sup/dto/anytype.h>
#include <sup/dto/anytype_helper.h>
#include <sup/dto/anyvalue.h>
#include <sup/dto/anyvalue_helper.h>

#include <stdexcept>

using namespace sup::dto;

class AbstractComposerComponentTests : public ::testing::Test
{
public:
  class TestComponent : public AbstractComposerComponent
  {
  public:
    TestComponent() = default;
    TestComponent(sup::dto::AnyValue&& value) : AbstractComposerComponent(std::move(value)) {}

    Type GetComponentType() const override { return Type::kValue; }
    bool Process(std::stack<component_t>&) override { return false; }
  };
};

//! Checking initial state of TestComponent class.

TEST_F(AbstractComposerComponentTests, InitialState)
{
  TestComponent node;
  EXPECT_TRUE(node.GetFieldName().empty());

  std::stack<AbstractComposerComponent::component_t> stack;
  EXPECT_FALSE(node.Process(stack));

  EXPECT_THROW(node.AddMember("name", sup::dto::AnyValue()), std::runtime_error);
  EXPECT_THROW(node.AddElement(sup::dto::AnyValue()), std::runtime_error);
}

TEST_F(AbstractComposerComponentTests, MoveAnyValue)
{
  TestComponent node(sup::dto::AnyValue{sup::dto::SignedInteger32Type, 42});

  auto result = node.MoveAnyValue();

  sup::dto::AnyValue expected{sup::dto::SignedInteger32Type, 42};
  EXPECT_EQ(result, expected);
}

TEST_F(AbstractComposerComponentTests, SetFieldName)
{
  TestComponent node;
  node.SetFieldName("field_name");
  EXPECT_EQ(node.GetFieldName(), std::string("field_name"));
}
