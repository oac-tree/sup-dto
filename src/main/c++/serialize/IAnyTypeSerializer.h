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
 * @file IAnyTypeSerializer.h
 * @brief Header file for the IAnyTypeSerializer interface.
 * @date 15/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the IAnyTypeSerializer interface.
 */

#ifndef _SUP_IAnyTypeSerializer_h_
#define _SUP_IAnyTypeSerializer_h_

#include <string>

namespace sup
{
namespace dto
{
class AnyType;

class IAnyTypeSerializer
{
public:
  virtual ~IAnyTypeSerializer() {};

  virtual void AddEmptyProlog(const AnyType* anytype) = 0;
  virtual void AddEmptyEpilog(const AnyType* anytype) = 0;

  virtual void AddStructProlog(const AnyType* anytype) = 0;
  virtual void AddStructMemberSeparator() = 0;
  virtual void AddStructEpilog(const AnyType* anytype) = 0;

  virtual void AddMemberProlog(const AnyType* anytype, std::string member_name) = 0;
  virtual void AddMemberEpilog(const AnyType* anytype, std::string member_name) = 0;

  virtual void AddArrayProlog(const AnyType* anytype) = 0;
  virtual void AddArrayElementSeparator() = 0;
  virtual void AddArrayEpilog(const AnyType* anytype) = 0;

  virtual void AddScalarProlog(const AnyType* anytype) = 0;
  virtual void AddScalarEpilog(const AnyType* anytype) = 0;
};
}  // namespace dto

}  // namespace sup

#endif  // _SUP_IAnyTypeSerializer_h_
