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
  explicit StructDataT(const std::string& name);
  ~StructDataT() = default;

  StructDataT(const StructDataT& other) = delete;
  StructDataT(StructDataT&& other) = delete;
  StructDataT& operator=(const StructDataT& other) = delete;
  StructDataT& operator=(StructDataT&& other) = delete;

  static TypeCode GetTypeCode();
  std::string GetTypeName() const;

  void AddMember(const std::string& name, std::unique_ptr<T>&& val);
  std::vector<std::string> MemberNames() const;
  std::size_t NumberOfMembers() const;

  bool HasChild(const std::string& child_name) const;
  T* GetChild(const std::string& child_name);
  T* GetChild(std::size_t idx);

  bool ShallowEquals(const T& other) const;

private:
  std::string m_name;
  std::vector<std::pair<std::string, std::unique_ptr<T>>> m_members;
};

template <typename T>
StructDataT<T>::StructDataT(const std::string& name)
  : m_name{name}
  , m_members{}
{}

template <typename T>
TypeCode StructDataT<T>::GetTypeCode()
{
  return TypeCode::Struct;
}

template <typename T>
std::string StructDataT<T>::GetTypeName() const
{
  return m_name;
}

template <typename T>
void StructDataT<T>::AddMember(const std::string& name, std::unique_ptr<T>&& val)
{
  utils::VerifyMemberName(name);
  if (HasChild(name))
  {
    throw InvalidOperationException("Cannot add duplicate member keys");
  }
  (void)m_members.emplace_back(name, std::move(val));
}

template <typename T>
std::vector<std::string> StructDataT<T>::MemberNames() const
{
  std::vector<std::string> result;
  (void)std::transform(m_members.begin(), m_members.end(), std::back_inserter(result),
                       [](const auto& member)
                       { return member.first; });
  return result;
}

template <typename T>
std::size_t StructDataT<T>::NumberOfMembers() const
{
  return m_members.size();
}

template <typename T>
bool StructDataT<T>::HasChild(const std::string& child_name) const
{
  auto pred = [child_name](const auto& member){
    return member.first == child_name;
  };
  auto it = std::find_if(m_members.begin(), m_members.end(), pred);
  return it != m_members.end();
}

template <typename T>
T* StructDataT<T>::GetChild(const std::string& child_name)
{
  auto pred = [child_name](const auto& member){
    return member.first == child_name;
  };
  auto it = std::find_if(m_members.begin(), m_members.end(), pred);
  if (it == m_members.end())
  {
    const std::string error =
      "StructDataT::GetChild() called with unknown child name \"" + child_name + "\"";
    throw InvalidOperationException(error);
  }
  return it->second.get();
}

template <typename T>
T* StructDataT<T>::GetChild(std::size_t idx)
{
  if (idx >= m_members.size())
  {
    const std::string error = "StructDataT::GetChild(): index out of bounds";
    throw InvalidOperationException(error);
  }
  return m_members[idx].second.get();
}

template <typename T>
bool StructDataT<T>::ShallowEquals(const T& other) const
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
  return true;
}

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_STRUCT_DATA_T_H_
