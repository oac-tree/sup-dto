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

#ifndef SUP_RPC_FUNCTION_PROTOCOL_PACK_H_
#define SUP_RPC_FUNCTION_PROTOCOL_PACK_H_

#include <sup/dto/anytype.h>
#include <sup/dto/anyvalue.h>

#include <string>
#include <vector>

namespace sup
{
namespace rpc
{

bool FunctionProtocolPack(sup::dto::AnyValue& output, const std::string& field_name, bool b);

bool FunctionProtocolPack(sup::dto::AnyValue& output, const std::string& field_name,
                          const std::string& str);

bool FunctionProtocolPack(sup::dto::AnyValue& output, const std::string& field_name,
                          const std::vector<std::string>& string_list);

bool FunctionProtocolPack(sup::dto::AnyValue& output, const std::string& field_name,
                          const sup::dto::AnyValue& anyvalue);

}  // namespace rpc

}  // namespace sup

#endif  // SUP_RPC_FUNCTION_PROTOCOL_PACK_H_
