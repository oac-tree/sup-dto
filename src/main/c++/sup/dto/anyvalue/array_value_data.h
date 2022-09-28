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

#ifndef _SUP_ARRAYVALUEDATA_H_
#define _SUP_ARRAYVALUEDATA_H_

#include <sup/dto/anyvalue/i_value_data.h>

#include <vector>

namespace sup
{
namespace dto
{
class ArrayValueData : public IValueData
{
public:
  ArrayValueData(std::size_t size, const AnyType& elem_type, const std::string& name);
  ~ArrayValueData() override;

  ArrayValueData* Clone() const override;
  TypeCode GetTypeCode() const override;
  std::string GetTypeName() const override;
  AnyType GetType() const override;

  void AddElement(const AnyValue& value) override;
  std::size_t NumberOfElements() const override;

  void Assign(const AnyValue& value) override;

  bool HasField(const std::string& fieldname) const override;
  AnyValue& operator[](const std::string& fieldname) override;
  AnyValue& operator[](std::size_t idx) override;

  bool Equals(const AnyValue& other) const override;

private:
  AnyType elem_type;
  std::string name;
  std::vector<AnyValue> elements;
};

ArrayValueData* CreateArrayValueData(const AnyType& anytype);

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

#endif  // _SUP_ARRAYVALUEDATA_H_
