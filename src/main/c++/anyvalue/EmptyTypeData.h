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

/**
 * @file EmptyTypeData.h
 * @brief Header file for EmptyTypeData.
 * @date 03/01/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the EmptyTypeData class.
 */

#ifndef _SUP_EmptyTypeData_h_
#define _SUP_EmptyTypeData_h_

#include "ITypeData.h"

namespace sup
{
namespace dto
{
class EmptyTypeData : public ITypeData
{
public:
  EmptyTypeData();
  ~EmptyTypeData() override;

  EmptyTypeData* Clone() const override;
  TypeCode GetTypeCode() const override;
  std::string GetTypeName() const override;

  AnyType& operator[](const std::string& fieldname) override;

  bool Equals(const AnyType& other) const override;
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_EmptyTypeData_h_
