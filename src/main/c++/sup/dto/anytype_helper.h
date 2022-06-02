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

#ifndef SUP_DTO_ANYTYPE_HELPER_H_
#define SUP_DTO_ANYTYPE_HELPER_H_

#include <sup/dto/i_any_visitor.h>

namespace sup
{
namespace dto
{
class AnyType;
class AnyTypeRegistry;

/**
 * @brief Serialize an AnyType using the given generic serializer.
 *
 * @param anytype AnyType object to serialize.
 * @param serializer Serializer object to use.
 */
void SerializeAnyType(const AnyType& anytype, IAnyVisitor<const AnyType>& serializer);

/**
 * @brief Serialize an AnyType to a JSON string.
 *
 * @param anytype AnyType object to serialize.
 * @param pretty Use pretty printing.
 *
 * @return JSON string if successfull, empty otherwise.
 */
std::string AnyTypeToJSONString(const AnyType& anytype, bool pretty=false);

/**
 * @brief Serialize an AnyType to a JSON file.
 *
 * @param anytype AnyType object to serialize.
 * @param filename Filename to use.
 * @param pretty Use pretty printing.
 *
 * @throws SerializeException Thrown when the JSON representation of the AnyType could not be
 * written to the file with given filename.
 */
void AnyTypeToJSONFile(const AnyType& anytype, const std::string& filename, bool pretty=false);

/**
 * @brief Parse an AnyType from a JSON string.
 *
 * @param json_str JSON string.
 *
 * @return Parsed AnyType.
 *
 * @throws ParseException Thrown when the JSON string could not be properly parsed into an AnyType.
 */
AnyType AnyTypeFromJSONString(const std::string& json_str);

/**
 * @brief Parse an AnyType from a JSON string.
 *
 * @param json_str JSON string.
 * @param anytype_registry AnyType registry to use during parsing.
 *
 * @return Parsed AnyType.
 *
 * @throws ParseException Thrown when the JSON string could not be properly parsed into an AnyType.
 */
AnyType AnyTypeFromJSONString(const AnyTypeRegistry* anytype_registry, const std::string& json_str);

/**
 * @brief Parse an AnyType from a JSON file.
 *
 * @param filename Filename to use.
 *
 * @return Parsed AnyType.
 *
 * @throws ParseException Thrown when the JSON file could not be properly parsed into an AnyType.
 */
AnyType AnyTypeFromJSONFile(const std::string& filename);

/**
 * @brief Parse an AnyType from a JSON file.
 *
 * @param filename Filename to use.
 * @param anytype_registry AnyType registry to use during parsing.
 *
 * @return Parsed AnyType.
 *
 * @throws ParseException Thrown when the JSON file could not be properly parsed into an AnyType.
 */
AnyType AnyTypeFromJSONFile(const AnyTypeRegistry* anytype_registry, const std::string& filename);

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ANYTYPE_HELPER_H_
