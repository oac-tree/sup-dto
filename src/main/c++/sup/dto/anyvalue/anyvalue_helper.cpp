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

#include <sup/dto/anyvalue_helper.h>

#include <sup/dto/json/json_reader.h>
#include <sup/dto/json/json_writer.h>
#include <sup/dto/visit/visit_t.h>

#include <sup/dto/anytype_registry.h>
#include <sup/dto/anyvalue.h>

#include <fstream>
#include <sstream>

namespace sup
{
namespace dto
{
bool SafeAssign(AnyValue& dest, const AnyValue& src, bool strict)
{
  try
  {
    if (strict)
    {
      if (!IsEmptyValue(dest) && dest.GetType() != src.GetType())
      {
        return false;
      }
    }
    dest = src;
  }
  catch(const InvalidConversionException&)
  {
    return false;
  }
  return true;
}

bool SafeAssignFields(AnyValue& dest, const std::string& dest_field,
                      const AnyValue& src, const std::string& src_field, bool strict)
{
  try
  {
    AnyValue& dest_ref = dest_field.empty() ? dest : dest[dest_field];
    const AnyValue& src_ref = src_field.empty() ? src : src[src_field];
    return SafeAssign(dest_ref, src_ref, strict);
  }
  catch(const InvalidOperationException&)
  {
    return false;
  }
}

void SerializeAnyValue(const AnyValue& anyvalue, IAnyVisitor<const AnyValue>& serializer)
{
  return Visit(anyvalue, serializer);
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
  AnyTypeRegistry anytype_registry;
  return AnyValueFromJSONString(&anytype_registry, json_str);
}

AnyValue AnyValueFromJSONString(const AnyTypeRegistry* anytype_registry,
                                const std::string& json_str)
{
  std::istringstream iss(json_str);
  return JSONParseAnyValue(anytype_registry, iss);
}

AnyValue AnyValueFromJSONFile(const std::string& filename)
{
  AnyTypeRegistry anytype_registry;
  return AnyValueFromJSONFile(&anytype_registry, filename);
}

AnyValue AnyValueFromJSONFile(const AnyTypeRegistry* anytype_registry, const std::string& filename)
{
  std::ifstream ifs(filename);
  if (!ifs.is_open())
  {
    throw ParseException("AnyValueFromJSONFile could not open the file for reading");
  }
  return JSONParseAnyValue(anytype_registry, ifs);
}

}  // namespace dto

}  // namespace sup
