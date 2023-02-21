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

#include "test_protocol.h"

#include <sup/rpc/protocol_rpc_client.h>
#include <sup/rpc/protocol_rpc_server.h>

#include <sup/rpc/protocol_rpc.h>
#include <sup/rpc/rpc_exceptions.h>
#include <sup/dto/any_functor.h>
#include <sup/dto/anyvalue.h>

#include <gtest/gtest.h>

using namespace sup::rpc;

static const std::string BAD_REPLY_FIELD = "bad_reply";
static const std::string THROW_FIELD = "throw";

class TestFunctor : public sup::dto::AnyFunctor
{
public:
  TestFunctor();
  ~TestFunctor();

  sup::dto::AnyValue operator()(const sup::dto::AnyValue& input) override;

  sup::dto::AnyValue GetLastRequest() const;

private:
  std::unique_ptr<sup::dto::AnyValue> m_last_request;
};

class ProtocolRPCClientTest : public ::testing::Test
{
protected:
  ProtocolRPCClientTest();
  virtual ~ProtocolRPCClientTest();

  std::unique_ptr<sup::dto::AnyFunctor> GetSharedFunctor();
  std::unique_ptr<sup::dto::AnyFunctor> GetServerFunctor();

  TestFunctor* m_test_functor;
  test::TestProtocol* m_test_protocol;
};

TEST_F(ProtocolRPCClientTest, Construction)
{
  EXPECT_THROW(ProtocolRPCClient null_client{std::unique_ptr<sup::dto::AnyFunctor>{}},
               NullDependencyException);
  EXPECT_NO_THROW(ProtocolRPCClient client{GetSharedFunctor()});
}

TEST_F(ProtocolRPCClientTest, InvokeEmptyInput)
{
  ProtocolRPCClient client{GetSharedFunctor()};
  sup::dto::AnyValue output;
  EXPECT_EQ(client.Invoke(sup::dto::AnyValue{}, output), TransportEncodingError);
  EXPECT_TRUE(sup::dto::IsEmptyValue(output));
  EXPECT_TRUE(sup::dto::IsEmptyValue(m_test_functor->GetLastRequest()));
}

TEST_F(ProtocolRPCClientTest, InvokeScalarInput)
{
  ProtocolRPCClient client{GetSharedFunctor()};
  sup::dto::AnyValue input{sup::dto::SignedInteger32Type, 42};
  sup::dto::AnyValue output;
  EXPECT_EQ(client.Invoke(input, output), Success);
  EXPECT_FALSE(sup::dto::IsEmptyValue(output));
  EXPECT_EQ(input, output);
  auto last_request = m_test_functor->GetLastRequest();
  EXPECT_FALSE(sup::dto::IsEmptyValue(last_request));
  EXPECT_TRUE(utils::CheckRequestFormat(last_request));
  EXPECT_EQ(last_request.GetTypeName(), constants::REQUEST_TYPE_NAME);
  EXPECT_TRUE(last_request.HasField(constants::REQUEST_TIMESTAMP));
  EXPECT_EQ(last_request[constants::REQUEST_TIMESTAMP].GetType(), sup::dto::UnsignedInteger64Type);
  EXPECT_TRUE(last_request.HasField(constants::REQUEST_PAYLOAD));
  EXPECT_EQ(last_request[constants::REQUEST_PAYLOAD].GetType(), sup::dto::SignedInteger32Type);
  EXPECT_EQ(last_request[constants::REQUEST_PAYLOAD], input);
}

TEST_F(ProtocolRPCClientTest, InvokeBadReply)
{
  ProtocolRPCClient client{GetSharedFunctor()};
  sup::dto::AnyValue input = {{
    {BAD_REPLY_FIELD, {sup::dto::BooleanType, true}}
  }};
  sup::dto::AnyValue output{};
  EXPECT_EQ(client.Invoke(input, output), TransportDecodingError);
  EXPECT_TRUE(sup::dto::IsEmptyValue(output));

  auto last_request = m_test_functor->GetLastRequest();
  EXPECT_FALSE(sup::dto::IsEmptyValue(last_request));
  EXPECT_TRUE(utils::CheckRequestFormat(last_request));
  EXPECT_EQ(last_request.GetTypeName(), constants::REQUEST_TYPE_NAME);
  EXPECT_TRUE(last_request.HasField(constants::REQUEST_TIMESTAMP));
  EXPECT_EQ(last_request[constants::REQUEST_TIMESTAMP].GetType(), sup::dto::UnsignedInteger64Type);
  EXPECT_TRUE(last_request.HasField(constants::REQUEST_PAYLOAD));
  EXPECT_EQ(last_request[constants::REQUEST_PAYLOAD].GetType(), input.GetType());
  EXPECT_EQ(last_request[constants::REQUEST_PAYLOAD], input);
}

