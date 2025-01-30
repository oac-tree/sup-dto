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

#ifndef SUP_DTO_STRUCT_TYPE_DATA_H_
#define SUP_DTO_STRUCT_TYPE_DATA_H_

#include <sup/dto/anyvalue/i_type_data.h>
#include <sup/dto/anyvalue/struct_data_t.h>

#include <vector>

namespace sup
{
namespace dto
{
class StructTypeData : public ITypeData
{
public:
  explicit StructTypeData(const std::string& name);
  ~StructTypeData() override;

  StructTypeData(const StructTypeData& other) = delete;
  StructTypeData(StructTypeData&& other) = delete;
  StructTypeData& operator=(const StructTypeData& other) = delete;
  StructTypeData& operator=(StructTypeData&& other) = delete;

  std::unique_ptr<ITypeData> Clone() const override;
  TypeCode GetTypeCode() const override;
  std::string GetTypeName() const override;

  void AddMember(const std::string& name, const AnyType& type) override;
  std::vector<std::string> MemberNames() const override;
  std::size_t NumberOfMembers() const override;

  bool HasField(const std::string& fieldname) const override;
  AnyType* GetChildType(const std::string& child_name) override;

  bool Equals(const AnyType& other) const override;

private:
  StructDataT<AnyType> m_member_data;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_STRUCT_TYPE_DATA_H_
