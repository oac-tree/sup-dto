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
  ~ScalarValueDataBase() override;

  TypeCode GetTypeCode() const override;

  AnyType GetType() const override;

  bool IsScalar() const override;

  bool HasLockedType() const override;

protected:
  ScalarValueDataBase(TypeCode type_code, value_flags::Constraints constraints);

private:
  TypeCode m_type_code;
  value_flags::Constraints m_constraints;
};

ScalarValueDataBase* CreateScalarValueData(TypeCode type_code,
                                           value_flags::Constraints constraints);

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_SCALAR_VALUE_DATA_BASE_H_
