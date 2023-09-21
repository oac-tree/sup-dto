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
 * Copyright (c) : 2010-2023 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include <sup/dto/anytype_helper.h>

#include <sup/dto/anytype_registry.h>
#include <sup/dto/json/json_reader.h>
#include <sup/dto/json/json_writer.h>
#include <sup/dto/parse/binary_parser.h>
#include <sup/dto/serialize/binary_serializer.h>
#include <sup/dto/serialize/binary_tokens.h>
#include <sup/dto/visit/visit_t.h>
#include <sup/dto/anytype.h>

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

std::string AnyTypeToJSONString(const AnyType& anytype)
{
  return AnyTypeToJSONString(anytype, false);
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

void AnyTypeToJSONFile(const AnyType& anytype, const std::string& filename)
{
  return AnyTypeToJSONFile(anytype, filename, false);
}

std::vector<uint8> AnyTypeToBinary(const AnyType& anytype)
{
  std::vector<uint8> result;
  result.push_back(ANYTYPE_TOKEN);
  BinaryTypeSerializer serializer{result};
  SerializeAnyType(anytype, serializer);
  return result;
}

AnyType AnyTypeFromBinary(const std::vector<uint8>& representation)
{
  if (representation.empty() || representation[0u] != ANYTYPE_TOKEN)
  {
    throw ParseException(
      "AnyTypeFromBinary(): representation does not start with correct AnyType token");
  }
  auto it = representation.cbegin() + 1;
  return ParseAnyType(it, representation.cend());
}

}  // namespace dto

}  // namespace sup
