/******************************************************************************
 *
 * Project       : Supervision and automation system EPICS interface
 *
 * Description   : Library of SUP components for EPICS network protocol
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
 *****************************************************************************/

#include "sup/dto/composer/anyvalue_composer_components.h"

#include <sup/dto/composer/anyvalue_composer_helper.h>

#include <iostream>
#include <stdexcept>

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
    : AbstractComposerComponent(value)
{
}

AbstractComposerComponent::Type ValueComposerComponent::GetComponentType() const
{
  return Type::kValue;
}

bool ValueComposerComponent::Process(std::stack<component_t> &stack)
{
  ValidateAddValueComponent(stack);
  return kKeepInStackRequest;
}

// ----------------------------------------------------------------------------
// StartStructComposerComponent
// ----------------------------------------------------------------------------

StartStructComposerComponent::StartStructComposerComponent(const std::string &struct_name)
    : AbstractComposerComponent(::sup::dto::EmptyStruct(struct_name))

{
}

AbstractComposerComponent::Type StartStructComposerComponent::GetComponentType() const
{
  return Type::kStartStruct;
}

bool StartStructComposerComponent::Process(std::stack<component_t> &stack)
{
  ValidateAddValueComponent(stack);
  return kKeepInStackRequest;
}

void StartStructComposerComponent::AddMember(const std::string &name,
                                             const sup::dto::AnyValue &value)
{
  m_value.AddMember(name, value);
}

// ----------------------------------------------------------------------------
// EndStructComposerComponent
// ----------------------------------------------------------------------------

AbstractComposerComponent::Type EndStructComposerComponent::GetComponentType() const
{
  return Type::kEndStruct;
}

bool EndStructComposerComponent::Process(std::stack<component_t> &stack)
{
  ValidateLastComponent(stack, Type::kStartStruct);

  // saving the value and removing StartStructBuildNode
  Consume(stack.top()->MoveAnyValue());
  stack.pop();

  return kKeepInStackRequest;
}

// ----------------------------------------------------------------------------
// EndFieldComposerComponent
// ----------------------------------------------------------------------------

StartFieldComposerComponent::StartFieldComposerComponent(const std::string &field_name)
    : AbstractComposerComponent()
{
  SetFieldName(field_name);
}

AbstractComposerComponent::Type StartFieldComposerComponent::GetComponentType() const
{
  return Type::kStartField;
}

bool StartFieldComposerComponent::Process(std::stack<component_t> &stack)
{
  ValidateLastComponent(stack, Type::kStartStruct);

  if (GetFieldName().empty())
  {
    throw std::runtime_error("Error in StartFieldBuildNode::Process(): fieldname is not defined");
  }

  return kKeepInStackRequest;
}

// ----------------------------------------------------------------------------
// EndFieldComposerComponent
// ----------------------------------------------------------------------------

AbstractComposerComponent::Type EndFieldComposerComponent::GetComponentType() const
{
  return Type::kEndField;
}

//! Processes the stack, finalizes the adding of the field to StartStructBuildNode.
//! @note It will remove two last nodes (with the value, and with the field name) and then
//! create a field in the remaining StartStructBuildNode.
bool EndFieldComposerComponent::Process(std::stack<component_t> &stack)
{
  ValidateIfValueComponentIsComplete(stack);

  // removing value node (scalar, struct or array), keeping the value for later reuse
  auto value = stack.top()->MoveAnyValue();
  stack.pop();

  ValidateLastComponent(stack, Type::kStartField);

  // removing StartFieldNode, keeping the name for later reuse
  auto field_name = stack.top()->GetFieldName();
  stack.pop();

  ValidateLastComponent(stack, Type::kStartStruct);

  // adding a new member to StartStructBuildNode
  stack.top()->AddMember(field_name, value);

  return kDoNotKeepInStackRequest;
}

// ----------------------------------------------------------------------------
// StartArrayComposerComponent
// ----------------------------------------------------------------------------

StartArrayComposerComponent::StartArrayComposerComponent(const std::string &array_name)
    : m_array_name(array_name)
{
}

AbstractComposerComponent::Type StartArrayComposerComponent::GetComponentType() const
{
  return Type::kStartArray;
}

bool StartArrayComposerComponent::Process(std::stack<component_t> &stack)
{
  ValidateAddValueComponent(stack);
  return kKeepInStackRequest;
}

//! Adds element to the array. If array doesn't exist, it will be initialised using the type of the
//! given value.
void StartArrayComposerComponent::AddElement(const sup::dto::AnyValue &value)
{
  if (sup::dto::IsEmptyValue(m_value))
  {
    m_value = sup::dto::AnyValue(0, value.GetType(), m_array_name);
    m_value.AddElement(value);
  }
  else
  {
    m_value.AddElement(value);
  }
}

// ----------------------------------------------------------------------------
// EndArrayComposerComponent
// ----------------------------------------------------------------------------

AbstractComposerComponent::Type EndArrayComposerComponent::GetComponentType() const
{
  return Type::kEndArray;
}

bool EndArrayComposerComponent::Process(std::stack<component_t> &stack)
{
  ValidateLastComponent(stack, Type::kStartArray);

  // replacing StartArrayBuildNode with EndArrayBuildNode
  Consume(stack.top()->MoveAnyValue());
  stack.pop();

  return kKeepInStackRequest;
}

// ----------------------------------------------------------------------------
// StartArrayElementComposerComponent
// ----------------------------------------------------------------------------

AbstractComposerComponent::Type StartArrayElementComposerComponent::GetComponentType() const
{
  return Type::kStartArrayElement;
}

bool StartArrayElementComposerComponent::Process(std::stack<component_t> &stack)
{
  ValidateLastComponent(stack, Type::kStartArray);
  return kKeepInStackRequest;
}

// ----------------------------------------------------------------------------
// EndArrayElementComposerComponent
// ----------------------------------------------------------------------------

AbstractComposerComponent::Type EndArrayElementComposerComponent::GetComponentType() const
{
  return Type::kEndArrayElement;
}

//! Processes the stack, finalizes the adding of the element to StartArrayBuildNode.
//! @note It will remove two last nodes (with the value, and StartArrayElementNode) and then
//! create a field in the remaining StartArrayBuildNode.

bool EndArrayElementComposerComponent::Process(std::stack<component_t> &stack)
{
  ValidateIfValueComponentIsComplete(stack);

  // removing value node (scalar, struct or array), keeping the value for later reuse
  auto value = stack.top()->MoveAnyValue();
  stack.pop();

  ValidateLastComponent(stack, Type::kStartArrayElement);
  stack.pop();

  // adding a new element to StartArrayBuildNode
  stack.top()->AddElement(value);

  return kDoNotKeepInStackRequest;
}

}  // namespace dto

}  // namespace sup
