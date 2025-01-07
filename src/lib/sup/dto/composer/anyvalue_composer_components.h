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
  ~ValueComposerComponent() override = default;
  ValueComposerComponent(const ValueComposerComponent& other) = delete;
  ValueComposerComponent(ValueComposerComponent&& other) = delete;
  ValueComposerComponent& operator=(const ValueComposerComponent& other) = delete;
  ValueComposerComponent& operator=(ValueComposerComponent&& other) = delete;


  Type GetComponentType() const override;

  bool Process(std::stack<component_t>& stack) override;
};

//! The component which is created at the start of the structure.

class StartStructValueComposerComponent : public AbstractValueComposerComponent
{
public:
  explicit StartStructValueComposerComponent(const std::string& struct_name);
  ~StartStructValueComposerComponent() override = default;
  StartStructValueComposerComponent(const StartStructValueComposerComponent& other) = delete;
  StartStructValueComposerComponent(StartStructValueComposerComponent&& other) = delete;
  StartStructValueComposerComponent& operator=(const StartStructValueComposerComponent& other) = delete;
  StartStructValueComposerComponent& operator=(StartStructValueComposerComponent&& other) = delete;


  Type GetComponentType() const override;

  bool Process(std::stack<component_t>& stack) override;

  void AddMember(const std::string& name, const sup::dto::AnyValue& value) override;
};

//! The component which is created at the end of the structure.

class EndStructValueComposerComponent : public AbstractValueComposerComponent
{
public:
  EndStructValueComposerComponent() = default;
  ~EndStructValueComposerComponent() override = default;
  EndStructValueComposerComponent(const EndStructValueComposerComponent& other) = delete;
  EndStructValueComposerComponent(EndStructValueComposerComponent&& other) = delete;
  EndStructValueComposerComponent& operator=(const EndStructValueComposerComponent& other) = delete;
  EndStructValueComposerComponent& operator=(EndStructValueComposerComponent&& other) = delete;

  Type GetComponentType() const override;

  bool Process(std::stack<component_t>& stack) override;
};

//! The component which is created at the beginning of the field creation.

class StartFieldValueComposerComponent : public AbstractValueComposerComponent
{
public:
  explicit StartFieldValueComposerComponent(const std::string& field_name);
  ~StartFieldValueComposerComponent() override = default;
  StartFieldValueComposerComponent(const StartFieldValueComposerComponent& other) = delete;
  StartFieldValueComposerComponent(StartFieldValueComposerComponent&& other) = delete;
  StartFieldValueComposerComponent& operator=(const StartFieldValueComposerComponent& other) = delete;
  StartFieldValueComposerComponent& operator=(StartFieldValueComposerComponent&& other) = delete;

  Type GetComponentType() const override;

  bool Process(std::stack<component_t>& stack) override;
};

//! The component which is created at the end of the field creation.

class EndFieldValueComposerComponent : public AbstractValueComposerComponent
{
public:
  EndFieldValueComposerComponent() = default;
  ~EndFieldValueComposerComponent() override = default;
  EndFieldValueComposerComponent(const EndFieldValueComposerComponent& other) = delete;
  EndFieldValueComposerComponent(EndFieldValueComposerComponent&& other) = delete;
  EndFieldValueComposerComponent& operator=(const EndFieldValueComposerComponent& other) = delete;
  EndFieldValueComposerComponent& operator=(EndFieldValueComposerComponent&& other) = delete;

  Type GetComponentType() const override;

  bool Process(std::stack<component_t>& stack) override;
};

//! The component which is created at the start of the array.

class StartArrayValueComposerComponent : public AbstractValueComposerComponent
{
public:
  explicit StartArrayValueComposerComponent(const std::string& array_name);
  ~StartArrayValueComposerComponent() override = default;
  StartArrayValueComposerComponent(const StartArrayValueComposerComponent& other) = delete;
  StartArrayValueComposerComponent(StartArrayValueComposerComponent&& other) = delete;
  StartArrayValueComposerComponent& operator=(const StartArrayValueComposerComponent& other) = delete;
  StartArrayValueComposerComponent& operator=(StartArrayValueComposerComponent&& other) = delete;


  Type GetComponentType() const override;

  bool Process(std::stack<component_t>& stack) override;

  void AddElement(const sup::dto::AnyValue& value) override;

private:
  std::string m_array_name;
};

//! The component which is created at the end of the array.

class EndArrayValueComposerComponent : public AbstractValueComposerComponent
{
public:
  EndArrayValueComposerComponent() = default;
  ~EndArrayValueComposerComponent() override = default;
  EndArrayValueComposerComponent(const EndArrayValueComposerComponent& other) = delete;
  EndArrayValueComposerComponent(EndArrayValueComposerComponent&& other) = delete;
  EndArrayValueComposerComponent& operator=(const EndArrayValueComposerComponent& other) = delete;
  EndArrayValueComposerComponent& operator=(EndArrayValueComposerComponent&& other) = delete;

  Type GetComponentType() const override;

  bool Process(std::stack<component_t>& stack) override;
};

//! The component which is created at the start of the element in the array.

class StartArrayElementValueComposerComponent : public AbstractValueComposerComponent
{
public:
  StartArrayElementValueComposerComponent() = default;
  ~StartArrayElementValueComposerComponent() override = default;
  StartArrayElementValueComposerComponent(const StartArrayElementValueComposerComponent& other) = delete;
  StartArrayElementValueComposerComponent(StartArrayElementValueComposerComponent&& other) = delete;
  StartArrayElementValueComposerComponent& operator=(const StartArrayElementValueComposerComponent& other) = delete;
  StartArrayElementValueComposerComponent& operator=(StartArrayElementValueComposerComponent&& other) = delete;

  Type GetComponentType() const override;

  bool Process(std::stack<component_t>& stack) override;
};

//! The component which is created at the start of the element in the array.

class EndArrayElementValueComposerComponent : public AbstractValueComposerComponent
{
public:
  EndArrayElementValueComposerComponent() = default;
  ~EndArrayElementValueComposerComponent() override = default;
  EndArrayElementValueComposerComponent(const EndArrayElementValueComposerComponent& other) = delete;
  EndArrayElementValueComposerComponent(EndArrayElementValueComposerComponent&& other) = delete;
  EndArrayElementValueComposerComponent& operator=(const EndArrayElementValueComposerComponent& other) = delete;
  EndArrayElementValueComposerComponent& operator=(EndArrayElementValueComposerComponent&& other) = delete;

  Type GetComponentType() const override;

  bool Process(std::stack<component_t>& stack) override;
};

}  // namespace dto
}  // namespace sup

#endif  // SUP_DTO_COMPOSER_ANYVALUE_COMPOSER_COMPONENTS_H_
