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

#ifndef _SUP_UnboundedArrayTypeData_h_
#define _SUP_UnboundedArrayTypeData_h_

#include "i_type_data.h"

namespace sup
{
namespace dto
{
class UnboundedArrayTypeData : public ITypeData
{
public:
  UnboundedArrayTypeData(const AnyType& elem_type, const std::string& name);
  ~UnboundedArrayTypeData() override;

  UnboundedArrayTypeData* Clone() const override;
  TypeCode GetTypeCode() const override;
  std::string GetTypeName() const override;

  AnyType ElementType() const override;

  AnyType& operator[](const std::string& fieldname) override;

  bool Equals(const AnyType& other) const override;

private:
  AnyType elem_type;
  std::string name;
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_UnboundedArrayTypeData_h_
