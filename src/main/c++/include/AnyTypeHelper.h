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
 * @file AnyTypeHelper.h
 * @brief Header file for AnyType helper classes and functions.
 * @date 15/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the AnyType helper classes and functions.
 */

#ifndef _SUP_AnyTypeHelper_h_
#define _SUP_AnyTypeHelper_h_

#include "IAnySerializer.h"

namespace sup
{
namespace dto
{
class AnyType;

/**
 * @brief Serialize an AnyType using the given generic serializer.
 *
 * @param anytype AnyType object to serialize.
 * @param serializer Serializer object to use.
 */
void SerializeAnyType(const AnyType& anytype, IAnySerializer<AnyType>& serializer);

/**
 * @brief Serialize an AnyType to a JSON string.
 *
 * @param anytype AnyType object to serialize.
 * @param pretty Use pretty printing.
 * @return JSON string if successfull, empty otherwise.
 */
std::string AnyTypeToJSONString(const AnyType& anytype, bool pretty=false);

/**
 * @brief Serialize an AnyType to a JSON file.
 *
 * @param anytype AnyType object to serialize.
 * @param filename Filename to use.
 * @param pretty Use pretty printing.
 */
void AnyTypeToJSONFile(const AnyType& anytype, const std::string& filename, bool pretty=false);

/**
 * @brief Parse an AnyType from a JSON string.
 *
 * @param json_str JSON string.
 * @return Parsed AnyType.
 */
AnyType AnyTypeFromJSONString(const std::string& json_str);

/**
 * @brief Parse an AnyType from a JSON file.
 *
 * @param filename Filename to use.
 * @return Parsed AnyType.
 */
AnyType AnyTypeFromJSONFile(const std::string& filename);

}  // namespace dto

}  // namespace sup

#endif  // _SUP_AnyTypeHelper_h_
