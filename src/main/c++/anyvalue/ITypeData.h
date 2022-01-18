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
  virtual ~ITypeData();

  virtual ITypeData* Clone() const = 0;
  virtual TypeCode GetTypeCode() const = 0;
  virtual std::string GetTypeName() const = 0;

  virtual void AddMember(const std::string& name, const AnyType& type);
  virtual bool HasMember(const std::string& name) const;
  virtual std::vector<std::string> MemberNames() const;
  virtual std::size_t NumberOfMembers() const;

  virtual AnyType& operator[](const std::string& fieldname) = 0;

  virtual bool Equals(const AnyType& other) const = 0;
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_ITypeData_h_
