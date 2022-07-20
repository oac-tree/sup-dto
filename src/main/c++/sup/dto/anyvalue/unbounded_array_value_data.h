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

#ifndef _SUP_UnboundedArrayValueData_h_
#define _SUP_UnboundedArrayValueData_h_

#include <sup/dto/anyvalue/i_value_data.h>

#include <vector>

namespace sup
{
namespace dto
{
class UnboundedArrayValueData : public IValueData
{
public:
  UnboundedArrayValueData(const AnyType& elem_type, const std::string& name);
  ~UnboundedArrayValueData() override;

  UnboundedArrayValueData* Clone() const override;
  TypeCode GetTypeCode() const override;
  std::string GetTypeName() const override;
  AnyType GetType() const override;

  void AddElement(const AnyValue& value) override;
  std::size_t NumberOfElements() const override;

  void Assign(const AnyValue& value) override;

  AnyValue& operator[](const std::string& fieldname) override;
  AnyValue& operator[](std::size_t idx) override;

  bool Equals(const AnyValue& other) const override;

private:
  AnyType elem_type;
  std::string name;
  std::vector<AnyValue> elements;
};

UnboundedArrayValueData* CreateUnboundedArrayValueData(const AnyType& anytype);

}  // namespace dto

}  // namespace sup

#endif  // _SUP_UnboundedArrayValueData_h_
