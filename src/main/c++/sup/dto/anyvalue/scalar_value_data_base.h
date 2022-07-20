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

#ifndef _SUP_ScalarValueDataBase_h_
#define _SUP_ScalarValueDataBase_h_

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

protected:
  ScalarValueDataBase(TypeCode type_code);

private:
  TypeCode type_code;
};

ScalarValueDataBase* CreateScalarValueData(TypeCode type_code);

}  // namespace dto

}  // namespace sup

#endif  // _SUP_ScalarValueDataBase_h_
