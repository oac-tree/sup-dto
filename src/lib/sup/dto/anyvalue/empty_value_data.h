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
 * Copyright (c) : 2010-2024 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#ifndef SUP_DTO_EMPTY_VALUE_DATA_H_
#define SUP_DTO_EMPTY_VALUE_DATA_H_

#include <sup/dto/anyvalue/i_value_data.h>

namespace sup
{
namespace dto
{
class EmptyValueData : public IValueData
{
public:
  explicit EmptyValueData(Constraints constraints);
  ~EmptyValueData() override;

  EmptyValueData(const EmptyValueData& other) = delete;
  EmptyValueData(EmptyValueData&& other) = delete;
  EmptyValueData& operator=(const EmptyValueData& other) = delete;
  EmptyValueData& operator=(EmptyValueData&& other) = delete;

  std::unique_ptr<IValueData> Clone(Constraints constraints) const override;
  TypeCode GetTypeCode() const override;
  AnyType GetType() const override;

  Constraints GetConstraints() const override;

  void ConvertFrom(const AnyValue& value) override;

  bool Equals(const AnyValue& other) const override;
private:
  Constraints m_constraints;
};

std::unique_ptr<IValueData> CreateDefaultValueData();

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_EMPTY_VALUE_DATA_H_
