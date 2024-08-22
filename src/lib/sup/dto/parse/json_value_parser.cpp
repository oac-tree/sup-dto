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
 * Copyright (c) : 2010-2024 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include <sup/dto/json_value_parser.h>

#include <sup/dto/anytype_registry.h>
#include <sup/dto/anyvalue_exceptions.h>
#include <sup/dto/json/json_reader.h>
#include <sup/dto/anyvalue.h>

#include <fstream>
#include <sstream>

namespace sup
{
namespace dto
{

JSONAnyValueParser::JSONAnyValueParser()
  : m_anyvalue{}
{}

JSONAnyValueParser::~JSONAnyValueParser() = default;

bool JSONAnyValueParser::ParseString(const std::string& json_str,
                                     const AnyTypeRegistry* type_registry)
{
  try
  {
    std::istringstream iss(json_str);
    const AnyTypeRegistry empty_registry;
    const auto registry = (type_registry == nullptr) ? &empty_registry : type_registry;
    m_anyvalue = JSONParseAnyValue(registry, iss);
  }
  catch(const MessageException&)
  {
    return false;
  }
  return true;
}

bool JSONAnyValueParser::ParseString(const std::string& json_str)
{
  return ParseString(json_str, nullptr);
}

bool JSONAnyValueParser::ParseFile(const std::string& filename,
                                   const AnyTypeRegistry* type_registry)
{
  std::ifstream ifs(filename);
  if (!ifs.is_open())
  {
    return false;
  }
  try
  {
    const AnyTypeRegistry empty_registry;
    const auto registry = (type_registry == nullptr) ? &empty_registry : type_registry;
    m_anyvalue = JSONParseAnyValue(registry, ifs);
  }
  catch(const MessageException&)
  {
    return false;
  }
  return true;
}

bool JSONAnyValueParser::ParseFile(const std::string& filename)
{
  return ParseFile(filename, nullptr);
}

bool JSONAnyValueParser::TypedParseString(const AnyType& anytype, const std::string& json_str)
{
  std::istringstream iss(json_str);
  try
  {
    m_anyvalue = JSONParseTypedAnyValue(anytype, iss);
  }
  catch(const MessageException&)
  {
    return false;
  }
  return true;
}

bool JSONAnyValueParser::TypedParseFile(const AnyType& anytype, const std::string& filename)
{
  std::ifstream ifs(filename);
  if (!ifs.is_open())
  {
    return false;
  }
  try
  {
    m_anyvalue = JSONParseTypedAnyValue(anytype, ifs);
  }
  catch(const MessageException&)
  {
    return false;
  }
  return true;
}

AnyValue JSONAnyValueParser::MoveAnyValue()
{
  return std::move(m_anyvalue);
}

}  // namespace dto

}  // namespace sup
