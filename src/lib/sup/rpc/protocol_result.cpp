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
  NETWORK_ENCODING,
  NETWORK_DECODING,
  TRANSPORT_ENCODING,
  TRANSPORT_DECODING
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
      {status::NETWORK_ENCODING, "NetworkEncodingError"},
      {status::NETWORK_DECODING, "NetworkDecodingError"},
      {status::TRANSPORT_ENCODING, "TransportEncodingError"},
      {status::TRANSPORT_DECODING, "TransportDecodingError"}};
  auto it = results.find(result.GetValue());
  if (it != results.end())
  {
    return it->second;
  }
  return "Unknown ProtocolResult: " + std::to_string(result.GetValue());
}

const ProtocolResult Success{status::SUCCESS};
const ProtocolResult NotConnected{status::NOT_CONNECTED};
const ProtocolResult NetworkEncodingError{status::NETWORK_ENCODING};
const ProtocolResult NetworkDecodingError{status::NETWORK_DECODING};
const ProtocolResult TransportEncodingError{status::TRANSPORT_ENCODING};
const ProtocolResult TransportDecodingError{status::TRANSPORT_DECODING};

}  // namespace rpc

}  // namespace sup
