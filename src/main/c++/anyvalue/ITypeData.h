/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : SUP - Sequencer
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
 * @file ITypeData.h
 * @brief Header file for ITypeData.
 * @date 03/01/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the ITypeData interface.
 */

#ifndef _SUP_ITypeData_h_
#define _SUP_ITypeData_h_

#include "AnyType.h"

namespace sup
{
namespace dto
{
class ITypeData
{
public:
  virtual ~ITypeData() = 0;

  virtual ITypeData* Clone() const = 0;
  virtual TypeCode GetTypeCode() const = 0;
  virtual std::string GetTypeName() const;

  virtual AnyType& operator[](std::string fieldname) = 0;
  virtual const AnyType& operator[](std::string fieldname) const = 0;
};

ITypeData* CreateTypeData(TypeCode type_code);

}  // namespace dto

}  // namespace sup

#endif  // _SUP_ITypeData_h_
