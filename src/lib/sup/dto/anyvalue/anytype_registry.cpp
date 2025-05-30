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

#include "sup/dto/anytype.h"
#include <sup/dto/anytype_registry.h>

#include <sup/dto/anyvalue_exceptions.h>

namespace sup
{
namespace dto
{

AnyTypeRegistry::AnyTypeRegistry()
  : m_anytypes{NameToAnyTypeLeafMap()}
{}

void AnyTypeRegistry::RegisterType(AnyType anytype)
{
  RegisterType(anytype.GetTypeName(), anytype);
}

void AnyTypeRegistry::RegisterType(const std::string& name, AnyType anytype)
{
  if (name.empty())
  {
    throw InvalidOperationException("AnyTypeRegistry::RegisterType(): empty name not allowed");
  }
  const auto it = m_anytypes.find(name);
  if ((it != m_anytypes.end()) && (it->second != anytype))
  {
    throw InvalidOperationException("AnyTypeRegistry::RegisterType(): name already in use "
                                    "for different AnyType instance");
  }
  if (it == m_anytypes.end())
  {
    m_anytypes[name] = anytype;
  }
}

bool AnyTypeRegistry::HasType(const std::string& name) const
{
  return m_anytypes.find(name) != m_anytypes.end();
}

std::vector<std::string> AnyTypeRegistry::RegisteredAnyTypeNames() const
{
  std::vector<std::string> result;
  for (const auto& [memberName, memberType] : m_anytypes)
  {
    result.push_back(memberName);
  }
  return result;
}

AnyType AnyTypeRegistry::GetType(const std::string& name) const
{
  const auto it = m_anytypes.find(name);
  if (it == m_anytypes.end())
  {
    throw InvalidOperationException("AnyTypeRegistry::GetType(): name not found");
  }
  return it->second;
}

std::map<std::string, AnyType> NameToAnyTypeLeafMap()
{
  std::map<std::string, AnyType> result;
  result[kEmptyTypeName] = EmptyType;
  const auto& scalar_type_definitions = ScalarTypeDefinitions();
  for (const auto& [memberCode, memberName] : scalar_type_definitions)
  {
    result[memberName] = AnyType(memberCode);
  }
  return result;
}

}  // namespace dto

}  // namespace sup
