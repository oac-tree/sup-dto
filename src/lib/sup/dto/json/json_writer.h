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
 * Copyright (c) : 2010-2026 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 * SPDX-License-Identifier: MIT
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file LICENSE located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#ifndef SUP_DTO_JSON_WRITER_H_
#define SUP_DTO_JSON_WRITER_H_

#include <ostream>

namespace sup
{
namespace dto
{
class AnyType;
class AnyValue;

void JSONSerializeAnyType(std::ostream& json_stream, const AnyType& anytype, bool pretty);
void JSONSerializeAnyType(std::ostream& json_stream, const AnyType& anytype);

void JSONSerializeAnyValue(std::ostream& json_stream, const AnyValue& anyvalue, bool pretty);
void JSONSerializeAnyValue(std::ostream& json_stream, const AnyValue& anyvalue);

void JSONSerializeAnyValueValues(std::ostream& json_stream, const AnyValue& anyvalue, bool pretty);
void JSONSerializeAnyValueValues(std::ostream& json_stream, const AnyValue& anyvalue);

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_JSON_WRITER_H_
