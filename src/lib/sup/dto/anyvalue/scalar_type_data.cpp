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
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include "scalar_type_data.h"
#include "sup/dto/anytype.h"

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

ScalarTypeData::ScalarTypeData(TypeCode type_code)
  : m_type_code{type_code}
{}

ScalarTypeData::~ScalarTypeData() = default;

TypeCode ScalarTypeData::GetTypeCode() const
{
  return m_type_code;
}

std::string ScalarTypeData::GetTypeName() const
{
  return ScalarTypeCodeToString(m_type_code);
}

std::unique_ptr<ITypeData> ScalarTypeData::CloneFromChildren(std::vector<AnyType>&& children) const
{
  if (!children.empty())
  {
    const std::string error =
      "ScalarTypeData::CloneFromChildren(): Trying to clone scalar type with child types";
    throw InvalidOperationException(error);
  }
  return std::make_unique<ScalarTypeData>(m_type_code);
}

bool ScalarTypeData::ShallowEquals(const AnyType& other) const
{
  return other.GetTypeCode() == GetTypeCode();
}

std::unique_ptr<ITypeData> CreateScalarData(TypeCode type_code)
{
  if (!IsScalarTypeCode(type_code))
  {
    throw InvalidOperationException("Not a known scalar type code");
  }
  return std::make_unique<ScalarTypeData>(type_code);
}

namespace
{
std::map<TypeCode, std::string> ScalarTypeCodeToStringMap()
{
  std::map<TypeCode, std::string> result;
  const auto& scalar_type_definitions = ScalarTypeDefinitions();
  for (auto& [memberCode, memberName] : scalar_type_definitions)
  {
    result[memberCode] = memberName;
  }
  return result;
}

std::string ScalarTypeCodeToString(TypeCode type_code)
{
  static const std::map<TypeCode, std::string> type_map = ScalarTypeCodeToStringMap();
  const auto it = type_map.find(type_code);
  return it->second;
}
}  // unnamed namespace

}  // namespace dto

}  // namespace sup
