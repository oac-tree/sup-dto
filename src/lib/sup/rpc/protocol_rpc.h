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

#ifndef SUP_RPC_PROTOCOL_RPC_H_
#define SUP_RPC_PROTOCOL_RPC_H_

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

/**
 * A service request is a simple packet, used for querying protocol types and health. It will
 * never reach the application layer, as it is either:
 * - intercepted by ProtocolRPCServer in case of a "server_status" request
 * - delegated to IProtocol::ApplicationType and IProtocol::ApplicationVersion in case of
 *   a "protocol_request" request
 * It contains:
 * - service: a string identifying the service request
*/
static const std::string SERVICE_REQUEST_TYPE_NAME = "sup::ServiceRequest/v1.0";
static const std::string SERVICE_REQUEST_FIELD = "service";
static const std::string PROTOCOL_REQUEST_VALUE = "protocol_request";
static const std::string SERVER_STATUS_VALUE = "server_status";

/**
 * A protocol reply is a structured AnyValue with the following fields:
 * - application_type: a string identifying the type of encapsulated application protocol
 * - application_version: a string identifying the version of the encapsulated application protocol
*/
static const std::string PROTOCOL_REPLY_TYPE_NAME = "sup::ProtocolReply/v1.0";
static const std::string PROTOCOL_REPLY_TYPE = "application_type";
static const std::string PROTOCOL_REPLY_VERSION = "application_version";

/**
 * A ping reply is a structured AnyValue with the following fields:
 * - timestamp: a 64bit unsigned integer
 * - alive_since: a 64bit unsigned integer timestamp indicating when the server was instantiated
 * - counter: a 64bit unsigned integer that increments on each request
*/
static const std::string SERVER_STATUS_REPLY_TYPE_NAME = "sup::ServerStatusReply/v1.0";
static const std::string SERVER_STATUS_REPLY_TIMESTAMP = "timestamp";
static const std::string SERVER_STATUS_REPLY_ALIVE_SINCE = "alive_since";
static const std::string SERVER_STATUS_REPLY_COUNTER = "counter";
}  // namespace constants

namespace utils
{
sup::dto::uint64 GetTimestamp();

bool CheckRequestFormat(const sup::dto::AnyValue& request);

bool CheckReplyFormat(const sup::dto::AnyValue& reply);

bool IsServiceRequest(const sup::dto::AnyValue& request);

bool CheckServerStatusReplyFormat(const sup::dto::AnyValue& reply);

bool CheckApplicationProtocolReplyFormat(const sup::dto::AnyValue& reply);

sup::dto::AnyValue CreateRPCRequest(const sup::dto::AnyValue& payload);

sup::dto::AnyValue CreateRPCReply(const sup::rpc::ProtocolResult& result,
                                  const std::string& reason = "",
                                  const sup::dto::AnyValue& payload = {});

sup::dto::AnyValue CreateServerStatusRequest();

sup::dto::AnyValue CreateServerStatusReply(sup::dto::uint64 alive_since, sup::dto::uint64 counter);

sup::dto::AnyValue CreateApplicationProtocolRequest();

sup::dto::AnyValue CreateApplicationProtocolReply(const std::string& application_type,
                                                  const std::string& application_version);

}  // namespace utils

}  // namespace rpc

}  // namespace sup

#endif  // SUP_RPC_PROTOCOL_RPC_H_
