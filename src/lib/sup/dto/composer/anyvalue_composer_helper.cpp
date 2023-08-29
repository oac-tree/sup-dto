/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : SUP - DTO
 *
 * Description   : Data transfer objects for SUP
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

#include "sup/dto/composer/anyvalue_composer_helper.h"

#include <sup/dto/anyvalue_exceptions.h>

#include <algorithm>
#include <sstream>
#include <vector>

namespace sup
{
namespace dto
{

bool CanAddValueComponent(const std::stack<AbstractComposerComponent::component_t> &stack)
{
  if (stack.empty())
  {
    return true;
  }

  using Type = AbstractComposerComponent::Type;
  static const std::vector<Type> expected_types{Type::kStartArrayElement, Type::kStartField};

  auto it =
      std::find(expected_types.begin(), expected_types.end(), stack.top()->GetComponentType());
  return it != expected_types.end();
}

void ValidateAddValueComponent(const std::stack<AbstractComposerComponent::component_t> &stack)
{
  if (!CanAddValueComponent(stack))
  {
    std::ostringstream ostr;
    ostr << "Error in ValidateAddValueComponent(): component can not be added, ";
    if (stack.empty())
    {
      ostr << "stack is empty.";
    }
    else
    {
      ostr << "last Type=" << static_cast<int>(stack.top()->GetComponentType()) << ".\n";
    }

    throw sup::dto::MessageException(ostr.str());
  }
}

void ValidateLastComponent(const std::stack<AbstractComposerComponent::component_t> &stack,
                           AbstractComposerComponent::Type component_type)
{
  if (stack.empty() || stack.top()->GetComponentType() != component_type)
  {
    throw sup::dto::MessageException(
        "Error in ValidateLastComponent(): wrong type of the last component");
  }
}

void ValidateIfValueComponentIsComplete(
    const std::stack<AbstractComposerComponent::component_t> &stack)
{
  if (stack.empty())
  {
    throw sup::dto::MessageException(
        "Error in ValidateIfValueComponentIsComplete(): stack is empty");
  }

  using Type = AbstractComposerComponent::Type;
  static const std::vector<Type> expected_types{Type::kValue, Type::kEndStruct, Type::kEndArray};

  auto it =
      std::find(expected_types.begin(), expected_types.end(), stack.top()->GetComponentType());

  if (it == expected_types.end())
  {
    throw sup::dto::MessageException(
        "Error in ValidateIfValueComponentIsComplete(): wrong component type");
  }
}

}  // namespace dto

}  // namespace sup
