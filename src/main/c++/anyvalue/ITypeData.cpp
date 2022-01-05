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

namespace
{
std::string TypeCodeToString(TypeCode type_code);
}  // unnamed namespace

ITypeData::~ITypeData() = default;

std::string ITypeData::GetTypeName() const
{
  return TypeCodeToString(GetTypeCode());
}

namespace
{
std::string TypeCodeToString(TypeCode type_code)
{
  static const std::map<TypeCode, std::string> type_map({
    { TypeCode::Empty, "empty" },
    { TypeCode::Int8, "int8" },
    { TypeCode::UInt8, "uint8" }
  });
  auto it = type_map.find(type_code);
  if (it == type_map.end())
  {
    throw UnknownKeyException("Unknown typecode");
  }
  return it->second;
}
}  // unnamed namespace

}  // namespace dto

}  // namespace sup
