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

#ifndef _SUP_RPC_PROTOCOL_RPC_CLIENT_H_
#define _SUP_RPC_PROTOCOL_RPC_CLIENT_H_

#include <sup/dto/any_functor.h>
#include <sup/rpc/protocol.h>

#include <memory>

namespace sup
{
namespace rpc
{
// Function declaration
/**
 * @brief The ProtocolRPCClient is a Protocol implementation that forwards to an AnyFunctor.
 *
 * @details The ProtocolRPCClient is intended to be used as a mediator between the Protocol
 * and a concrete RPC client class that derives from AnyFunctor.
 *
 * It forwards the input as a payload of an RPC request into the AnyFunctor and extracts the
 * payload from the RPC reply (see protocol_rpc.h).
 */
class ProtocolRPCClient : public Protocol
{
public:
  ProtocolRPCClient(std::unique_ptr<dto::AnyFunctor>&& any_functor);
  ~ProtocolRPCClient();

  ProtocolResult Invoke(const sup::dto::AnyValue& input, sup::dto::AnyValue& output) override;
private:
  std::unique_ptr<dto::AnyFunctor> m_any_functor;
};

}  // namespace rpc

}  // namespace sup

#endif  // _SUP_RPC_PROTOCOL_RPC_CLIENT_H_
