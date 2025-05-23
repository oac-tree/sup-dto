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
 * SPDX-License-Identifier: MIT
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file LICENSE located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#ifndef SUP_DTO_I_ANY_VISITOR_H_
#define SUP_DTO_I_ANY_VISITOR_H_

#include <string>

namespace sup
{
namespace dto
{

/**
 * @brief Interface that gets called repeatedly while visiting an AnyType/AnyValue tree.
 *
 * @details
 */
template <typename T>
class IAnyVisitor
{
public:
  IAnyVisitor() = default;
  virtual ~IAnyVisitor() = default;

  IAnyVisitor(const IAnyVisitor&) = delete;
  IAnyVisitor& operator=(const IAnyVisitor&) = delete;
  IAnyVisitor(IAnyVisitor&&) = delete;
  IAnyVisitor& operator=(IAnyVisitor&&) = delete;

  virtual void EmptyProlog(T* val) = 0;
  virtual void EmptyEpilog(T* val) = 0;

  virtual void StructProlog(T* val) = 0;
  virtual void StructMemberSeparator() = 0;
  virtual void StructEpilog(T* val) = 0;

  virtual void MemberProlog(T* val, const std::string& member_name) = 0;
  virtual void MemberEpilog(T* val, const std::string& member_name) = 0;

  virtual void ArrayProlog(T* val) = 0;
  virtual void ArrayElementSeparator() = 0;
  virtual void ArrayEpilog(T* val) = 0;

  virtual void ScalarProlog(T* val) = 0;
  virtual void ScalarEpilog(T* val) = 0;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_I_ANY_VISITOR_H_
