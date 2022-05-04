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

#ifndef _SUP_AnyValue_h_
#define _SUP_AnyValue_h_

#include "AnyType.h"

#include "AnyValueExceptions.h"
#include "AnyValueHelper.h"
#include "BasicScalarTypes.h"

#include <cstring>
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
   *
   * @note This constructor default initializes all its leaf values.
   */
  explicit AnyValue(const AnyType& anytype);

  /**
   * @brief Constructor from scalar value.
   *
   * @param val scalar value.
   *
   * @note These constructors must be implicit for other constructors to work as expected.
   */
  AnyValue(boolean val);
  AnyValue(char8 val);
  AnyValue(int8 val);
  AnyValue(uint8 val);
  AnyValue(int16 val);
  AnyValue(uint16 val);
  AnyValue(int32 val);
  AnyValue(uint32 val);
  AnyValue(int64 val);
  AnyValue(uint64 val);
  AnyValue(float32 val);
  AnyValue(float64 val);
  AnyValue(const std::string& val);
  AnyValue(const char* val);

  /**
   * @brief Constructor with type and value specification.
   *
   * @param anytype type specification.
   * @param anyvalue value specification.
   *
   * @note This constructor performs possible conversion of scalar types.
   */
  AnyValue(const AnyType& anytype, const AnyValue& anyvalue);

  /**
   * @brief Constructor for structures.
   *
   * @param members list of member names and values.
   * @param type_name Optional name for the underlying structured type.
   *
   * @throws InvalidOperationException Thrown when the given arguments do not allow the construction
   * of a structured value (e.g. empty value as member).
   */
  AnyValue(std::initializer_list<std::pair<std::string, AnyValue>> members,
          const std::string& type_name = {});

  /**
   * @brief Constructor for arrays.
   *
   * @param size number of elements in the array.
   * @param elem_type type of the elements in the array.
   * @param name Optional name for the type.
   *
   * @throws InvalidOperationException Thrown when the given arguments do not allow the construction
   * of an array value (e.g. empty type as element type).
   */
  AnyValue(std::size_t size, const AnyType& elem_type, const std::string& name = {});

  /**
   * @brief Constructor for unbounded arrays.
   *
   * @param tag tag to indicate unbounded array.
   * @param elem_type type of the elements in the array.
   * @param name Optional name for the type.
   *
   * @throws InvalidOperationException Thrown when the given arguments do not allow the construction
   * of an unbounded array value (e.g. empty type as element type).
   */
  AnyValue(AnyType::UnboundedArrayTag tag, const AnyType& elem_type, const std::string& name = {});

  /**
   * @brief Copy constructor.
   *
   * @param other Source AnyValue for copy construction.
   */
  AnyValue(const AnyValue& other);

  /**
   * @brief Copy assignment.
   *
   * @param other Source AnyValue for copy assignment.
   *
   * @return Reference to this.
   *
   * @throws InvalidConversionException Thrown when the given AnyValue cannot be properly converted
   * to this AnyValue.
   */
  AnyValue& operator=(const AnyValue& other);

  /**
   * @brief Move constructor.
   *
   * @param other Source AnyValue for move construction.
   */
  AnyValue(AnyValue&& other);

  /**
   * @brief Move assignment.
   *
   * @param other Source AnyValue for move assignment.
   *
   * @return Reference to this.
   *
   * @throws InvalidConversionException Thrown when the given AnyValue cannot be properly converted
   * to this AnyValue (only possible when conversions are required, meaning the types are not
   * exactly equal).
   */
  AnyValue& operator=(AnyValue&& other);

  /**
   * @brief Destructor.
   */
  ~AnyValue();

  /**
   * @brief Get type code.
   *
   * @return Type code of this value.
   */
  TypeCode GetTypeCode() const;

  /**
   * @brief Get type specification.
   *
   * @return AnyType associated with this value.
   */
  AnyType GetType() const;

  /**
   * @brief Get type name.
   *
   * @return Type name of this value.
   */
  std::string GetTypeName() const;

  /**
   * @brief Add member value.
   *
   * @param name Name to use for registering the member value.
   * @param value AnyValue to register as a member value.
   *
   * @return Reference to this.
   *
   * @throws InvalidOperationException Thrown when this value does not support adding members or
   * when the given arguments are not allowed (e.g. empty member name).
   */
  AnyValue& AddMember(const std::string& name, const AnyValue& value);

  /**
   * @brief Checks if this value has a member with the given name.
   *
   * @param name Name of the member to check.
   *
   * @return true if a member with the given name exists.
   *
   * @note Doesn't throw when the type doesn't support members, but returns false.
   */
  bool HasMember(const std::string& name) const;

  /**
   * @brief Get list of member names.
   *
   * @return List of member names.
   *
   * @note Returns empty list when type doesn't support member types.
   */
  std::vector<std::string> MemberNames() const;

  /**
   * @brief Return number of member values.
   *
   * @return Number of member values or zero if member values are not supported.
   */
  std::size_t NumberOfMembers() const;

  /**
   * @brief Append an element to an unbounded array.
   *
   * @param value AnyValue to append at the end of the array.
   *
   * @return Reference to this.
   *
   * @throws InvalidOperationException Thrown when this value does not support appending elements or
   * when the given value is not allowed (e.g. wrong type).
   */
  AnyValue& Append(const AnyValue& value);

  /**
   * @brief Return number of elements in the array type.
   *
   * @return Number of elements in the array type or zero if not supported.
   */
  std::size_t NumberOfElements() const;

  /**
   * @brief Cast to given type.
   *
   * @return This value as a T value when successful.
   *
   * @throws InvalidConversionException Thrown when this value could not be converted to T.
   * @throws SerializeException Thrown when this value could not be serialized to T.
   */
  template <typename T>
  T As() const;

  /**
   * @brief Cast to given type.
   *
   * @param value Reference to value to copy this value into.
   *
   * @return true on success.
   *
   * @note Does not throw on invalid conversions.
   */
  template <typename T>
  bool As(T& value) const;

  /**
   * @brief Index operators.
   *
   * @param fieldname Name of the field to access (see details).
   *
   * @return Reference to found subvalue.
   *
   * @throws InvalidOperationException Thrown when indexed access is not supported for this value
   * or when the given fieldname didn't lead to an existing subvalue.
   *
   * @details Retrieves the embedded AnyValue by following the fields in fieldname, seperated
   * by '[index]' and '.'.
   * @code
     // Get value of first message from a structure with field 'messages', which is an array of messages:
     auto message_value = my_value["messages[0]"]
     @endcode
   */
  AnyValue& operator[](const std::string& fieldname);
  const AnyValue& operator[](const std::string& fieldname) const;

  /**
   * @brief Retrieves the embedded AnyValue by numeric index.
   *
   * @param idx index of the element to access.

   * @return Element at index idx.
   *
   * @throws InvalidOperationException Thrown when indexed access is not supported for this value
   * or when the given fieldname didn't lead to an existing subvalue.
   */
  AnyValue& operator[](std::size_t idx);
  const AnyValue& operator[](std::size_t idx) const;

  /**
   * @brief Comparison operators.
   *
   * @param other AnyValue to compare this value to.
   *
   * @return true when the values are exactly equal, including possible subvalues.
   */
  bool operator==(const AnyValue& other) const;
  bool operator!=(const AnyValue& other) const;

