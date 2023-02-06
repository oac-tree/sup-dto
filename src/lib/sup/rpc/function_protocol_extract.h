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

#ifndef SUP_RPC_FUNCTION_PROTOCOL_EXTRACT_H_
#define SUP_RPC_FUNCTION_PROTOCOL_EXTRACT_H_

#include <sup/dto/anyvalue.h>
#include <sup/rpc/protocol_result.h>

#include <map>
#include <string>

namespace sup
{
namespace rpc
{

bool FunctionProtocolExtract(std::string& str, const sup::dto::AnyValue& input,
                             const std::string& field_name);

bool FunctionProtocolExtract(sup::dto::AnyValue& anyvalue, const sup::dto::AnyValue& input,
                             const std::string& field_name);

bool FunctionProtocolExtract(sup::dto::AnyType& anytype, const sup::dto::AnyValue& input,
                             const std::string& field_name);

}  // namespace rpc

}  // namespace sup

#endif  // SUP_RPC_FUNCTION_PROTOCOL_EXTRACT_H_
