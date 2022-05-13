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

#ifndef _SUP_AnyVisitorNode_h_
#define _SUP_AnyVisitorNode_h_

#include "sup/dto/IAnyVisitor.h"

#include <memory>

namespace sup
{
namespace dto
{

/**
 * @brief Templated interface for thin nodes to visit an AnyType/AnyValue tree in
 * Depth First Search.
 *
 * @details Example usage is the serialization of AnyType/AnyValue without recursion.
 */
template <typename T>
class IAnyVisitorNode
{
public:
  IAnyVisitorNode(T* val);
  virtual ~IAnyVisitorNode() = default;

  T* GetValue() const;

  virtual std::unique_ptr<IAnyVisitorNode<T>> NextChild() = 0;

  virtual void AddProlog(IAnyVisitor<T>& visitor) const = 0;
  virtual void AddSeparator(IAnyVisitor<T>& visitor) const = 0;
  virtual void AddEpilog(IAnyVisitor<T>& visitor) const = 0;

private:
  T* val;
};

/**
 * @brief Templated RAII class for IAnyVisitorNode classes.
 */
template <typename T>
class AnyVisitorNode
{
public:
  AnyVisitorNode(std::unique_ptr<IAnyVisitorNode<T>> node);
  ~AnyVisitorNode();

  AnyVisitorNode(AnyVisitorNode&& other);
  AnyVisitorNode& operator=(AnyVisitorNode&& other);

  AnyVisitorNode(const AnyVisitorNode&) = delete;
  AnyVisitorNode& operator=(const AnyVisitorNode& other) = delete;

  AnyVisitorNode NextChild();
  bool IsValid() const;

  void AddProlog(IAnyVisitor<T>& visitor) const;
  void AddSeparator(IAnyVisitor<T>& visitor) const;
  void AddEpilog(IAnyVisitor<T>& visitor) const;

private:
  std::unique_ptr<IAnyVisitorNode<T>> node;
};

template <typename T>
IAnyVisitorNode<T>::IAnyVisitorNode(T* val_)
  : val{val_}
{}

template <typename T>
T* IAnyVisitorNode<T>::GetValue() const
{
  return val;
}

template <typename T>
AnyVisitorNode<T>::AnyVisitorNode(std::unique_ptr<IAnyVisitorNode<T>> node_)
  : node{std::move(node_)}
{}

template <typename T>
AnyVisitorNode<T>::~AnyVisitorNode() = default;

template <typename T>
AnyVisitorNode<T>::AnyVisitorNode(AnyVisitorNode<T>&& other)
  : node{std::move(other.node)}
{}

template <typename T>
AnyVisitorNode<T>& AnyVisitorNode<T>::operator=(AnyVisitorNode<T>&& other)
{
  if (this != &other)
  {
    AnyVisitorNode moved{std::move(other)};
    std::swap(this->node, moved.node);
  }
  return *this;
}

template <typename T>
AnyVisitorNode<T> AnyVisitorNode<T>::NextChild()
{
  return node->NextChild();
}

template <typename T>
bool AnyVisitorNode<T>::IsValid() const
{
  return static_cast<bool>(node);
}

template <typename T>
void AnyVisitorNode<T>::AddProlog(IAnyVisitor<T>& visitor) const
{
  return node->AddProlog(visitor);
}

template <typename T>
void AnyVisitorNode<T>::AddSeparator(IAnyVisitor<T>& visitor) const
{
  return node->AddSeparator(visitor);
}

template <typename T>
void AnyVisitorNode<T>::AddEpilog(IAnyVisitor<T>& visitor) const
{
  return node->AddEpilog(visitor);
}

}  // namespace dto

}  // namespace sup

#endif  // _SUP_AnyVisitorNode_h_
