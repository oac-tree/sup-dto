/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : SUP - DTO
 *
 * Description   : Data transfer objects for SUP
 *
 * Author        : Kevin Meyer
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

#ifndef _SUP_RPC_PROTOCOL_RESULT_H_
#define _SUP_RPC_PROTOCOL_RESULT_H_

#include <string>

namespace sup
{
namespace rpc
{

/**
 * @brief Start value for the general application errors.
 *
 * @details This is the start value for error codes defined by generic frameworks that link
 * generic interfaces with the Protocol.
 * @sa ProtocolResult
 */
static const unsigned int GENERIC_APPLICATION_ERROR_START = 100u;

/**
 * @brief Start value for application-specific errors.
 *
 * @sa ProtocolResult
 */
static const unsigned int SPECIFIC_APPLICATION_ERROR_START = 1000u;

/**
 * @brief The ProtocolResult class represents the return value from a Protocol operation.
 *
 * @details The return value describes whether the function call (represented by the Protocol
 * interface) has succeeded or not. If the call was not successful, then the value provides
 * information on probable failure modes.
 *
 * There are three categories of possible values:
 *  - Network and transport layer status: Applies to the lowest levels of the communication stack.
 *  - Generic application errors: Applies to generic frameworks that process the protocol.
 *  - Specific application errors: Applies to application-specific issues with the protocol.
 *
 * The values in each category have fixed ranges with the following start values:
 *  - Network and transport layer status: 0
 *  - Generic application errors: @c GENERIC_APPLICATION_ERROR_START
 *  - Specific application errors: @c SPECIFIC_APPLICATION_ERROR_START
 *
 * The appropriate start value must be used When defining errors for the relevant category. For
 * example, to define values for general application errors:
 *
 * @code{.cpp}
  namespace status
  {
  enum ApplicationErrors
  {
    EMPTY_INPUT =
        GENERIC_APPLICATION_ERROR_START,  ///< Empty input, can not extract function information.
    UNKNOWN_FUNCTION,                     ///< The requested function does not exist.
    BAD_REGISTRATION,                     ///< Problem with the RegisteredFunction parameters.
    ASSIGNMENT_ERROR,                     ///< Unable to assign output value.
  };
  }
 * @endcode
 *
 */
class ProtocolResult
{
protected:
  unsigned int m_value;

public:
  /**
   * @brief Default constructor implies success.
   */
  ProtocolResult();

  ~ProtocolResult();

  /**
   * @brief Construct a new ProtocolResult object for ApplicationSpecific results.
   */
  ProtocolResult(unsigned int value);

  /**
   * @brief Copy construction and assigment.
   */
  ProtocolResult(const ProtocolResult& other);
  ProtocolResult& operator=(const ProtocolResult& other);

  /**
   * @brief Get status as integer.
   *
   * @return Application Specific error result as integer.
   */
  unsigned int GetValue() const;

  /**
   * @brief Comparison operators.
   */
  bool operator==(const ProtocolResult& other) const;
  bool operator!=(const ProtocolResult& other) const;
};

/**
 * @brief Return a string representation of the ProtocolResult.
 *
 * @param result enumeration input.
 * @return std::string output.
 */
std::string ProtocolResultToString(const ProtocolResult& result);

/**
 * @brief Result returned for a successful call.
*/
extern const ProtocolResult Success;
/**
 * @brief Result returned when the network layer cannot properly exchange messages betweem
 * client and server.
*/
extern const ProtocolResult NotConnected;
/**
 * @brief Error when the network layer cannot encode the transport packet into a network packet.
 *
 * Example: the format of the AnyValue, representing a transport packet, is not supported for
 * translation into a pvxs::Value (network packet). This happens when some allowed AnyValue types
 * are not supported in the underlying network implementation, such as arrays of structures.
*/
extern const ProtocolResult NetworkEncodingError;
/**
 * @brief Error when the network layer cannot decode the network packet into a transport packet.
 *
 * Example: the received pvxs::Value (network packet) cannot be converted to an AnyValue. Note that
 * with the current implementation, this never happens.
*/
extern const ProtocolResult NetworkDecodingError;
/**
 * @brief Error when the transport layer cannot encode the Protocol input or result/output into
 * a transport packet.
 *
 * @note This only happens when the Protocol input value is empty. All other values are trivially
 * supported.
*/
extern const ProtocolResult TransportEncodingError;
/**
 * @brief Error when the transport layer cannot extract the Protocol input or result/output from the
 * transport packet.
 *
 * @note This signals a malformed transport message (request or reply).
*/
extern const ProtocolResult TransportDecodingError;

}  // namespace rpc

}  // namespace sup

#endif  // _SUP_RPC_PROTOCOL_RESULT_H_
