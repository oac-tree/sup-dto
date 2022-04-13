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
 * @file MemberVisitorNode.h
 * @brief Header file for the MemberVisitorNode class template.
 * @date 16/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the MemberVisitorNode class template.
 */

#ifndef _SUP_MemberVisitorNode_h_
#define _SUP_MemberVisitorNode_h_

#include "AnyVisitorNode.h"
#include "CreateAnyVisitorNode.h"

#include <string>

namespace sup
{
namespace dto
{
/**
 * @brief Templated visitor node for members of structured types.
 */
template <typename T>
class MemberVisitorNode : public IAnyVisitorNode<T>
{
public:
  MemberVisitorNode(T* any, const std::string& member_name);
  ~MemberVisitorNode() override;

  std::unique_ptr<IAnyVisitorNode<T>> NextChild() override;

  void AddProlog(IAnyVisitor<T>& serializer) const override;
  void AddSeparator(IAnyVisitor<T>& serializer) const override;
  void AddEpilog(IAnyVisitor<T>& serializer) const override;

private:
  std::string member_name;
  bool child_returned;
};

template <typename T>
MemberVisitorNode<T>::MemberVisitorNode(T* any, const std::string& member_name_)
  : IAnyVisitorNode<T>{any}
  , member_name{member_name_}
  , child_returned{false}
{}

template <typename T>
MemberVisitorNode<T>::~MemberVisitorNode() = default;

template <typename T>
std::unique_ptr<IAnyVisitorNode<T>> MemberVisitorNode<T>::NextChild()
{
  if (child_returned)
  {
    return {};
  }
  child_returned = true;
  return CreateVisitorNode(this->GetValue());
}

template <typename T>
void MemberVisitorNode<T>::AddProlog(IAnyVisitor<T>& serializer) const
{
  serializer.MemberProlog(this->GetValue(), member_name);
}

template <typename T>
void MemberVisitorNode<T>::AddSeparator(IAnyVisitor<T>&) const
{}

template <typename T>
void MemberVisitorNode<T>::AddEpilog(IAnyVisitor<T>& serializer) const
{
  serializer.MemberEpilog(this->GetValue(), member_name);
}

}  // namespace dto

}  // namespace sup

#endif  // _SUP_MemberVisitorNode_h_
