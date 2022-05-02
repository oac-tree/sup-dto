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

#include "AnyTypeRegistry.h"

#include "AnyValueExceptions.h"

namespace sup
{
namespace dto
{

AnyTypeRegistry::AnyTypeRegistry()
  : anytypes{}
{}

AnyTypeRegistry::AnyTypeRegistry(const std::map<std::string, AnyType>& anytypes_)
  : anytypes{anytypes_}
{}

AnyTypeRegistry::~AnyTypeRegistry() = default;

void AnyTypeRegistry::RegisterType(const std::string& name, AnyType anytype)
{
  auto it = anytypes.find(name);
  if (it != anytypes.end() && it->second != anytype)
  {
    throw InvalidOperationException("AnyTypeRegistry::RegisterType(): name already in use "
                                    "for different AnyType instance");
  }
  if (it == anytypes.end())
  {
    anytypes[name] = anytype;
  }
}

void AnyTypeRegistry::RemoveType(const std::string& name)
{
  auto it = anytypes.find(name);
  if (it == anytypes.end())
  {
    throw InvalidOperationException("AnyTypeRegistry::RemoveType(): name not found");
  }
  anytypes.erase(it);
}

bool AnyTypeRegistry::HasType(const std::string& name) const
{
  return anytypes.find(name) != anytypes.end();
}

std::vector<std::string> AnyTypeRegistry::RegisteredAnyTypeNames() const
{
  std::vector<std::string> result;
  for (const auto& name_anytype_pair : anytypes)
  {
    result.push_back(name_anytype_pair.first);
  }
  return result;
}

AnyType AnyTypeRegistry::GetType(const std::string& name) const
{
  auto it = anytypes.find(name);
  if (it == anytypes.end())
  {
    throw InvalidOperationException("AnyTypeRegistry::GetType(): name not found");
  }
  return it->second;
}

}  // namespace dto

}  // namespace sup
