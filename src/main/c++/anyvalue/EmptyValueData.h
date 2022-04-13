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

#ifndef _SUP_EmptyValueData_h_
#define _SUP_EmptyValueData_h_

#include "IValueData.h"

namespace sup
{
namespace dto
{
class EmptyValueData : public IValueData
{
public:
  EmptyValueData();
  ~EmptyValueData() override;

  EmptyValueData* Clone() const override;
  TypeCode GetTypeCode() const override;
  AnyType GetType() const override;

  bool Equals(const AnyValue& other) const override;
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_EmptyValueData_h_
