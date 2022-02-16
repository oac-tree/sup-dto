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
 * @file IAnySerializer.h
 * @brief Header file for the IAnySerializer templated interface.
 * @date 15/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the IAnySerializer templated interface.
 */

#ifndef _SUP_IAnySerializer_h_
#define _SUP_IAnySerializer_h_

#include <string>

namespace sup
{
namespace dto
{

template <typename T>
class IAnySerializer
{
public:
  virtual ~IAnySerializer() {};

  virtual void AddEmptyProlog(const T* val) = 0;
  virtual void AddEmptyEpilog(const T* val) = 0;

  virtual void AddStructProlog(const T* val) = 0;
  virtual void AddStructMemberSeparator() = 0;
  virtual void AddStructEpilog(const T* val) = 0;

  virtual void AddMemberProlog(const T* val, const std::string& member_name) = 0;
  virtual void AddMemberEpilog(const T* val, const std::string& member_name) = 0;

  virtual void AddArrayProlog(const T* val) = 0;
  virtual void AddArrayElementSeparator() = 0;
  virtual void AddArrayEpilog(const T* val) = 0;

  virtual void AddScalarProlog(const T* val) = 0;
  virtual void AddScalarEpilog(const T* val) = 0;
};

class AnyType;

class IAnyTypeSerializer : public IAnySerializer<AnyType>
{
public:
  ~IAnyTypeSerializer() = default;
};
}  // namespace dto

}  // namespace sup

#endif  // _SUP_IAnySerializer_h_
