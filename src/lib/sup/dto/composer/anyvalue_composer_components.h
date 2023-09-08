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

#ifndef SUP_DTO_COMPOSER_ANYVALUE_COMPOSER_COMPONENTS_H_
#define SUP_DTO_COMPOSER_ANYVALUE_COMPOSER_COMPONENTS_H_

//! @file anyvalue_composer_components.h
//! Collection of classes representing components for AnyValueComposer.

#include <sup/dto/composer/abstract_value_composer_component.h>

#include <string>

namespace sup
{
namespace dto
{

//! The component to build AnyValue. Used when a single scalar is necessary, or during adding the
//! structure's field or the element of the array.

class ValueComposerComponent : public AbstractValueComposerComponent
{
public:
  explicit ValueComposerComponent(const sup::dto::AnyValue& value);

  Type GetComponentType() const override;

  bool Process(std::stack<component_t>& stack) override;
};

//! The component which is created at the start of the structure.

class StartStructValueComposerComponent : public AbstractValueComposerComponent
{
public:
  explicit StartStructValueComposerComponent(const std::string& struct_name);

  Type GetComponentType() const override;

  bool Process(std::stack<component_t>& stack) override;

  void AddMember(const std::string& name, const sup::dto::AnyValue& value) override;
};

//! The component which is created at the end of the structure.

class EndStructValueComposerComponent : public AbstractValueComposerComponent
{
public:
  Type GetComponentType() const override;

  bool Process(std::stack<component_t>& stack) override;
};

//! The component which is created at the beginning of the field creation.

class StartFieldValueComposerComponent : public AbstractValueComposerComponent
{
public:
  explicit StartFieldValueComposerComponent(const std::string& field_name);

  Type GetComponentType() const override;

  bool Process(std::stack<component_t>& stack) override;
};

//! The component which is created at the end of the field creation.

class EndFieldValueComposerComponent : public AbstractValueComposerComponent
{
public:
  Type GetComponentType() const override;

  bool Process(std::stack<component_t>& stack) override;
};

//! The component which is created at the start of the array.

class StartArrayValueComposerComponent : public AbstractValueComposerComponent
{
public:
  explicit StartArrayValueComposerComponent(const std::string& array_name);

  Type GetComponentType() const override;

  bool Process(std::stack<component_t>& stack) override;

  void AddElement(const sup::dto::AnyValue& value) override;

private:
  std::string m_array_name{};
};

//! The component which is created at the end of the array.

class EndArrayValueComposerComponent : public AbstractValueComposerComponent
{
public:
  Type GetComponentType() const override;

  bool Process(std::stack<component_t>& stack) override;
};

//! The component which is created at the start of the element in the array.

class StartArrayElementValueComposerComponent : public AbstractValueComposerComponent
{
public:
  Type GetComponentType() const override;

  bool Process(std::stack<component_t>& stack) override;
};

//! The component which is created at the start of the element in the array.

class EndArrayElementValueComposerComponent : public AbstractValueComposerComponent
{
public:
  Type GetComponentType() const override;

  bool Process(std::stack<component_t>& stack) override;
};

}  // namespace dto
}  // namespace sup

#endif  // SUP_DTO_COMPOSER_ANYVALUE_COMPOSER_COMPONENTS_H_
