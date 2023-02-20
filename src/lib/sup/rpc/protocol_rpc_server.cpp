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

#include "protocol_rpc_server.h"

#include <sup/dto/anyvalue_helper.h>
#include <sup/rpc/rpc_exceptions.h>
#include <sup/rpc/protocol_rpc.h>

namespace sup
{
namespace rpc
{

ProtocolRPCServer::ProtocolRPCServer(std::unique_ptr<Protocol>&& protocol)
  : m_protocol{std::move(protocol)}
  , m_alive_since{utils::GetTimestamp()}
  , m_counter{0}
{
  if (!m_protocol)
  {
    throw NullDependencyException("ProtocolRPCServer constructed with empty protocol");
  }
}

ProtocolRPCServer::~ProtocolRPCServer() = default;

sup::dto::AnyValue ProtocolRPCServer::operator()(const sup::dto::AnyValue& request)
{
  if (utils::IsServiceRequest(request))
  {
    return HandleServiceRequest(request);
  }
  if (!utils::CheckRequestFormat(request))
  {
    return utils::CreateRPCReply(TransportDecodingError);
  }
  sup::dto::AnyValue output;
  ProtocolResult result = Success;
  try
  {
    result = m_protocol->Invoke(request[constants::REQUEST_PAYLOAD], output);
  }
  catch(...)
  {
    return utils::CreateRPCReply(TransportEncodingError);
  }
  return utils::CreateRPCReply(result, "", output);
}

sup::dto::AnyValue ProtocolRPCServer::HandleServiceRequest(const sup::dto::AnyValue& request)
{
  auto request_type = request[constants::SERVICE_REQUEST_FIELD].As<std::string>();
  if (request_type == constants::SERVER_STATUS_VALUE)
  {
    return utils::CreateServerStatusReply(m_alive_since, m_counter++);
  }
  if (request_type == constants::PROTOCOL_REQUEST_VALUE)
  {
    auto info = m_protocol->GetApplicationProtocol();
    return utils::CreateApplicationProtocolReply(info.m_application_type,
                                                 info.m_application_version);
  }
  return utils::CreateRPCReply(TransportDecodingError);
}

}  // namespace rpc

}  // namespace sup
