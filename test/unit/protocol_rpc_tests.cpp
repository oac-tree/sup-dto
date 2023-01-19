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

#include <sup/rpc/protocol_rpc.h>

#include <sup/dto/anyvalue.h>

using namespace sup::rpc;

class ProtocolRPCTest : public ::testing::Test
{
protected:
  ProtocolRPCTest();
  virtual ~ProtocolRPCTest();
};

TEST_F(ProtocolRPCTest, RequestFormat)
{
  // Correctly formatted request
  sup::dto::AnyValue correct_request = {{
    { constants::REQUEST_TIMESTAMP, {sup::dto::UnsignedInteger64Type, 42u }},
    { constants::REQUEST_PAYLOAD, {sup::dto::BooleanType, true }}
  }};
  EXPECT_TRUE(utils::CheckRequestFormat(correct_request));

  // Correctly formatted request with extra field
  sup::dto::AnyValue correct_request_extra_field = {{
    { constants::REQUEST_TIMESTAMP, {sup::dto::UnsignedInteger64Type, 42u }},
    { constants::REQUEST_PAYLOAD, {sup::dto::BooleanType, true }},
    { "extra_field", "extra content" }
  }};
  EXPECT_TRUE(utils::CheckRequestFormat(correct_request_extra_field));

  // Missing timestamp field
  sup::dto::AnyValue request_missing_timestamp = {{
    { constants::REQUEST_PAYLOAD, {sup::dto::BooleanType, true }}
  }};
  EXPECT_FALSE(utils::CheckRequestFormat(request_missing_timestamp));

  // Incorrect type of timestamp field
  sup::dto::AnyValue request_wrong_timestamp_type = {{
    { constants::REQUEST_TIMESTAMP, {sup::dto::SignedInteger16Type, 42 }},
    { constants::REQUEST_PAYLOAD, {sup::dto::BooleanType, true }}
  }};
  EXPECT_FALSE(utils::CheckRequestFormat(request_wrong_timestamp_type));

  // Missing payload
  sup::dto::AnyValue request_missing_payload = {{
    { constants::REQUEST_TIMESTAMP, {sup::dto::UnsignedInteger64Type, 42u }}
  }};
  EXPECT_FALSE(utils::CheckRequestFormat(request_missing_payload));
}

