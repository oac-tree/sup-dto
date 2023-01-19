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

  // NetworkEncodingError
  result = NetworkEncodingError;
  EXPECT_EQ(result.GetValue(), NetworkEncodingError.GetValue());
  EXPECT_EQ(result, NetworkEncodingError);

  // NetworkDecodingError
  result = NetworkDecodingError;
  EXPECT_EQ(result.GetValue(), NetworkDecodingError.GetValue());
  EXPECT_EQ(result, NetworkDecodingError);

  // TransportEncodingError
  result = TransportEncodingError;
  EXPECT_EQ(result.GetValue(), TransportEncodingError.GetValue());
  EXPECT_EQ(result, TransportEncodingError);

  // TransportDecodingError
  result = TransportDecodingError;
  EXPECT_EQ(result.GetValue(), TransportDecodingError.GetValue());
  EXPECT_EQ(result, TransportDecodingError);

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

  // NetworkEncodingError
  result = NetworkEncodingError;
  EXPECT_EQ(ProtocolResultToString(result), "NetworkEncodingError");

  // NetworkDecodingError
  result = NetworkDecodingError;
  EXPECT_EQ(ProtocolResultToString(result), "NetworkDecodingError");

  // TransportEncodingError
  result = TransportEncodingError;
  EXPECT_EQ(ProtocolResultToString(result), "TransportEncodingError");

  // TransportDecodingError
  result = TransportDecodingError;
  EXPECT_EQ(ProtocolResultToString(result), "TransportDecodingError");

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
  EXPECT_FALSE(result == NetworkEncodingError);
  EXPECT_FALSE(result == NetworkDecodingError);
  EXPECT_FALSE(result == TransportEncodingError);
  EXPECT_FALSE(result == TransportDecodingError);

  // Non equality
  ProtocolResult custom_result{42};
  EXPECT_TRUE(custom_result != Success);
  EXPECT_TRUE(custom_result != NotConnected);
  EXPECT_TRUE(custom_result != NetworkEncodingError);
  EXPECT_TRUE(custom_result != NetworkDecodingError);
  EXPECT_TRUE(custom_result != TransportEncodingError);
  EXPECT_TRUE(custom_result != TransportDecodingError);
  EXPECT_FALSE(custom_result != ProtocolResult(42u));
}

ProtocolResultTest::ProtocolResultTest() = default;

ProtocolResultTest::~ProtocolResultTest() = default;
