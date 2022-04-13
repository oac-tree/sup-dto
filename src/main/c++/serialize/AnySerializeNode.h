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

/**
 * @file AnySerializeNode.h
 * @brief Header file for serialization node class templates.
 * @date 15/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the serialization node class templates.
 */

#ifndef _SUP_AnySerializeNode_h_
#define _SUP_AnySerializeNode_h_

#include "IAnyVisitor.h"

#include <memory>

namespace sup
{
namespace dto
{

/**
 * @brief Templated interface for thin nodes that iterate over an AnyType/AnyValue tree in
 * Depth First Search.
 *
 * @details This class hierarchy is used for serialization without recursion.
 */
template <typename T>
class IAnySerializeNode
{
public:
  IAnySerializeNode(const T* val);
  virtual ~IAnySerializeNode() = default;

  const T* GetValue() const;

  virtual std::unique_ptr<IAnySerializeNode<T>> NextChild() = 0;

  virtual void AddProlog(IAnyVisitor<const T>& serializer) const = 0;
  virtual void AddSeparator(IAnyVisitor<const T>& serializer) const = 0;
  virtual void AddEpilog(IAnyVisitor<const T>& serializer) const = 0;

private:
  const T* val;
};

/**
 * @brief Templated RAII class for IAnySerializeNode classes.
 */
template <typename T>
class AnySerializeNode
{
public:
  AnySerializeNode(std::unique_ptr<IAnySerializeNode<T>> node);
  ~AnySerializeNode();

  AnySerializeNode(AnySerializeNode&& other);
  AnySerializeNode& operator=(AnySerializeNode&& other);

  AnySerializeNode(const AnySerializeNode&) = delete;
  AnySerializeNode& operator=(const AnySerializeNode& other) = delete;

  AnySerializeNode NextChild();
  bool IsValid() const;

  void AddProlog(IAnyVisitor<const T>& serializer) const;
  void AddSeparator(IAnyVisitor<const T>& serializer) const;
  void AddEpilog(IAnyVisitor<const T>& serializer) const;

private:
  std::unique_ptr<IAnySerializeNode<T>> node;
};

template <typename T>
IAnySerializeNode<T>::IAnySerializeNode(const T* val_)
  : val{val_}
{}

template <typename T>
const T* IAnySerializeNode<T>::GetValue() const
{
  return val;
}

template <typename T>
AnySerializeNode<T>::AnySerializeNode(std::unique_ptr<IAnySerializeNode<T>> node_)
  : node{std::move(node_)}
{}

template <typename T>
AnySerializeNode<T>::~AnySerializeNode() = default;

template <typename T>
AnySerializeNode<T>::AnySerializeNode(AnySerializeNode<T>&& other)
  : node{std::move(other.node)}
{}

template <typename T>
AnySerializeNode<T>& AnySerializeNode<T>::operator=(AnySerializeNode<T>&& other)
{
  if (this != &other)
  {
    AnySerializeNode moved{std::move(other)};
    std::swap(this->node, moved.node);
  }
  return *this;
}

template <typename T>
AnySerializeNode<T> AnySerializeNode<T>::NextChild()
{
  return node->NextChild();
}

template <typename T>
bool AnySerializeNode<T>::IsValid() const
{
  return static_cast<bool>(node);
}

template <typename T>
void AnySerializeNode<T>::AddProlog(IAnyVisitor<const T>& serializer) const
{
  return node->AddProlog(serializer);
}

template <typename T>
void AnySerializeNode<T>::AddSeparator(IAnyVisitor<const T>& serializer) const
{
  return node->AddSeparator(serializer);
}

template <typename T>
void AnySerializeNode<T>::AddEpilog(IAnyVisitor<const T>& serializer) const
{
  return node->AddEpilog(serializer);
}

}  // namespace dto

}  // namespace sup

#endif  // _SUP_AnySerializeNode_h_
