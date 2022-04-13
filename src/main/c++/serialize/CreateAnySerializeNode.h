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
 * @file CreateAnySerializeNode.h
 * @brief Header file for serialization node creation function templates.
 * @date 17/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the serialization node creation function
 * templates.
 */

#ifndef _SUP_CreateAnySerializeNode_h_
#define _SUP_CreateAnySerializeNode_h_

#include "AnyType.h"
#include "AnyValue.h"
#include "AnyVisitorNode.h"

#include <memory>

namespace sup
{
namespace dto
{

std::unique_ptr<IAnyVisitorNode<const AnyType>> CreateSerializeNode(const AnyType* anytype);
std::unique_ptr<IAnyVisitorNode<const AnyValue>> CreateSerializeNode(const AnyValue* anyvalue);

}  // namespace dto

}  // namespace sup

#endif  // _SUP_CreateAnySerializeNode_h_
