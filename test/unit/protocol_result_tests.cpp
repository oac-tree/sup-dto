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

#include <sup/rpc/protocol_result.h>

#include <sup/dto/anyvalue.h>

using namespace sup::rpc;

class ProtocolResultTest : public ::testing::Test
{
protected:
  ProtocolResultTest();
  virtual ~ProtocolResultTest();
};

TEST_F(ProtocolResultTest, Construction)
{
  ProtocolResult default_result;
  EXPECT_EQ(default_result.GetValue(), 0);
  EXPECT_EQ(default_result, Success);

  ProtocolResult custom_result{42};
  EXPECT_EQ(custom_result.GetValue(), 42u);
  EXPECT_NE(custom_result, Success);

  ProtocolResult not_connected_copy{NotConnected};
  EXPECT_EQ(not_connected_copy.GetValue(), NotConnected.GetValue());
  EXPECT_EQ(not_connected_copy, NotConnected);
}

TEST_F(ProtocolResultTest, Copy)
{
  ProtocolResult result;
  EXPECT_EQ(result.GetValue(), 0);
  EXPECT_EQ(result, Success);

  // NotConnected
  result = NotConnected;
  EXPECT_EQ(result.GetValue(), NotConnected.GetValue());
  EXPECT_EQ(result, NotConnected);

  // ClientNetworkEncodingError
  result = ClientNetworkEncodingError;
  EXPECT_EQ(result.GetValue(), ClientNetworkEncodingError.GetValue());
  EXPECT_EQ(result, ClientNetworkEncodingError);

  // ServerNetworkEncodingError
  result = ServerNetworkEncodingError;
  EXPECT_EQ(result.GetValue(), ServerNetworkEncodingError.GetValue());
  EXPECT_EQ(result, ServerNetworkEncodingError);

  // ClientNetworkDecodingError
  result = ClientNetworkDecodingError;
  EXPECT_EQ(result.GetValue(), ClientNetworkDecodingError.GetValue());
  EXPECT_EQ(result, ClientNetworkDecodingError);

  // ServerNetworkDecodingError
  result = ServerNetworkDecodingError;
  EXPECT_EQ(result.GetValue(), ServerNetworkDecodingError.GetValue());
  EXPECT_EQ(result, ServerNetworkDecodingError);

  // ClientTransportEncodingError
  result = ClientTransportEncodingError;
  EXPECT_EQ(result.GetValue(), ClientTransportEncodingError.GetValue());
  EXPECT_EQ(result, ClientTransportEncodingError);

  // ServerTransportEncodingError
  result = ServerTransportEncodingError;
  EXPECT_EQ(result.GetValue(), ServerTransportEncodingError.GetValue());
  EXPECT_EQ(result, ServerTransportEncodingError);

  // ClientTransportDecodingError
  result = ClientTransportDecodingError;
  EXPECT_EQ(result.GetValue(), ClientTransportDecodingError.GetValue());
  EXPECT_EQ(result, ClientTransportDecodingError);

  // ServerTransportDecodingError
  result = ServerTransportDecodingError;
  EXPECT_EQ(result.GetValue(), ServerTransportDecodingError.GetValue());
  EXPECT_EQ(result, ServerTransportDecodingError);

  // ClientProtocolEncodingError
  result = ClientProtocolEncodingError;
  EXPECT_EQ(result.GetValue(), ClientProtocolEncodingError.GetValue());
  EXPECT_EQ(result, ClientProtocolEncodingError);

  // ServerProtocolEncodingError
  result = ServerProtocolEncodingError;
  EXPECT_EQ(result.GetValue(), ServerProtocolEncodingError.GetValue());
  EXPECT_EQ(result, ServerProtocolEncodingError);

  // ClientProtocolDecodingError
  result = ClientProtocolDecodingError;
  EXPECT_EQ(result.GetValue(), ClientProtocolDecodingError.GetValue());
  EXPECT_EQ(result, ClientProtocolDecodingError);

  // ServerProtocolDecodingError
  result = ServerProtocolDecodingError;
  EXPECT_EQ(result.GetValue(), ServerProtocolDecodingError.GetValue());
  EXPECT_EQ(result, ServerProtocolDecodingError);

  // Custom result
  ProtocolResult custom_result{42};
  result = custom_result;
  EXPECT_EQ(result.GetValue(), custom_result.GetValue());
  EXPECT_EQ(result, custom_result);
}

