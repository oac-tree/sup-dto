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
 * @file JSONSerializer.h
 * @brief Header file for the JSONSerializer class.
 * @date 23/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the JSONSerializer class.
 */

#ifndef _SUP_JSONSerializer_h_
#define _SUP_JSONSerializer_h_

#include "IAnySerializer.h"
#include "BasicScalarTypes.h"
#include "IJSONWriter.h"

#include <memory>

namespace sup
{
namespace dto
{
class AnyType;
class AnyValue;
class JSONRepresentation;

class JSONSerializer
{
public:
  JSONSerializer(IJSONWriter* writer);
  ~JSONSerializer();

  bool SerializeAnyType(const AnyType& anytype);
  bool SerializeAnyValue(const AnyValue& anyvalue);

private:
  IJSONWriter* writer;
};

/**
 * @brief JSON serialization for AnyType.
 */
class JSONTypeSerializer : public IAnySerializer<AnyType>
{
public:
  JSONTypeSerializer();
  ~JSONTypeSerializer() override;

  void ResetRepresentation() override;
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
  std::unique_ptr<JSONRepresentation> representation;
};


/**
 * @brief JSON serialization for AnyValue.
 */
class JSONValueSerializer : public IAnySerializer<AnyValue>
{
public:
  JSONValueSerializer();
  ~JSONValueSerializer() override;

  void ResetRepresentation() override;
  std::string GetRepresentation() const;

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
  std::unique_ptr<JSONRepresentation> representation;
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_JSONSerializer_h_
