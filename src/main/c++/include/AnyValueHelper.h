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

/**
 * @file AnyValueHelper.h
 * @brief Header file for AnyValue helper classes and functions.
 * @date 17/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the AnyValue helper classes and functions.
 */

#ifndef _SUP_AnyValueHelper_h_
#define _SUP_AnyValueHelper_h_

#include "IAnySerializer.h"
#include "BasicScalarTypes.h"

#include <vector>

namespace sup
{
namespace dto
{
class AnyValue;

/**
 * @brief Serialize an AnyValue using the given generic serializer.
 *
 * @param anyvalue AnyValue object to serialize.
 * @param serializer Serializer object to use.
 */
void SerializeAnyValue(const AnyValue& anyvalue, IAnySerializer<AnyValue>& serializer);

/**
 * @brief Serialize an AnyValue to an array of bytes.
 *
 * @param anyvalue AnyValue object to serialize.
 *
 * @note This serialization is used to cast to C-type structures.
 */
std::vector<uint8> ToBytes(const AnyValue& anyvalue);

/**
 * @brief Serialize the values of an AnyValue using a JSON serializer.
 *
 * @param anyvalue AnyValue object to serialize.
 * @param pretty Use pretty printing.
 * @return JSON string if successfull, empty otherwise.
 *
 * @note This serialization only contains a map of the values and is insufficient to reconstruct the
 * exact AnyValue back. Reversible serialization also requires the type (see ToJSONString function).
 */
std::string ValuesToJSONString(const AnyValue& anyvalue, bool pretty=false);

/**
 * @brief Serialize an AnyValue using a JSON serializer.
 *
 * @param anyvalue AnyValue object to serialize.
 * @param pretty Use pretty printing.
 * @return JSON string if successfull, empty otherwise.
 *
 * @note This serialization is meant to be reversible. The JSON string will contain both type
 * information as specific values of leaf nodes.
 */
std::string ToJSONString(const AnyValue& anyvalue, bool pretty=false);

/**
 * @brief Parse an AnyValue from a string using a JSON parser.
 *
 * @param json_str JSON string.
 * @return Parsed AnyValue.
 */
AnyValue AnyValueFromJSONString(const std::string& json_str);

}  // namespace dto

}  // namespace sup

#endif  // _SUP_AnyValueHelper_h_