TEST_F(ProtocolRPCTest, ReplyFormat)
{
  // Correctly formatted reply
  sup::dto::AnyValue correct_reply = {{
    { constants::REPLY_RESULT, {sup::dto::UnsignedInteger32Type, 42u }},
    { constants::REPLY_TIMESTAMP, {sup::dto::UnsignedInteger64Type, 42u }},
    { constants::REPLY_REASON, "some reason"}
  }};
  EXPECT_TRUE(utils::CheckReplyFormat(correct_reply));

  // Correctly formatted reply with payload
  sup::dto::AnyValue correct_reply_payload = {{
    { constants::REPLY_RESULT, {sup::dto::UnsignedInteger32Type, 42u }},
    { constants::REPLY_TIMESTAMP, {sup::dto::UnsignedInteger64Type, 42u }},
    { constants::REPLY_REASON, "some reason"},
    { constants::REPLY_PAYLOAD, {sup::dto::BooleanType, true }}
  }};
  EXPECT_TRUE(utils::CheckReplyFormat(correct_reply_payload));

  // Correctly formatted reply with payload and extra field
  sup::dto::AnyValue correct_reply_extra_field = {{
    { constants::REPLY_RESULT, {sup::dto::UnsignedInteger32Type, 42u }},
    { constants::REPLY_TIMESTAMP, {sup::dto::UnsignedInteger64Type, 42u }},
    { constants::REPLY_REASON, "some reason"},
    { constants::REPLY_PAYLOAD, {sup::dto::BooleanType, true }},
    { "extra_field", "extra content" }
  }};
  EXPECT_TRUE(utils::CheckReplyFormat(correct_reply_extra_field));

  // Reply with missing result field
  sup::dto::AnyValue reply_missing_result = {{
    { constants::REPLY_TIMESTAMP, {sup::dto::UnsignedInteger64Type, 42u }},
    { constants::REPLY_REASON, "some reason"},
    { constants::REPLY_PAYLOAD, {sup::dto::BooleanType, true }}
  }};
  EXPECT_FALSE(utils::CheckReplyFormat(reply_missing_result));

  // Reply with wrong type for result field
  sup::dto::AnyValue reply_wrong_result_type = {{
    { constants::REPLY_RESULT, {sup::dto::UnsignedInteger64Type, 42u }},
    { constants::REPLY_TIMESTAMP, {sup::dto::UnsignedInteger64Type, 42u }},
    { constants::REPLY_REASON, "some reason"},
    { constants::REPLY_PAYLOAD, {sup::dto::BooleanType, true }}
  }};
  EXPECT_FALSE(utils::CheckReplyFormat(reply_wrong_result_type));

  // Reply with missing timestamp field
  sup::dto::AnyValue reply_missing_timestamp = {{
    { constants::REPLY_RESULT, {sup::dto::UnsignedInteger32Type, 42u }},
    { constants::REPLY_REASON, "some reason"},
    { constants::REPLY_PAYLOAD, {sup::dto::BooleanType, true }}
  }};
  EXPECT_FALSE(utils::CheckReplyFormat(reply_missing_timestamp));

  // Reply with wrong type for timestamp field
  sup::dto::AnyValue reply_wrong_timestamp_type = {{
    { constants::REPLY_RESULT, {sup::dto::UnsignedInteger32Type, 42u }},
    { constants::REPLY_TIMESTAMP, {sup::dto::SignedInteger16Type, 42 }},
    { constants::REPLY_REASON, "some reason"},
    { constants::REPLY_PAYLOAD, {sup::dto::BooleanType, true }}
  }};
  EXPECT_FALSE(utils::CheckReplyFormat(reply_wrong_timestamp_type));

  // Reply with missing reason field
  sup::dto::AnyValue reply_missing_reason = {{
    { constants::REPLY_RESULT, {sup::dto::UnsignedInteger32Type, 42u }},
    { constants::REPLY_TIMESTAMP, {sup::dto::UnsignedInteger64Type, 42u }},
    { constants::REPLY_PAYLOAD, {sup::dto::BooleanType, true }}
  }};
  EXPECT_FALSE(utils::CheckReplyFormat(reply_missing_reason));

  // Reply with wrong type for reason field
  sup::dto::AnyValue reply_wrong_reason_type = {{
    { constants::REPLY_RESULT, {sup::dto::UnsignedInteger32Type, 42u }},
    { constants::REPLY_TIMESTAMP, {sup::dto::UnsignedInteger64Type, 42u }},
    { constants::REPLY_REASON, 3.14 },
    { constants::REPLY_PAYLOAD, {sup::dto::BooleanType, true }}
  }};
  EXPECT_FALSE(utils::CheckReplyFormat(reply_wrong_reason_type));
}

TEST_F(ProtocolRPCTest, CreateRequest)
{
  // Request without payload
  auto request_no_payload = utils::CreateRPCRequest({});
  EXPECT_EQ(request_no_payload.GetTypeName(), constants::REQUEST_TYPE_NAME);
  ASSERT_TRUE(request_no_payload.HasField(constants::REQUEST_TIMESTAMP));
  EXPECT_EQ(request_no_payload[constants::REQUEST_TIMESTAMP].GetType(),
            sup::dto::UnsignedInteger64Type);
  EXPECT_FALSE(request_no_payload.HasField(constants::REQUEST_PAYLOAD));
  // A request without payload is considered badly formed
  EXPECT_FALSE(utils::CheckRequestFormat(request_no_payload));

  // Request with payload
  sup::dto::AnyValue payload = {{
    { "enabled", true },
    { "value", 2.0f }
  }};
  auto request_payload = utils::CreateRPCRequest(payload);
  EXPECT_EQ(request_payload.GetTypeName(), constants::REQUEST_TYPE_NAME);
  ASSERT_TRUE(request_payload.HasField(constants::REQUEST_TIMESTAMP));
  EXPECT_EQ(request_payload[constants::REQUEST_TIMESTAMP].GetType(),
            sup::dto::UnsignedInteger64Type);
  ASSERT_TRUE(request_payload.HasField(constants::REQUEST_PAYLOAD));
  auto payload_from_request = request_payload[constants::REQUEST_PAYLOAD];
  EXPECT_EQ(payload_from_request.GetType(), payload.GetType());
  EXPECT_EQ(payload_from_request, payload);
  EXPECT_TRUE(utils::CheckRequestFormat(request_payload));
}

