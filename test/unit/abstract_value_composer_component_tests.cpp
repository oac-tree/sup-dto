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
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include "sup/dto/composer/abstract_value_composer_component.h"

#include <gtest/gtest.h>
#include <sup/dto/anytype.h>
#include <sup/dto/anytype_helper.h>
#include <sup/dto/anyvalue.h>
#include <sup/dto/anyvalue_helper.h>

#include <sup/dto/anyvalue_exceptions.h>

using namespace sup::dto;

class AbstractValueComposerComponentTests : public ::testing::Test
{
public:
  class TestComponent : public AbstractValueComposerComponent
  {
  public:
    TestComponent() = default;
    TestComponent(sup::dto::AnyValue&& value) : AbstractValueComposerComponent(std::move(value)) {}

    Type GetComponentType() const override { return Type::kValue; }
    bool Process(std::stack<component_t>&) override { return false; }
  };
};

//! Checking initial state of TestComponent class.

TEST_F(AbstractValueComposerComponentTests, InitialState)
{
  TestComponent node;
  EXPECT_TRUE(node.GetFieldName().empty());

  std::stack<AbstractValueComposerComponent::component_t> stack;
  EXPECT_FALSE(node.Process(stack));

  EXPECT_THROW(node.AddMember("name", sup::dto::AnyValue()), sup::dto::ParseException);
  EXPECT_THROW(node.AddElement(sup::dto::AnyValue()), sup::dto::ParseException);
}

TEST_F(AbstractValueComposerComponentTests, MoveAnyValue)
{
  TestComponent node(sup::dto::AnyValue{sup::dto::SignedInteger32Type, 42});

  auto result = node.MoveAnyValue();

  sup::dto::AnyValue expected{sup::dto::SignedInteger32Type, 42};
  EXPECT_EQ(result, expected);
}

TEST_F(AbstractValueComposerComponentTests, SetFieldName)
{
  TestComponent node;
  node.SetFieldName("field_name");
  EXPECT_EQ(node.GetFieldName(), std::string("field_name"));
}
