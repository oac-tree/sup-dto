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

#include "AnyValueHelper.h"
#include "AnyValue.h"
#include "ByteSerializer.h"
#include "JSONReader.h"
#include "JSONWriter.h"
#include "SerializeT.h"

#include <fstream>
#include <sstream>

namespace sup
{
namespace dto
{

void SerializeAnyValue(const AnyValue& anyvalue, IAnySerializer<AnyValue>& serializer)
{
  return Serialize(anyvalue, serializer);
}

std::vector<uint8> ToBytes(const AnyValue& anyvalue)
{
  ByteSerializer serializer;
  Serialize(anyvalue, serializer);
  return serializer.GetRepresentation();
}

std::string ValuesToJSONString(const AnyValue& anyvalue, bool pretty)
{
  std::ostringstream oss;
  JSONSerializeAnyValueValues(oss, anyvalue, pretty);
  return oss.str();
}

std::string AnyValueToJSONString(const AnyValue& anyvalue, bool pretty)
{
  std::ostringstream oss;
  JSONSerializeAnyValue(oss, anyvalue, pretty);
  return oss.str();
}

void AnyValueToJSONFile(const AnyValue& anyvalue, const std::string& filename, bool pretty)
{
  std::ofstream ofs(filename);
  if (!ofs.is_open())
  {
    throw SerializeException("AnyValueToJSONFile could not open the file for writing");
  }
  JSONSerializeAnyValue(ofs, anyvalue, pretty);
  return;
}

AnyValue AnyValueFromJSONString(const std::string& json_str)
{
  std::istringstream iss(json_str);
  return JSONParseAnyValue(iss);
}

AnyValue AnyValueFromJSONFile(const std::string& filename)
{
  std::ifstream ifs(filename);
  if (!ifs.is_open())
  {
    throw ParseException("AnyValueFromJSONFile could not open the file for reading");
  }
  return JSONParseAnyValue(ifs);
}

}  // namespace dto

}  // namespace sup
