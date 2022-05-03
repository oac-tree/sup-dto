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

#include "JSONReader.h"

#include "AnyType.h"
#include "AnyTypeBuilder.h"
#include "AnyValue.h"
#include "AnyValueBuilder.h"
#include "AnyValueExceptions.h"

#include "rapidjson/istreamwrapper.h"
#include "rapidjson/reader.h"

namespace sup
{
namespace dto
{

AnyType JSONParseAnyType(const AnyTypeRegistry* anytype_registry, std::istream& json_stream)
{
  AnyTypeBuilder builder(anytype_registry);
  rapidjson::IStreamWrapper istream(json_stream);
  rapidjson::Reader reader;

  reader.Parse(istream, builder);
  if (reader.HasParseError())
  {
    throw ParseException("Parsing AnyType from JSON failed");
  }
  return builder.MoveAnyType();
}

AnyValue JSONParseAnyValue(const AnyTypeRegistry* anytype_registry, std::istream& json_stream)
{
  AnyValueBuilder builder(anytype_registry);
  rapidjson::IStreamWrapper istream(json_stream);
  rapidjson::Reader reader;

  reader.Parse(istream, builder);
  if (reader.HasParseError())
  {
    throw ParseException("Parsing AnyValue from JSON failed");
  }
  return builder.MoveAnyValue();
}

}  // namespace dto

}  // namespace sup
