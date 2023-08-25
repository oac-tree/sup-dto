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

#include <vector>

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
 * @param src AnyValue object to convert from.
 *
 * @note When conversion fails, the destination is left unchanged and false is returned.
 */
bool TryConvert(AnyValue& dest, const AnyValue& src);

/**
 * @brief Try to assign an AnyValue to another AnyValue.
 *
 * @param dest AnyValue object to assign to.
 * @param src AnyValue object to assign from.
 *
 * @note When assignment or conversion fails, the destination is left unchanged and false is
 * returned.
 */
bool TryAssign(AnyValue& dest, const AnyValue& src);

/**
 * @brief Assign if destination is empty, otherwise try to convert.
 *
 * @param dest AnyValue object to assign/convert to.
 * @param src AnyValue object to assign/convert from.
 *
 * @note When assignment or conversion fails, the destination is left unchanged and false is
 * returned.
 */
bool TryAssignIfEmptyOrConvert(AnyValue& dest, const AnyValue& src);

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
 * @brief Serialize an AnyValue to a binary representation.
 *
 * @param anyvalue AnyValue object to serialize.
 *
 * @note This serialization is reversible and, unlike the C type casting support in AnyValue, it
 * supports arbitrary length strings.
 */
std::vector<uint8> AnyValueToBinary(const AnyValue& anyvalue);

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ANYVALUE_HELPER_H_
