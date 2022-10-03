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

#ifndef SUP_DTO_COMPOSER_ANYVALUE_BUILDNODES_H_
#define SUP_DTO_COMPOSER_ANYVALUE_BUILDNODES_H_

//! @file anyvalue_buildnode.h
//! Collection of classes representing nodes for AnyValueBuildAdapterV2.

#include <sup/dto/composer/abstract_composer_component.h>

#include <string>

namespace sup
{
namespace dto
{

//! The node to build AnyValue. Used when a single scalar is necessary, or during adding the
//! structure's field or the element of the array.

class AnyValueBuildNode : public AbstractComposerComponent
{
public:
  AnyValueBuildNode(const sup::dto::AnyValue& value);

  NodeType GetNodeType() const override;

  bool Process(std::stack<node_t>& stack) override;
};

//! The node which is created at the start of the structure.

class StartStructBuildNode : public AbstractComposerComponent
{
public:
  StartStructBuildNode(const std::string& struct_name);

  NodeType GetNodeType() const override;

  bool Process(std::stack<node_t>& stack) override;

  void AddMember(const std::string& name, const sup::dto::AnyValue& value) override;
};

//! The node which is created at the end of the structure.

class EndStructBuildNode : public AbstractComposerComponent
{
public:
  NodeType GetNodeType() const override;

  bool Process(std::stack<node_t>& stack) override;
};

//! The node which is created at the beginning of the field creation.

class StartFieldBuildNode : public AbstractComposerComponent
{
public:
  explicit StartFieldBuildNode(const std::string& field_name);

  NodeType GetNodeType() const override;

  bool Process(std::stack<node_t>& stack) override;
};

//! The node which is created at the end of the field creation.

class EndFieldBuildNode : public AbstractComposerComponent
{
public:
  NodeType GetNodeType() const override;

  bool Process(std::stack<node_t>& stack) override;
};

//! The node which is created at the start of the array.

class StartArrayBuildNode : public AbstractComposerComponent
{
public:
  StartArrayBuildNode(const std::string& array_name);

  NodeType GetNodeType() const override;

  bool Process(std::stack<node_t>& stack) override;

  void AddElement(const sup::dto::AnyValue& value) override;

private:
  std::string m_array_name{};
};

//! The node which is created at the end of the array.

class EndArrayBuildNode : public AbstractComposerComponent
{
public:
  NodeType GetNodeType() const override;

  bool Process(std::stack<node_t>& stack) override;
};

//! The node which is created at the start of the element in the array.

class StartArrayElementBuildNode : public AbstractComposerComponent
{
public:
  NodeType GetNodeType() const override;

  bool Process(std::stack<node_t>& stack) override;
};

//! The node which is created at the start of the element in the array.

class EndArrayElementBuildNode : public AbstractComposerComponent
{
public:
  NodeType GetNodeType() const override;

  bool Process(std::stack<node_t>& stack) override;
};

}  // namespace dto
}  // namespace sup

#endif  // SUP_DTO_COMPOSER_ANYVALUE_BUILDNODES_H_
