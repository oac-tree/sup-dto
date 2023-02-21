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
class Protocol;

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
 * A service request is a simple packet, used for querying the application protocol. It will
 * never reach the application layer and is intercepted by the application layer specific
 * protocol implementation. This allows providing generic information about the application
 * interface that is encapsulated by the protocol.
 * It contains:
 * - service: a payload identifying the service request
*/
static const std::string SERVICE_REQUEST_TYPE_NAME = "sup::ServiceRequest/v1.0";
static const std::string SERVICE_REQUEST_PAYLOAD = "service";

/**
 * A service reply is a structured AnyValue with the following fields:
 * - result: a 32bit unsigned integer denoting success or failure status
 * - reply (optional): the payload of the service reply
*/
static const std::string SERVICE_REPLY_TYPE_NAME = "sup::ServiceReply/v1.0";
static const std::string SERVICE_REPLY_RESULT = "result";
static const std::string SERVICE_REPLY_PAYLOAD = "reply";

/**
 * Currently only one generic service request and reply is defined: the request to receive the
 * name and version of the application protocol. Any other service request will be application
 * protocol specific and can be requested after identifying the application protocol.
 * The reply for this application protocol info contains:
 * - application_type: string identifying the encapsulated application interface
 * - application_version: string identifying the version for the application protocol
*/
static const std::string APPLICATION_PROTOCOL_INFO_REQUEST = "application_protocol_info";
static const std::string APPLICATION_PROTOCOL_TYPE = "application_type";
static const std::string APPLICATION_PROTOCOL_VERSION = "application_version";

}  // namespace constants

namespace utils
{
/**
 * Structure that identifies a specific application protocol with its version.
*/
struct ApplicationProtocolInfo
{
  std::string m_application_type;
  std::string m_application_version;
};

bool CheckRequestFormat(const sup::dto::AnyValue& request);

bool CheckReplyFormat(const sup::dto::AnyValue& reply);

sup::dto::AnyValue CreateRPCRequest(const sup::dto::AnyValue& payload);

sup::dto::AnyValue CreateRPCReply(const sup::rpc::ProtocolResult& result,
                                  const std::string& reason = "",
                                  const sup::dto::AnyValue& payload = {});

bool IsServiceRequest(const sup::dto::AnyValue& request);

bool CheckServiceReplyFormat(const sup::dto::AnyValue& reply);

sup::dto::AnyValue CreateServiceRequest(const sup::dto::AnyValue& payload);

sup::dto::AnyValue CreateServiceReply(const sup::rpc::ProtocolResult& result,
                                      const sup::dto::AnyValue& payload = {});

bool IsApplicationProtocolRequestPayload(const sup::dto::AnyValue& payload);

bool CheckApplicationProtocolReplyPayload(const sup::dto::AnyValue& payload);

ApplicationProtocolInfo GetApplicationProtocolInfo(Protocol& protocol);

sup::rpc::ProtocolResult HandleApplicationProtocolInfo(sup::dto::AnyValue& output,
                                                       const std::string& application_type,
                                                       const std::string& application_version);

}  // namespace utils

}  // namespace rpc

}  // namespace sup

#endif  // SUP_RPC_PROTOCOL_RPC_H_
