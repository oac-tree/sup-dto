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

namespace
{
using sup::dto::AnyType;
void PrintAnyTypeToStream(std::ostream& os, const AnyType& anytype, const std::string& indent);
void PrintStructTypeToStream(std::ostream& os, const AnyType& anytype, const std::string& indent);
void PrintArrayTypeToStream(std::ostream& os, const AnyType& anytype, const std::string& indent);
}  // unnamed namespace

namespace sup
{
namespace dto
{

void SerializeAnyType(const AnyType& anytype, IAnyVisitor<const AnyType>& serializer)
{
  return Visit(anytype, serializer);
}

std::string PrintAnyType(const AnyType& anytype)
{
  std::ostringstream oss;
  PrintAnyTypeToStream(oss, anytype, "");
  return oss.str();
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
  if ((representation.empty()) || (representation[0u] != ANYTYPE_TOKEN))
  {
    throw ParseException(
      "AnyTypeFromBinary(): representation does not start with correct AnyType token");
  }
  auto it = representation.cbegin() + 1;
  return ParseAnyType(it, representation.cend());
}

}  // namespace dto

}  // namespace sup

namespace
{
using sup::dto::TypeCode;

const std::string kBasicPrintIndent = "    ";

void PrintAnyTypeToStream(std::ostream& os, const AnyType& anytype, const std::string& indent)
{
  switch (anytype.GetTypeCode())
  {
  case TypeCode::Struct :
    PrintStructTypeToStream(os, anytype, indent);
    break;
  case TypeCode::Array :
    PrintArrayTypeToStream(os, anytype, indent);
    break;
  default:
    os << anytype.GetTypeName() << "\n";
    break;
  }
}

void PrintStructTypeToStream(std::ostream& os, const AnyType& anytype, const std::string& indent)
{
  os << "struct " << anytype.GetTypeName() << "\n";
  for (const auto& member_name : anytype.MemberNames())
  {
    const std::string new_indent = indent + kBasicPrintIndent;
    os << new_indent << member_name << ": ";
    PrintAnyTypeToStream(os, anytype[member_name], new_indent);
  }
}

void PrintArrayTypeToStream(std::ostream& os, const AnyType& anytype, const std::string& indent)
{
  os << "array " << anytype.GetTypeName() << "\n";
  const std::string new_indent = indent + kBasicPrintIndent;
  os << new_indent << "size: " << std::to_string(anytype.NumberOfElements()) << "\n";
  os << new_indent << "element: ";
  PrintAnyTypeToStream(os, anytype.ElementType(), new_indent);
}

}  // unnamed namespace
