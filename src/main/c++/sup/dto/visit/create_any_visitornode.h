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

#ifndef _SUP_CreateAnyVisitorNode_h_
#define _SUP_CreateAnyVisitorNode_h_

#include <sup/dto/visit/any_visitornode.h>

#include <sup/dto/anytype.h>
#include <sup/dto/anyvalue.h>

#include <memory>

namespace sup
{
namespace dto
{

std::unique_ptr<IAnyVisitorNode<AnyType>> CreateVisitorNode(AnyType* anytype);
std::unique_ptr<IAnyVisitorNode<AnyValue>> CreateVisitorNode(AnyValue* anyvalue);

std::unique_ptr<IAnyVisitorNode<const AnyType>> CreateVisitorNode(const AnyType* anytype);
std::unique_ptr<IAnyVisitorNode<const AnyValue>> CreateVisitorNode(const AnyValue* anyvalue);

}  // namespace dto

}  // namespace sup

#endif  // _SUP_CreateAnyVisitorNode_h_
