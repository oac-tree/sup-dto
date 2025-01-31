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
  ArrayValueData(std::size_t size, const AnyType& elem_type, const std::string& name,
                 Constraints constraints);
  ~ArrayValueData() override;

  ArrayValueData(const ArrayValueData& other) = delete;
  ArrayValueData(ArrayValueData&& other) = delete;
  ArrayValueData& operator=(const ArrayValueData& other) = delete;
  ArrayValueData& operator=(ArrayValueData&& other) = delete;

  std::unique_ptr<IValueData> Clone(Constraints constraints) const override;
  TypeCode GetTypeCode() const override;
  std::string GetTypeName() const override;
  AnyType GetType() const override;

  Constraints GetConstraints() const override;

  void AddElement(const AnyValue& value) override;
  std::size_t NumberOfElements() const override;

  void ConvertFrom(const AnyValue& value) override;

  AnyValue& operator[](std::size_t idx) override;

  bool HasChild(const std::string& child_name) const override;
  std::vector<std::string> ChildNames() const override;
  AnyValue* GetChildValue(const std::string& child_name) override;
  bool ShallowEquals(const AnyValue& other) const override;

private:
  AnyType m_elem_type;
  std::string m_name;
  std::vector<std::unique_ptr<AnyValue>> m_elements;
  Constraints m_constraints;
};

std::unique_ptr<IValueData> CreateArrayValueData(const AnyType& anytype, Constraints constraints);

/**
 * @brief Strips the index from the fieldname.
 *
 * @param fieldname Full fieldname.
 *
 * @return Pair of integer index and the remainder of the fieldname.
 *
 * @note An optional dot '.' after the square brackets will be ignored.
 *
 * @throws InvalidOperationException Thrown when the fieldname cannot be parsed correctly (e.g. no
 * starting square brackets or characters inside square brackets cannot be interpreted as a
 * positive integer).
 */
std::pair<std::size_t, std::string> StripValueIndex(const std::string& fieldname);

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ARRAY_VALUE_DATA_H_
