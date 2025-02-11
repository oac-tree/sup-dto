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

#ifndef SUP_DTO_SCALAR_VALUE_DATA_H_
#define SUP_DTO_SCALAR_VALUE_DATA_H_

#include <sup/dto/low_level/scalar_conversion.h>
#include <sup/dto/anyvalue/scalar_type_functions.h>
#include <sup/dto/anyvalue/scalar_value_data_base.h>

namespace sup
{
namespace dto
{

template <typename T>
class ScalarValueDataT : public ScalarValueDataBase
{
public:
  ScalarValueDataT(T value, Constraints constraints);
  ~ScalarValueDataT() override = default;

  ScalarValueDataT(const ScalarValueDataT& other) = delete;
  ScalarValueDataT(ScalarValueDataT&& other) = delete;
  ScalarValueDataT& operator=(const ScalarValueDataT& other) = delete;
  ScalarValueDataT& operator=(ScalarValueDataT&& other) = delete;

  boolean AsBoolean() const override;
  char8 AsCharacter8() const override;
  int8 AsSignedInteger8() const override;
  uint8 AsUnsignedInteger8() const override;
  int16 AsSignedInteger16() const override;
  uint16 AsUnsignedInteger16() const override;
  int32 AsSignedInteger32() const override;
  uint32 AsUnsignedInteger32() const override;
  int64 AsSignedInteger64() const override;
  uint64 AsUnsignedInteger64() const override;
  float32 AsFloat32() const override;
  float64 AsFloat64() const override;
  std::string AsString() const override;

  std::unique_ptr<IValueData> CloneFromChildren(std::vector<std::unique_ptr<AnyValue>>&& children,
                                                Constraints constraints) const override;
  bool ScalarEquals(const IValueData* other) const override;
  void ShallowConvertFrom(const AnyValue& value) override;

private:
  T m_value;
};

template <typename T>
ScalarValueDataT<T>::ScalarValueDataT(T value, Constraints constraints)
  : ScalarValueDataBase{TypeToCode<T>::code, constraints}
  , m_value{value}
{}

template <typename T>
boolean ScalarValueDataT<T>::AsBoolean() const
{
  return ConvertScalar<boolean, T>(m_value);
}

template <typename T>
char8 ScalarValueDataT<T>::AsCharacter8() const
{
  return ConvertScalar<char8, T>(m_value);
}

template <typename T>
int8 ScalarValueDataT<T>::AsSignedInteger8() const
{
  return ConvertScalar<int8, T>(m_value);
}

template <typename T>
uint8 ScalarValueDataT<T>::AsUnsignedInteger8() const
{
  return ConvertScalar<uint8, T>(m_value);
}

template <typename T>
int16 ScalarValueDataT<T>::AsSignedInteger16() const
{
  return ConvertScalar<int16, T>(m_value);
}

template <typename T>
uint16 ScalarValueDataT<T>::AsUnsignedInteger16() const
{
  return ConvertScalar<uint16, T>(m_value);
}

template <typename T>
int32 ScalarValueDataT<T>::AsSignedInteger32() const
{
  return ConvertScalar<int32, T>(m_value);
}

template <typename T>
uint32 ScalarValueDataT<T>::AsUnsignedInteger32() const
{
  return ConvertScalar<uint32, T>(m_value);
}

template <typename T>
int64 ScalarValueDataT<T>::AsSignedInteger64() const
{
  return ConvertScalar<int64, T>(m_value);
}

template <typename T>
uint64 ScalarValueDataT<T>::AsUnsignedInteger64() const
{
  return ConvertScalar<uint64, T>(m_value);
}

template <typename T>
float32 ScalarValueDataT<T>::AsFloat32() const
{
  return ConvertScalar<float32, T>(m_value);
}

template <typename T>
float64 ScalarValueDataT<T>::AsFloat64() const
{
  return ConvertScalar<float64, T>(m_value);
}

template <typename T>
std::string ScalarValueDataT<T>::AsString() const
{
  return ConvertScalar<std::string, T>(m_value);
}

template <typename T>
std::unique_ptr<IValueData> ScalarValueDataT<T>::CloneFromChildren(
  std::vector<std::unique_ptr<AnyValue>>&& children, Constraints constraints) const
{
  if (!children.empty())
  {
    const std::string error =
      "ScalarValueDataT::CloneFromChildren(): Trying to clone scalar value with child values";
    throw InvalidOperationException(error);
  }
  return std::make_unique<ScalarValueDataT<T>>(m_value, constraints);
}

template <typename T>
bool ScalarValueDataT<T>::ScalarEquals(const IValueData* other) const
{
  try
  {
    auto mem_function = TypeToConversionFunc<T>::MemFunc;
    if (m_value == (other->*mem_function)())
    {
      return true;
    }
  }
  catch(const MessageException&)
  {
    return false;
  }
  return false;
}

template <typename T>
void ScalarValueDataT<T>::ShallowConvertFrom(const AnyValue& value)
{
  m_value = value.As<T>();
}

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_SCALAR_VALUE_DATA_H_
