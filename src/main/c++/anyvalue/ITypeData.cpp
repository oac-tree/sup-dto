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

#include "ITypeData.h"

#include "AnyValueExceptions.h"

#include <map>

namespace sup
{
namespace dto
{

ITypeData::~ITypeData() = default;

std::string ITypeData::GetTypeName() const
{
  return TypeCodeToString(GetTypeCode());
}

void ITypeData::AddMember(const std::string&, const AnyType&)
{
  throw InvalidOperationException("Add member only supported for structured types");
}

bool ITypeData::HasMember(const std::string&) const
{
  return false;
}

std::vector<std::string> ITypeData::MemberNames() const
{
  return {};
}

std::size_t ITypeData::NumberOfMembers() const
{
  return 0;
}

std::string TypeCodeToString(TypeCode type_code)
{
  static const std::map<TypeCode, std::string> type_map({
    { TypeCode::Empty, EMPTY_TYPE_NAME },
    { TypeCode::Bool, BOOLEAN_TYPE_NAME },
    { TypeCode::Char8, CHAR8_TYPE_NAME },
    { TypeCode::Int8, INT8_TYPE_NAME },
    { TypeCode::UInt8, UINT8_TYPE_NAME },
    { TypeCode::Int16, INT16_TYPE_NAME },
    { TypeCode::UInt16, UINT16_TYPE_NAME },
    { TypeCode::Int32, INT32_TYPE_NAME },
    { TypeCode::UInt32, UINT32_TYPE_NAME },
    { TypeCode::Int64, INT64_TYPE_NAME },
    { TypeCode::UInt64, UINT64_TYPE_NAME },
  });
  auto it = type_map.find(type_code);
  if (it == type_map.end())
  {
    throw UnknownKeyException("Unknown typecode");
  }
  return it->second;
}

}  // namespace dto

}  // namespace sup
