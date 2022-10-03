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

#include <sup/dto/composer/abstract_composer_component.h>

#include <stdexcept>

namespace sup
{
namespace dto
{

AbstractComposerComponent::AbstractComposerComponent() : m_value(), m_field_name() {}

AbstractComposerComponent::AbstractComposerComponent(const sup::dto::AnyValue &value)
    : m_value(value), m_field_name()
{
}

void AbstractComposerComponent::Consume(sup::dto::AnyValue &&value)
{
  m_value = std::move(value);
}

sup::dto::AnyValue AbstractComposerComponent::MoveAnyValue() const
{
  return std::move(m_value);
}

std::string AbstractComposerComponent::GetFieldName() const
{
  return m_field_name;
}

void AbstractComposerComponent::SetFieldName(const std::string &name)
{
  m_field_name = name;
}

void AbstractComposerComponent::AddMember(const std::string &name, const sup::dto::AnyValue &value)
{
  (void)name;
  (void)value;
  throw std::runtime_error("Error in AbstractComposerComponent::AddMember() : not implemented");
}

void AbstractComposerComponent::AddElement(const sup::dto::AnyValue &value)
{
  (void)value;
  throw std::runtime_error("Error in AbstractComposerComponent::AddMember() : not implemented");
}

}  // namespace dto
}  // namespace sup
