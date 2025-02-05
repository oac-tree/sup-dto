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

#ifndef SUP_DTO_ARRAY_TYPE_DATA_H_
#define SUP_DTO_ARRAY_TYPE_DATA_H_

#include <sup/dto/anyvalue/i_type_data.h>

namespace sup
{
namespace dto
{
class ArrayTypeData : public ITypeData
{
public:
  ArrayTypeData(std::size_t size, const AnyType& elem_type, const std::string& name);
  ArrayTypeData(std::size_t size, AnyType&& elem_type, const std::string& name);
  ~ArrayTypeData() override;

  ArrayTypeData(const ArrayTypeData& other) = delete;
  ArrayTypeData(ArrayTypeData&& other) = delete;
  ArrayTypeData& operator=(const ArrayTypeData& other) = delete;
  ArrayTypeData& operator=(ArrayTypeData&& other) = delete;

  TypeCode GetTypeCode() const override;
  std::string GetTypeName() const override;

  AnyType ElementType() const override;
  std::size_t NumberOfElements() const override;

  bool HasChild(const std::string& child_name) const override;
  std::vector<std::string> ChildNames() const override;
  AnyType* GetChildType(const std::string& child_name) override;
  std::unique_ptr<ITypeData> CloneFromChildren(
    std::vector<std::unique_ptr<AnyType>>&& children) const override;

  bool ShallowEquals(const AnyType& other) const override;

private:
  std::size_t m_size;
  AnyType m_elem_type;
  std::string m_name;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ARRAY_TYPE_DATA_H_
