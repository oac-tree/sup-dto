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
 * @file MemberSerializeNode.h
 * @brief Header file for the MemberSerializeNode class template.
 * @date 16/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the MemberSerializeNode class template.
 */

#ifndef _SUP_MemberSerializeNode_h_
#define _SUP_MemberSerializeNode_h_

#include "AnyVisitorNode.h"
#include "CreateAnySerializeNode.h"

#include <string>

namespace sup
{
namespace dto
{
/**
 * @brief Templated serialization node for members of structured types.
 */
template <typename T>
class MemberSerializeNode : public IAnyVisitorNode<const T>
{
public:
  MemberSerializeNode(const T* any, const std::string& member_name);
  ~MemberSerializeNode() override;

  std::unique_ptr<IAnyVisitorNode<const T>> NextChild() override;

  void AddProlog(IAnyVisitor<const T>& serializer) const override;
  void AddSeparator(IAnyVisitor<const T>& serializer) const override;
  void AddEpilog(IAnyVisitor<const T>& serializer) const override;

private:
  std::string member_name;
  bool child_returned;
};

template <typename T>
MemberSerializeNode<T>::MemberSerializeNode(const T* any, const std::string& member_name_)
  : IAnyVisitorNode<const T>{any}
  , member_name{member_name_}
  , child_returned{false}
{}

template <typename T>
MemberSerializeNode<T>::~MemberSerializeNode() = default;

template <typename T>
std::unique_ptr<IAnyVisitorNode<const T>> MemberSerializeNode<T>::NextChild()
{
  if (child_returned)
  {
    return {};
  }
  child_returned = true;
  return CreateSerializeNode(this->GetValue());
}

template <typename T>
void MemberSerializeNode<T>::AddProlog(IAnyVisitor<const T>& serializer) const
{
  serializer.MemberProlog(this->GetValue(), member_name);
}

template <typename T>
void MemberSerializeNode<T>::AddSeparator(IAnyVisitor<const T>&) const
{}

template <typename T>
void MemberSerializeNode<T>::AddEpilog(IAnyVisitor<const T>& serializer) const
{
  serializer.MemberEpilog(this->GetValue(), member_name);
}

}  // namespace dto

}  // namespace sup

#endif  // _SUP_MemberSerializeNode_h_
