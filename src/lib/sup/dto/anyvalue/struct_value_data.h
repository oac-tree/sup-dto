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

#ifndef SUP_DTO_STRUCT_VALUE_DATA_H_
#define SUP_DTO_STRUCT_VALUE_DATA_H_

#include <sup/dto/anyvalue/i_value_data.h>

#include <utility>
#include <vector>

namespace sup
{
namespace dto
{
class StructValueData : public IValueData
{
public:
  StructValueData(const std::string& type_name, value_flags::Constraints constraints);
  ~StructValueData() override;

  StructValueData* Clone(value_flags::Constraints constraints) const override;
  TypeCode GetTypeCode() const override;
  std::string GetTypeName() const override;
  AnyType GetType() const override;

  value_flags::Constraints GetConstraints() const override;

  void AddMember(const std::string& name, const AnyValue& value) override;
  std::vector<std::string> MemberNames() const override;
  std::size_t NumberOfMembers() const override;

  void Assign(const AnyValue& value) override;

  bool HasField(const std::string& fieldname) const override;
  AnyValue& operator[](const std::string& fieldname) override;

  bool Equals(const AnyValue& other) const override;

private:
  std::string m_name;
  std::vector<std::pair<std::string, std::unique_ptr<AnyValue>>> m_members;
  value_flags::Constraints m_constraints;
};

StructValueData* CreateStructValueData(const AnyType& anytype,
                                       value_flags::Constraints constraints);

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_STRUCT_VALUE_DATA_H_
