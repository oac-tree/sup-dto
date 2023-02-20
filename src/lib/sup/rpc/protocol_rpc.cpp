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

#include "protocol_rpc.h"

#include <chrono>

namespace sup
{
namespace rpc
{
namespace utils
{
sup::dto::uint64 GetTimestamp()
{
  auto now = std::chrono::system_clock::now();
  auto ns = std::chrono::duration_cast<std::chrono::duration<sup::dto::uint64, std::nano>>(
    now.time_since_epoch());
  return ns.count();
}

bool CheckRequestFormat(const sup::dto::AnyValue& request)
{
  if (!request.HasField(constants::REQUEST_TIMESTAMP)
      || request[constants::REQUEST_TIMESTAMP].GetType() != sup::dto::UnsignedInteger64Type)
  {
    return false;
  }
  if (!request.HasField(constants::REQUEST_PAYLOAD))
  {
    return false;
  }
  return true;
}

bool CheckReplyFormat(const sup::dto::AnyValue& reply)
{
  if (!reply.HasField(constants::REPLY_RESULT)
      || reply[constants::REPLY_RESULT].GetType() != sup::dto::UnsignedInteger32Type)
  {
    return false;
  }
  if (!reply.HasField(constants::REPLY_TIMESTAMP)
      || reply[constants::REPLY_TIMESTAMP].GetType() != sup::dto::UnsignedInteger64Type)
  {
    return false;
  }
  if (!reply.HasField(constants::REPLY_REASON)
      || reply[constants::REPLY_REASON].GetType() != sup::dto::StringType)
  {
    return false;
  }
  return true;
}

bool IsServiceRequest(const sup::dto::AnyValue& request)
{
  if (!request.HasField(constants::SERVICE_REQUEST_FIELD))
  {
    return false;
  }
  return request[constants::SERVICE_REQUEST_FIELD].GetType() == sup::dto::StringType;
}

bool CheckServerStatusReplyFormat(const sup::dto::AnyValue& reply)
{
  if (!reply.HasField(constants::SERVER_STATUS_REPLY_TIMESTAMP) ||
      reply[constants::SERVER_STATUS_REPLY_TIMESTAMP].GetType() != sup::dto::UnsignedInteger64Type)
  {
    return false;
  }
  if (!reply.HasField(constants::SERVER_STATUS_REPLY_ALIVE_SINCE) ||
      reply[constants::SERVER_STATUS_REPLY_ALIVE_SINCE].GetType() != sup::dto::UnsignedInteger64Type)
  {
    return false;
  }
  if (!reply.HasField(constants::SERVER_STATUS_REPLY_COUNTER) ||
      reply[constants::SERVER_STATUS_REPLY_COUNTER].GetType() != sup::dto::UnsignedInteger64Type)
  {
    return false;
  }
  return true;
}

bool CheckApplicationProtocolReplyFormat(const sup::dto::AnyValue& reply)
{
  if (!reply.HasField(constants::PROTOCOL_REPLY_TYPE) ||
      reply[constants::PROTOCOL_REPLY_TYPE].GetType() != sup::dto::StringType)
  {
    return false;
  }
  if (!reply.HasField(constants::PROTOCOL_REPLY_VERSION) ||
      reply[constants::PROTOCOL_REPLY_VERSION].GetType() != sup::dto::StringType)
  {
    return false;
  }
  return true;
}

sup::dto::AnyValue CreateRPCRequest(const sup::dto::AnyValue& payload)
{
  sup::dto::AnyValue request = {{
    { constants::REQUEST_TIMESTAMP, {sup::dto::UnsignedInteger64Type, GetTimestamp()} }
  }, constants::REQUEST_TYPE_NAME};
  if (!sup::dto::IsEmptyValue(payload))
  {
    request.AddMember(constants::REQUEST_PAYLOAD, payload);
  }
  return request;
}

sup::dto::AnyValue CreateRPCReply(const sup::rpc::ProtocolResult& result,
                                  const std::string& reason,
                                  const sup::dto::AnyValue& payload)
{
  sup::dto::AnyValue reply = {{
    { constants::REPLY_RESULT, {sup::dto::UnsignedInteger32Type, result.GetValue()} },
    { constants::REPLY_TIMESTAMP, {sup::dto::UnsignedInteger64Type, GetTimestamp()} },
    { constants::REPLY_REASON, {sup::dto::StringType, reason} }
  }, constants::REPLY_TYPE_NAME};
  if (!sup::dto::IsEmptyValue(payload))
  {
    reply.AddMember(constants::REPLY_PAYLOAD, payload);
  }
  return reply;
}

sup::dto::AnyValue CreateServerStatusRequest()
{
  sup::dto::AnyValue server_status_request = {{
    { constants::SERVICE_REQUEST_FIELD, {sup::dto::StringType, constants::SERVER_STATUS_VALUE} }
  }, constants::SERVICE_REQUEST_TYPE_NAME};
  return server_status_request;
}

sup::dto::AnyValue CreateServerStatusReply(sup::dto::uint64 alive_since, sup::dto::uint64 counter)
{
  sup::dto::AnyValue server_status_reply = {{
    { constants::SERVER_STATUS_REPLY_TIMESTAMP, {sup::dto::UnsignedInteger64Type, GetTimestamp()} },
    { constants::SERVER_STATUS_REPLY_ALIVE_SINCE, {sup::dto::UnsignedInteger64Type, alive_since} },
    { constants::SERVER_STATUS_REPLY_COUNTER, {sup::dto::UnsignedInteger64Type, counter} },
  }, constants::SERVER_STATUS_REPLY_TYPE_NAME};
  return server_status_reply;
}

sup::dto::AnyValue CreateApplicationProtocolRequest()
{
  sup::dto::AnyValue application_protocol_request = {{
    { constants::SERVICE_REQUEST_FIELD, {sup::dto::StringType, constants::PROTOCOL_REQUEST_VALUE} }
  }, constants::SERVICE_REQUEST_TYPE_NAME};
  return application_protocol_request;
}

sup::dto::AnyValue CreateApplicationProtocolReply(const std::string& application_type,
                                                  const std::string& application_version)
{
  sup::dto::AnyValue server_status_reply = {{
    { constants::PROTOCOL_REPLY_TYPE, {sup::dto::StringType, application_type} },
    { constants::PROTOCOL_REPLY_VERSION, {sup::dto::StringType, application_version} },
  }, constants::PROTOCOL_REPLY_TYPE_NAME};
  return server_status_reply;
}

}  // namespace utils

}  // namespace rpc

}  // namespace sup
