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

#include "sup/dto/anytype_composer.h"

#include <sup/dto/composer/anytype_composer_components.h>
#include <sup/dto/composer/abstract_type_composer_component.h>

#include <sup/dto/anytype.h>
#include <sup/dto/anyvalue_exceptions.h>

#include <stack>

namespace sup
{
namespace dto
{

struct AnyTypeComposer::AnyTypeComposerImpl
{
  std::stack<AbstractTypeComposerComponent::component_t> m_stack;

  template <typename T, typename... Args>
  void ProcessComponent(Args &&...args)
  {
    auto component = std::unique_ptr<T>(new T((args)...));
    if (component->Process(m_stack))
    {
      m_stack.push(std::move(component));
    }
  }

  void AddScalarTypeComponent(const ::sup::dto::AnyType& anytype)
  {
    ProcessComponent<LeafTypeComposerComponent>(anytype);
  }

  AnyTypeComposerImpl() : m_stack() {}
};

AnyTypeComposer::AnyTypeComposer() : p_impl(new AnyTypeComposerImpl) {}

sup::dto::AnyType AnyTypeComposer::MoveAnyType()
{
  if (p_impl->m_stack.size() != 1)
  {
    const std::string error =
      "AnyTypeComposer::MoveAnyType: stack size not equal to one, AnyType "
      " construction was not correctly finished";
    throw ParseException(error);
  }
  return p_impl->m_stack.top()->MoveAnyType();
}

AnyTypeComposer::~AnyTypeComposer() = default;

void AnyTypeComposer::Empty()
{
  p_impl->AddScalarTypeComponent(::sup::dto::EmptyType);
}

void AnyTypeComposer::Bool()
{
  p_impl->AddScalarTypeComponent(::sup::dto::BooleanType);
}

void AnyTypeComposer::Char8()
{
  p_impl->AddScalarTypeComponent(::sup::dto::Character8Type);
}

void AnyTypeComposer::Int8()
{
  p_impl->AddScalarTypeComponent(::sup::dto::SignedInteger8Type);
}

void AnyTypeComposer::UInt8()
{
  p_impl->AddScalarTypeComponent(::sup::dto::UnsignedInteger8Type);
}

void AnyTypeComposer::Int16()
{
  p_impl->AddScalarTypeComponent(::sup::dto::SignedInteger16Type);
}

void AnyTypeComposer::UInt16()
{
  p_impl->AddScalarTypeComponent(::sup::dto::UnsignedInteger16Type);
}

void AnyTypeComposer::Int32()
{
  p_impl->AddScalarTypeComponent(::sup::dto::SignedInteger32Type);
}

void AnyTypeComposer::UInt32()
{
  p_impl->AddScalarTypeComponent(::sup::dto::UnsignedInteger32Type);
}

void AnyTypeComposer::Int64()
{
  p_impl->AddScalarTypeComponent(::sup::dto::SignedInteger64Type);
}

void AnyTypeComposer::UInt64()
{
  p_impl->AddScalarTypeComponent(::sup::dto::UnsignedInteger64Type);
}

void AnyTypeComposer::Float32()
{
  p_impl->AddScalarTypeComponent(::sup::dto::Float32Type);
}

void AnyTypeComposer::Float64()
{
  p_impl->AddScalarTypeComponent(::sup::dto::Float64Type);
}

void AnyTypeComposer::String()
{
  p_impl->AddScalarTypeComponent(::sup::dto::StringType);
}

void AnyTypeComposer::StartStruct(const std::string &struct_name)
{
  p_impl->ProcessComponent<StartStructTypeComposerComponent>(struct_name);
}

void AnyTypeComposer::StartStruct()
{
  StartStruct({});
}

void AnyTypeComposer::EndStruct()
{
  p_impl->ProcessComponent<EndStructTypeComposerComponent>();
}

void AnyTypeComposer::StartField(const std::string &field_name)
{
  p_impl->ProcessComponent<StartFieldTypeComposerComponent>(field_name);
}

void AnyTypeComposer::EndField()
{
  p_impl->ProcessComponent<EndFieldTypeComposerComponent>();
}

void AnyTypeComposer::StartArray(const std::string& array_name, sup::dto::uint64 array_size)
{
  p_impl->ProcessComponent<StartArrayTypeComposerComponent>(array_name, array_size);
}

void AnyTypeComposer::EndArray()
{
  p_impl->ProcessComponent<EndArrayTypeComposerComponent>();
}

void AnyTypeComposer::StartArrayElement()
{
  p_impl->ProcessComponent<StartArrayElementTypeComposerComponent>();
}

void AnyTypeComposer::EndArrayElement()
{
  p_impl->ProcessComponent<EndArrayElementTypeComposerComponent>();
}

sup::dto::uint64 AnyTypeComposer::GetStackSize() const
{
  return p_impl->m_stack.size();
}

}  // namespace dto
}  // namespace sup
