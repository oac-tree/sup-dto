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

#include "sup/dto/anyvalue_composer.h"

#include <sup/dto/anytype.h>
#include <sup/dto/anyvalue.h>
#include <sup/dto/anyvalue_helper.h>
#include <sup/dto/composer/anyvalue_composer_components.h>

#include <stack>
#include <stdexcept>

namespace sup
{
namespace dto
{

struct AnyValueComposer::AnyValueComposerImpl
{
  std::stack<AbstractComposerComponent::component_t> m_stack;

  template <typename T, typename... Args>
  void ProcessComponent(Args &&...args)
  {
    auto component = std::unique_ptr<T>(new T((args)...));
    if (component->Process(m_stack))
    {
      m_stack.push(std::move(component));
    }
  }

  void AddValueComponent(const ::sup::dto::AnyValue &value)
  {
    ProcessComponent<ValueComposerComponent>(value);
  }

  AnyValueComposerImpl() : m_stack() {}
};

AnyValueComposer::AnyValueComposer() : p_impl(new AnyValueComposerImpl) {}

sup::dto::AnyValue AnyValueComposer::MoveAnyValue() const
{
  return p_impl->m_stack.empty() ? sup::dto::AnyValue() : p_impl->m_stack.top()->MoveAnyValue();
}

AnyValueComposer::~AnyValueComposer() = default;

void AnyValueComposer::Empty()
{
  p_impl->AddValueComponent(::sup::dto::AnyValue{});
}

void AnyValueComposer::Bool(sup::dto::boolean value)
{
  p_impl->AddValueComponent(::sup::dto::AnyValue(value));
}

void AnyValueComposer::Char8(sup::dto::char8 value)
{
  p_impl->AddValueComponent(::sup::dto::AnyValue(value));
}

void AnyValueComposer::Int8(sup::dto::int8 value)
{
  p_impl->AddValueComponent(::sup::dto::AnyValue(value));
}

void AnyValueComposer::UInt8(sup::dto::uint8 value)
{
  p_impl->AddValueComponent(::sup::dto::AnyValue(value));
}

void AnyValueComposer::Int16(sup::dto::int16 value)
{
  p_impl->AddValueComponent(::sup::dto::AnyValue(value));
}

void AnyValueComposer::UInt16(sup::dto::uint16 value)
{
  p_impl->AddValueComponent(::sup::dto::AnyValue(value));
}

void AnyValueComposer::Int32(sup::dto::int32 value)
{
  p_impl->AddValueComponent(::sup::dto::AnyValue(value));
}

void AnyValueComposer::UInt32(sup::dto::uint32 value)
{
  p_impl->AddValueComponent(::sup::dto::AnyValue(value));
}

void AnyValueComposer::Int64(sup::dto::int64 value)
{
  p_impl->AddValueComponent(::sup::dto::AnyValue(value));
}

void AnyValueComposer::UInt64(sup::dto::uint64 value)
{
  p_impl->AddValueComponent(::sup::dto::AnyValue(value));
}

void AnyValueComposer::Float32(sup::dto::float32 value)
{
  p_impl->AddValueComponent(::sup::dto::AnyValue(value));
}

void AnyValueComposer::Float64(sup::dto::float64 value)
{
  p_impl->AddValueComponent(::sup::dto::AnyValue(value));
}

void AnyValueComposer::String(const std::string &value)
{
  p_impl->AddValueComponent(::sup::dto::AnyValue(value));
}

//! Adds the value as array element, or structure field, or single scalar.
//! @param anyvalue The value to be added.
//! @note Must be used under one of three scenario:
//! 1. Adding this value is the only operation with the builder. It can be a
//! scalar, array or structure. The value will be returned to the user on MoveAnyValue as it is.
//! 2. StartArrayElement was called before. Then the value will be added to the array elements.
//! 3. StartField was called before. Then the value will be added to current struct as a field.

void AnyValueComposer::AddValue(const sup::dto::AnyValue &anyvalue)
{
  p_impl->AddValueComponent(anyvalue);
}

void AnyValueComposer::StartStruct(const std::string &struct_name)
{
  p_impl->ProcessComponent<StartStructComposerComponent>(struct_name);
}

void AnyValueComposer::EndStruct()
{
  p_impl->ProcessComponent<EndStructComposerComponent>();
}

void AnyValueComposer::StartField(const std::string &field_name)
{
  p_impl->ProcessComponent<StartFieldComposerComponent>(field_name);
}

void AnyValueComposer::EndField()
{
  p_impl->ProcessComponent<EndFieldComposerComponent>();
}

//! Adds member with given name to the structure.
//! @param anyvalue Scalar anyvalue, completed structure or array.
//! @note Equivalent of calls StartField/AddValue/EndField.

void AnyValueComposer::AddMember(const std::string &name, sup::dto::AnyValue anyvalue)
{
  StartField(name);
  AddValue(anyvalue);
  EndField();
}

void AnyValueComposer::StartArray(const std::string &array_name)
{
  p_impl->ProcessComponent<StartArrayComposerComponent>(array_name);
}

void AnyValueComposer::StartArrayElement()
{
  p_impl->ProcessComponent<StartArrayElementComposerComponent>();
}

void AnyValueComposer::EndArrayElement()
{
  p_impl->ProcessComponent<EndArrayElementComposerComponent>();
}

//! Adds array element.
//! @param anyvalue Scalar anyvalue, completed structure or array.
//! @note Equivalent of calls StartArrayElement/AddValue/EndArrayElement.

void AnyValueComposer::AddArrayElement(const sup::dto::AnyValue &anyvalue)
{
  StartArrayElement();
  AddValue(anyvalue);
  EndArrayElement();
}

void AnyValueComposer::EndArray()
{
  p_impl->ProcessComponent<EndArrayComposerComponent>();
}

int AnyValueComposer::GetStackSize() const
{
  return static_cast<int>(p_impl->m_stack.size());
}

}  // namespace dto
}  // namespace sup
