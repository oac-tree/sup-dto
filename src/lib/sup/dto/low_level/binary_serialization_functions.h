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
 * Copyright (c) : 2010-2024 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#ifndef SUP_DTO_BINARY_SERIALIZATION_FUNCTIONS_H_
#define SUP_DTO_BINARY_SERIALIZATION_FUNCTIONS_H_

#include <sup/dto/anytype.h>
#include <sup/dto/basic_scalar_types.h>

#include <string>
#include <vector>

namespace sup
{
namespace dto
{
class AnyValue;

void AppendScalarToken(std::vector<sup::dto::uint8>& representation, const TypeCode& type_code);

void AppendSize(std::vector<sup::dto::uint8>& representation, sup::dto::uint64 size);

void AppendBinaryScalar(std::vector<sup::dto::uint8>& representation, const AnyValue& anyvalue);

void AppendBinaryString(std::vector<sup::dto::uint8>& representation, const std::string& str);

void AppendBinaryStringValue(std::vector<sup::dto::uint8>& representation, const std::string& str);

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_BINARY_SERIALIZATION_FUNCTIONS_H_
