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

#ifndef SUP_DTO_STRUCT_VISITORNODE_H_
#define SUP_DTO_STRUCT_VISITORNODE_H_

#include <sup/dto/visit/any_visitornode.h>
#include <sup/dto/visit/member_visitornode.h>

namespace sup
{
namespace dto
{
/**
 * @brief Templated visitor node for structured types.
 */
template <typename T>
class StructVisitorNode : public IAnyVisitorNode<T>
{
public:
  StructVisitorNode(T* any);
  ~StructVisitorNode() override;

  std::unique_ptr<IAnyVisitorNode<T>> NextChild() override;

  void AddProlog(IAnyVisitor<T>& visitor) const override;
  void AddSeparator(IAnyVisitor<T>& visitor) const override;
  void AddEpilog(IAnyVisitor<T>& visitor) const override;

private:
  std::size_t next_index;
};

template <typename T>
StructVisitorNode<T>::StructVisitorNode(T* any)
  : IAnyVisitorNode<T>{any}
  , next_index{0}
{}

template <typename T>
StructVisitorNode<T>::~StructVisitorNode() = default;

template <typename T>
std::unique_ptr<IAnyVisitorNode<T>> StructVisitorNode<T>::NextChild()
{
  auto member_names = this->GetValue()->MemberNames();
  if (next_index >= member_names.size())
  {
    return {};
  }
  auto member_name = member_names[next_index];
  ++next_index;
  T *member_type = &this->GetValue()->operator[](member_name);
  std::unique_ptr<IAnyVisitorNode<T>> result{
      new MemberVisitorNode<T>(member_type, member_name)};
  return result;
}

template <typename T>
void StructVisitorNode<T>::AddProlog(IAnyVisitor<T>& visitor) const
{
  visitor.StructProlog(this->GetValue());
}

template <typename T>
void StructVisitorNode<T>::AddSeparator(IAnyVisitor<T>& visitor) const
{
  visitor.StructMemberSeparator();
}

template <typename T>
void StructVisitorNode<T>::AddEpilog(IAnyVisitor<T>& visitor) const
{
  visitor.StructEpilog(this->GetValue());
}

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_STRUCT_VISITORNODE_H_
