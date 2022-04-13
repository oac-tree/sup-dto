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
 * @file StructSerializeNode.h
 * @brief Header file for the StructSerializeNode class template.
 * @date 16/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the StructSerializeNode class template.
 */

#ifndef _SUP_StructSerializeNode_h_
#define _SUP_StructSerializeNode_h_

#include "AnySerializeNode.h"
#include "MemberSerializeNode.h"

namespace sup
{
namespace dto
{
/**
 * @brief Templated Serialization node for structured types.
 */
template <typename T>
class StructSerializeNode : public IAnySerializeNode<T>
{
public:
  StructSerializeNode(const T* any);
  ~StructSerializeNode() override;

  std::unique_ptr<IAnySerializeNode<T>> NextChild() override;

  void AddProlog(IAnyVisitor<const T>& serializer) const override;
  void AddSeparator(IAnyVisitor<const T>& serializer) const override;
  void AddEpilog(IAnyVisitor<const T>& serializer) const override;

private:
  std::size_t next_index;
};

template <typename T>
StructSerializeNode<T>::StructSerializeNode(const T* any)
  : IAnySerializeNode<T>{any}
  , next_index{0}
{}

template <typename T>
StructSerializeNode<T>::~StructSerializeNode() = default;

template <typename T>
std::unique_ptr<IAnySerializeNode<T>> StructSerializeNode<T>::NextChild()
{
  auto member_names = this->GetValue()->MemberNames();
  if (next_index >= member_names.size())
  {
    return {};
  }
  auto member_name = member_names[next_index];
  ++next_index;
  const T *member_type = &this->GetValue()->operator[](member_name);
  std::unique_ptr<IAnySerializeNode<T>> result{
      new MemberSerializeNode<T>(member_type, member_name)};
  return result;
}

template <typename T>
void StructSerializeNode<T>::AddProlog(IAnyVisitor<const T>& serializer) const
{
  serializer.StructProlog(this->GetValue());
}

template <typename T>
void StructSerializeNode<T>::AddSeparator(IAnyVisitor<const T>& serializer) const
{
  serializer.StructMemberSeparator();
}

template <typename T>
void StructSerializeNode<T>::AddEpilog(IAnyVisitor<const T>& serializer) const
{
  serializer.StructEpilog(this->GetValue());
}

}  // namespace dto

}  // namespace sup

#endif  // _SUP_StructSerializeNode_h_
