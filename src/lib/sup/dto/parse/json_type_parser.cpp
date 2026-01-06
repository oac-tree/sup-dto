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

#include <sup/dto/json_type_parser.h>

#include <sup/dto/anytype_registry.h>
#include <sup/dto/anyvalue_exceptions.h>
#include <sup/dto/json/json_reader.h>
#include <sup/dto/anytype.h>

#include <fstream>
#include <sstream>

namespace sup
{
namespace dto
{

JSONAnyTypeParser::JSONAnyTypeParser()
  : m_anytype{}
{}

JSONAnyTypeParser::~JSONAnyTypeParser() = default;

bool JSONAnyTypeParser::ParseString(const std::string& json_str,
                                    const AnyTypeRegistry* type_registry)
{
  try
  {
    std::istringstream iss(json_str);
    const AnyTypeRegistry empty_registry;
    const auto registry = (type_registry == nullptr) ? &empty_registry : type_registry;
    m_anytype = JSONParseAnyType(registry, iss);
  }
  catch(const MessageException&)
  {
    return false;
  }
  return true;
}

bool JSONAnyTypeParser::ParseString(const std::string& json_str)
{
  return ParseString(json_str, nullptr);
}

bool JSONAnyTypeParser::ParseFile(const std::string& filename,
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
    m_anytype = JSONParseAnyType(registry, ifs);
  }
  catch(const MessageException&)
  {
    return false;
  }
  return true;
}

bool JSONAnyTypeParser::ParseFile(const std::string& filename)
{
  return ParseFile(filename, nullptr);
}

AnyType JSONAnyTypeParser::MoveAnyType()
{
  return std::move(m_anytype);
}

}  // namespace dto

}  // namespace sup
