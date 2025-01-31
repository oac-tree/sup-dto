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

#ifndef SUP_DTO_I_TYPE_DATA_H_
#define SUP_DTO_I_TYPE_DATA_H_

#include <sup/dto/anytype.h>

namespace sup
{
namespace dto
{
class ITypeData
{
public:
  ITypeData() = default;
  virtual ~ITypeData();

  ITypeData(const ITypeData&) = delete;
  ITypeData& operator=(const ITypeData&) = delete;
  ITypeData(ITypeData&&) = delete;
  ITypeData& operator=(ITypeData&&) = delete;

  virtual TypeCode GetTypeCode() const = 0;
  virtual std::string GetTypeName() const = 0;

  // Pass AnyType by value to support both lvalues and rvalues
  virtual void AddMember(const std::string&, AnyType&&);
  virtual std::vector<std::string> MemberNames() const;
  virtual std::size_t NumberOfMembers() const;

  virtual AnyType ElementType() const;
  virtual std::size_t NumberOfElements() const;

  virtual bool HasChild(const std::string& child_name) const;
  virtual std::vector<std::string> ChildNames() const;
  virtual AnyType* GetChildType(const std::string& child_name);
  virtual std::unique_ptr<ITypeData> CloneFromChildren(std::vector<AnyType>&& children) const = 0;

  virtual bool ShallowEquals(const AnyType& other) const = 0;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_I_TYPE_DATA_H_
