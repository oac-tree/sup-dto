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

#ifndef SUP_CONFIG_TEST_PROTOCOL_H_
#define SUP_CONFIG_TEST_PROTOCOL_H_

#include <sup/rpc/protocol.h>

#include <memory>

namespace sup
{
namespace rpc
{
namespace test
{
const std::string ECHO_FIELD = "echo";
const std::string THROW_FIELD = "throw";
const std::string REQUESTED_STATUS_FIELD = "requested_status";

const std::string TEST_PROTOCOL_TYPE = "TestProtocol";
const std::string TEST_PROTOCOL_VERSION = "1.0";

class TestProtocol : public Protocol
{
public:
  TestProtocol();
  ~TestProtocol();

  ProtocolResult Invoke(const sup::dto::AnyValue& input, sup::dto::AnyValue& output) override;

  ProtocolResult Service(const sup::dto::AnyValue& input, sup::dto::AnyValue& output) override;

  void SetFailForServiceRequest(bool fail);
  void SetThrowForServiceRequest(bool enable_throw);

  sup::dto::AnyValue GetLastInput() const;

private:
  std::unique_ptr<sup::dto::AnyValue> m_last_input;
  bool m_service_fail;
  bool m_service_throw;
};

}  // namespace test

}  // namespace rpc

}  // namespace sup

#endif  // SUP_CONFIG_TEST_PROTOCOL_H_
