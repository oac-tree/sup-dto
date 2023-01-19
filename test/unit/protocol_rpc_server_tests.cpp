/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : SUP - DTO
 *
 * Description   : Unit test code
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

#include <gtest/gtest.h>

#include <sup/rpc/protocol_rpc_server.h>

#include <sup/rpc/protocol_rpc.h>
#include <sup/rpc/rpc_exceptions.h>
#include <sup/dto/anyvalue.h>
#include <sup/dto/anyvalue_helper.h>

using namespace sup::rpc;

static const std::string THROW_FIELD = "throw";
static const std::string ECHO_FIELD = "echo";
static const std::string REQUESTED_STATUS_FIELD = "requested_status";

class TestProtocol : public Protocol
{
public:
  TestProtocol();
  ~TestProtocol();

  ProtocolResult Invoke(const sup::dto::AnyValue& input, sup::dto::AnyValue& output) override;

  sup::dto::AnyValue GetLastInput() const;

private:
  std::unique_ptr<sup::dto::AnyValue> m_last_input;
};

class SharedTestProtocol : public Protocol
{
public:
  SharedTestProtocol(Protocol* shared_protocol);
  ~SharedTestProtocol();

  ProtocolResult Invoke(const sup::dto::AnyValue& input, sup::dto::AnyValue& output) override;

private:
  Protocol* m_shared_protocol;
};

class ProtocolRPCServerTest : public ::testing::Test
{
protected:
  ProtocolRPCServerTest();
  virtual ~ProtocolRPCServerTest();

  std::unique_ptr<Protocol> GetSharedProtocol();

  TestProtocol m_test_protocol;
};

TEST_F(ProtocolRPCServerTest, Construction)
{
  EXPECT_THROW(ProtocolRPCServer null_server{std::unique_ptr<Protocol>{}},
               NullDependencyException);
  EXPECT_NO_THROW(ProtocolRPCServer server{GetSharedProtocol()});
}

TEST_F(ProtocolRPCServerTest, EmptyRequest)
{
  ProtocolRPCServer server{GetSharedProtocol()};
  sup::dto::AnyValue request;
  auto reply = server(request);
  EXPECT_TRUE(utils::CheckReplyFormat(reply));
  EXPECT_EQ(reply[constants::REPLY_RESULT].As<unsigned int>(), TransportDecodingError.GetValue());
  EXPECT_FALSE(reply.HasField(constants::REPLY_PAYLOAD));
}

TEST_F(ProtocolRPCServerTest, BadRequest)
{
  ProtocolRPCServer server{GetSharedProtocol()};

  // Request contains no timestamp field
  sup::dto::AnyValue request_no_timestamp = {{
    { constants::REPLY_PAYLOAD, {sup::dto::UnsignedInteger8Type, 1 }}
  }};
  auto reply_1 = server(request_no_timestamp);
  EXPECT_TRUE(utils::CheckReplyFormat(reply_1));
  EXPECT_EQ(reply_1[constants::REPLY_RESULT].As<unsigned int>(), TransportDecodingError.GetValue());
  EXPECT_FALSE(reply_1.HasField(constants::REPLY_PAYLOAD));

  // Request contains no payload field
  sup::dto::AnyValue request_no_payload = {{
    { constants::REQUEST_TIMESTAMP, {sup::dto::UnsignedInteger64Type, 54321u }}
  }};
  auto reply_2 = server(request_no_payload);
  EXPECT_TRUE(utils::CheckReplyFormat(reply_2));
  EXPECT_EQ(reply_2[constants::REPLY_RESULT].As<unsigned int>(), TransportDecodingError.GetValue());
  EXPECT_FALSE(reply_2.HasField(constants::REPLY_PAYLOAD));

  // Request contains timestamp field of wrong type
  sup::dto::AnyValue request_wrong_timestamp_type = {{
    { constants::REQUEST_TIMESTAMP, {sup::dto::UnsignedInteger32Type, 54321u }},
    { constants::REQUEST_PAYLOAD, {sup::dto::UnsignedInteger8Type, 1 }}
  }};
  auto reply_3 = server(request_wrong_timestamp_type);
  EXPECT_TRUE(utils::CheckReplyFormat(reply_3));
  EXPECT_EQ(reply_3[constants::REPLY_RESULT].As<unsigned int>(), TransportDecodingError.GetValue());
  EXPECT_FALSE(reply_3.HasField(constants::REPLY_PAYLOAD));
}

