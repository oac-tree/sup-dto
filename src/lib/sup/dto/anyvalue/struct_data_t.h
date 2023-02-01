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

#ifndef SUP_DTO_STRUCT_DATA_T_H_
#define SUP_DTO_STRUCT_DATA_T_H_

#include <sup/dto/anyvalue/field_utils.h>

#include <sup/dto/anytype.h>
#include <sup/dto/anyvalue_exceptions.h>

#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace sup
{
namespace dto
{

template <typename T>
class StructDataT
{
public:
  StructDataT(const std::string& name);
  ~StructDataT() = default;

  TypeCode GetTypeCode() const;
  std::string GetTypeName() const;

  void AddMember(const std::string& name, const T& type);
  std::vector<std::string> MemberNames() const;
  std::size_t NumberOfMembers() const;

  bool HasField(const std::string& fieldname) const;
  T& operator[](const std::string& fieldname);
  const T& operator[](const std::string& fieldname) const;

  bool Equals(const T& other) const;

private:
  std::string name;
  std::vector<std::pair<std::string, T>> members;
};

template <typename T>
StructDataT<T>::StructDataT(const std::string& name_)
  : name{name_}
  , members{}
{}

template <typename T>
TypeCode StructDataT<T>::GetTypeCode() const
{
  return TypeCode::Struct;
}

template <typename T>
std::string StructDataT<T>::GetTypeName() const
{
  return name;
}

template <typename T>
void StructDataT<T>::AddMember(const std::string& name, const T& type)
{
  utils::VerifyMemberName(name);
  if (HasField(name))
  {
    throw InvalidOperationException("Cannot add duplicate member keys");
  }
  if (type == T{})
  {
    throw InvalidOperationException("Cannot add empty type/value to structure");
  }
  members.push_back({name, type});
}

template <typename T>
bool StructDataT<T>::HasField(const std::string& fieldname) const
{
  auto fields = utils::StripFirstFieldName(fieldname);
  auto it = std::find_if(members.cbegin(), members.cend(),
                         [&fields](typename decltype(members)::const_reference member){
                           return member.first == fields.first;
                         });
  if (it == members.cend())
  {
    return false;
  }
  if (fields.second.empty())
  {
    return true;
  }
  auto& member = it->second;
  return member.HasField(fields.second);
}

template <typename T>
std::vector<std::string> StructDataT<T>::MemberNames() const
{
  std::vector<std::string> result;
  std::transform(members.begin(), members.end(), std::back_inserter(result),
                 [](typename decltype(members)::const_reference member){
                   return member.first;
                 });
  return result;
}

template <typename T>
std::size_t StructDataT<T>::NumberOfMembers() const
{
  return members.size();
}

template <typename T>
T& StructDataT<T>::operator[](const std::string& fieldname)
{
  return const_cast<T&>(static_cast<const StructDataT<T>&>(*this)[fieldname]);
}

template <typename T>
const T& StructDataT<T>::operator[](const std::string& fieldname) const
{
  using cref_pair_type = typename decltype(members)::const_reference;
  if (fieldname.empty())
  {
    throw InvalidOperationException("Trying to access a member with empty field name");
  }
  auto fields = utils::StripFirstFieldName(fieldname);
  auto it = std::find_if(members.cbegin(), members.cend(),
                      [&fields](cref_pair_type member){
                        return member.first == fields.first;
                      });
  if (it == members.cend())
  {
    throw InvalidOperationException("Trying to access a member with unknown field name");
  }
  auto& member = it->second;
  if (fields.second.empty())
  {
    return member;
  }
  return member[fields.second];
}

template <typename T>
bool StructDataT<T>::Equals(const T& other) const
{
  if (other.GetTypeCode() != TypeCode::Struct)
  {
    return false;
  }
  if (other.GetTypeName() != GetTypeName())
  {
    return false;
  }
  if (other.MemberNames() != MemberNames())
  {
    return false;
  }
  for (auto &member : members)
  {
    auto &other_member_field = other[member.first];
    if (other_member_field != member.second)
    {
      return false;
    }
  }
  return true;
}

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_STRUCT_DATA_T_H_
