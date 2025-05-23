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

#ifndef SUP_DTO_ANYTYPE_REGISTRY_H_
#define SUP_DTO_ANYTYPE_REGISTRY_H_

#include <sup/dto/anytype.h>

#include <map>
#include <string>
#include <vector>

namespace sup
{
namespace dto
{
/**
 * @brief Class for registering AnyTypes.
 */
class AnyTypeRegistry
{
public:
  /**
   * @brief Default constructor creates registry with scalar and empty types.
   */
  AnyTypeRegistry();

  /**
   * @brief Destructor.
   */
  ~AnyTypeRegistry() = default;

  AnyTypeRegistry(const AnyTypeRegistry& other) = default;
  AnyTypeRegistry(AnyTypeRegistry&& other) noexcept = default;
  AnyTypeRegistry& operator=(const AnyTypeRegistry& other) & = default;
  AnyTypeRegistry& operator=(AnyTypeRegistry&& other) & noexcept = default;

  /**
   * @brief Register an AnyType instance under its own name.
   *
   * @param anytype AnyType instance to register.
   *
   * @throws InvalidOperationException Thrown when the given name was already used for the
   * registration of a different type (multiple registration calls for the same name AND type
   * are allowed).
   */
  void RegisterType(AnyType anytype);

  /**
   * @brief Register an AnyType instance under the given name.
   *
   * @param name name under which to register the AnyType.
   * @param anytype AnyType instance to register.
   *
   * @throws InvalidOperationException Thrown when the given name was already used for the
   * registration of a different type (multiple registration calls for the same name AND type
   * are allowed).
   */
  void RegisterType(const std::string& name, AnyType anytype);

  /**
   * @brief Query the existance of a registered AnyType instance under the given name.
   *
   * @param name name under which the AnyType instance was registered.
   *
   * @return true if an AnyType instance was registered under the given name, false otherwise.
   */
  bool HasType(const std::string& name) const;

  /**
   * @brief Retrieve all names under which AnyType instances are registered.
   *
   * @return List of all names under which AnyType instances are registered.
   */
  std::vector<std::string> RegisteredAnyTypeNames() const;

  /**
   * @brief Retrieve a registered AnyType instance for the given name.
   *
   * @param name name under which the AnyType instance was registered.
   *
   * @return The AnyType instance that was registered under the given name.

   * @throws InvalidOperationException Thrown when the given name does not correspond to a
   * reigstered AnyType instance.
   */
  AnyType GetType(const std::string& name) const;

private:
  std::map<std::string, AnyType> m_anytypes;
};

std::map<std::string, AnyType> NameToAnyTypeLeafMap();

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ANYTYPE_REGISTRY_H_
