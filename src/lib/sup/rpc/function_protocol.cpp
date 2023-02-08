/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : Supervision and Automation - Configuration
 *
 * Description   : Configuration and CVVF libraries for the Supervision and Automation System.
 *
 * Author        : Walter Van Herck (IO)
 *
 * Copyright (c) : 2010-2023 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include "function_protocol.h"

namespace sup
{
namespace rpc
{

sup::dto::AnyValue FunctionProtocolInput(const std::string& func_name)
{
  sup::dto::AnyValue result = sup::dto::EmptyStruct();
  result.AddMember(FUNCTION_FIELD_NAME, func_name);
  return result;
}

}  // namespace rpc

}  // namespace sup
