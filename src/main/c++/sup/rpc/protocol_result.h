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
 * @details This value must be used when defining general application errors, which provide
 * convenience functions to support the Protocol implementation.
 * @sa ProtocolResult
 */
static const unsigned int GENERAL_APPLICATION_ERROR_START = 100u;

/**
 * @brief Offset that specifies the enum offset for implementation application-specific errors.
 *
 * @details This value must be used when defining RPC specific application errors, which provide
 * user-level functions that provide the Protocol inplementation.
 * @sa ProtocolResult
 */
static const unsigned int SPECIFIC_APPLICATION_ERROR_START = 1000u;

/**
 * @brief The ProtocolResult class represents the return value from an RPC operation.
 *
 * @details The return value describes whether the RPC function call (represented by the Protocol
 * interface) has succeeded or not. If the call was not successful, then the value provides
 * information on probable failure modes.
 *
 * There are three categories of possible values:
 *  - Protocol status: Applies to the lowest level of the RPC protocol.
 *  - General application errors: Applies to convenience routines that process the protocol.
 *  - Specific application errors: Applies to final implementations of the RPC protocol to provide
 *    an RPC service.
 *
 * The values in each category have fixed ranges with the following start values:
 *  - Protocol status: 0
 *  - General application errors: @c GENERAL_APPLICATION_ERROR_START
 *  - Specific application errors: @c SPECIFIC_APPLICATION_ERROR_START
 *
 * The appropriate start value must be used When defining errors for the relevant category. For
 * example, to define values for general applciation errors:
 *
 * @code{.cpp}
  namespace status
  {
  enum ApplicationErrors
  {
    EMPTY_INPUT =
        GENERAL_APPLICATION_ERROR_START,  ///< Empty input, can not extract function information.
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

extern const ProtocolResult Success;
extern const ProtocolResult NotConnected;
extern const ProtocolResult InvalidRequest;
extern const ProtocolResult ProtocolError;

}  // namespace rpc

}  // namespace sup

#endif  // _SUP_RPC_PROTOCOL_RESULT_H_
