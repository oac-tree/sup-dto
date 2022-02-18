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
 * @file AnyValueHelper.h
 * @brief Header file for AnyValue helper classes and functions.
 * @date 17/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the AnyValue helper classes and functions.
 */

#ifndef _SUP_AnyValueHelper_h_
#define _SUP_AnyValueHelper_h_

#include "IAnySerializer.h"
#include "BasicScalarTypes.h"

#include <vector>

namespace sup
{
namespace dto
{
class AnyValue;

void SerializeAnyValue(const AnyValue& anyvalue, IAnySerializer<AnyValue>& serializer);

std::vector<uint8> AnyValueToByteArray(const AnyValue& anyvalue);

}  // namespace dto

}  // namespace sup

#endif  // _SUP_AnyValueHelper_h_
