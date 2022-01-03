/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : SUP - Sequencer
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

#include "AnyType.h"
#include "EmptyTypeData.h"

#include <unordered_set>

namespace sup
{
namespace dto
{

namespace
{
std::unordered_set<TypeCode> ScalarTypes();
}  // unnamed namespace

AnyType::AnyType()
  : data{new EmptyTypeData()}
{}

AnyType::AnyType(TypeCode type_code, std::string name)
  : data{CreateTypeData(type_code, name)}
{}

AnyType::AnyType(const AnyType& other)
  : data{other.data->Clone()}
{}

AnyType& AnyType::operator=(const AnyType& other)
{
  if (this != &other)
  {
    data.reset(other.data->Clone());
  }
  return *this;
}

AnyType::AnyType(AnyType&& other)
  : data{other.data.release()}
{
  other.data.reset(new EmptyTypeData());
}

AnyType& AnyType::operator=(AnyType&& other)
{
  if (this != &other)
  {
    data.reset(other.data.release());
    other.data.reset(new EmptyTypeData());
  }
  return *this;
}

AnyType::~AnyType() = default;

TypeCode AnyType::GetTypeCode() const
{
  return data->GetTypeCode();
}

AnyType& AnyType::operator[](std::string fieldname)
{
  return (*data)[fieldname];
}

const AnyType& AnyType::operator[](std::string fieldname) const
{
  return (*data)[fieldname];
}

bool IsEmptyType(const AnyType& anytype)
{
  return anytype.GetTypeCode() == TypeCode::Empty;
}

bool IsStructType(const AnyType& anytype)
{
  return anytype.GetTypeCode() == TypeCode::Struct;
}

bool IsArrayType(const AnyType& anytype)
{
  return anytype.GetTypeCode() == TypeCode::Array;
}

bool IsScalarType(const AnyType& anytype)
{
  static auto scalar_types = ScalarTypes();
  auto type_code = anytype.GetTypeCode();
  return scalar_types.count(type_code) == 1;
}

namespace
{
std::unordered_set<TypeCode> ScalarTypes()
{
  std::unordered_set<TypeCode> result;
  result.insert({ TypeCode::Int8,
                  TypeCode::UInt8 });
  return result;
}
}  // unnamed namespace

}  // namespace dto

}  // namespace sup
