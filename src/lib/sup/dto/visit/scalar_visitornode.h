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

#ifndef SUP_DTO_SCALAR_VISITORNODE_H_
#define SUP_DTO_SCALAR_VISITORNODE_H_

#include <sup/dto/visit/any_visitornode.h>

namespace sup
{
namespace dto
{
/**
 * @brief Templated visitor node for scalar types.
 */
template <typename T>
class ScalarVisitorNode : public IAnyVisitorNode<T>
{
public:
  explicit ScalarVisitorNode(T* any);
  ~ScalarVisitorNode() override;

  ScalarVisitorNode(const ScalarVisitorNode& other) = delete;
  ScalarVisitorNode(ScalarVisitorNode&& other) = delete;
  ScalarVisitorNode& operator=(const ScalarVisitorNode& other) = delete;
  ScalarVisitorNode& operator=(ScalarVisitorNode&& other) = delete;

  std::unique_ptr<IAnyVisitorNode<T>> NextChild() override;

  void AddProlog(IAnyVisitor<T>& visitor) const override;
  void AddSeparator(IAnyVisitor<T>& visitor) const override;
  void AddEpilog(IAnyVisitor<T>& visitor) const override;
};

template <typename T>
ScalarVisitorNode<T>::ScalarVisitorNode(T* any)
  : IAnyVisitorNode<T>{any}
{}

template <typename T>
ScalarVisitorNode<T>::~ScalarVisitorNode() = default;

template <typename T>
std::unique_ptr<IAnyVisitorNode<T>> ScalarVisitorNode<T>::NextChild()
{
  return {};
}

template <typename T>
void ScalarVisitorNode<T>::AddProlog(IAnyVisitor<T>& visitor) const
{
  visitor.ScalarProlog(this->GetValue());
}

template <typename T>
void ScalarVisitorNode<T>::AddSeparator(IAnyVisitor<T>&) const
{}

template <typename T>
void ScalarVisitorNode<T>::AddEpilog(IAnyVisitor<T>& visitor) const
{
  visitor.ScalarEpilog(this->GetValue());
}

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_SCALAR_VISITORNODE_H_