private:
  std::unique_ptr<IValueData> data;
};

template <typename T>
T AnyValue::As() const
{
  auto byte_array = ToBytes(*this);
  if (byte_array.size() != sizeof(T))
  {
    throw SerializeException("Serialization to C-type: size mismatch");
  }
  T result;
  std::memcpy(&result, byte_array.data(), sizeof(T));
  return result;
}

template <>
AnyValue AnyValue::As<AnyValue>() const;

template <>
boolean AnyValue::As<boolean>() const;

template <>
char8 AnyValue::As<char8>() const;

template <>
int8 AnyValue::As<int8>() const;

template <>
uint8 AnyValue::As<uint8>() const;

template <>
int16 AnyValue::As<int16>() const;

template <>
uint16 AnyValue::As<uint16>() const;

template <>
int32 AnyValue::As<int32>() const;

template <>
uint32 AnyValue::As<uint32>() const;

template <>
int64 AnyValue::As<int64>() const;

template <>
uint64 AnyValue::As<uint64>() const;

template <>
float32 AnyValue::As<float32>() const;

template <>
float64 AnyValue::As<float64>() const;

template <>
std::string AnyValue::As<std::string>() const;

template <typename T>
bool AnyValue::As(T& value) const
{
  try
  {
    value = As<T>();
    return true;
  }
  catch(const InvalidConversionException&)
  {
    return false;
  }
  catch(const SerializeException&)
  {
    return false;
  }
}

  /**
   * @brief Assigns to an AnyValue using a plain C type.
   *
   * @param anyvalue AnyValue to assign to.
   * @param object C type source object.
   *
   * @throws ParseException Thrown when the source object cannot be correctly parsed into the
   * existing structure of the AnyValue.
   *
   * @note The source object needs be a packed structure of values that correspond to the structure
   * of the AnyValue object.
   */
template <typename T>
void AssignFromCType(AnyValue& anyvalue, const T& object)
{
  FromBytes(anyvalue, reinterpret_cast<const uint8*>(&object), sizeof(T));
}

  /**
   * @brief Non-throwing version of AssignFromCType.
   *
   * @param anyvalue AnyValue to assign to.
   * @param object C type source object.
   *
   * @return true on success, false otherwise.
   */
template <typename T>
bool SafeAssignFromCType(AnyValue& anyvalue, const T& object)
{
  try
  {
    AssignFromCType(anyvalue, object);
    return true;
  }
  catch(const ParseException&)
  {
    return false;
  }
}

  /**
   * @brief Constructs an empty structure.
   *
   * @param type_name Optional name for the underlying structured type.
   *
   * @return AnyValue with empty structure type.
   */
AnyValue EmptyStruct(const std::string& type_name = {});

  /**
   * @brief Constructs a bounded array value.
   *
   * @param elements list of element values.
   * @param type_name Optional name for the underlying structured type.
   *
   * @return Constructed array value.
   *
   * @note The type of the first element in the list determines the element type of
   * the array.
   */
AnyValue ArrayValue(std::initializer_list<AnyValue> elements, const std::string& type_name = {});

  /**
   * @brief Constructs an unbounded array value.
   *
   * @param elements list of element values.
   * @param type_name Optional name for the underlying structured type.
   *
   * @return Constructed unbounded array value.
   *
   * @note The type of the first element in the list determines the element type of
   * the array.
   */
AnyValue UnboundedArrayValue(std::initializer_list<AnyValue> elements,
                             const std::string& type_name = {});

bool IsEmptyValue(const AnyValue& anyvalue);
bool IsStructValue(const AnyValue& anyvalue);
bool IsArrayValue(const AnyValue& anyvalue);
bool IsUnboundedArrayValue(const AnyValue& anyvalue);
bool IsScalarValue(const AnyValue& anyvalue);

}  // namespace dto

}  // namespace sup

#endif  // _SUP_AnyValue_h_
