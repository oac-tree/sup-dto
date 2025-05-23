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

#ifndef SUP_DTO_ARRAY_VALUE_DATA_H_
#define SUP_DTO_ARRAY_VALUE_DATA_H_

#include <sup/dto/anyvalue/i_value_data.h>

#include <vector>

namespace sup
{
namespace dto
{
class ArrayValueData : public IValueData
{
public:
  ArrayValueData(const AnyType& elem_type, const std::string& name, Constraints constraints);
  ~ArrayValueData() override;

  ArrayValueData(const ArrayValueData& other) = delete;
  ArrayValueData(ArrayValueData&& other) = delete;
  ArrayValueData& operator=(const ArrayValueData& other) = delete;
  ArrayValueData& operator=(ArrayValueData&& other) = delete;

  TypeCode GetTypeCode() const override;
  std::string GetTypeName() const override;

  Constraints GetConstraints() const override;

  void AddElement(std::unique_ptr<AnyValue>&& value) override;
  std::size_t NumberOfElements() const override;
  AnyType ElementType() const override;

  AnyValue& operator[](std::size_t idx) override;

  std::size_t NumberOfChildren() const override;
  bool HasChild(const std::string& child_name) const override;
  AnyValue* GetChildValue(const std::string& child_name) override;
  AnyValue* GetChildValue(std::size_t idx) override;
  std::unique_ptr<IValueData> CloneFromChildren(std::vector<std::unique_ptr<AnyValue>>&& children,
                                                Constraints constraints) const override;
  bool ShallowEquals(const IValueData* other) const override;
  void ShallowConvertFrom(const AnyValue& value) override;

private:
  AnyType m_elem_type;
  std::string m_name;
  std::vector<std::unique_ptr<AnyValue>> m_elements;
  Constraints m_constraints;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ARRAY_VALUE_DATA_H_
