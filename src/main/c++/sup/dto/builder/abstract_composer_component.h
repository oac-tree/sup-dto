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
 * Copyright (c) : 2010-2022 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#ifndef SUP_DTO_BUILDER_ABSTRACT_COMPOSER_COMPONENT_H_
#define SUP_DTO_BUILDER_ABSTRACT_COMPOSER_COMPONENT_H_

#include <sup/dto/anyvalue.h>

#include <memory>
#include <stack>
#include <string>

namespace sup
{
namespace dto
{

//! The node for AnyValueBuildAdapter to build AnyValue.

class AbstractComposerComponent
{
public:
  virtual ~AbstractComposerComponent() = default;
  using node_t = std::unique_ptr<AbstractComposerComponent>;

  enum class NodeType
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

  AbstractComposerComponent();
  AbstractComposerComponent(const sup::dto::AnyValue& value);

  virtual NodeType GetNodeType() const = 0;

  //! Performs manipulations with the stack, if necessary.
  //! @return True if nodes wants it to be saved in a stack.
  virtual bool Process(std::stack<node_t>& stack) = 0;

  virtual void Consume(sup::dto::AnyValue&& value);

  sup::dto::AnyValue MoveAnyValue() const;

  std::string GetFieldName() const;
  void SetFieldName(const std::string& name);

  virtual void AddMember(const std::string& name, const sup::dto::AnyValue& value);

  virtual void AddElement(const sup::dto::AnyValue& value);

protected:
  sup::dto::AnyValue m_value;
  std::string m_field_name;
};

}  // namespace dto
}  // namespace sup

#endif  // SUP_DTO_BUILDER_ABSTRACT_COMPOSER_COMPONENT_H_
