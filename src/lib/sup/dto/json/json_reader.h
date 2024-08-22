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

#ifndef SUP_DTO_JSON_READER_H_
#define SUP_DTO_JSON_READER_H_

#include <istream>

namespace sup
{
namespace dto
{
class AnyType;
class AnyTypeRegistry;
class AnyValue;

AnyType JSONParseAnyType(const AnyTypeRegistry* anytype_registry, std::istream& json_stream);

AnyValue JSONParseAnyValue(const AnyTypeRegistry* anytype_registry, std::istream& json_stream);

AnyValue JSONParseTypedAnyValue(const AnyType& anytype, std::istream& json_stream);

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_JSON_READER_H_
