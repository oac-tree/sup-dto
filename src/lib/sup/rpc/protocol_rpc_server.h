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

#ifndef SUP_RPC_PROTOCOL_RPC_SERVER_H_
#define SUP_RPC_PROTOCOL_RPC_SERVER_H_

#include <sup/dto/any_functor.h>
#include <sup/dto/basic_scalar_types.h>
#include <sup/rpc/protocol.h>

#include <memory>

namespace sup
{
namespace rpc
{
// Function declaration
/**
 * @brief The ProtocolRPCServer is an AnyFunctor implementation that forwards to a Protocol.
 *
 * @details The ProtocolRPCServer is intended to be used as a mediator between an RPC server
 * and a Protocol implementation.
 *
 * The input structure needs to conform to an RPC request structure and it returns an RPC reply
 * structure (see protocol_rpc.h).
 */
class ProtocolRPCServer : public dto::AnyFunctor
{
public:
  ProtocolRPCServer(std::unique_ptr<Protocol>&& protocol);
  ~ProtocolRPCServer();

  sup::dto::AnyValue operator()(const sup::dto::AnyValue& request) override;
private:
  sup::dto::AnyValue HandleServiceRequest(const sup::dto::AnyValue& request);
  std::unique_ptr<Protocol> m_protocol;
};

}  // namespace rpc

}  // namespace sup

#endif  // SUP_RPC_PROTOCOL_RPC_SERVER_H_
