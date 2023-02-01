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

#ifndef _SUP_RPC_PROTOCOL_RPC_H_
#define _SUP_RPC_PROTOCOL_RPC_H_

#include <sup/dto/anyvalue.h>
#include <sup/rpc/protocol_result.h>

namespace sup
{
namespace rpc
{
namespace constants
{
/**
 * An RPC request is a structured AnyValue with two fields:
 * - timestamp: a 64bit unsigned integer
 * - query: a generic AnyValue that contains the payload of the request
*/
static const std::string REQUEST_TYPE_NAME = "sup::RPCRequest/v1.0";
static const std::string REQUEST_TIMESTAMP = "timestamp";
static const std::string REQUEST_PAYLOAD = "query";

/**
 * An RPC reply is a structured AnyValue with the following fields:
 * - result: a 32bit unsigned integer denoting success or failure status
 * - timestamp: a 64bit unsigned integer
 * - reason: a string describing the failure (often left empty when the 'result' field is sufficient)
 * - reply (optional): a field that contains the payload of the RPC reply (may be omitted if not
 *                     required)
*/
static const std::string REPLY_TYPE_NAME = "sup::RPCReply/v1.0";
static const std::string REPLY_RESULT = "result";
static const std::string REPLY_TIMESTAMP = "timestamp";
static const std::string REPLY_REASON = "reason";
static const std::string REPLY_PAYLOAD = "reply";
}  // namespace constants

namespace utils
{
bool CheckRequestFormat(const sup::dto::AnyValue& request);

bool CheckReplyFormat(const sup::dto::AnyValue& reply);

sup::dto::AnyValue CreateRPCRequest(const sup::dto::AnyValue& payload);

sup::dto::AnyValue CreateRPCReply(const sup::rpc::ProtocolResult& result,
                                  const std::string& reason = "",
                                  const sup::dto::AnyValue& payload = {});

}  // namespace utils

}  // namespace rpc

}  // namespace sup

#endif  // _SUP_RPC_PROTOCOL_RPC_H_
