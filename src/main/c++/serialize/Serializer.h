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
 * @file Serializer.h
 * @brief Header file for the Serializer class.
 * @date 23/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the Serializer class.
 */

#ifndef _SUP_Serializer_h_
#define _SUP_Serializer_h_

#include "IWriter.h"

namespace sup
{
namespace dto
{
class AnyType;
class AnyValue;

class Serializer
{
public:
  Serializer();
  ~Serializer();

  bool SerializeAnyType(const AnyType& anytype, IWriter* writer);
  bool SerializeAnyValue(const AnyValue& anyvalue, IWriter* writer);
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_Serializer_h_
