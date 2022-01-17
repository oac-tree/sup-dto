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

/**
 * @file StructValueData.h
 * @brief Header file for StructValueData.
 * @date 14/01/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the StructValueData class.
 */

#ifndef _SUP_StructValueData_h_
#define _SUP_StructValueData_h_

#include "IValueData.h"
#include "StructDataT.h"

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
  bool HasMember(const std::string& name) const override;
  std::vector<std::string> MemberNames() const override;
  std::size_t NumberOfMembers() const override;

  AnyValue& operator[](const std::string& fieldname) override;
  const AnyValue& operator[](const std::string& fieldname) const override;

  bool Equals(const AnyValue& other) const override;

private:
  StructValueData(const StructDataT<AnyValue>& member_data);
  StructDataT<AnyValue> member_data;
};

StructValueData* CreateStructValueData(const AnyType& anytype);

}  // namespace dto

}  // namespace sup

#endif  // _SUP_StructValueData_h_
