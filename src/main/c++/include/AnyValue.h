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
 * Copyright (c) : 2010-2021 ITER Organization,
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
 * @file AnyValue.h
 * @brief Header file for AnyValue.
 * @date 26/12/2021
 * @author Walter Van Herck (IO)
 * @copyright 2010-2021 ITER Organization
 * @details This header file contains the definition of the AnyValue class.
 */

#ifndef _SUP_AnyValue_h_
#define _SUP_AnyValue_h_

#include "AnyType.h"

#include "AnyValueExceptions.h"
#include "BasicScalarTypes.h"

#include <initializer_list>
#include <memory>
#include <string>
#include <utility>

namespace sup
{
namespace dto
{
class IValueData;

/**
 * @brief Class for structured data transfer objects.
 */
class AnyValue
{
public:
  /**
   * @brief Default constructor creates empty value.
   */
  AnyValue();

  /**
   * @brief Constructor with type specification.
   *
   * @param anytype type specification.
   * @note This constructor default initializes all its leaf values.
   */
  explicit AnyValue(AnyType anytype);

  /**
   * @brief Copy constructor.
   */
  AnyValue(const AnyValue& other);

  /**
   * @brief Copy assignment.
   */
  AnyValue& operator=(const AnyValue& other);

  /**
   * @brief Move constructor.
   */
  AnyValue(AnyValue&& other);

  /**
   * @brief Move assignment.
   */
  AnyValue& operator=(AnyValue&& other);

  /**
   * @brief Destructor.
   */
  ~AnyValue();

  /**
   * @brief Get type code.
   */
  TypeCode GetTypeCode() const;

  /**
   * @brief Get type specification.
   */
  AnyType GetType() const;

  /**
   * @brief Get type name.
   */
  std::string GetTypeName() const;

  /**
   * @brief Cast to given type.
   *
   * @note Throws when conversion is not supported.
   */
  template <typename T>
  T As() const;

  /**
   * @brief Cast to given type.
   *
   * @return true on success.
   * @note Does not throw on invalid conversions.
   */
  template <typename T>
  bool As(T& value) const;

  /**
   * @brief Index operators.
   *
   * @details Retrieves the embedded AnyValue by following the fields in fieldname, seperated
   * by '[index]' and '.'.
   * @code
     // Get value of first message from a structure with field 'messages', which is an array of messages:
     auto message_value = my_value["messages[0]"]
     @endcode
   */
  AnyValue& operator[](std::string fieldname);
  const AnyValue& operator[](std::string fieldname) const;

  /**
   * @brief Comparison operators.
   */
  bool operator==(const AnyValue& other) const;
  bool operator!=(const AnyValue& other) const;

private:
  std::unique_ptr<IValueData> data;
};

template <typename T>
T AnyValue::As() const
{
  throw InvalidConversionException("Conversion not supported");
}

template <>
boolean AnyValue::As<boolean>() const;

template <>
int8 AnyValue::As<int8>() const;

template <>
uint8 AnyValue::As<uint8>() const;

template <typename T>
bool AnyValue::As(T& value) const
{
  try
  {
    value = As<T>();
    return true;
  }
  catch(const InvalidConversionException& e)
  {
    return false;
  }
}

bool IsEmptyValue(const AnyValue& anyvalue);
bool IsStructValue(const AnyValue& anyvalue);
bool IsArrayValue(const AnyValue& anyvalue);
bool IsScalarValue(const AnyValue& anyvalue);

}  // namespace dto

}  // namespace sup

#endif  // _SUP_AnyValue_h_
