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

#include "sup/dto/anytype_helper.h"
#include "sup/dto/anytype.h"
#include "sup/dto/anytype_registry.h"
#include "JSONReader.h"
#include "JSONWriter.h"
#include "VisitT.h"

#include <fstream>
#include <sstream>

namespace sup
{
namespace dto
{

void SerializeAnyType(const AnyType& anytype, IAnyVisitor<const AnyType>& serializer)
{
  return Visit(anytype, serializer);
}

std::string AnyTypeToJSONString(const AnyType& anytype, bool pretty)
{
  std::ostringstream oss;
  JSONSerializeAnyType(oss, anytype, pretty);
  return oss.str();
}

void AnyTypeToJSONFile(const AnyType& anytype, const std::string& filename, bool pretty)
{
  std::ofstream ofs(filename);
  if (!ofs.is_open())
  {
    throw SerializeException("AnyTypeToJSONFile could not open the file for writing");
  }
  JSONSerializeAnyType(ofs, anytype, pretty);
  return;
}

AnyType AnyTypeFromJSONString(const std::string& json_str)
{
  AnyTypeRegistry anytype_registry;
  return AnyTypeFromJSONString(&anytype_registry, json_str);
}

AnyType AnyTypeFromJSONString(const AnyTypeRegistry* anytype_registry, const std::string& json_str)
{
  std::istringstream iss(json_str);
  return JSONParseAnyType(anytype_registry, iss);
}

AnyType AnyTypeFromJSONFile(const std::string& filename)
{
  AnyTypeRegistry anytype_registry;
  return AnyTypeFromJSONFile(&anytype_registry, filename);
}

AnyType AnyTypeFromJSONFile(const AnyTypeRegistry* anytype_registry, const std::string& filename)
{
  std::ifstream ifs(filename);
  if (!ifs.is_open())
  {
    throw ParseException("AnyTypeFromJSONFile could not open the file for reading");
  }
  return JSONParseAnyType(anytype_registry, ifs);
}

}  // namespace dto

}  // namespace sup
