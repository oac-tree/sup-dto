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
 * Copyright (c) : 2010-2025 ITER Organization,
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

#include <sup/dto/anyvalue_helper.h>

#include <sup/dto/anytype_helper.h>

#include <sup/dto/json/json_reader.h>
#include <sup/dto/json/json_writer.h>
#include <sup/dto/parse/binary_parser.h>
#include <sup/dto/parse/binary_value_parser.h>
#include <sup/dto/serialize/binary_serializer.h>
#include <sup/dto/serialize/binary_tokens.h>
#include <sup/dto/visit/visit_t.h>

#include <sup/dto/anytype_registry.h>
#include <sup/dto/anyvalue.h>

#include <fstream>
#include <sstream>

namespace
{
using sup::dto::AnyValue;
void PrintAnyValueToStream(std::ostream& os, const AnyValue& anyvalue, const std::string& indent);
void PrintStructValueToStream(std::ostream& os, const AnyValue& anyvalue, const std::string& indent);
void PrintArrayValueToStream(std::ostream& os, const AnyValue& anyvalue, const std::string& indent);
}  // unnamed namespace

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
  catch(const MessageException&)
  {
    return false;
  }
  return true;
}

bool TryAssign(AnyValue& dest, const AnyValue& src)
{
  try
  {
    dest = src;
  }
  catch(const MessageException&)
  {
    return false;
  }
  return true;
}

bool TryAssignIfEmptyOrConvert(AnyValue& dest, const AnyValue& src)
{
  try
  {
    if (IsEmptyValue(dest))
    {
      dest = src;
    }
    else
    {
      dest.ConvertFrom(src);
    }
  }
  catch(const MessageException&)
  {
    return false;
  }
  return true;
}

void SerializeAnyValue(const AnyValue& anyvalue, IAnyVisitor<const AnyValue>& serializer)
{
  return Visit(anyvalue, serializer);
}

std::string PrintAnyValue(const AnyValue& anyvalue)
{
  std::ostringstream oss;
  PrintAnyValueToStream(oss, anyvalue, "");
  return oss.str();
}

std::string ValuesToJSONString(const AnyValue& anyvalue, bool pretty)
{
  std::ostringstream oss;
  JSONSerializeAnyValueValues(oss, anyvalue, pretty);
  return oss.str();
}

std::string ValuesToJSONString(const AnyValue& anyvalue)
{
  return ValuesToJSONString(anyvalue, false);
}

std::string AnyValueToJSONString(const AnyValue& anyvalue, bool pretty)
{
  std::ostringstream oss;
  JSONSerializeAnyValue(oss, anyvalue, pretty);
  return oss.str();
}

std::string AnyValueToJSONString(const AnyValue& anyvalue)
{
  return AnyValueToJSONString(anyvalue, false);
}

void ValuesToJSONFile(const AnyValue& anyvalue, const std::string& filename, bool pretty)
{
  std::ofstream ofs(filename);
  if (!ofs.is_open())
  {
    throw SerializeException("ValuesToJSONFile could not open the file for writing");
  }
  JSONSerializeAnyValueValues(ofs, anyvalue, pretty);
}

void ValuesToJSONFile(const AnyValue& anyvalue, const std::string& filename)
{
  return ValuesToJSONFile(anyvalue, filename, false);
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

void AnyValueToJSONFile(const AnyValue& anyvalue, const std::string& filename)
{
  return AnyValueToJSONFile(anyvalue, filename, false);
}

std::vector<uint8> AnyValueToBinary(const AnyValue& anyvalue)
{
  std::vector<uint8> result;
  result.push_back(ANYTYPE_TOKEN);
  BinaryTypeSerializer type_serializer{result};
  SerializeAnyType(anyvalue.GetType(), type_serializer);
  result.push_back(ANYVALUE_TOKEN);
  BinaryValueSerializer value_serializer{result};
  SerializeAnyValue(anyvalue, value_serializer);
  return result;
}

AnyValue AnyValueFromBinary(const std::vector<uint8>& representation)
{
  if ((representation.empty()) || (representation[0u] != ANYTYPE_TOKEN))
  {
    throw ParseException(
      "AnyValueFromBinary(): type representation does not start with correct token");
  }
  auto iter = representation.cbegin() + 1;
  auto end_iter = representation.cend();
  auto anytype = ParseAnyType(iter, end_iter);
  if ((iter == end_iter) || (*iter != ANYVALUE_TOKEN))
  {
    throw ParseException(
      "AnyValueFromBinary(): value representation does not start with correct token");
  }
  iter++;
  BinaryValueParser parser{iter, end_iter};
  AnyValue result{anytype};
  Visit(result, parser);
  if (!parser.IsFinished())
  {
    throw ParseException("AnyValueFromBinary(): ended before parsing all input bytes");
  }
  return result;
}

}  // namespace dto

}  // namespace sup

namespace
{
using sup::dto::TypeCode;
using sup::dto::ValuesToJSONString;

const std::string kBasicPrintIndent = "    ";

void PrintAnyValueToStream(std::ostream& os, const AnyValue& anyvalue, const std::string& indent)
{
  switch (anyvalue.GetTypeCode())
  {
  case TypeCode::Struct :
    PrintStructValueToStream(os, anyvalue, indent);
    break;
  case TypeCode::Array :
    PrintArrayValueToStream(os, anyvalue, indent);
    break;
  default:
    os << anyvalue.GetTypeName() << " " << ValuesToJSONString(anyvalue) << "\n";
    break;
  }
}

void PrintStructValueToStream(std::ostream& os, const AnyValue& anyvalue, const std::string& indent)
{
  os << "struct " << anyvalue.GetTypeName() << "\n";
  for (const auto& member_name : anyvalue.MemberNames())
  {
    const std::string new_indent = indent + kBasicPrintIndent;
    os << new_indent << member_name << ": ";
    PrintAnyValueToStream(os, anyvalue[member_name], new_indent);
  }
}

void PrintArrayValueToStream(std::ostream& os, const AnyValue& anyvalue, const std::string& indent)
{
  os << "array " << anyvalue.GetTypeName() << "\n";
  const std::string new_indent = indent + kBasicPrintIndent;
  for (std::size_t i = 0u; i < anyvalue.NumberOfElements(); ++i)
  {
    os << new_indent << std::to_string(i) << ": ";
    PrintAnyValueToStream(os, anyvalue[i], new_indent);
  }
}

}  // unnamed namespace
