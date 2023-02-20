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

#include "protocol_rpc_client.h"

#include <sup/dto/anyvalue_helper.h>
#include <sup/rpc/rpc_exceptions.h>
#include <sup/rpc/protocol_rpc.h>

namespace sup
{
namespace rpc
{

ProtocolRPCClient::ProtocolRPCClient(std::unique_ptr<dto::AnyFunctor>&& any_functor)
  : m_any_functor{std::move(any_functor)}
{
  if (!m_any_functor)
  {
    throw NullDependencyException("ProtocolRPCClient constructed with empty functor");
  }
}

ProtocolRPCClient::~ProtocolRPCClient() = default;

ProtocolResult ProtocolRPCClient::Invoke(const sup::dto::AnyValue& input,
                                         sup::dto::AnyValue& output)
{
  if (sup::dto::IsEmptyValue(input))
  {
    return TransportEncodingError;
  }
  auto request = utils::CreateRPCRequest(input);
  sup::dto::AnyValue reply;
  try
  {
    reply = (*m_any_functor)(request);
  }
  catch(...)
  {
    // If the previous code threw an exception, the next check will detect a malformed reply.
  }
  if (!utils::CheckReplyFormat(reply))
  {
    return TransportDecodingError;
  }
  if (reply.HasField(constants::REPLY_PAYLOAD))
  {
    if (!sup::dto::TryConvert(output, reply[constants::REPLY_PAYLOAD]))
    {
      return TransportDecodingError;
    }
  }
  return ProtocolResult{reply[constants::REPLY_RESULT].As<sup::dto::uint32>()};
}

ApplicationProtocolInfo ProtocolRPCClient::GetApplicationProtocol()
{
  auto request = utils::CreateApplicationProtocolRequest();
  sup::dto::AnyValue reply;
  try
  {
    reply = (*m_any_functor)(request);
  }
  catch(...)
  {
    // If the previous code threw an exception, the next check will detect a malformed reply.
  }
  if (!utils::CheckApplicationProtocolReplyFormat(reply))
  {
    return {};
  }
  auto application_type = reply[constants::PROTOCOL_REPLY_TYPE].As<std::string>();
  auto application_version = reply[constants::PROTOCOL_REPLY_VERSION].As<std::string>();
  return { application_type, application_version };
}

ServerStatusInfo ProtocolRPCClient::GetServerStatus()
{
  auto request = utils::CreateServerStatusRequest();
  sup::dto::AnyValue reply;
  try
  {
    reply = (*m_any_functor)(request);
  }
  catch(...)
  {
    // If the previous code threw an exception, the next check will detect a malformed reply.
  }
  if (!utils::CheckServerStatusReplyFormat(reply))
  {
    return {};
  }
  auto timestamp = reply[constants::SERVER_STATUS_REPLY_TIMESTAMP].As<sup::dto::uint64>();
  auto alive_since = reply[constants::SERVER_STATUS_REPLY_ALIVE_SINCE].As<sup::dto::uint64>();
  auto counter = reply[constants::SERVER_STATUS_REPLY_COUNTER].As<sup::dto::uint64>();
  return { timestamp, alive_since, counter };
}

}  // namespace rpc

}  // namespace sup
