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
 * SPDX-License-Identifier: MIT
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file LICENSE located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#ifndef SUP_DTO_EMPTY_TYPE_DATA_H_
#define SUP_DTO_EMPTY_TYPE_DATA_H_

#include <sup/dto/anyvalue/i_type_data.h>

namespace sup
{
namespace dto
{
class EmptyTypeData : public ITypeData
{
public:
  EmptyTypeData();
  ~EmptyTypeData() override;

  EmptyTypeData(const EmptyTypeData& other) = delete;
  EmptyTypeData(EmptyTypeData&& other) = delete;
  EmptyTypeData& operator=(const EmptyTypeData& other) = delete;
  EmptyTypeData& operator=(EmptyTypeData&& other) = delete;

  TypeCode GetTypeCode() const override;
  std::string GetTypeName() const override;

  std::unique_ptr<ITypeData> CloneFromChildren(
    std::vector<std::unique_ptr<AnyType>>&& children) const override;

  bool ShallowEquals(const AnyType& other) const override;
};

std::unique_ptr<ITypeData> CreateDefaultTypeData();

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_EMPTY_TYPE_DATA_H_
