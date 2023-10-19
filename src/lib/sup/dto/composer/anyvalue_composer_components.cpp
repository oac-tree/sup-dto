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

#include "sup/dto/composer/anyvalue_composer_components.h"

#include <sup/dto/anyvalue_exceptions.h>
#include <sup/dto/composer/anyvalue_composer_helper.h>

#include <iostream>

namespace
{
const bool kKeepInStackRequest{true};
const bool kDoNotKeepInStackRequest{false};
}  // namespace

namespace sup
{
namespace dto
{

// ----------------------------------------------------------------------------
// ValueComposerComponent
// ----------------------------------------------------------------------------

ValueComposerComponent::ValueComposerComponent(const sup::dto::AnyValue &value)
    : AbstractValueComposerComponent(value)
{
}

AbstractValueComposerComponent::Type ValueComposerComponent::GetComponentType() const
{
  return Type::kValue;
}

bool ValueComposerComponent::Process(std::stack<component_t> &stack)
{
  ValidateAddValueComponent(stack);
  return kKeepInStackRequest;
}

// ----------------------------------------------------------------------------
// StartStructValueComposerComponent
// ----------------------------------------------------------------------------

StartStructValueComposerComponent::StartStructValueComposerComponent(const std::string &struct_name)
    : AbstractValueComposerComponent(::sup::dto::EmptyStruct(struct_name))

{
}

AbstractValueComposerComponent::Type StartStructValueComposerComponent::GetComponentType() const
{
  return Type::kStartStruct;
}

bool StartStructValueComposerComponent::Process(std::stack<component_t> &stack)
{
  ValidateAddValueComponent(stack);
  return kKeepInStackRequest;
}

void StartStructValueComposerComponent::AddMember(const std::string &name,
                                             const sup::dto::AnyValue &value)
{
  GetValue().AddMember(name, value);
}

// ----------------------------------------------------------------------------
// EndStructValueComposerComponent
// ----------------------------------------------------------------------------

AbstractValueComposerComponent::Type EndStructValueComposerComponent::GetComponentType() const
{
  return Type::kEndStruct;
}

bool EndStructValueComposerComponent::Process(std::stack<component_t> &stack)
{
  ValidateLastComponent(stack, Type::kStartStruct);

  // saving the value and removing StartStructValueComposerComponent
  Consume(stack.top()->MoveAnyValue());
  stack.pop();

  return kKeepInStackRequest;
}

// ----------------------------------------------------------------------------
// StartFieldValueComposerComponent
// ----------------------------------------------------------------------------

StartFieldValueComposerComponent::StartFieldValueComposerComponent(const std::string &field_name)
    : AbstractValueComposerComponent()
{
  SetFieldName(field_name);
}

AbstractValueComposerComponent::Type StartFieldValueComposerComponent::GetComponentType() const
{
  return Type::kStartField;
}

bool StartFieldValueComposerComponent::Process(std::stack<component_t> &stack)
{
  ValidateLastComponent(stack, Type::kStartStruct);

  if (GetFieldName().empty())
  {
    throw sup::dto::ParseException(
        "Error in StartFieldValueComposerComponent::Process(): fieldname is not defined");
  }

  return kKeepInStackRequest;
}

// ----------------------------------------------------------------------------
// EndFieldValueComposerComponent
// ----------------------------------------------------------------------------

AbstractValueComposerComponent::Type EndFieldValueComposerComponent::GetComponentType() const
{
  return Type::kEndField;
}

//! Processes the stack, finalizes the adding of the field to StartStructValueComposerComponent.
//! @note It will remove two last stack elements (with the value, and with the field name) and then
//! create a field in the remaining StartStructValueComposerComponent.
bool EndFieldValueComposerComponent::Process(std::stack<component_t> &stack)
{
  ValidateIfValueComponentIsComplete(stack);

  // removing value component (scalar, struct or array), keeping the value for later reuse
  const auto value = stack.top()->MoveAnyValue();
  stack.pop();

  ValidateLastComponent(stack, Type::kStartField);

  // removing StartFieldValueComposerComponent, keeping the name for later reuse
  const auto field_name = stack.top()->GetFieldName();
  stack.pop();

  ValidateLastComponent(stack, Type::kStartStruct);

  // adding a new member to StartStructValueComposerComponent
  stack.top()->AddMember(field_name, value);

  return kDoNotKeepInStackRequest;
}

// ----------------------------------------------------------------------------
// StartArrayValueComposerComponent
// ----------------------------------------------------------------------------

StartArrayValueComposerComponent::StartArrayValueComposerComponent(const std::string &array_name)
    : m_array_name(array_name)
{
}

AbstractValueComposerComponent::Type StartArrayValueComposerComponent::GetComponentType() const
{
  return Type::kStartArray;
}

bool StartArrayValueComposerComponent::Process(std::stack<component_t> &stack)
{
  ValidateAddValueComponent(stack);
  return kKeepInStackRequest;
}

//! Adds element to the array. If array doesn't exist, it will be initialised using the type of the
//! given value.
void StartArrayValueComposerComponent::AddElement(const sup::dto::AnyValue &value)
{
  if (sup::dto::IsEmptyValue(GetValue()))
  {
    auto array_val = sup::dto::AnyValue(0u, value.GetType(), m_array_name);
    array_val.AddElement(value);
    SetValue(array_val);
  }
  else
  {
    GetValue().AddElement(value);
  }
}

// ----------------------------------------------------------------------------
// EndArrayValueComposerComponent
// ----------------------------------------------------------------------------

AbstractValueComposerComponent::Type EndArrayValueComposerComponent::GetComponentType() const
{
  return Type::kEndArray;
}

bool EndArrayValueComposerComponent::Process(std::stack<component_t> &stack)
{
  ValidateLastComponent(stack, Type::kStartArray);

  // replacing StartArrayValueComposerComponent with EndArrayValueComposerComponent

  // empty anyvalue means an attempt to create an array without elements
  auto anyvalue = stack.top()->MoveAnyValue();
  if (IsEmptyValue(anyvalue))
  {
    throw sup::dto::ParseException("Attempt to create an array without defining an element type");
  }

  Consume(std::move(anyvalue));
  stack.pop();

  return kKeepInStackRequest;
}

// ----------------------------------------------------------------------------
// StartArrayElementValueComposerComponent
// ----------------------------------------------------------------------------

AbstractValueComposerComponent::Type StartArrayElementValueComposerComponent::GetComponentType() const
{
  return Type::kStartArrayElement;
}

bool StartArrayElementValueComposerComponent::Process(std::stack<component_t> &stack)
{
  ValidateLastComponent(stack, Type::kStartArray);
  return kKeepInStackRequest;
}

// ----------------------------------------------------------------------------
// EndArrayElementValueComposerComponent
// ----------------------------------------------------------------------------

AbstractValueComposerComponent::Type EndArrayElementValueComposerComponent::GetComponentType() const
{
  return Type::kEndArrayElement;
}

//! Processes the stack, finalizes the adding of the element to StartArrayValueComposerComponent.
//! @note It will remove two last stack elements (with the value, and
//! StartArrayElementValueComposerComponent) and then create a field in the remaining
//! StartArrayValueComposerComponent.

bool EndArrayElementValueComposerComponent::Process(std::stack<component_t> &stack)
{
  ValidateIfValueComponentIsComplete(stack);

  // removing value component (scalar, struct or array), keeping the value for later reuse
  const auto value = stack.top()->MoveAnyValue();
  stack.pop();

  ValidateLastComponent(stack, Type::kStartArrayElement);
  stack.pop();

  // adding a new element to StartArrayValueComposerComponent
  stack.top()->AddElement(value);

  return kDoNotKeepInStackRequest;
}

}  // namespace dto

}  // namespace sup
