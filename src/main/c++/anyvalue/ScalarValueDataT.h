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
 * @file ScalarValueDataT.h
 * @brief Header file for ScalarValueDataT.
 * @date 06/01/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the ScalarValueDataT class template.
 */

#ifndef _SUP_ScalarValueDataT_h_
#define _SUP_ScalarValueDataT_h_

#include "ScalarValueDataBase.h"
#include "ScalarConversion.h"

namespace sup
{
namespace dto
{

template <typename T>
struct TypeToCode;

template <>
struct TypeToCode<boolean>
{
  static constexpr TypeCode code = TypeCode::Bool;
};

template <>
struct TypeToCode<int8>
{
  static constexpr TypeCode code = TypeCode::Int8;
};

template <>
struct TypeToCode<uint8>
{
  static constexpr TypeCode code = TypeCode::UInt8;
};

template <typename T>
class ScalarValueDataT : public ScalarValueDataBase
{
public:
  ScalarValueDataT(T value = {});
  ~ScalarValueDataT() override = default;

  void Assign(const AnyValue& value) override;

  boolean AsBoolean() const override;
  int8 AsSignedInteger8() const override;
  uint8 AsUnsignedInteger8() const override;

private:
  T value;
};

template <typename T>
ScalarValueDataT<T>::ScalarValueDataT(T value_)
  : ScalarValueDataBase{TypeToCode<T>::code}
  , value{value_}
{}

template <typename T>
void ScalarValueDataT<T>::Assign(const AnyValue& value_)
{
  value = value_.As<T>();
}

template <typename T>
boolean ScalarValueDataT<T>::AsBoolean() const
{
  return ConvertScalar<boolean, T>(value);
}

template <typename T>
int8 ScalarValueDataT<T>::AsSignedInteger8() const
{
  return ConvertScalar<int8, T>(value);
}

template <typename T>
uint8 ScalarValueDataT<T>::AsUnsignedInteger8() const
{
  return ConvertScalar<uint8, T>(value);
}

}  // namespace dto

}  // namespace sup

#endif  // _SUP_ScalarValueDataT_h_
