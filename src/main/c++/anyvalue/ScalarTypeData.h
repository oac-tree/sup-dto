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

#ifndef _SUP_ScalarTypeData_h_
#define _SUP_ScalarTypeData_h_

#include "ITypeData.h"

namespace sup
{
namespace dto
{
class ScalarTypeData : public ITypeData
{
public:
  ScalarTypeData(TypeCode type_code);
  ~ScalarTypeData() override;

  ScalarTypeData* Clone() const override;
  TypeCode GetTypeCode() const override;
  std::string GetTypeName() const override;

  bool Equals(const AnyType& other) const override;

private:
  TypeCode type_code;
};

ScalarTypeData* CreateScalarData(TypeCode type_code);

}  // namespace dto

}  // namespace sup

#endif  // _SUP_ScalarTypeData_h_
