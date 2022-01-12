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
 * @file IValueData.h
 * @brief Header file for IValueData.
 * @date 06/01/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the IValueData interface.
 */

#ifndef _SUP_IValueData_h_
#define _SUP_IValueData_h_

#include "AnyValue.h"

namespace sup
{
namespace dto
{
class IValueData
{
public:
  virtual ~IValueData();

  virtual IValueData* Clone() const = 0;
  virtual TypeCode GetTypeCode() const = 0;
  virtual std::string GetTypeName() const;
  virtual AnyType GetType() const = 0;

  virtual void Assign(const AnyValue& value);

  virtual boolean AsBoolean() const;
  virtual int8 AsSignedInteger8() const;
  virtual uint8 AsUnsignedInteger8() const;

  virtual AnyValue& operator[](const std::string& fieldname) = 0;
  virtual const AnyValue& operator[](const std::string& fieldname) const = 0;

  virtual bool Equals(const IValueData* other) const = 0;
};

IValueData* CreateValueData(const AnyType& anytype);

}  // namespace dto

}  // namespace sup

#endif  // _SUP_IValueData_h_
