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

/**
 * @file TestSerializers.h
 * @brief Header file for serializer classes for unit testing.
 * @date 16/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the serializer classes for unit testing.
 */

#ifndef _SUP_TestSerializers_h_
#define _SUP_TestSerializers_h_

#include "IAnySerializer.h"

namespace sup
{
namespace dto
{
class AnyType;

/**
 * @brief Simple serialization for AnyType.
 */
class SimpleAnyTypeSerializer : public IAnySerializer<AnyType>
{
public:
  SimpleAnyTypeSerializer();
  ~SimpleAnyTypeSerializer() override;

  std::string GetRepresentation() const;

  void AddEmptyProlog(const AnyType* anytype) override;
  void AddEmptyEpilog(const AnyType* anytype) override;

  void AddStructProlog(const AnyType* anytype) override;
  void AddStructMemberSeparator() override;
  void AddStructEpilog(const AnyType* anytype) override;

  void AddMemberProlog(const AnyType* anytype, const std::string& member_name) override;
  void AddMemberEpilog(const AnyType* anytype, const std::string& member_name) override;

  void AddArrayProlog(const AnyType* anytype) override;
  void AddArrayElementSeparator() override;
  void AddArrayEpilog(const AnyType* anytype) override;

  void AddScalarProlog(const AnyType* anytype) override;
  void AddScalarEpilog(const AnyType* anytype) override;

private:
  std::string representation;
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_TestSerializers_h_
