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

#ifndef _SUP_StructValueData_h_
#define _SUP_StructValueData_h_

#include <sup/dto/anyvalue/i_value_data.h>
#include <sup/dto/anyvalue/struct_data_t.h>

#include <vector>

namespace sup
{
namespace dto
{
class StructValueData : public IValueData
{
public:
  StructValueData(const std::string& type_name);
  ~StructValueData() override;

  StructValueData* Clone() const override;
  TypeCode GetTypeCode() const override;
  AnyType GetType() const override;
  std::string GetTypeName() const override;
  void Assign(const AnyValue& value) override;

  void AddMember(const std::string& name, const AnyValue& value) override;
  std::vector<std::string> MemberNames() const override;
  std::size_t NumberOfMembers() const override;

  bool HasMember(const std::string& fieldname) const override;
  AnyValue& operator[](const std::string& fieldname) override;

  bool Equals(const AnyValue& other) const override;

private:
  StructValueData(const StructDataT<AnyValue>& member_data);
  StructDataT<AnyValue> member_data;
};

StructValueData* CreateStructValueData(const AnyType& anytype);

}  // namespace dto

}  // namespace sup

#endif  // _SUP_StructValueData_h_
