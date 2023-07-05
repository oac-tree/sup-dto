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

#ifndef SUP_DTO_SCALAR_VALUE_DATA_H_
#define SUP_DTO_SCALAR_VALUE_DATA_H_

#include <sup/dto/anyvalue/scalar_conversion.h>
#include <sup/dto/anyvalue/scalar_value_data_base.h>

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
struct TypeToCode<char8>
{
  static constexpr TypeCode code = TypeCode::Char8;
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

template <>
struct TypeToCode<int16>
{
  static constexpr TypeCode code = TypeCode::Int16;
};

template <>
struct TypeToCode<uint16>
{
  static constexpr TypeCode code = TypeCode::UInt16;
};

template <>
struct TypeToCode<int32>
{
  static constexpr TypeCode code = TypeCode::Int32;
};

template <>
struct TypeToCode<uint32>
{
  static constexpr TypeCode code = TypeCode::UInt32;
};

template <>
struct TypeToCode<int64>
{
  static constexpr TypeCode code = TypeCode::Int64;
};

template <>
struct TypeToCode<uint64>
{
  static constexpr TypeCode code = TypeCode::UInt64;
};

template <>
struct TypeToCode<float32>
{
  static constexpr TypeCode code = TypeCode::Float32;
};

template <>
struct TypeToCode<float64>
{
  static constexpr TypeCode code = TypeCode::Float64;
};

template <>
struct TypeToCode<std::string>
{
  static constexpr TypeCode code = TypeCode::String;
};

template <typename T>
class ScalarValueDataT : public ScalarValueDataBase
{
public:
  ScalarValueDataT(T value = {});
  ~ScalarValueDataT() override = default;

  ScalarValueDataT<T>* Clone() const override;

  void Assign(const AnyValue& value) override;

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

  bool Equals(const AnyValue& other) const override;

private:
  T m_value;
};

template <typename T>
ScalarValueDataT<T>::ScalarValueDataT(T value)
  : ScalarValueDataBase{TypeToCode<T>::code}
  , m_value{value}
{}

template <typename T>
ScalarValueDataT<T>* ScalarValueDataT<T>::Clone() const
{
  return new ScalarValueDataT<T>(m_value);
}

template <typename T>
void ScalarValueDataT<T>::Assign(const AnyValue& value)
{
  m_value = value.As<T>();
}

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
bool ScalarValueDataT<T>::Equals(const AnyValue& other) const
{
  if (!IsScalarValue(other))
  {
    return false;
  }
  try
  {
    if (m_value == other.As<T>())
    {
      return true;
    }
  }
  catch(const InvalidConversionException&)
  {
    return false;
  }
  return false;
}


}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_SCALAR_VALUE_DATA_H_
