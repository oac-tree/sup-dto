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

#include "StructValueData.h"

namespace sup
{
namespace dto
{

StructValueData::StructValueData(const std::string& type_name)
  : member_data{type_name}
{}

StructValueData::~StructValueData() = default;

StructValueData* StructValueData::Clone() const
{
  auto result = std::unique_ptr<StructValueData>(new StructValueData(member_data));
  return result.release();
}

TypeCode StructValueData::GetTypeCode() const
{
  return member_data.GetTypeCode();
}

AnyType StructValueData::GetType() const
{
  auto result = EmptyStructType(member_data.GetTypeName());
  for (const auto& member_name : member_data.MemberNames())
  {
    result.AddMember(member_name, member_data[member_name].GetType());
  }
  return result;
}

std::string StructValueData::GetTypeName() const
{
  return member_data.GetTypeName();
}

void StructValueData::Assign(const AnyValue& value)
{
  if (value.GetTypeCode() != TypeCode::Struct)
  {
    IValueData::Assign(value);
  }
  if (value.MemberNames() != MemberNames())
  {
    throw InvalidConversionException("Can't convert AnyValues with different list of fields");
  }
  for (const auto &member_name : member_data.MemberNames())
  {
    auto &other_member_value = value[member_name];
    member_data[member_name] = other_member_value;
  }
}

void StructValueData::AddMember(const std::string& name, const AnyValue& value)
{
  return member_data.AddMember(name, value);
}

bool StructValueData::HasMember(const std::string& name) const
{
  return member_data.HasMember(name);
}

std::vector<std::string> StructValueData::MemberNames() const
{
  return member_data.MemberNames();
}

std::size_t StructValueData::NumberOfMembers() const
{
  return member_data.NumberOfMembers();
}

AnyValue& StructValueData::operator[](const std::string& fieldname)
{
  return member_data[fieldname];
}

bool StructValueData::Equals(const AnyValue& other) const
{
  return member_data.Equals(other);
}

StructValueData::StructValueData(const StructDataT<AnyValue>& member_data_)
  : member_data{member_data_}
{}

StructValueData* CreateStructValueData(const AnyType& anytype)
{
  auto result = std::unique_ptr<StructValueData>(new StructValueData(anytype.GetTypeName()));
  for (const auto& member_name : anytype.MemberNames())
  {
    result->AddMember(member_name, AnyValue(anytype[member_name]));
  }
  return result.release();
}

}  // namespace dto

}  // namespace sup
