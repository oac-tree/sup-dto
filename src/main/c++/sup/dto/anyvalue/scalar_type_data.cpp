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

#include "scalar_type_data.h"

#include <sup/dto/anyvalue_exceptions.h>

#include <map>

namespace sup
{
namespace dto
{

namespace
{
std::map<TypeCode, std::string> ScalarTypeCodeToStringMap();
std::string ScalarTypeCodeToString(TypeCode type_code);
}  // unnamed namespace

ScalarTypeData::ScalarTypeData(TypeCode type_code_)
  : type_code{type_code_}
{}

ScalarTypeData::~ScalarTypeData() = default;

ScalarTypeData* ScalarTypeData::Clone() const
{
  return new ScalarTypeData(type_code);
}

TypeCode ScalarTypeData::GetTypeCode() const
{
  return type_code;
}

std::string ScalarTypeData::GetTypeName() const
{
  return ScalarTypeCodeToString(type_code);
}

bool ScalarTypeData::Equals(const AnyType& other) const
{
  return other.GetTypeCode() == GetTypeCode();
}

ScalarTypeData* CreateScalarData(TypeCode type_code)
{
  if (!IsScalarTypeCode(type_code))
  {
    throw InvalidOperationException("Not a known scalar type code");
  }
  return new ScalarTypeData(type_code);
}

namespace
{
std::map<TypeCode, std::string> ScalarTypeCodeToStringMap()
{
  std::map<TypeCode, std::string> result;
  const auto& scalar_type_definitions = ScalarTypeDefinitions();
  for (const auto& entry : scalar_type_definitions)
  {
    result[entry.first] = entry.second;
  }
  return result;
}

std::string ScalarTypeCodeToString(TypeCode type_code)
{
  static const std::map<TypeCode, std::string> type_map = ScalarTypeCodeToStringMap();
  auto it = type_map.find(type_code);
  return it->second;
}
}  // unnamed namespace

}  // namespace dto

}  // namespace sup
