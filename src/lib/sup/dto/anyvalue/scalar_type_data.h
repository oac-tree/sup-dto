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

#ifndef SUP_DTO_SCALAR_TYPE_DATA_H_
#define SUP_DTO_SCALAR_TYPE_DATA_H_

#include <sup/dto/anyvalue/i_type_data.h>

namespace sup
{
namespace dto
{
class ScalarTypeData : public ITypeData
{
public:
  explicit ScalarTypeData(TypeCode type_code);
  ~ScalarTypeData() override;

  ScalarTypeData(const ScalarTypeData& other) = delete;
  ScalarTypeData(ScalarTypeData&& other) = delete;
  ScalarTypeData& operator=(const ScalarTypeData& other) = delete;
  ScalarTypeData& operator=(ScalarTypeData&& other) = delete;

  std::unique_ptr<ITypeData> Clone() const override;
  TypeCode GetTypeCode() const override;
  std::string GetTypeName() const override;

  bool Equals(const AnyType& other) const override;

private:
  TypeCode m_type_code;
};

std::unique_ptr<ITypeData> CreateScalarData(TypeCode type_code);

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_SCALAR_TYPE_DATA_H_
