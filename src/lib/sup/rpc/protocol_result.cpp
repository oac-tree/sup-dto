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

#include "protocol_result.h"

#include <map>

namespace sup
{
namespace rpc
{
namespace status
{
enum ProtocolStatus
{
  SUCCESS = 0,
  NOT_CONNECTED,
  CLIENT_NETWORK_ENCODING,
  SERVER_NETWORK_ENCODING,
  CLIENT_NETWORK_DECODING,
  SERVER_NETWORK_DECODING,
  CLIENT_TRANSPORT_ENCODING,
  SERVER_TRANSPORT_ENCODING,
  CLIENT_TRANSPORT_DECODING,
  SERVER_TRANSPORT_DECODING,
  CLIENT_PROTOCOL_ENCODING,
  SERVER_PROTOCOL_ENCODING,
  CLIENT_PROTOCOL_DECODING,
  SERVER_PROTOCOL_DECODING
};
}  // namespace status

ProtocolResult::ProtocolResult()
  : m_value{status::SUCCESS}
{}

ProtocolResult::~ProtocolResult() = default;

ProtocolResult::ProtocolResult(unsigned int value)
  : m_value{value}
{}

ProtocolResult::ProtocolResult(const ProtocolResult& other)
  : m_value{other.m_value}
{}

ProtocolResult& ProtocolResult::operator=(const ProtocolResult& other)
{
  m_value = other.m_value;
  return *this;
}

unsigned int ProtocolResult::GetValue() const
{
  return m_value;
}

bool ProtocolResult::operator==(const ProtocolResult& other) const
{
  return m_value == other.m_value;
}

bool ProtocolResult::operator!=(const ProtocolResult& other) const
{
  return !this->operator==(other);
}

std::string ProtocolResultToString(const ProtocolResult& result)
{
  static std::map<int, std::string> results = {
      {status::SUCCESS, "Success"},
      {status::NOT_CONNECTED, "NotConnected"},
      {status::CLIENT_NETWORK_ENCODING, "ClientNetworkEncodingError"},
      {status::SERVER_NETWORK_ENCODING, "ServerNetworkEncodingError"},
      {status::CLIENT_NETWORK_DECODING, "ClientNetworkDecodingError"},
      {status::SERVER_NETWORK_DECODING, "ServerNetworkDecodingError"},
      {status::CLIENT_TRANSPORT_ENCODING, "ClientTransportEncodingError"},
      {status::SERVER_TRANSPORT_ENCODING, "ServerTransportEncodingError"},
      {status::CLIENT_TRANSPORT_DECODING, "ClientTransportDecodingError"},
      {status::SERVER_TRANSPORT_DECODING, "ServerTransportDecodingError"},
      {status::CLIENT_PROTOCOL_ENCODING, "ClientProtocolEncodingError"},
      {status::SERVER_PROTOCOL_ENCODING, "ServerProtocolEncodingError"},
      {status::CLIENT_PROTOCOL_DECODING, "ClientProtocolDecodingError"},
      {status::SERVER_PROTOCOL_DECODING, "ServerProtocolDecodingError"}};
  auto it = results.find(result.GetValue());
  if (it != results.end())
  {
    return it->second;
  }
  return "Unknown ProtocolResult: " + std::to_string(result.GetValue());
}

const ProtocolResult Success{status::SUCCESS};
const ProtocolResult NotConnected{status::NOT_CONNECTED};
const ProtocolResult ClientNetworkEncodingError{status::CLIENT_NETWORK_ENCODING};
const ProtocolResult ServerNetworkEncodingError{status::SERVER_NETWORK_ENCODING};
const ProtocolResult ClientNetworkDecodingError{status::CLIENT_NETWORK_DECODING};
const ProtocolResult ServerNetworkDecodingError{status::SERVER_NETWORK_DECODING};
const ProtocolResult ClientTransportEncodingError{status::CLIENT_TRANSPORT_ENCODING};
const ProtocolResult ServerTransportEncodingError{status::SERVER_TRANSPORT_ENCODING};
const ProtocolResult ClientTransportDecodingError{status::CLIENT_TRANSPORT_DECODING};
const ProtocolResult ServerTransportDecodingError{status::SERVER_TRANSPORT_DECODING};
const ProtocolResult ClientProtocolEncodingError{status::CLIENT_PROTOCOL_ENCODING};
const ProtocolResult ServerProtocolEncodingError{status::SERVER_PROTOCOL_ENCODING};
const ProtocolResult ClientProtocolDecodingError{status::CLIENT_PROTOCOL_DECODING};
const ProtocolResult ServerProtocolDecodingError{status::SERVER_PROTOCOL_DECODING};

}  // namespace rpc

}  // namespace sup
