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
 * Copyright (c) : 2010-2024 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#ifndef SUP_DTO_COMPOSER_ANYTYPE_COMPOSER_COMPONENTS_H_
#define SUP_DTO_COMPOSER_ANYTYPE_COMPOSER_COMPONENTS_H_

#include <sup/dto/composer/abstract_type_composer_component.h>

#include <sup/dto/basic_scalar_types.h>

#include <string>

namespace sup
{
namespace dto
{

//! The component to build a scalar type.
class LeafTypeComposerComponent : public AbstractTypeComposerComponent
{
public:
  explicit LeafTypeComposerComponent(const sup::dto::AnyType& anytype);

  ~LeafTypeComposerComponent() override = default;
  LeafTypeComposerComponent(const LeafTypeComposerComponent& other) = delete;
  LeafTypeComposerComponent(LeafTypeComposerComponent&& other) = delete;
  LeafTypeComposerComponent& operator=(const LeafTypeComposerComponent& other) = delete;
  LeafTypeComposerComponent& operator=(LeafTypeComposerComponent&& other) = delete;

  Type GetComponentType() const override;

  bool Process(std::stack<component_t>& stack) override;
};

//! The component which is created at the start of the structure.
class StartStructTypeComposerComponent : public AbstractTypeComposerComponent
{
public:
  explicit StartStructTypeComposerComponent(const std::string& struct_name);

  ~StartStructTypeComposerComponent() override = default;
  StartStructTypeComposerComponent(const StartStructTypeComposerComponent& other) = delete;
  StartStructTypeComposerComponent(StartStructTypeComposerComponent&& other) = delete;
  StartStructTypeComposerComponent& operator=(const StartStructTypeComposerComponent& other) = delete;
  StartStructTypeComposerComponent& operator=(StartStructTypeComposerComponent&& other) = delete;

  Type GetComponentType() const override;

  bool Process(std::stack<component_t>& stack) override;

  void AddMember(const std::string& name, const sup::dto::AnyType& anytype) override;
};

//! The component which is created at the end of the structure.
class EndStructTypeComposerComponent : public AbstractTypeComposerComponent
{
public:
  EndStructTypeComposerComponent() = default;
  ~EndStructTypeComposerComponent() override = default;
  EndStructTypeComposerComponent(const EndStructTypeComposerComponent& other) = delete;
  EndStructTypeComposerComponent(EndStructTypeComposerComponent&& other) = delete;
  EndStructTypeComposerComponent& operator=(const EndStructTypeComposerComponent& other) = delete;
  EndStructTypeComposerComponent& operator=(EndStructTypeComposerComponent&& other) = delete;

  Type GetComponentType() const override;

  bool Process(std::stack<component_t>& stack) override;
};

//! The component which is created at the beginning of field creation.
class StartFieldTypeComposerComponent : public AbstractTypeComposerComponent
{
public:
  explicit StartFieldTypeComposerComponent(const std::string& field_name);

  ~StartFieldTypeComposerComponent() override = default;
  StartFieldTypeComposerComponent(const StartFieldTypeComposerComponent& other) = delete;
  StartFieldTypeComposerComponent(StartFieldTypeComposerComponent&& other) = delete;
  StartFieldTypeComposerComponent& operator=(const StartFieldTypeComposerComponent& other) = delete;
  StartFieldTypeComposerComponent& operator=(StartFieldTypeComposerComponent&& other) = delete;

  Type GetComponentType() const override;

  bool Process(std::stack<component_t>& stack) override;
};

//! The component which is created at the end of field creation.
class EndFieldTypeComposerComponent : public AbstractTypeComposerComponent
{
public:
  EndFieldTypeComposerComponent() = default;
  ~EndFieldTypeComposerComponent() override = default;
  EndFieldTypeComposerComponent(const EndFieldTypeComposerComponent& other) = delete;
  EndFieldTypeComposerComponent(EndFieldTypeComposerComponent&& other) = delete;
  EndFieldTypeComposerComponent& operator=(const EndFieldTypeComposerComponent& other) = delete;
  EndFieldTypeComposerComponent& operator=(EndFieldTypeComposerComponent&& other) = delete;

  Type GetComponentType() const override;

  bool Process(std::stack<component_t>& stack) override;
};

//! The component which is created at the start of an array.
class StartArrayTypeComposerComponent : public AbstractTypeComposerComponent
{
public:
  StartArrayTypeComposerComponent(const std::string& array_name, sup::dto::uint64 array_size);

  ~StartArrayTypeComposerComponent() override = default;
  StartArrayTypeComposerComponent(const StartArrayTypeComposerComponent& other) = delete;
  StartArrayTypeComposerComponent(StartArrayTypeComposerComponent&& other) = delete;
  StartArrayTypeComposerComponent& operator=(const StartArrayTypeComposerComponent& other) = delete;
  StartArrayTypeComposerComponent& operator=(StartArrayTypeComposerComponent&& other) = delete;

  Type GetComponentType() const override;

  bool Process(std::stack<component_t>& stack) override;

  void AddElement(const sup::dto::AnyType& anytype) override;

private:
  std::string m_array_name;
  sup::dto::uint64 m_array_size;
};

//! The component which is created at the end of an array.
class EndArrayTypeComposerComponent : public AbstractTypeComposerComponent
{
public:
  EndArrayTypeComposerComponent() = default;
  ~EndArrayTypeComposerComponent() override = default;
  EndArrayTypeComposerComponent(const EndArrayTypeComposerComponent& other) = delete;
  EndArrayTypeComposerComponent(EndArrayTypeComposerComponent&& other) = delete;
  EndArrayTypeComposerComponent& operator=(const EndArrayTypeComposerComponent& other) = delete;
  EndArrayTypeComposerComponent& operator=(EndArrayTypeComposerComponent&& other) = delete;

  Type GetComponentType() const override;

  bool Process(std::stack<component_t>& stack) override;
};

//! The component which is created at the start of an element in an array.
class StartArrayElementTypeComposerComponent : public AbstractTypeComposerComponent
{
public:
  StartArrayElementTypeComposerComponent() = default;
  ~StartArrayElementTypeComposerComponent() override = default;
  StartArrayElementTypeComposerComponent(const StartArrayElementTypeComposerComponent& other) = delete;
  StartArrayElementTypeComposerComponent(StartArrayElementTypeComposerComponent&& other) = delete;
  StartArrayElementTypeComposerComponent& operator=(const StartArrayElementTypeComposerComponent& other) = delete;
  StartArrayElementTypeComposerComponent& operator=(StartArrayElementTypeComposerComponent&& other) = delete;

  Type GetComponentType() const override;

  bool Process(std::stack<component_t>& stack) override;
};

//! The component which is created at the end of an element in an array.
class EndArrayElementTypeComposerComponent : public AbstractTypeComposerComponent
{
public:
  EndArrayElementTypeComposerComponent() = default;
  ~EndArrayElementTypeComposerComponent() override = default;
  EndArrayElementTypeComposerComponent(const EndArrayElementTypeComposerComponent& other) = delete;
  EndArrayElementTypeComposerComponent(EndArrayElementTypeComposerComponent&& other) = delete;
  EndArrayElementTypeComposerComponent& operator=(const EndArrayElementTypeComposerComponent& other) = delete;
  EndArrayElementTypeComposerComponent& operator=(EndArrayElementTypeComposerComponent&& other) = delete;

  Type GetComponentType() const override;

  bool Process(std::stack<component_t>& stack) override;
};


}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_COMPOSER_ANYTYPE_COMPOSER_COMPONENTS_H_