TEST_F(ProtocolRPCClientTest, InvokeBadOutput)
{
  ProtocolRPCClient client{GetSharedFunctor()};
  sup::dto::AnyValue input{sup::dto::SignedInteger32Type, 42};
  sup::dto::AnyValue output_start{sup::dto::StringType, "start_value"};
  sup::dto::AnyValue output{output_start};
  EXPECT_EQ(client.Invoke(input, output), TransportDecodingError);
  EXPECT_FALSE(sup::dto::IsEmptyValue(output));
  EXPECT_EQ(output, output_start);
}

TEST_F(ProtocolRPCClientTest, FunctorThrows)
{
  ProtocolRPCClient client{GetSharedFunctor()};
  sup::dto::AnyValue input = {{
    {THROW_FIELD, {sup::dto::BooleanType, true}}
  }};
  sup::dto::AnyValue output{};
  EXPECT_EQ(client.Invoke(input, output), TransportDecodingError);
  EXPECT_TRUE(sup::dto::IsEmptyValue(output));

  auto last_request = m_test_functor->GetLastRequest();
  EXPECT_FALSE(sup::dto::IsEmptyValue(last_request));
  EXPECT_TRUE(utils::CheckRequestFormat(last_request));
  EXPECT_EQ(last_request.GetTypeName(), constants::REQUEST_TYPE_NAME);
  EXPECT_TRUE(last_request.HasField(constants::REQUEST_TIMESTAMP));
  EXPECT_EQ(last_request[constants::REQUEST_TIMESTAMP].GetType(), sup::dto::UnsignedInteger64Type);
  EXPECT_TRUE(last_request.HasField(constants::REQUEST_PAYLOAD));
  EXPECT_EQ(last_request[constants::REQUEST_PAYLOAD].GetType(), input.GetType());
  EXPECT_EQ(last_request[constants::REQUEST_PAYLOAD], input);
}

TEST_F(ProtocolRPCClientTest, ApplicationProtocolInfo)
{
  ProtocolRPCClient client{GetServerFunctor()};
  // Successful retrieval of application protocol information
  m_test_protocol->SetFailForServiceRequest(false);
  auto protocol_info = utils::GetApplicationProtocolInfo(client);
  EXPECT_EQ(protocol_info.m_application_type, test::TEST_PROTOCOL_TYPE);
  EXPECT_EQ(protocol_info.m_application_version, test::TEST_PROTOCOL_VERSION);
  // Failing retrieval of application protocol information
  m_test_protocol->SetFailForServiceRequest(true);
  protocol_info = utils::GetApplicationProtocolInfo(client);
  EXPECT_TRUE(protocol_info.m_application_type.empty());
  EXPECT_TRUE(protocol_info.m_application_version.empty());
}

TestFunctor::TestFunctor()
  : m_last_request{}
{}

TestFunctor::~TestFunctor() = default;

sup::dto::AnyValue TestFunctor::operator()(const sup::dto::AnyValue& input)
{
  m_last_request.reset(new sup::dto::AnyValue(input));
  auto query = input[constants::REQUEST_PAYLOAD];
  if (query.HasField(BAD_REPLY_FIELD) && query[BAD_REPLY_FIELD].As<bool>())
  {
    return sup::dto::AnyValue{{{"BadReplyFormat", {sup::dto::BooleanType, true}}}};
  }
  if (query.HasField(THROW_FIELD) && query[THROW_FIELD].As<bool>())
  {
    throw std::runtime_error("Throwing on demand");
  }
  return utils::CreateRPCReply(Success, "", query);
}

sup::dto::AnyValue TestFunctor::GetLastRequest() const
{
  if (!m_last_request)
  {
    return {};
  }
  sup::dto::AnyValue result{*m_last_request};
  return result;
}

ProtocolRPCClientTest::ProtocolRPCClientTest()
  : m_test_functor{nullptr}
  , m_test_protocol{nullptr}
{}

ProtocolRPCClientTest::~ProtocolRPCClientTest() = default;

std::unique_ptr<sup::dto::AnyFunctor> ProtocolRPCClientTest::GetSharedFunctor()
{
  m_test_functor = new TestFunctor{};
  return std::unique_ptr<sup::dto::AnyFunctor>{m_test_functor};
}

std::unique_ptr<sup::dto::AnyFunctor> ProtocolRPCClientTest::GetServerFunctor()
{
  m_test_protocol = new test::TestProtocol;
  std::unique_ptr<Protocol> protocol{m_test_protocol};
  return std::unique_ptr<sup::dto::AnyFunctor>{new ProtocolRPCServer{std::move(protocol)}};
}
