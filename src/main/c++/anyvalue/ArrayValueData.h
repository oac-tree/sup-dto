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
 * @file ArrayValueData.h
 * @brief Header file for ArrayValueData.
 * @date 18/01/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the ArrayValueData class.
 */

#ifndef _SUP_ArrayValueData_h_
#define _SUP_ArrayValueData_h_

#include "IValueData.h"

#include <vector>

namespace sup
{
namespace dto
{
class ArrayValueData : public IValueData
{
public:
  ArrayValueData(std::size_t size, const AnyType& elem_type, const std::string& name);
  ~ArrayValueData() override;

  ArrayValueData* Clone() const override;
  TypeCode GetTypeCode() const override;
  std::string GetTypeName() const override;
  AnyType GetType() const override;

  std::size_t NumberOfElements() const override;

  void Assign(const AnyValue& value) override;

  AnyValue& operator[](const std::string& fieldname) override;
  AnyValue& operator[](std::size_t idx) override;

  bool Equals(const AnyValue& other) const override;

private:
  AnyType elem_type;
  std::string name;
  std::vector<AnyValue> elements;
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_ArrayValueData_h_
