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
 * Copyright (c) : 2010-2026 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 * SPDX-License-Identifier: MIT
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file LICENSE located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include "sup/dto/composer/anytype_composer_helper.h"

#include <sup/dto/anyvalue_exceptions.h>

#include <algorithm>
#include <sstream>
#include <vector>

namespace sup
{
namespace dto
{

bool CanAddTypeComponent(const std::stack<AbstractTypeComposerComponent::component_t>& stack)
{
  if (stack.empty())
  {
    return true;
  }
  using Type = AbstractTypeComposerComponent::Type;
  static const std::vector<Type> expected_types{Type::kStartArrayElement, Type::kStartField};
  const auto it =
      std::find(expected_types.begin(), expected_types.end(), stack.top()->GetComponentType());
  return it != expected_types.end();
}

void ValidateAddTypeComponent(const std::stack<AbstractTypeComposerComponent::component_t>& stack)
{
  if (!CanAddTypeComponent(stack))
  {
    const std::string error =
      "ValidateAddTypeComponent(): component can not be added, last type: "
      + std::to_string(static_cast<sup::dto::uint32>(stack.top()->GetComponentType()));
    throw sup::dto::ParseException(error);
  }
}

void ValidateLastTypeComponent(const std::stack<AbstractTypeComposerComponent::component_t>& stack,
                               AbstractTypeComposerComponent::Type component_type)
{
  if ((stack.empty()) || (stack.top()->GetComponentType() != component_type))
  {
    const std::string error =
      "ValidateLastTypeComponent(): last component does not have the required type: "
       + std::to_string(static_cast<sup::dto::uint32>(component_type));
    throw sup::dto::ParseException(error);
  }
}

void ValidateIfTypeComponentIsComplete(
    const std::stack<AbstractTypeComposerComponent::component_t>& stack)
{
  if (stack.empty())
  {
    const std::string error = "ValidateIfTypeComponentIsComplete(): stack is empty";
    throw sup::dto::ParseException(error);
  }
  using Type = AbstractTypeComposerComponent::Type;
  static const std::vector<Type> expected_types{Type::kLeafType, Type::kEndStruct,
                                                Type::kEndArray};

  const auto it =
      std::find(expected_types.begin(), expected_types.end(), stack.top()->GetComponentType());

  if (it == expected_types.end())
  {
    const std::string error = "ValidateIfTypeComponentIsComplete(): wrong component type";
    throw sup::dto::ParseException(error);
  }
}

}  // namespace dto

}  // namespace sup
