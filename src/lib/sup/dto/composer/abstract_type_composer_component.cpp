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

#include <sup/dto/anyvalue_exceptions.h>
#include <sup/dto/composer/abstract_type_composer_component.h>

namespace sup
{
namespace dto
{

AbstractTypeComposerComponent::AbstractTypeComposerComponent()
  : m_type{}
  , m_field_name{}
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

void AbstractTypeComposerComponent::AddMember(const std::string &name,
                                              const sup::dto::AnyType& anytype)
{
  (void)name;
  (void)anytype;
  throw sup::dto::ParseException(
      "Error in AbstractTypeComposerComponent::AddMember() : not implemented");
}

void AbstractTypeComposerComponent::AddElement(sup::dto::AnyType& anytype)
{
  (void)anytype;
  throw sup::dto::ParseException(
      "Error in AbstractTypeComposerComponent::AddElement() : not implemented");
}

}  // namespace dto

}  // namespace sup
