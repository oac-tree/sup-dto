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

#include <sup/dto/builder/abstract_anyvalue_buildnode.h>

#include <stdexcept>

namespace sup
{
namespace dto
{

AbstractAnyValueBuildNode::AbstractAnyValueBuildNode() : m_value(), m_field_name()
{

}

AbstractAnyValueBuildNode::AbstractAnyValueBuildNode(const sup::dto::AnyValue &value)
    : m_value(value), m_field_name()
{
}

void AbstractAnyValueBuildNode::Consume(sup::dto::AnyValue &&value)
{
  m_value = std::move(value);
}

sup::dto::AnyValue AbstractAnyValueBuildNode::MoveAnyValue() const
{
  return std::move(m_value);
}

std::string AbstractAnyValueBuildNode::GetFieldName() const
{
  return m_field_name;
}

void AbstractAnyValueBuildNode::SetFieldName(const std::string &name)
{
  m_field_name = name;
}

void AbstractAnyValueBuildNode::AddMember(const std::string &name, const sup::dto::AnyValue &value)
{
  (void)name;
  (void)value;
  throw std::runtime_error("Error in AbstractAnyValueBuildNode::AddMember() : not implemented");
}

void AbstractAnyValueBuildNode::AddElement(const sup::dto::AnyValue &value)
{
  (void)value;
  throw std::runtime_error("Error in AbstractAnyValueBuildNode::AddMember() : not implemented");
}

}  // namespace dto
}  // namespace sup
