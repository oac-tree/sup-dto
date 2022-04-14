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

#ifndef _SUP_AnyValueHelper_h_
#define _SUP_AnyValueHelper_h_

#include "IAnyVisitor.h"
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
void SerializeAnyValue(const AnyValue& anyvalue, IAnyVisitor<const AnyValue>& serializer);

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
 * @brief Serialize an AnyValue to a JSON string.
 *
 * @param anyvalue AnyValue object to serialize.
 * @param pretty Use pretty printing.
 * @return JSON string if successfull, empty otherwise.
 *
 * @note This serialization is meant to be reversible. The JSON string will contain both type
 * information as specific values of leaf nodes.
 */
std::string AnyValueToJSONString(const AnyValue& anyvalue, bool pretty=false);

/**
 * @brief Serialize an AnyValue to a JSON file.
 *
 * @param anyvalue AnyValue object to serialize.
 * @param filename Filename to use.
 * @param pretty Use pretty printing.
 *
 * @note This serialization is meant to be reversible. The JSON file will contain both type
 * information as specific values of leaf nodes.
 */
void AnyValueToJSONFile(const AnyValue& anyvalue, const std::string& filename, bool pretty=false);

/**
 * @brief Parse AnyValue content from an array of bytes.
 *
 * @param anyvalue AnyValue object to assign to.
 * @param bytes Array of bytes.
 * @param total_size Size of the array of bytes.
 *
 * @throws ParseException Thrown when the byte array cannot be correctly parsed (e.g. sizes
 * don't match, absence of null terminator in C-style string or unknown scalar type).
 *
 * @note This method is used to cast from C-type structures.
 */
void FromBytes(AnyValue& anyvalue, const uint8* bytes, std::size_t total_size);

/**
 * @brief Parse an AnyValue from a JSON string.
 *
 * @param json_str JSON string.
 * @return Parsed AnyValue.
 */
AnyValue AnyValueFromJSONString(const std::string& json_str);

/**
 * @brief Parse an AnyValue from a JSON file.
 *
 * @param filename Filename to use.
 * @return Parsed AnyValue.
 */
AnyValue AnyValueFromJSONFile(const std::string& filename);

}  // namespace dto

}  // namespace sup

#endif  // _SUP_AnyValueHelper_h_
