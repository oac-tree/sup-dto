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
 * @file AnyTypeBuilder.h
 * @brief Header file for the AnyTypeBuilder class.
 * @date 28/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the AnyTypeBuilder class.
 */

#ifndef _SUP_AnyTypeBuilder_h_
#define _SUP_AnyTypeBuilder_h_

#include "AnyType.h"

#include <string>
#include <utility>
#include <vector>

namespace sup
{
namespace dto
{
class AnyTypeBuilder
{
public:
  AnyTypeBuilder();
  ~AnyTypeBuilder();
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_AnyTypeBuilder_h_