TEST_F(ProtocolRPCServerTest, ScalarPayload)
{
  ProtocolRPCServer server{GetSharedProtocol()};

  sup::dto::AnyValue request = {{
    { constants::REQUEST_TIMESTAMP, {sup::dto::UnsignedInteger64Type, 54321u }},
    { constants::REQUEST_PAYLOAD, {sup::dto::UnsignedInteger8Type, 1 }}
  }};
  auto reply = server(request);
  EXPECT_TRUE(utils::CheckReplyFormat(reply));
  EXPECT_EQ(reply[constants::REPLY_RESULT].As<unsigned int>(), Success.GetValue());
  EXPECT_FALSE(reply.HasField(constants::REPLY_PAYLOAD));

  auto last_input = m_test_protocol.GetLastInput();
  EXPECT_FALSE(sup::dto::IsEmptyValue(last_input));
  EXPECT_EQ(last_input.GetType(), sup::dto::UnsignedInteger8Type);
  EXPECT_EQ(last_input.As<sup::dto::uint8>(), 1);
}

TEST_F(ProtocolRPCServerTest, ExtraFieldInRequest)
{
  ProtocolRPCServer server{GetSharedProtocol()};

  // Extra fields are ignored in the request structure
  sup::dto::AnyValue request = {{
    { constants::REQUEST_TIMESTAMP, {sup::dto::UnsignedInteger64Type, 54321u }},
    { constants::REQUEST_PAYLOAD, {sup::dto::UnsignedInteger8Type, 1 }},
    { "extra_field", {sup::dto::Float32Type, 3.25f }}
  }};
  auto reply = server(request);
  EXPECT_TRUE(utils::CheckReplyFormat(reply));
  EXPECT_EQ(reply[constants::REPLY_RESULT].As<unsigned int>(), Success.GetValue());
  EXPECT_FALSE(reply.HasField(constants::REPLY_PAYLOAD));

  auto last_input = m_test_protocol.GetLastInput();
  EXPECT_FALSE(sup::dto::IsEmptyValue(last_input));
  EXPECT_EQ(last_input.GetType(), sup::dto::UnsignedInteger8Type);
  EXPECT_EQ(last_input.As<sup::dto::uint8>(), 1);
}

TEST_F(ProtocolRPCServerTest, ProtocolThrows)
{
  ProtocolRPCServer server{GetSharedProtocol()};

  sup::dto::AnyValue payload = {{
    { THROW_FIELD, {sup::dto::BooleanType, true }}
  }};
  sup::dto::AnyValue request = {{
    { constants::REQUEST_TIMESTAMP, {sup::dto::UnsignedInteger64Type, 54321u }},
    { constants::REQUEST_PAYLOAD, payload }
  }};
  auto reply = server(request);
  EXPECT_TRUE(utils::CheckReplyFormat(reply));
  EXPECT_EQ(reply[constants::REPLY_RESULT].As<unsigned int>(), TransportEncodingError.GetValue());
  EXPECT_FALSE(reply.HasField(constants::REPLY_PAYLOAD));

  auto last_input = m_test_protocol.GetLastInput();
  EXPECT_FALSE(sup::dto::IsEmptyValue(last_input));
  EXPECT_EQ(last_input.GetType(), payload.GetType());
  EXPECT_EQ(last_input, payload);
}

