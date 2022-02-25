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
 * @file ByteSerializer.h
 * @brief Header file for the ByteSerializer class.
 * @date 18/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the ByteSerializer class.
 */

#ifndef _SUP_ByteSerializer_h_
#define _SUP_ByteSerializer_h_

#include "IAnySerializer.h"
#include "BasicScalarTypes.h"

#include <vector>

namespace sup
{
namespace dto
{
class AnyValue;

class ByteSerializer : public IAnySerializer<AnyValue>
{
public:
  ByteSerializer();
  ~ByteSerializer() override;

  std::vector<uint8> GetRepresentation() const;

  void AddEmptyProlog(const AnyValue* anyvalue) override;
  void AddEmptyEpilog(const AnyValue* anyvalue) override;

  void AddStructProlog(const AnyValue* anyvalue) override;
  void AddStructMemberSeparator() override;
  void AddStructEpilog(const AnyValue* anyvalue) override;

  void AddMemberProlog(const AnyValue* anyvalue, const std::string& member_name) override;
  void AddMemberEpilog(const AnyValue* anyvalue, const std::string& member_name) override;

  void AddArrayProlog(const AnyValue* anyvalue) override;
  void AddArrayElementSeparator() override;
  void AddArrayEpilog(const AnyValue* anyvalue) override;

  void AddScalarProlog(const AnyValue* anyvalue) override;
  void AddScalarEpilog(const AnyValue* anyvalue) override;

private:
  std::vector<uint8> representation;
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_ByteSerializer_h_
