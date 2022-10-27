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

namespace
{
sup::dto::uint64 GetTimestamp()
{
  auto now = std::chrono::system_clock::now();
  auto ns = std::chrono::duration_cast<std::chrono::duration<sup::dto::uint64, std::nano>>(
    now.time_since_epoch());
  return ns.count();
}
}  // unnamed namespace

namespace sup
{
namespace rpc
{
namespace utils
{
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

sup::dto::AnyValue CreateRPCRequest(const sup::dto::AnyValue& payload)
{
  if (sup::dto::IsEmptyValue(payload))
  {
    return {};
  }
  sup::dto::AnyValue request = {{
    { constants::REQUEST_TIMESTAMP, {sup::dto::UnsignedInteger64Type, GetTimestamp()} },
    { constants::REQUEST_PAYLOAD, payload }
  }, constants::REQUEST_TYPE_NAME};
  return request;
}

sup::dto::AnyValue CreateRPCReply(const sup::rpc::ProtocolResult& result,
                                  const std::string& reason,
                                  const sup::dto::AnyValue& payload)
{
  sup::dto::AnyValue reply = CreateRPCBaseReply(result, GetTimestamp(), reason);
  if (!sup::dto::IsEmptyValue(payload))
  {
    reply.AddMember(constants::REPLY_PAYLOAD, payload);
  }
  return reply;
}

sup::dto::AnyValue CreateRPCBaseReply(const sup::rpc::ProtocolResult& result,
                                      const sup::dto::uint64 timestamp,
                                      const std::string& reason)
{
  sup::dto::AnyValue reply = {{
    { constants::REPLY_RESULT, {sup::dto::UnsignedInteger32Type, result.GetValue()} },
    { constants::REPLY_TIMESTAMP, {sup::dto::UnsignedInteger64Type, timestamp} },
    { constants::REPLY_REASON, {sup::dto::StringType, reason} }
  }, constants::REPLY_TYPE_NAME};
  return reply;
}

}  // namespace utils

}  // namespace rpc

}  // namespace sup