TEST_F(ProtocolResultTest, ToString)
{
  ProtocolResult result;
  EXPECT_EQ(ProtocolResultToString(result), "Success");

  // NotConnected
  result = NotConnected;
  EXPECT_EQ(ProtocolResultToString(result), "NotConnected");

  // ClientNetworkEncodingError
  result = ClientNetworkEncodingError;
  EXPECT_EQ(ProtocolResultToString(result), "ClientNetworkEncodingError");

  // ServerNetworkEncodingError
  result = ServerNetworkEncodingError;
  EXPECT_EQ(ProtocolResultToString(result), "ServerNetworkEncodingError");

  // ClientNetworkDecodingError
  result = ClientNetworkDecodingError;
  EXPECT_EQ(ProtocolResultToString(result), "ClientNetworkDecodingError");

  // ServerNetworkDecodingError
  result = ServerNetworkDecodingError;
  EXPECT_EQ(ProtocolResultToString(result), "ServerNetworkDecodingError");

  // ClientTransportEncodingError
  result = ClientTransportEncodingError;
  EXPECT_EQ(ProtocolResultToString(result), "ClientTransportEncodingError");

  // ServerTransportEncodingError
  result = ServerTransportEncodingError;
  EXPECT_EQ(ProtocolResultToString(result), "ServerTransportEncodingError");

  // ClientTransportDecodingError
  result = ClientTransportDecodingError;
  EXPECT_EQ(ProtocolResultToString(result), "ClientTransportDecodingError");

  // ServerTransportDecodingError
  result = ServerTransportDecodingError;
  EXPECT_EQ(ProtocolResultToString(result), "ServerTransportDecodingError");

  // ClientProtocolEncodingError
  result = ClientProtocolEncodingError;
  EXPECT_EQ(ProtocolResultToString(result), "ClientProtocolEncodingError");

  // ServerProtocolEncodingError
  result = ServerProtocolEncodingError;
  EXPECT_EQ(ProtocolResultToString(result), "ServerProtocolEncodingError");

  // ClientProtocolDecodingError
  result = ClientProtocolDecodingError;
  EXPECT_EQ(ProtocolResultToString(result), "ClientProtocolDecodingError");

  // ServerProtocolDecodingError
  result = ServerProtocolDecodingError;
  EXPECT_EQ(ProtocolResultToString(result), "ServerProtocolDecodingError");

  // Custom result
  ProtocolResult custom_result{42};
  result = custom_result;
  EXPECT_EQ(ProtocolResultToString(result), "Unknown ProtocolResult: 42");
}

TEST_F(ProtocolResultTest, Comparison)
{
  // Equality
  ProtocolResult result;
  EXPECT_TRUE(result == Success);
  EXPECT_FALSE(result == NotConnected);
  EXPECT_FALSE(result == ClientNetworkEncodingError);
  EXPECT_FALSE(result == ServerNetworkDecodingError);
  EXPECT_FALSE(result == ClientTransportEncodingError);
  EXPECT_FALSE(result == ServerTransportDecodingError);

  // Non equality
  ProtocolResult custom_result{42};
  EXPECT_TRUE(custom_result != Success);
  EXPECT_TRUE(custom_result != NotConnected);
  EXPECT_TRUE(custom_result != ClientNetworkEncodingError);
  EXPECT_TRUE(custom_result != ServerNetworkEncodingError);
  EXPECT_TRUE(custom_result != ClientNetworkDecodingError);
  EXPECT_TRUE(custom_result != ServerNetworkDecodingError);
  EXPECT_TRUE(custom_result != ClientTransportEncodingError);
  EXPECT_TRUE(custom_result != ServerTransportEncodingError);
  EXPECT_TRUE(custom_result != ClientTransportDecodingError);
  EXPECT_TRUE(custom_result != ServerTransportDecodingError);
  EXPECT_TRUE(custom_result != ClientProtocolEncodingError);
  EXPECT_TRUE(custom_result != ServerProtocolEncodingError);
  EXPECT_TRUE(custom_result != ClientProtocolDecodingError);
  EXPECT_TRUE(custom_result != ServerProtocolDecodingError);
  EXPECT_FALSE(custom_result != ProtocolResult(42u));
}

ProtocolResultTest::ProtocolResultTest() = default;

ProtocolResultTest::~ProtocolResultTest() = default;
