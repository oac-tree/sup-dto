/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : SUP - DTO
 *
 * Description   : Data transfer objects for SUP
 *
 * Author        : Walter Van Herck (IO)
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

#include "sup/dto/composer/anytype_composer_components.h"

#include <sup/dto/composer/anytype_composer_helper.h>

#include <sup/dto/anyvalue_exceptions.h>

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
// LeafTypeComposerComponent
// ----------------------------------------------------------------------------

LeafTypeComposerComponent::LeafTypeComposerComponent(const sup::dto::AnyType& anytype)
  : AbstractTypeComposerComponent(anytype)
{}

AbstractTypeComposerComponent::Type LeafTypeComposerComponent::GetComponentType() const
{
  return Type::kLeafType;
}

bool LeafTypeComposerComponent::Process(std::stack<component_t>& stack)
{
  ValidateAddTypeComponent(stack);
  return kKeepInStackRequest;
}

// ----------------------------------------------------------------------------
// StartStructTypeComposerComponent
// ----------------------------------------------------------------------------

StartStructTypeComposerComponent::StartStructTypeComposerComponent(const std::string& struct_name)
  : AbstractTypeComposerComponent(::sup::dto::EmptyStructType(struct_name))
{}

AbstractTypeComposerComponent::Type StartStructTypeComposerComponent::GetComponentType() const
{
  return Type::kStartStruct;
}

bool StartStructTypeComposerComponent::Process(std::stack<component_t>& stack)
{
  ValidateAddTypeComponent(stack);
  return kKeepInStackRequest;
}

void StartStructTypeComposerComponent::AddMember(const std::string& name,
                                                 const sup::dto::AnyType& anytype)
{
  (void)GetType().AddMember(name, anytype);
}

// ----------------------------------------------------------------------------
// EndStructTypeComposerComponent
// ----------------------------------------------------------------------------

AbstractTypeComposerComponent::Type EndStructTypeComposerComponent::GetComponentType() const
{
  return Type::kEndStruct;
}

bool EndStructTypeComposerComponent::Process(std::stack<component_t>& stack)
{
  ValidateLastTypeComponent(stack, Type::kStartStruct);

  // saving the value and removing StartStructTypeComposerComponent
  Consume(stack.top()->MoveAnyType());
  stack.pop();

  return kKeepInStackRequest;
}

// ----------------------------------------------------------------------------
// StartFieldTypeComposerComponent
// ----------------------------------------------------------------------------

StartFieldTypeComposerComponent::StartFieldTypeComposerComponent(const std::string& field_name)
    : AbstractTypeComposerComponent{}
{
  SetFieldName(field_name);
}

AbstractTypeComposerComponent::Type StartFieldTypeComposerComponent::GetComponentType() const
{
  return Type::kStartField;
}

bool StartFieldTypeComposerComponent::Process(std::stack<component_t>& stack)
{
  ValidateLastTypeComponent(stack, Type::kStartStruct);

  return kKeepInStackRequest;
}

// ----------------------------------------------------------------------------
// EndFieldTypeComposerComponent
// ----------------------------------------------------------------------------

AbstractTypeComposerComponent::Type EndFieldTypeComposerComponent::GetComponentType() const
{
  return Type::kEndField;
}

//! Processes the stack, finalizes the adding of the field to StartStructComposerComponent.
//! @note It will remove two last stack elements (with the value, and with the field name) and then
//! create a field in the remaining StartStructComposerComponent.
bool EndFieldTypeComposerComponent::Process(std::stack<component_t>& stack)
{
  ValidateIfTypeComponentIsComplete(stack);

  // removing type component (scalar, struct or array) and storing the type
  const auto field_type = stack.top()->MoveAnyType();
  stack.pop();

  ValidateLastTypeComponent(stack, Type::kStartField);

  // removing StartFieldTypeComposerComponent and storing the name
  const auto field_name = stack.top()->GetFieldName();
  stack.pop();

  // adding a new member to StartStructComposerComponent
  stack.top()->AddMember(field_name, field_type);

  return kDoNotKeepInStackRequest;
}

// ----------------------------------------------------------------------------
// StartArrayTypeComposerComponent
// ----------------------------------------------------------------------------

StartArrayTypeComposerComponent::StartArrayTypeComposerComponent(const std::string& array_name,
                                                                 sup::dto::uint64 array_size)
  : AbstractTypeComposerComponent()
  , m_array_name{array_name}
  , m_array_size{array_size}
{}

AbstractTypeComposerComponent::Type StartArrayTypeComposerComponent::GetComponentType() const
{
  return Type::kStartArray;
}

bool StartArrayTypeComposerComponent::Process(std::stack<component_t>& stack)
{
  ValidateAddTypeComponent(stack);
  return kKeepInStackRequest;
}

//! Adds element to the array. If array doesn't exist, it will be initialised using the type of the
//! given value.
void StartArrayTypeComposerComponent::AddElement(const sup::dto::AnyType& anytype)
{
  if (GetType() != sup::dto::EmptyType)
  {
    const std::string error =
      "StartArrayTypeComposerComponent::AddElement: can only be called once on given object";
    throw ParseException(error);
  }
  SetType(sup::dto::AnyType(m_array_size, anytype, m_array_name));
}

// ----------------------------------------------------------------------------
// EndArrayTypeComposerComponent
// ----------------------------------------------------------------------------

AbstractTypeComposerComponent::Type EndArrayTypeComposerComponent::GetComponentType() const
{
  return Type::kEndArray;
}

bool EndArrayTypeComposerComponent::Process(std::stack<component_t>& stack)
{
  ValidateLastTypeComponent(stack, Type::kStartArray);

  // replacing StartArrayTypeComposerComponent with EndArrayTypeComposerComponent
  auto anytype = stack.top()->MoveAnyType();
  if (sup::dto::IsEmptyType(anytype))
  {
    const std::string error = "EndArrayTypeComposerComponent::Process: no element type defined";
    throw ParseException(error);
  }
  Consume(std::move(anytype));
  stack.pop();

  return kKeepInStackRequest;
}

// ----------------------------------------------------------------------------
// StartArrayElementTypeComposerComponent
// ----------------------------------------------------------------------------

AbstractTypeComposerComponent::Type StartArrayElementTypeComposerComponent::GetComponentType() const
{
  return Type::kStartArrayElement;
}

bool StartArrayElementTypeComposerComponent::Process(std::stack<component_t>& stack)
{
  ValidateLastTypeComponent(stack, Type::kStartArray);
  return kKeepInStackRequest;
}

// ----------------------------------------------------------------------------
// EndArrayElementTypeComposerComponent
// ----------------------------------------------------------------------------

AbstractTypeComposerComponent::Type EndArrayElementTypeComposerComponent::GetComponentType() const
{
  return Type::kEndArrayElement;
}

//! Processes the stack, finalizes the adding of the element to StartArrayTypeComposerComponent.
//! @note It will remove the two last stack elements (with the type and
//! StartArrayElementTypeComposerComponent) and then create an element in the remaining
//! StartArrayComposerComponent.

bool EndArrayElementTypeComposerComponent::Process(std::stack<component_t>& stack)
{
  ValidateIfTypeComponentIsComplete(stack);

  // removing type component (scalar, struct or array) and storing the type
  const auto anytype = stack.top()->MoveAnyType();
  stack.pop();

  ValidateLastTypeComponent(stack, Type::kStartArrayElement);
  stack.pop();

  // adding a new element to StartArrayTypeComposerComponent
  stack.top()->AddElement(anytype);

  return kDoNotKeepInStackRequest;
}

}  // namespace dto

}  // namespace sup
