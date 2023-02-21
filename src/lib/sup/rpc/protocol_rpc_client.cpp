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
    return ClientTransportEncodingError;
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
    return ClientTransportDecodingError;
  }
  if (reply.HasField(constants::REPLY_PAYLOAD))
  {
    if (!sup::dto::TryConvert(output, reply[constants::REPLY_PAYLOAD]))
    {
      return ClientTransportDecodingError;
    }
  }
  return ProtocolResult{reply[constants::REPLY_RESULT].As<sup::dto::uint32>()};
}

ProtocolResult ProtocolRPCClient::Service(const sup::dto::AnyValue& input,
                                          sup::dto::AnyValue& output)
{
  if (sup::dto::IsEmptyValue(input))
  {
    return ClientTransportEncodingError;
  }
  auto request = utils::CreateServiceRequest(input);
  sup::dto::AnyValue reply;
  try
  {
    reply = (*m_any_functor)(request);
  }
  catch(...)
  {
    // If the previous code threw an exception, the next check will detect a malformed reply.
  }
  if (!utils::CheckServiceReplyFormat(reply))
  {
    return ClientTransportDecodingError;
  }
  if (reply.HasField(constants::SERVICE_REPLY_PAYLOAD))
  {
    if (!sup::dto::TryConvert(output, reply[constants::SERVICE_REPLY_PAYLOAD]))
    {
      return ClientTransportDecodingError;
    }
  }
  return ProtocolResult{reply[constants::SERVICE_REPLY_RESULT].As<sup::dto::uint32>()};
}

}  // namespace rpc

}  // namespace sup
