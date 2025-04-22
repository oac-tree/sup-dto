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

#ifndef SUP_DTO_SCALAR_VALUE_DATA_BASE_H_
#define SUP_DTO_SCALAR_VALUE_DATA_BASE_H_

#include <sup/dto/anyvalue/i_value_data.h>

namespace sup
{
namespace dto
{
class ScalarValueDataBase : public IValueData
{
public:
  virtual ~ScalarValueDataBase();

  ScalarValueDataBase(const ScalarValueDataBase& other) = delete;
  ScalarValueDataBase& operator=(const ScalarValueDataBase&) = delete;
  ScalarValueDataBase(ScalarValueDataBase&& other) = delete;
  ScalarValueDataBase& operator=(ScalarValueDataBase&&) = delete;

  TypeCode GetTypeCode() const override;
  std::string GetTypeName() const override;

  bool IsScalar() const override;

  Constraints GetConstraints() const override;

  bool ShallowEquals(const IValueData* other) const override;

protected:
  ScalarValueDataBase(TypeCode type_code, Constraints constraints);

private:
  TypeCode m_type_code;
  Constraints m_constraints;
};

std::unique_ptr<IValueData> CreateScalarValueData(TypeCode type_code, Constraints constraints);

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_SCALAR_VALUE_DATA_BASE_H_
