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

#include "rpc_exceptions.h"

namespace sup
{
namespace rpc
{

NullDependencyException::NullDependencyException(const std::string& message)
  : MessageException{message}
{}

InvalidOperationException::InvalidOperationException(const std::string& message)
  : MessageException{message}
{}

}  // namespace rpc

}  // namespace sup
