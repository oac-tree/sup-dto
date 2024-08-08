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

#ifndef SUP_DTO_ANY_VISITORNODE_H_
#define SUP_DTO_ANY_VISITORNODE_H_

#include <sup/dto/i_any_visitor.h>

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
  explicit IAnyVisitorNode(T* val);
  virtual ~IAnyVisitorNode() = default;

  IAnyVisitorNode(const IAnyVisitorNode& other) = delete;
  IAnyVisitorNode(IAnyVisitorNode&& other) = delete;
  IAnyVisitorNode& operator=(const IAnyVisitorNode& other) = delete;
  IAnyVisitorNode& operator=(IAnyVisitorNode&& other) = delete;

  T* GetValue() const &;

  virtual std::unique_ptr<IAnyVisitorNode<T>> NextChild() = 0;

  virtual void AddProlog(IAnyVisitor<T>& visitor) const = 0;
  virtual void AddSeparator(IAnyVisitor<T>& visitor) const = 0;
  virtual void AddEpilog(IAnyVisitor<T>& visitor) const = 0;

private:
  T* m_any;
};

/**
 * @brief Templated RAII class for IAnyVisitorNode classes.
 */
template <typename T>
class AnyVisitorNode
{
public:
  explicit AnyVisitorNode(std::unique_ptr<IAnyVisitorNode<T>> node);
  ~AnyVisitorNode();

  AnyVisitorNode(AnyVisitorNode&& other) = default;
  AnyVisitorNode& operator=(AnyVisitorNode&& other) & noexcept;

  AnyVisitorNode(const AnyVisitorNode&) = delete;
  AnyVisitorNode& operator=(const AnyVisitorNode& other) = delete;

  AnyVisitorNode NextChild();
  bool IsValid() const;

  void AddProlog(IAnyVisitor<T>& visitor) const;
  void AddSeparator(IAnyVisitor<T>& visitor) const;
  void AddEpilog(IAnyVisitor<T>& visitor) const;

private:
  std::unique_ptr<IAnyVisitorNode<T>> m_node;
};

template <typename T>
IAnyVisitorNode<T>::IAnyVisitorNode(T* val)
  : m_any{val}
{}

template <typename T>
T* IAnyVisitorNode<T>::GetValue() const &
{
  return m_any;
}

template <typename T>
AnyVisitorNode<T>::AnyVisitorNode(std::unique_ptr<IAnyVisitorNode<T>> node)
  : m_node{std::move(node)}
{}

template <typename T>
AnyVisitorNode<T>::~AnyVisitorNode() = default;

template <typename T>
AnyVisitorNode<T>& AnyVisitorNode<T>::operator=(AnyVisitorNode<T>&& other) & noexcept
{
  if (this != &other)
  {
    AnyVisitorNode moved{std::move(other)};
    std::swap(this->m_node, moved.m_node);
  }
  return *this;
}

template <typename T>
AnyVisitorNode<T> AnyVisitorNode<T>::NextChild()
{
  return AnyVisitorNode{m_node->NextChild()};
}

template <typename T>
bool AnyVisitorNode<T>::IsValid() const
{
  return m_node != nullptr;
}

template <typename T>
void AnyVisitorNode<T>::AddProlog(IAnyVisitor<T>& visitor) const
{
  return m_node->AddProlog(visitor);
}

template <typename T>
void AnyVisitorNode<T>::AddSeparator(IAnyVisitor<T>& visitor) const
{
  return m_node->AddSeparator(visitor);
}

template <typename T>
void AnyVisitorNode<T>::AddEpilog(IAnyVisitor<T>& visitor) const
{
  return m_node->AddEpilog(visitor);
}

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ANY_VISITORNODE_H_
