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

#ifndef SUP_RPC_FUNCTION_PROTOCOL_H_
#define SUP_RPC_FUNCTION_PROTOCOL_H_

#include <sup/dto/anyvalue.h>
#include <sup/rpc/protocol_result.h>

#include <map>
#include <string>

namespace sup
{
namespace rpc
{

static const std::string FUNCTION_FIELD_NAME = "function";

sup::dto::AnyValue FunctionProtocolInput(const std::string& func_name);

template <typename T>
using ProtocolMemberFunction = ProtocolResult(T::*)(const sup::dto::AnyValue&, sup::dto::AnyValue&);

template <typename T>
using ProtocolMemberFunctionMap = std::map<std::string, ProtocolMemberFunction<T>>;

template <typename T>
ProtocolResult CallFunctionProtocol(T& obj, const ProtocolMemberFunctionMap<T>& func_map,
                                    const sup::dto::AnyValue& input, sup::dto::AnyValue& output,
                                    const ProtocolResult& not_found_result)
{
  if (!input.HasField(FUNCTION_FIELD_NAME) ||
      input[FUNCTION_FIELD_NAME].GetType() != sup::dto::StringType)
  {
    return not_found_result;
  }
  auto func_name = input[FUNCTION_FIELD_NAME].As<std::string>();
  auto it = func_map.find(func_name);
  if (it == func_map.end())
  {
    return not_found_result;
  }
  auto mem_fun = it->second;
  return (obj.*mem_fun)(input, output);
}

}  // namespace rpc

}  // namespace sup

#endif  // SUP_RPC_FUNCTION_PROTOCOL_H_
