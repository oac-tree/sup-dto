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
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include <sup/dto/anyvalue_exceptions.h>
#include <sup/dto/composer/abstract_value_composer_component.h>

namespace sup
{
namespace dto
{

AbstractValueComposerComponent::AbstractValueComposerComponent()
  : AbstractValueComposerComponent(AnyValue{})
{}

AbstractValueComposerComponent::AbstractValueComposerComponent(const sup::dto::AnyValue& value)
    : m_value(value), m_field_name()
{}

void AbstractValueComposerComponent::Consume(sup::dto::AnyValue&& value)
{
  m_value = std::move(value);
}

sup::dto::AnyValue AbstractValueComposerComponent::MoveAnyValue()
{
  return std::move(m_value);
}

std::string AbstractValueComposerComponent::GetFieldName() const
{
  return m_field_name;
}

void AbstractValueComposerComponent::SetFieldName(const std::string& name)
{
  m_field_name = name;
}

void AbstractValueComposerComponent::AddMember(const std::string&, const sup::dto::AnyValue&)
{
  throw sup::dto::ParseException(
      "Error in AbstractValueComposerComponent::AddMember() : not implemented");
}

void AbstractValueComposerComponent::AddElement(const sup::dto::AnyValue&)
{
  throw sup::dto::ParseException(
      "Error in AbstractValueComposerComponent::AddMember() : not implemented");
}

sup::dto::AnyValue& AbstractValueComposerComponent::GetValue() &
{
  return m_value;
}

void AbstractValueComposerComponent::SetValue(const sup::dto::AnyValue& value)
{
  m_value = value;
}

}  // namespace dto

}  // namespace sup
