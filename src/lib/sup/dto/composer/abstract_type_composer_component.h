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

#ifndef SUP_DTO_COMPOSER_ABSTRACT_TYPE_COMPOSER_COMPONENT_H_
#define SUP_DTO_COMPOSER_ABSTRACT_TYPE_COMPOSER_COMPONENT_H_

#include <sup/dto/anytype.h>

#include <memory>
#include <stack>
#include <string>

namespace sup
{
namespace dto
{

//! The component for AnyTypeComposer to build AnyType.

class AbstractTypeComposerComponent
{
public:
  using component_t = std::unique_ptr<AbstractTypeComposerComponent>;

  AbstractTypeComposerComponent();
  AbstractTypeComposerComponent(const sup::dto::AnyType& anytype);

  virtual ~AbstractTypeComposerComponent();

  enum class Type
  {
    kLeafType,
    kStartStruct,
    kEndStruct,
    kStartField,
    kEndField,
    kStartArray,
    kEndArray,
    kStartArrayElement,
    kEndArrayElement
  };

  virtual Type GetComponentType() const = 0;

  //! Performs manipulations with the stack, if necessary.
  //! @return True if component wants it to be saved in a stack.
  virtual bool Process(std::stack<component_t>& stack) = 0;

  void Consume(sup::dto::AnyType&& anytype);

  sup::dto::AnyType MoveAnyType();

  std::string GetFieldName() const;
  void SetFieldName(const std::string& name);

  virtual void AddMember(const std::string& name, const sup::dto::AnyType& anytype);

  virtual void AddElement(const sup::dto::AnyType& anytype);

protected:
  sup::dto::AnyType m_type;
  std::string m_field_name;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_COMPOSER_ABSTRACT_TYPE_COMPOSER_COMPONENT_H_
