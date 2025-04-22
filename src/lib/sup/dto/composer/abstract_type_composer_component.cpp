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
 * Copyright (c) : 2010-2025 ITER Organization,
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

#include <sup/dto/anyvalue_exceptions.h>
#include <sup/dto/composer/abstract_type_composer_component.h>

namespace sup
{
namespace dto
{

AbstractTypeComposerComponent::AbstractTypeComposerComponent()
  : AbstractTypeComposerComponent(EmptyType)
{}

AbstractTypeComposerComponent::AbstractTypeComposerComponent(const sup::dto::AnyType& anytype)
  : m_type{anytype}
  , m_field_name{}
{}

AbstractTypeComposerComponent::~AbstractTypeComposerComponent() = default;

void AbstractTypeComposerComponent::Consume(sup::dto::AnyType&& anytype)
{
  m_type = std::move(anytype);
}

sup::dto::AnyType AbstractTypeComposerComponent::MoveAnyType()
{
  return std::move(m_type);
}

std::string AbstractTypeComposerComponent::GetFieldName() const
{
  return m_field_name;
}

void AbstractTypeComposerComponent::SetFieldName(const std::string &name)
{
  m_field_name = name;
}

void AbstractTypeComposerComponent::AddMember(const std::string&, const sup::dto::AnyType&)
{
  throw sup::dto::ParseException(
      "Error in AbstractTypeComposerComponent::AddMember() : not implemented");
}

void AbstractTypeComposerComponent::AddElement(const sup::dto::AnyType&)
{
  throw sup::dto::ParseException(
      "Error in AbstractTypeComposerComponent::AddElement() : not implemented");
}

sup::dto::AnyType& AbstractTypeComposerComponent::GetType() &
{
  return m_type;
}

void AbstractTypeComposerComponent::SetType(const sup::dto::AnyType& anytype)
{
  m_type = anytype;
}

}  // namespace dto

}  // namespace sup
