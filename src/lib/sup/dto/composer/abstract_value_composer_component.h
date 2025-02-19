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

#ifndef SUP_DTO_COMPOSER_ABSTRACT_COMPOSER_COMPONENT_H_
#define SUP_DTO_COMPOSER_ABSTRACT_COMPOSER_COMPONENT_H_

#include <sup/dto/anyvalue.h>

#include <memory>
#include <stack>
#include <string>

namespace sup
{
namespace dto
{

//! The component for AnyValueComposer to build AnyValue.

class AbstractValueComposerComponent
{
public:
  virtual ~AbstractValueComposerComponent();
  using component_t = std::unique_ptr<AbstractValueComposerComponent>;

  enum class Type : sup::dto::uint32
  {
    kValue,
    kStartStruct,
    kEndStruct,
    kStartField,
    kEndField,
    kStartArray,
    kEndArray,
    kStartArrayElement,
    kEndArrayElement
  };

  AbstractValueComposerComponent();
  explicit AbstractValueComposerComponent(const sup::dto::AnyValue& value);

  AbstractValueComposerComponent(AbstractValueComposerComponent&& other) = delete;
  AbstractValueComposerComponent& operator=(AbstractValueComposerComponent&&) = delete;

  virtual Type GetComponentType() const = 0;

  //! Performs manipulations with the stack, if necessary.
  //! @return True if component wants it to be saved in a stack.
  virtual bool Process(std::stack<component_t>& stack) = 0;

  void Consume(sup::dto::AnyValue&& value);

  sup::dto::AnyValue MoveAnyValue();

  std::string GetFieldName() const;
  void SetFieldName(const std::string& name);

  virtual void AddMember(const std::string&, const sup::dto::AnyValue&);

  virtual void AddElement(const sup::dto::AnyValue&);

protected:
  sup::dto::AnyValue& GetValue() &;
  void SetValue(const sup::dto::AnyValue& value);

private:
  sup::dto::AnyValue m_value;
  std::string m_field_name;
};

}  // namespace dto
}  // namespace sup

#endif  // SUP_DTO_COMPOSER_ABSTRACT_COMPOSER_COMPONENT_H_
