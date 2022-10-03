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

#include "sup/dto/builder/anyvalue_build_adapter.h"

#include <sup/dto/anytype.h>
#include <sup/dto/anyvalue.h>
#include <sup/dto/anyvalue_helper.h>
#include <sup/dto/builder/anyvalue_buildnodes.h>

#include <stack>
#include <stdexcept>

namespace sup
{
namespace dto
{

struct AnyValueBuildAdapter::AnyValueBuildAdapterImpl
{
  std::stack<AbstractAnyValueBuildNode::node_t> m_stack;

  template <typename T, typename... Args>
  void ProcessNode(Args &&...args)
  {
    auto node = std::unique_ptr<T>(new T((args)...));
    if (node->Process(m_stack))
    {
      m_stack.push(std::move(node));
    }
  }

  void AddValueNode(const ::sup::dto::AnyValue &value) { ProcessNode<AnyValueBuildNode>(value); }
};

AnyValueBuildAdapter::AnyValueBuildAdapter() : p_impl(new AnyValueBuildAdapterImpl) {}

sup::dto::AnyValue AnyValueBuildAdapter::MoveAnyValue() const
{
  return p_impl->m_stack.empty() ? sup::dto::AnyValue() : p_impl->m_stack.top()->MoveAnyValue();
}

AnyValueBuildAdapter::~AnyValueBuildAdapter() = default;

void AnyValueBuildAdapter::Bool(sup::dto::boolean value)
{
  p_impl->AddValueNode(::sup::dto::AnyValue(value));
}

void AnyValueBuildAdapter::Int8(sup::dto::int8 value)
{
  p_impl->AddValueNode(::sup::dto::AnyValue(value));
}

void AnyValueBuildAdapter::UInt8(sup::dto::uint8 value)
{
  p_impl->AddValueNode(::sup::dto::AnyValue(value));
}

void AnyValueBuildAdapter::Int16(sup::dto::int16 value)
{
  p_impl->AddValueNode(::sup::dto::AnyValue(value));
}

void AnyValueBuildAdapter::UInt16(sup::dto::uint16 value)
{
  p_impl->AddValueNode(::sup::dto::AnyValue(value));
}

void AnyValueBuildAdapter::Int32(sup::dto::int32 value)
{
  p_impl->AddValueNode(::sup::dto::AnyValue(value));
}

void AnyValueBuildAdapter::UInt32(sup::dto::uint32 value)
{
  p_impl->AddValueNode(::sup::dto::AnyValue(value));
}

void AnyValueBuildAdapter::Int64(sup::dto::int64 value)
{
  p_impl->AddValueNode(::sup::dto::AnyValue(value));
}

void AnyValueBuildAdapter::UInt64(sup::dto::uint64 value)
{
  p_impl->AddValueNode(::sup::dto::AnyValue(value));
}

void AnyValueBuildAdapter::Float32(sup::dto::float32 value)
{
  p_impl->AddValueNode(::sup::dto::AnyValue(value));
}

void AnyValueBuildAdapter::Float64(sup::dto::float64 value)
{
  p_impl->AddValueNode(::sup::dto::AnyValue(value));
}

void AnyValueBuildAdapter::String(const std::string &value)
{
  p_impl->AddValueNode(::sup::dto::AnyValue(value));
}

//! Adds the value as array element, or structure field, or single scalar.
//! @param anyvalue The value to be added.
//! @note Must be used under one of three scenario:
//! 1. Adding this value is the only operation with the builder. It can be a
//! scalar, array or structure. The value will be returned to the user on MoveAnyValue as it is.
//! 2. StartArrayElement was called before. Then the value will be added to the array elements.
//! 2. StartField was called before. Then the value will be added to current struct as a field.

void AnyValueBuildAdapter::AddValue(const sup::dto::AnyValue &anyvalue)
{
  p_impl->AddValueNode(anyvalue);
}

void AnyValueBuildAdapter::StartStruct(const std::string &struct_name)
{
  p_impl->ProcessNode<StartStructBuildNode>(struct_name);
}

void AnyValueBuildAdapter::EndStruct()
{
  p_impl->ProcessNode<EndStructBuildNode>();
}

void AnyValueBuildAdapter::StartField(const std::string &field_name)
{
  p_impl->ProcessNode<StartFieldBuildNode>(field_name);
}

void AnyValueBuildAdapter::EndField()
{
  p_impl->ProcessNode<EndFieldBuildNode>();
}

//! Adds member with given name to the structure.
//! @param anyvalue Scalar anyvalue, completed structure or array.
//! @note Equivalent of calls StartField/AddValue/EndField.

void AnyValueBuildAdapter::AddMember(const std::string &name, sup::dto::AnyValue anyvalue)
{
  StartField(name);
  AddValue(anyvalue);
  EndField();
}

void AnyValueBuildAdapter::StartArray(const std::string &array_name)
{
  p_impl->ProcessNode<StartArrayBuildNode>(array_name);
}

void AnyValueBuildAdapter::StartArrayElement()
{
  p_impl->ProcessNode<StartArrayElementBuildNode>();
}

void AnyValueBuildAdapter::EndArrayElement()
{
  p_impl->ProcessNode<EndArrayElementBuildNode>();
}

//! Adds array element.
//! @param anyvalue Scalar anyvalue, completed structure or array.
//! @note Equivalent of calls StartArrayElement/AddValue/EndArrayElement.

void AnyValueBuildAdapter::AddArrayElement(const sup::dto::AnyValue &anyvalue)
{
  StartArrayElement();
  AddValue(anyvalue);
  EndArrayElement();
}

void AnyValueBuildAdapter::EndArray()
{
  p_impl->ProcessNode<EndArrayBuildNode>();
}

int AnyValueBuildAdapter::GetStackSize() const
{
  return static_cast<int>(p_impl->m_stack.size());
}

}  // namespace dto
}  // namespace sup
