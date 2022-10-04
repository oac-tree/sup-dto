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
  std::istringstream iss(json_str);
  AnyTypeRegistry empty_registry;
  auto registry = type_registry == nullptr ? &empty_registry : type_registry;
  try
  {
    auto parsed_type = JSONParseAnyType(registry, iss);
    m_anytype.reset(new AnyType(std::move(parsed_type)));
  }
  catch(const ParseException&)
  {
    return false;
  }
  return true;
}

bool JSONAnyTypeParser::ParseFile(const std::string& filename,
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
    auto parsed_type = JSONParseAnyType(registry, ifs);
    m_anytype.reset(new AnyType(std::move(parsed_type)));
  }
  catch(const ParseException&)
  {
    return false;
  }
  return true;
}

AnyType JSONAnyTypeParser::MoveAnyType()
{
  if (!m_anytype)
  {
    return {};
  }
  return std::move(*m_anytype.release());
}

}  // namespace dto

}  // namespace sup
