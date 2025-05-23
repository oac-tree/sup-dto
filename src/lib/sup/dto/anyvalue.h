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

#ifndef SUP_DTO_ANYVALUE_H_
#define SUP_DTO_ANYVALUE_H_

#include <sup/dto/anytype.h>

#include <sup/dto/anyvalue_exceptions.h>
#include <sup/dto/basic_scalar_types.h>

#include <cstring>
#include <initializer_list>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace sup
{
namespace dto
{
class IValueData;
enum class Constraints : sup::dto::uint32;

/**
 * @brief Class for structured data transfer objects.
 */
class AnyValue
{
public:
  /**
   * @brief Default constructor creates empty value.
   */
  AnyValue() noexcept;

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
   * Delete constructors to prevent implicit conversion from pointers to boolean, or nullptr to
   * const char*.
  */
  AnyValue(std::nullptr_t) = delete;
  template <typename T> AnyValue(T*) = delete;

  /**
   * @brief Constructor with type and value specification.
   *
   * @param anytype type specification.
   * @param anyvalue value specification.
   *
   * @throws InvalidConversionException Thrown when the given AnyValue cannot be properly converted
   * to an AnyValue of the given AnyType.
   *
   * @note This constructor performs possible conversion of scalar types.
   */
  AnyValue(const AnyType& anytype, const AnyValue& anyvalue);

  /**
   * @brief Constructor for structures.
   *
   * @param members list of member names and values.
   * @param type_name Name for the underlying structured type.
   *
   * @throws InvalidOperationException Thrown when the given arguments do not allow the construction
   * of a structured value (e.g. empty value as member).
   */
  AnyValue(std::initializer_list<std::pair<std::string, AnyValue>> members,
           const std::string& type_name);

  /**
   * @brief Constructor for structures with empty type name.
   *
   * @param members list of member names and values.
   *
   * @throws InvalidOperationException Thrown when the given arguments do not allow the construction
   * of a structured value (e.g. empty value as member).
   */
  AnyValue(std::initializer_list<std::pair<std::string, AnyValue>> members);

  /**
   * @brief Constructor for arrays.
   *
   * @param size number of elements in the array.
   * @param elem_type type of the elements in the array.
   * @param name Name for the type.
   *
   * @throws InvalidOperationException Thrown when the given arguments do not allow the construction
   * of an array value (e.g. empty type as element type).
   */
  AnyValue(std::size_t size, const AnyType& elem_type, const std::string& name);

  /**
   * @brief Constructor for arrays with empty type name.
   *
   * @param size number of elements in the array.
   * @param elem_type type of the elements in the array.
   *
   * @throws InvalidOperationException Thrown when the given arguments do not allow the construction
   * of an array value (e.g. empty type as element type).
   */
  AnyValue(std::size_t size, const AnyType& elem_type);

  /**
   * @brief Copy constructor.
   *
   * @param other Source AnyValue for copy construction.
   */
  AnyValue(const AnyValue& other);

  /**
   * @brief Move constructor.
   *
   * @param other Source AnyValue for move construction.
   */
  AnyValue(AnyValue&& other) noexcept;

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
  AnyValue& operator=(const AnyValue& other) &;

  /**
   * @brief Move assignment.
   *
   * @param other Source AnyValue for move assignment.
   *
   * @return Reference to this.
   *
   * @throws InvalidConversionException Thrown when the given AnyValue cannot be properly converted
   * to this AnyValue (only possible when conversions are required, meaning the types are not
   * compatible).
   */
  AnyValue& operator=(AnyValue&& other) &;

  /**
   * @brief Try to convert from other AnyValue without changing the underlying type.
   *
   * @note This operation could leave this AnyValue in a partially updated state if the execution
   * throws. However, the object is always in a consistent state.
   *
   * @param other Source AnyValue for conversion.
   *
   * @throws InvalidConversionException Thrown when the given AnyValue cannot be properly converted
   * to this AnyValue (only possible when conversions are required, meaning the types are not
   * compatible).
   */
  void ConvertFrom(const AnyValue& other);

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
   * @brief Query if this value is scalar (not empty, struct or array).
   *
   * @return true when this value is scalar.
   */
  bool IsScalar() const;

  /**
   * @brief Add member value.
   *
   * @note AnyValue is passed by value (see Scott Meyers Effective Modern C++ Item 41: consider
   * pass by value for copyable parameters that are cheap to move and always copied)
   *
   * @param name Name to use for registering the member value.
   * @param value AnyValue to register as a member value.
   *
   * @return Reference to this.
   *
   * @throws InvalidOperationException Thrown when this value does not support adding members or
   * when the given arguments are not allowed (e.g. empty member name).
   */
  AnyValue& AddMember(const std::string& name, AnyValue value) &;

  /**
   * @brief Add member value.
   *
   * @note AnyValue is passed by value (see Scott Meyers Effective Modern C++ Item 41: consider
   * pass by value for copyable parameters that are cheap to move and always copied)
   *
   * @param name Name to use for registering the member value.
   * @param value AnyValue to register as a member value.
   *
   * @return Rvalue of this.
   *
   * @throws InvalidOperationException Thrown when this value does not support adding members or
   * when the given arguments are not allowed (e.g. empty member name).
   */
  AnyValue&& AddMember(const std::string& name, AnyValue value) &&;

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
   * @brief Add an element to the end of an array.
   *
   * @param value AnyValue to add at the end of the array.
   *
   * @return Reference to this.
   *
   * @throws InvalidOperationException Thrown when this value does not support adding elements or
   * when the given value is not allowed (e.g. wrong type).
   */
  AnyValue& AddElement(const AnyValue& value) &;

  /**
   * @brief Return number of elements in the array type.
   *
   * @return Number of elements in the array type or zero if not supported.
   */
  std::size_t NumberOfElements() const;

  /**
   * @brief Return the type of the elements of an array.
   *
   * @return AnyType of the array's elements.
   * @throws InvalidOperationException when the current AnyValue is not an array.
   */
  AnyType ElementType() const;

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
   * @brief Cast to given Ctype structure.
   *
   * @return This value as a T value when successful.
   *
   * @throws InvalidConversionException Thrown when this value could not be converted to T.
   * @throws SerializeException Thrown when this value could not be serialized to T.
   */
  template <typename T>
  T ToCType() const;

  /**
   * @brief Cast to given Ctype structure.
   *
   * @param value Reference to value to copy this value into.
   *
   * @return true on success.
   *
   * @note Does not throw on invalid conversions.
   */
  template <typename T>
  bool ToCType(T& value) const;

  /**
   * @brief Checks if this value has a (nested) subvalue with the given field name.
   *
   * @param fieldname Field name of the subvalue to check.
   *
   * @return true if a subvalue with the given name exists.
   *
   * @note This method handles both (nested) array elements and structure members.
   * @note Doesn't throw when the type doesn't support members, but returns false.
   */
  bool HasField(const std::string& fieldname) const;

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

  /**
   * @brief Get number of child values. This is mostly used to be able to visit an AnyValue tree
   * structure.
   *
   * @return Number of child values.
   */
  std::size_t NumberOfChildren() const;

  /**
   * @brief Get the child value for the given index. This is mostly used to be able to visit an
   * AnyValue tree.
   *
   * @param idx Index of the child value.
   * @return Child value for the given index.
   * @throws InvalidOperationException if no child value for the given index exists.
   */
  AnyValue* GetChildValue(std::size_t idx);
  const AnyValue* GetChildValue(std::size_t idx) const;

private:
  static std::unique_ptr<AnyValue> MakeAnyValue(
    const AnyType& anytype, std::vector<std::unique_ptr<AnyValue>>&& children,
    Constraints constraints);
  static std::unique_ptr<AnyValue> MakeStructAnyValue(
    const AnyType& anytype, std::vector<std::unique_ptr<AnyValue>>&& children,
    Constraints constraints);
  static std::unique_ptr<AnyValue> MakeArrayAnyValue(
    const AnyType& anytype, std::vector<std::unique_ptr<AnyValue>>&& children,
    Constraints constraints);
  static std::unique_ptr<AnyValue> MakeScalarAnyValue(const AnyType& anytype,
                                                      Constraints constraints);
  static std::unique_ptr<AnyValue> MakeEmptyAnyValue(Constraints constraints);
  explicit AnyValue(std::unique_ptr<IValueData>&& data);
  AnyValue(const AnyValue& other, Constraints constraints);
  AnyValue(const AnyType& anytype, Constraints constraints);
  bool HasChild(const std::string& child_name) const;
  const AnyValue* GetChildValue(const std::string& child_name) const;
  std::unique_ptr<AnyValue> CloneFromChildren(std::vector<std::unique_ptr<AnyValue>>&& children,
                                              Constraints constraints) const;
  // Equality function that disregards child values
  bool ShallowEquals(const AnyValue& other) const;
  void ShallowConvertFrom(const AnyValue& other);
  std::unique_ptr<IValueData> m_data;
};

  /**
   * @brief Constructs an empty structure.
   *
   * @param type_name Name for the underlying structured type.
   *
   * @return AnyValue with empty structure type.
   */
AnyValue EmptyStruct(const std::string& type_name);

  /**
   * @brief Constructs an empty structure with empty type name.
   *
   * @return AnyValue with empty structure type.
   */
AnyValue EmptyStruct();

  /**
   * @brief Constructs a bounded array value.
   *
   * @param elements list of element values.
   * @param type_name Name for the underlying structured type.
   *
   * @return Constructed array value.
   *
   * @note The type of the first element in the list determines the element type of
   * the array.
   */
AnyValue ArrayValue(std::initializer_list<AnyValue> elements, const std::string& type_name);

  /**
   * @brief Constructs a bounded array value with empty type name.
   *
   * @param elements list of element values.
   *
   * @return Constructed array value.
   *
   * @note The type of the first element in the list determines the element type of
   * the array.
   */
AnyValue ArrayValue(std::initializer_list<AnyValue> elements);

bool IsEmptyValue(const AnyValue& anyvalue);
bool IsStructValue(const AnyValue& anyvalue);
bool IsArrayValue(const AnyValue& anyvalue);
bool IsScalarValue(const AnyValue& anyvalue);

/**
 * @brief Splits a possibly nested fieldname for an AnyValue into its component names.
 *
 * @param fieldname Full fieldname.
 * @return List of component names.
 *
 * @throws InvalidOperationException Thrown when the fieldname cannot be properly parsed.
 *
 * @note Optional dots '.' after the square brackets will be removed too.
 *
 * @code {.cpp}
 * auto names_1 = SplitAnyValueFieldname("[2]subfieldname");   // returns {"[2]", "subfieldname"}
 * auto names_2 = SplitAnyValueFieldname("[2].subfieldname");  // idem
 * auto names_3 = SplitAnyValueFieldname("[oops]");           // throws InvalidOperationException
 * @endcode
 */
std::deque<std::string> SplitAnyValueFieldname(const std::string& fieldname);

/**
 * @brief Serialize an AnyValue to an array of bytes.
 * @deprecated Use `AnyValueToBinary` instead.
 *
 * @param anyvalue AnyValue object to serialize.
 *
 * @throws SerializeException Thrown when the AnyValue cannot be correctly serialized into a byte
 * array (e.g. string field too long or unknown scalar type).
 *
 * @note This serialization was used to cast to C-type structures.
 */
std::vector<uint8> ToBytes(const AnyValue& anyvalue);

/**
 * @brief Parse AnyValue content from an array of bytes.
 * @deprecated Use `AnyValueFromBinary` instead.
 *
 * @param anyvalue AnyValue object to assign to.
 * @param bytes Array of bytes.
 * @param total_size Size of the array of bytes.
 *
 * @throws ParseException Thrown when the byte array cannot be correctly parsed (e.g. sizes
 * don't match, absence of null terminator in C-style string or unknown scalar type).
 *
 * @note This method was used to cast from C-type structures.
 */
void FromBytes(AnyValue& anyvalue, const uint8* bytes, std::size_t total_size);

template <typename T>
T AnyValue::ToCType() const
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
  catch(const MessageException&)
  {
    return false;
  }
}

template <typename T>
bool AnyValue::ToCType(T& value) const
{
  try
  {
    value = ToCType<T>();
    return true;
  }
  catch(const MessageException&)
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
  catch(const MessageException&)
  {
    return false;
  }
}

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ANYVALUE_H_
