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

#ifndef SUP_DTO_ANYVALUE_HELPER_H_
#define SUP_DTO_ANYVALUE_HELPER_H_

#include <sup/dto/i_any_visitor.h>
#include <sup/dto/basic_scalar_types.h>

namespace sup
{
namespace dto
{
class AnyValue;
class AnyTypeRegistry;

/**
 * @brief Try to convert an AnyValue to another AnyValue.
 *
 * @param dest AnyValue object to assign to.
 * @param src AnyValue object to assign from.
 *
 * @note When conversion fails, the destination is left unchanged and false is returned.
 */
bool TryConvert(AnyValue& dest, const AnyValue& src);

/**
 * @brief Serialize an AnyValue using the given generic serializer.
 *
 * @param anyvalue AnyValue object to serialize.
 * @param serializer Serializer object to use.
 */
void SerializeAnyValue(const AnyValue& anyvalue, IAnyVisitor<const AnyValue>& serializer);

/**
 * @brief Serialize the values of an AnyValue using a JSON serializer.
 *
 * @param anyvalue AnyValue object to serialize.
 * @param pretty Use pretty printing.
 *
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
 *
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
 * @throws SerializeException Thrown when the JSON representation of the AnyValue could not be
 * written to the file with given filename.
 *
 * @note This serialization is meant to be reversible. The JSON file will contain both type
 * information as specific values of leaf nodes.
 */
void AnyValueToJSONFile(const AnyValue& anyvalue, const std::string& filename, bool pretty=false);

/**
 * @brief Parse an AnyValue from a JSON string.
 *
 * @param json_str JSON string.
 *
 * @return Parsed AnyValue.
 *
 * @throws ParseException Thrown when the JSON string cannot be correctly parsed into an AnyValue.
 */
AnyValue AnyValueFromJSONString(const std::string& json_str);

/**
 * @brief Parse an AnyValue from a JSON string.
 *
 * @param json_str JSON string.
 * @param anytype_registry AnyType registry to use during parsing.
 *
 * @return Parsed AnyValue.
 *
 * @throws ParseException Thrown when the JSON string cannot be correctly parsed into an AnyValue.
 */
AnyValue AnyValueFromJSONString(const AnyTypeRegistry* anytype_registry,
                                const std::string& json_str);

/**
 * @brief Parse an AnyValue from a JSON file.
 *
 * @param filename Filename to use.
 *
 * @return Parsed AnyValue.
 *
 * @throws ParseException Thrown when the JSON file cannot be correctly parsed into an AnyValue.
 */
AnyValue AnyValueFromJSONFile(const std::string& filename);

/**
 * @brief Parse an AnyValue from a JSON file.
 *
 * @param filename Filename to use.
 * @param anytype_registry AnyType registry to use during parsing.
 *
 * @return Parsed AnyValue.
 *
 * @throws ParseException Thrown when the JSON file cannot be correctly parsed into an AnyValue.
 */
AnyValue AnyValueFromJSONFile(const AnyTypeRegistry* anytype_registry, const std::string& filename);

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ANYVALUE_HELPER_H_
