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

#include "AnyTypeHelper.h"
#include "AnyType.h"
#include "SerializeT.h"
#include "Serializer.h"
#include "JSONWriter.h"

#include "rapidjson/stringbuffer.h"

namespace sup
{
namespace dto
{

void SerializeAnyType(const AnyType& anytype, IAnySerializer<AnyType>& serializer)
{
  return Serialize(anytype, serializer);
}

std::string ToJSONString(const AnyType& anytype)
{
  rapidjson::StringBuffer buffer;
  JSONStringWriter writer(buffer);
  Serializer serializer;
  serializer.SerializeAnyType(anytype, &writer);
  return buffer.GetString();
}

}  // namespace dto

}  // namespace sup
