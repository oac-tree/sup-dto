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

#include <sup/dto/anyvalue_helper.h>

#include <sup/dto/anytype_helper.h>

#include <sup/dto/anyvalue/subtype_copy_node.h>
#include <sup/dto/json/json_reader.h>
#include <sup/dto/json/json_writer.h>
#include <sup/dto/parse/binary_parser.h>
#include <sup/dto/parse/binary_value_parser.h>
#include <sup/dto/serialize/binary_serializer.h>
#include <sup/dto/serialize/binary_tokens.h>
#include <sup/dto/visit/visit_t.h>

#include <sup/dto/anytype_registry.h>
#include <sup/dto/anyvalue.h>

#include <deque>
#include <fstream>
#include <optional>
#include <sstream>

namespace
{
using sup::dto::AnyValue;
using sup::dto::AnyType;
void PrintAnyValueToStream(std::ostream& os, const AnyValue& anyvalue, const std::string& indent);
void PrintStructValueToStream(std::ostream& os, const AnyValue& anyvalue, const std::string& indent);
void PrintArrayValueToStream(std::ostream& os, const AnyValue& anyvalue, const std::string& indent);

struct NarrowingConvertNode
{
  AnyValue* m_dest;
  const AnyValue* m_src;
};

// Try to create a new type that has the same tree structure as the source type, but with leaf
// types from the corresponding target type. The target type is allowed to contain
// unused structure members. If at some node location, the target is not a structure, it
// will be used directly into the result, even when the corresponding source type has an
// incompatible type at this node. This simplifies the code and since it is used only to do
// conversions of AnyValues, such incompatibilities will be caught there.
std::optional<AnyType> TrySubtypeCopy(const AnyType& src_type, const AnyType& target_type);
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

std::pair<bool, AnyValue> TryConvertAllowExtraSourceFields(const AnyValue& src,
                                                           const AnyType& target_type)
{
  const std::pair<bool, AnyValue> failure{ false, {} };
  AnyValue result{target_type};
  std::deque<NarrowingConvertNode> stack{};
  stack.push_back(NarrowingConvertNode{std::addressof(result), std::addressof(src)});
  while (!stack.empty())
  {
    auto& front = stack.front();
    auto* current_dest = front.m_dest;
    auto* current_src = front.m_src;
    if (IsStructValue(*current_dest))
    {
      auto mem_names = current_dest->MemberNames();
      for (const auto& mem_name : mem_names)
      {
        if (!current_src->HasField(mem_name))
        {
          return failure;
        }
        auto* dest_mem = std::addressof((*current_dest)[mem_name]);
        auto* src_mem = std::addressof((*current_src)[mem_name]);
        stack.push_back(NarrowingConvertNode{dest_mem, src_mem});
      }
    }
    else
    {
      if (!TryConvert(*current_dest, *current_src))
      {
        return failure;
      }
    }
    stack.pop_front();
  }
  return { true, result };
}

std::pair<bool, AnyValue> TryConvertAllowExtraTargetFields(const AnyValue& src,
                                                           const AnyType& target_type)
{
  std::pair<bool, AnyValue> failure{ false, {} };
  auto required_type = TrySubtypeCopy(src.GetType(), target_type);
  if (!required_type)
  {
    return failure;
  }
  AnyValue result{required_type.value()};
  if (!TryConvert(result, src))
  {
    return failure;
  }
  return { true, result };
}

void SerializeAnyValue(const AnyValue& anyvalue, IAnyVisitor<const AnyValue>& serializer)
{
  Visit(anyvalue, serializer);
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
  ValuesToJSONFile(anyvalue, filename, false);
}

void AnyValueToJSONFile(const AnyValue& anyvalue, const std::string& filename, bool pretty)
{
  std::ofstream ofs(filename);
  if (!ofs.is_open())
  {
    throw SerializeException("AnyValueToJSONFile could not open the file for writing");
  }
  JSONSerializeAnyValue(ofs, anyvalue, pretty);
}

void AnyValueToJSONFile(const AnyValue& anyvalue, const std::string& filename)
{
  AnyValueToJSONFile(anyvalue, filename, false);
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
using namespace sup::dto;

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
  const auto n_elements = anyvalue.NumberOfElements();
  for (std::size_t i = 0u; i < n_elements; ++i)
  {
    os << new_indent << std::to_string(i) << ": ";
    PrintAnyValueToStream(os, anyvalue[i], new_indent);
  }
}

std::optional<AnyType> TrySubtypeCopy(const AnyType& src_type, const AnyType& target_type)
{
  std::deque<SubtypeCopyNode> stack{};
  (void)stack.emplace_back(std::addressof(src_type), std::addressof(target_type));
  while (true)
  {
    auto& top = stack.back();
    if (top.HasNextChild())
    {
      auto next_child_node = top.GetNextChildNode();
      if (!next_child_node)
      {
        return {};
      }
      stack.push_back(std::move(next_child_node.value()));
    }
    else
    {
      auto current_node = std::move(top);
      stack.pop_back();
      if (!stack.empty())
      {
        stack.back().AddChildNode(current_node);
      }
      else
      {
        return current_node.MoveResult();
      }
    }
  }
}
}  // unnamed namespace
