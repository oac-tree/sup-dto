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
bool TryConvert(AnyValue& dest, const AnyValue& src)
{
  try
  {
    dest.ConvertFrom(src);
  }
  catch(const InvalidConversionException&)
  {
    return false;
  }
  return true;
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

}  // namespace dto

}  // namespace sup
