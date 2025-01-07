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
 * Copyright (c) : 2010-2025 ITER Organization,
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

#include <sup/dto/basic_scalar_types.h>
#include <sup/dto/i_any_visitor.h>

#include <vector>

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
 * @brief Serialize an AnyType to a string for printing.
 *
 * @param anytype AnyType object to serialize.
 *
 * @return String representation of AnyType for printing.
 */
std::string PrintAnyType(const AnyType& anytype);

/**
 * @brief Serialize an AnyType to a JSON string.
 *
 * @param anytype AnyType object to serialize.
 * @param pretty Use pretty printing.
 *
 * @return JSON string if successfull, empty otherwise.
 */
std::string AnyTypeToJSONString(const AnyType& anytype, bool pretty);

/**
 * @brief Serialize an AnyType to a JSON string (default without pretty printing).
 *
 * @param anytype AnyType object to serialize.
 *
 * @return JSON string if successfull, empty otherwise.
 */
std::string AnyTypeToJSONString(const AnyType& anytype);

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
void AnyTypeToJSONFile(const AnyType& anytype, const std::string& filename, bool pretty);

/**
 * @brief Serialize an AnyType to a JSON file (default without pretty printing).
 *
 * @param anytype AnyType object to serialize.
 * @param filename Filename to use.
 *
 * @throws SerializeException Thrown when the JSON representation of the AnyType could not be
 * written to the file with given filename.
 */
void AnyTypeToJSONFile(const AnyType& anytype, const std::string& filename);

/**
 * @brief Serialize an AnyType to a binary representation.
 *
 * @param anytype AnyType object to serialize.
 *
 * @return Binary representation of the anytype.
 */
std::vector<uint8> AnyTypeToBinary(const AnyType& anytype);

/**
 * @brief Parse an AnyType from a binary representation.
 *
 * @param representation Binary representation of an AnyType object.
 */
AnyType AnyTypeFromBinary(const std::vector<uint8>& representation);

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ANYTYPE_HELPER_H_