TEST_F(ProtocolRPCServerTest, RequestProtocolResult)
{
  ProtocolRPCServer server{GetSharedProtocol()};

  sup::dto::AnyValue payload = {{
    { REQUESTED_STATUS_FIELD, {sup::dto::UnsignedInteger32Type, 42 }}
  }};
  sup::dto::AnyValue request = {{
    { constants::REQUEST_TIMESTAMP, {sup::dto::UnsignedInteger64Type, 54321u }},
    { constants::REQUEST_PAYLOAD, payload }
  }};
  auto reply = server(request);
  EXPECT_TRUE(utils::CheckReplyFormat(reply));
  EXPECT_EQ(reply[constants::REPLY_RESULT].As<unsigned int>(), 42u);
  EXPECT_FALSE(reply.HasField(constants::REPLY_PAYLOAD));

  auto last_input = m_test_protocol.GetLastInput();
  EXPECT_FALSE(sup::dto::IsEmptyValue(last_input));
  EXPECT_EQ(last_input.GetType(), payload.GetType());
  EXPECT_EQ(last_input, payload);
}

TEST_F(ProtocolRPCServerTest, EchoPayload)
{
  ProtocolRPCServer server{GetSharedProtocol()};

  sup::dto::AnyValue payload = {{
    { REQUESTED_STATUS_FIELD, {sup::dto::UnsignedInteger32Type, 65 }},
    { ECHO_FIELD, {sup::dto::BooleanType, true }}
  }};
  sup::dto::AnyValue request = {{
    { constants::REQUEST_TIMESTAMP, {sup::dto::UnsignedInteger64Type, 54321u }},
    { constants::REQUEST_PAYLOAD, payload }
  }};
  auto reply = server(request);
  EXPECT_TRUE(utils::CheckReplyFormat(reply));
  EXPECT_EQ(reply[constants::REPLY_RESULT].As<unsigned int>(), 65u);

  auto last_input = m_test_protocol.GetLastInput();
  EXPECT_FALSE(sup::dto::IsEmptyValue(last_input));
  EXPECT_EQ(last_input.GetType(), payload.GetType());
  EXPECT_EQ(last_input, payload);

  EXPECT_TRUE(reply.HasField(constants::REPLY_PAYLOAD));
  auto reply_payload = reply[constants::REPLY_PAYLOAD];
  EXPECT_EQ(reply_payload.GetType(), payload.GetType());
  EXPECT_EQ(reply_payload, payload);
}

TestProtocol::TestProtocol()
  : m_last_input{}
{}

TestProtocol::~TestProtocol() = default;

ProtocolResult TestProtocol::Invoke(const sup::dto::AnyValue& input, sup::dto::AnyValue& output)
{
  m_last_input.reset(new sup::dto::AnyValue(input));
  if (input.HasField(ECHO_FIELD) && input[ECHO_FIELD].As<bool>())
  {
    sup::dto::TryConvert(output, input);
  }
  if (input.HasField(THROW_FIELD) && input[THROW_FIELD].As<bool>())
  {
    throw std::runtime_error("Throwing on demand");
  }
  if (input.HasField(REQUESTED_STATUS_FIELD) &&
      input[REQUESTED_STATUS_FIELD].GetType() == sup::dto::UnsignedInteger32Type)
  {
    return ProtocolResult(input[REQUESTED_STATUS_FIELD].As<sup::dto::uint32>());
  }
  return Success;
}

sup::dto::AnyValue TestProtocol::GetLastInput() const
{
  if (!m_last_input)
  {
    return {};
  }
  sup::dto::AnyValue result{*m_last_input};
  return result;
}

SharedTestProtocol::SharedTestProtocol(Protocol* shared_protocol)
  : m_shared_protocol{shared_protocol}
{}

SharedTestProtocol::~SharedTestProtocol() = default;

ProtocolResult SharedTestProtocol::Invoke(const sup::dto::AnyValue& input,
                                          sup::dto::AnyValue& output)
{
  return m_shared_protocol->Invoke(input, output);
}

ProtocolRPCServerTest::ProtocolRPCServerTest()
  : m_test_protocol{}
{}

ProtocolRPCServerTest::~ProtocolRPCServerTest() = default;

std::unique_ptr<Protocol> ProtocolRPCServerTest::GetSharedProtocol()
{
  return std::unique_ptr<Protocol>(new SharedTestProtocol(&m_test_protocol));
}