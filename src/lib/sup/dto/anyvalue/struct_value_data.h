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

#ifndef SUP_DTO_STRUCT_VALUE_DATA_H_
#define SUP_DTO_STRUCT_VALUE_DATA_H_

#include <sup/dto/anyvalue/i_value_data.h>
#include <sup/dto/anyvalue/struct_data_t.h>

#include <utility>
#include <vector>

namespace sup
{
namespace dto
{
class StructValueData : public IValueData
{
public:
  StructValueData(const std::string& type_name, Constraints constraints);
  StructValueData(const AnyType& anytype, Constraints constraints);
  ~StructValueData() override;

  StructValueData(const StructValueData& other) = delete;
  StructValueData(StructValueData&& other) = delete;
  StructValueData& operator=(const StructValueData& other) = delete;
  StructValueData& operator=(StructValueData&& other) = delete;

  TypeCode GetTypeCode() const override;
  std::string GetTypeName() const override;
  AnyType GetType() const override;

  Constraints GetConstraints() const override;

  void AddMember(const std::string& name, AnyValue&& value) override;
  std::vector<std::string> MemberNames() const override;
  std::size_t NumberOfMembers() const override;

  void ConvertFrom(const AnyValue& value) override;

  std::size_t NumberOfChildren() const override;
  bool HasChild(const std::string& child_name) const override;
  AnyValue* GetChildValue(const std::string& child_name) override;
  AnyValue* GetChildValue(std::size_t idx) override;
  std::unique_ptr<IValueData> CloneFromChildren(std::vector<std::unique_ptr<AnyValue>>&& children,
                                                Constraints constraints) const override;
  bool ShallowEquals(const AnyValue& other) const override;

private:
  StructDataT<AnyValue> m_member_data;
  Constraints m_constraints;
};

std::unique_ptr<IValueData> CreateStructValueData(const AnyType& anytype, Constraints constraints);

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_STRUCT_VALUE_DATA_H_
