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
  std::istringstream iss(json_str);
  AnyTypeRegistry empty_registry;
  auto registry = type_registry == nullptr ? &empty_registry : type_registry;
  try
  {
    auto parsed_value = JSONParseAnyValue(registry, iss);
    m_anyvalue.reset(new AnyValue(std::move(parsed_value)));
  }
  catch(const ParseException&)
  {
    return false;
  }
  return true;
}

bool JSONAnyValueParser::ParseFile(const std::string& filename,
                                   const AnyTypeRegistry* type_registry)
{
  std::ifstream ifs(filename);
  if (!ifs.is_open())
  {
    return false;
  }
  AnyTypeRegistry empty_registry;
  auto registry = type_registry == nullptr ? &empty_registry : type_registry;
  try
  {
    auto parsed_value = JSONParseAnyValue(registry, ifs);
    m_anyvalue.reset(new AnyValue(std::move(parsed_value)));
  }
  catch(const ParseException&)
  {
    return false;
  }
  return true;
}

AnyValue JSONAnyValueParser::MoveAnyValue()
{
  if (!m_anyvalue)
  {
    return {};
  }
  return std::move(*m_anyvalue.release());
}

}  // namespace dto

}  // namespace sup
