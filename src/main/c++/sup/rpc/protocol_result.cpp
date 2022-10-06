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
  SUCCESS = 0,     ///< Successful.
  NOT_CONNECTED,    ///< The service is not connected.
  INVALID_REQUEST,  ///< Generic error, check the logs for details.
  PROTOCOL_ERROR,   ///< Low-level protocol error, e.g. malformed request.
};
}  // namespace status

ProtocolResult::ProtocolResult()
  : m_value{status::SUCCESS}
{}

ProtocolResult::~ProtocolResult() = default;

ProtocolResult::ProtocolResult(int value)
  : m_value{value}
{}

ProtocolResult::ProtocolResult(const ProtocolResult& other)
  : m_value{other.m_value}
{}

ProtocolResult& ProtocolResult::operator=(const ProtocolResult& other)
{
  m_value = other.m_value;
}

int ProtocolResult::GetValue() const
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
      {status::INVALID_REQUEST, "InvalidRequest"},
      {status::PROTOCOL_ERROR, "ProtocolError"}};
  auto it = results.find(result.GetValue());
  if (it != results.end())
  {
    return it->second;
  }
  return "Unknown ProtocolResult: " + std::to_string(result.GetValue());
}

const ProtocolResult Success{status::SUCCESS};
const ProtocolResult NotConnected{status::NOT_CONNECTED};
const ProtocolResult InvalidRequest{status::INVALID_REQUEST};
const ProtocolResult ProtocolError{status::PROTOCOL_ERROR};

}  // namespace rpc

}  // namespace sup