TEST_F(ProtocolRPCTest, CreateReply)
{
  // Reply from result only
  auto reply_from_result = utils::CreateRPCReply(Success);
  EXPECT_EQ(reply_from_result.GetTypeName(), constants::REPLY_TYPE_NAME);
  ASSERT_TRUE(reply_from_result.HasField(constants::REPLY_RESULT));
  EXPECT_EQ(reply_from_result[constants::REPLY_RESULT].GetType(),
            sup::dto::UnsignedInteger32Type);
  EXPECT_EQ(reply_from_result[constants::REPLY_RESULT].As<unsigned int>(), Success.GetValue());
  ASSERT_TRUE(reply_from_result.HasField(constants::REPLY_TIMESTAMP));
  EXPECT_EQ(reply_from_result[constants::REPLY_TIMESTAMP].GetType(),
            sup::dto::UnsignedInteger64Type);
  ASSERT_TRUE(reply_from_result.HasField(constants::REPLY_REASON));
  EXPECT_EQ(reply_from_result[constants::REPLY_REASON].GetType(), sup::dto::StringType);
  EXPECT_EQ(reply_from_result[constants::REPLY_REASON].As<std::string>(), "");
  EXPECT_FALSE(reply_from_result.HasField(constants::REPLY_PAYLOAD));
  EXPECT_TRUE(utils::CheckReplyFormat(reply_from_result));

  // Reply from result and custom reason
  std::string custom_reason = "oops!";
  auto reply_custom_reason = utils::CreateRPCReply(NotConnected, custom_reason);
  EXPECT_EQ(reply_custom_reason.GetTypeName(), constants::REPLY_TYPE_NAME);
  ASSERT_TRUE(reply_custom_reason.HasField(constants::REPLY_RESULT));
  EXPECT_EQ(reply_custom_reason[constants::REPLY_RESULT].GetType(),
            sup::dto::UnsignedInteger32Type);
  EXPECT_EQ(reply_custom_reason[constants::REPLY_RESULT].As<unsigned int>(),
            NotConnected.GetValue());
  ASSERT_TRUE(reply_custom_reason.HasField(constants::REPLY_TIMESTAMP));
  EXPECT_EQ(reply_custom_reason[constants::REPLY_TIMESTAMP].GetType(),
            sup::dto::UnsignedInteger64Type);
  ASSERT_TRUE(reply_custom_reason.HasField(constants::REPLY_REASON));
  EXPECT_EQ(reply_custom_reason[constants::REPLY_REASON].GetType(), sup::dto::StringType);
  EXPECT_EQ(reply_custom_reason[constants::REPLY_REASON].As<std::string>(), custom_reason);
  EXPECT_FALSE(reply_custom_reason.HasField(constants::REPLY_PAYLOAD));
  EXPECT_TRUE(utils::CheckReplyFormat(reply_custom_reason));

  // Reply from result, reason and payload
  sup::dto::AnyValue payload = {{
    { "enabled", true },
    { "value", 2.0f }
  }};
  auto reply_payload = utils::CreateRPCReply(NetworkEncodingError, custom_reason, payload);
  EXPECT_EQ(reply_payload.GetTypeName(), constants::REPLY_TYPE_NAME);
  ASSERT_TRUE(reply_payload.HasField(constants::REPLY_RESULT));
  EXPECT_EQ(reply_payload[constants::REPLY_RESULT].GetType(),
            sup::dto::UnsignedInteger32Type);
  EXPECT_EQ(reply_payload[constants::REPLY_RESULT].As<unsigned int>(),
            NetworkEncodingError.GetValue());
  ASSERT_TRUE(reply_payload.HasField(constants::REPLY_TIMESTAMP));
  EXPECT_EQ(reply_payload[constants::REPLY_TIMESTAMP].GetType(),
            sup::dto::UnsignedInteger64Type);
  ASSERT_TRUE(reply_payload.HasField(constants::REPLY_REASON));
  EXPECT_EQ(reply_payload[constants::REPLY_REASON].GetType(), sup::dto::StringType);
  EXPECT_EQ(reply_payload[constants::REPLY_REASON].As<std::string>(), custom_reason);
  ASSERT_TRUE(reply_payload.HasField(constants::REPLY_PAYLOAD));
  EXPECT_EQ(reply_payload[constants::REPLY_PAYLOAD].GetType(), payload.GetType());
  EXPECT_EQ(reply_payload[constants::REPLY_PAYLOAD], payload);
  EXPECT_TRUE(utils::CheckReplyFormat(reply_payload));
}

ProtocolRPCTest::ProtocolRPCTest() = default;

ProtocolRPCTest::~ProtocolRPCTest() = default;
