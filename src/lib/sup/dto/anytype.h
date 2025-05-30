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

#ifndef SUP_DTO_ANYTYPE_H_
#define SUP_DTO_ANYTYPE_H_

#include <sup/dto/basic_scalar_types.h>

#include <deque>
#include <functional>
#include <initializer_list>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace sup
{
namespace dto
{
/**
 * @brief Enumeration indicating the different types of nodes for AnyType.
 */
enum class TypeCode : sup::dto::uint32
{
  Empty = 0,
  Bool,
  Char8,
  Int8,
  UInt8,
  Int16,
  UInt16,
  Int32,
  UInt32,
  Int64,
  UInt64,
  Float32,
  Float64,
  String,
  Struct,
  Array
};

const std::string kEmptyTypeName = "empty";
const std::string kBooleanTypeName = "bool";
const std::string kChar8TypeName = "char8";
const std::string kInt8TypeName = "int8";
const std::string kUInt8TypeName = "uint8";
const std::string kInt16TypeName = "int16";
const std::string kUInt16TypeName = "uint16";
const std::string kInt32TypeName = "int32";
const std::string kUInt32TypeName = "uint32";
const std::string kInt64TypeName = "int64";
const std::string kUInt64TypeName = "uint64";
const std::string kFloat32TypeName = "float32";
const std::string kFloat64TypeName = "float64";
const std::string kStringTypeName = "string";

class ITypeData;
class AnyValue;

/**
 * @brief Class for structured data transfer object types.
 */
class AnyType
{
public:
  /**
   * @brief Default constructor creates empty type.
   */
  AnyType() noexcept;

  /**
   * @brief Constructor with typecode. Only for scalar types.
   *
   * @param type_code typecode.
   *
   * @throws InvalidOperationException Thrown when the given TypeCode does not correspond to a known
   * scalar type.
   */
  explicit AnyType(TypeCode type_code);

  /**
   * @brief Constructor for structure types.
   *
   * @param members list of member names and types.
   * @param name Optional name for the type.
   *
   * @throws InvalidOperationException Thrown when the given arguments do not allow the construction
   * of a valid structure type (e.g. duplicate or invalid member names).
   */
  AnyType(std::initializer_list<std::pair<std::string, AnyType>> members, const std::string& name);

  /**
   * @brief Constructor for structure types with empty name.
   *
   * @param members list of member names and types.
   *
   * @throws InvalidOperationException Thrown when the given arguments do not allow the construction
   * of a valid structure type (e.g. duplicate or invalid member names).
   */
  AnyType(std::initializer_list<std::pair<std::string, AnyType>> members);

  /**
   * @brief Constructor for array types.
   *
   * @param size number of elements in the array.
   * @param elem_type type of the elements in the array.
   * @param name Optional name for the type.
   */
  AnyType(std::size_t size, AnyType elem_type, const std::string& name);

  /**
   * @brief Constructor for array types with empty name.
   *
   * @param size number of elements in the array.
   * @param elem_type type of the elements in the array.
   */
  AnyType(std::size_t size, AnyType elem_type);

  /**
   * @brief Construct type from given value.
   *
   * @param anyvalue AnyValue whose type to construct.
   */
  explicit AnyType(const AnyValue& anyvalue);

  /**
   * @brief Copy constructor.
   *
   * @param other Source AnyType for copy construction.
   */
  AnyType(const AnyType& other);

  /**
   * @brief Move constructor.
   *
   * @param other Source AnyType for move construction.
   */
  AnyType(AnyType&& other) noexcept;

  /**
   * @brief Copy assignment.
   *
   * @param other Source AnyType for copy assignment.
   *
   * @return Reference to this.
   *
   * @note Always succeeds and overwrites the currently held type.
   */
  AnyType& operator=(const AnyType& other) &;

  /**
   * @brief Move assignment.
   *
   * @param other Source AnyType for move assignment.
   *
   * @return Reference to this.
   *
   * @note Always succeeds and overwrites the currently held type.
   */
  AnyType& operator=(AnyType&& other) & noexcept;

  /**
   * @brief Destructor.
   */
  ~AnyType();

  /**
   * @brief Get type code.
   *
   * @return Type code of this type.
   */
  TypeCode GetTypeCode() const;

  /**
   * @brief Get type name.
   *
   * @return Type name of this type.
   */
  std::string GetTypeName() const;

  /**
   * @brief Query if this type is scalar (not empty, struct or array).
   *
   * @return true when this type is scalar.
   */
  bool IsScalar() const;

  /**
   * @brief Add member type.
   *
   * @note AnyType is passed by value (see Scott Meyers Effective Modern C++ Item 41: consider
   * pass by value for copyable parameters that are cheap to move and always copied)
   *
   * @param name Name to use for registering the member type.
   * @param type AnyType to register as a member type.
   *
   * @return Reference to this.
   *
   * @throws InvalidOperationException Thrown when this type does not support adding members or when
   * the given arguments are not allowed (e.g. empty member name).
   */
  AnyType& AddMember(const std::string& name, AnyType type) &;

  /**
   * @brief Add member type.
   *
   * @note AnyType is passed by value (see Scott Meyers Effective Modern C++ Item 41: consider
   * pass by value for copyable parameters that are cheap to move and always copied)
   *
   * @param name Name to use for registering the member type.
   * @param type AnyType to register as a member type.
   *
   * @return rvalue of this.
   *
   * @throws InvalidOperationException Thrown when this type does not support adding members or when
   * the given arguments are not allowed (e.g. empty member name).
   */
  AnyType&& AddMember(const std::string& name, AnyType type) &&;

  /**
   * @brief Get list of member names.
   *
   * @return List of member names.
   *
   * @note Returns empty list when type doesn't support member types.
   */
  std::vector<std::string> MemberNames() const;

  /**
   * @brief Return number of member types.
   *
   * @return Number of member types or zero if member types are not supported.
   */
  std::size_t NumberOfMembers() const;

  /**
   * @brief Return type of elements in the array type.
   *
   * @return Type of the elements in the array.
   *
   * @throws InvalidOperationException Thrown when this is not an array type.
   */
  AnyType ElementType() const;

  /**
   * @brief Return number of elements in the array type.
   *
   * @return Number of elements in the array type or zero if not supported.
   */
  std::size_t NumberOfElements() const;

  /**
   * @brief Checks if this type has a (nested) subtype with the given field name.
   *
   * @param fieldname Field name of the subtype to check.
   *
   * @return true if a subtype with the given name exists.
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
   * @return Reference to found subtype.
   *
   * @throws InvalidOperationException Thrown when indexed access is not supported for this type or
   * when the given fieldname didn't lead to an existing subtype.
   *
   * @details Retrieves the embedded AnyType by following the fields in fieldname, seperated
   * by '[]' and '.'. Note that the '[]' seperator does not allow for an index since the element
   * type of an array type must be independent of the element's index.
   * @code
     // Get type of messages from a structure with field 'messages', which is an array of messages:
     auto message_type = my_type["messages[]"]
     @endcode
   */
  AnyType& operator[](const std::string& fieldname);
  const AnyType& operator[](const std::string& fieldname) const;

  /**
   * @brief Comparison operators.
   *
   * @param other AnyType to compare this type to.
   *
   * @return true when the types are exactly equal, including possible subtypes.
   */
  bool operator==(const AnyType& other) const;
  bool operator!=(const AnyType& other) const;

  /**
   * @brief Get number of child types. This is mostly used to be able to visit an AnyType tree
   * structure.
   *
   * @return Number of child types.
   */
  std::size_t NumberOfChildren() const;

  /**
   * @brief Get the child type for the given index. This is mostly used to be able to visit an
   * AnyType tree.
   *
   * @param idx Index of the child type.
   * @return Child type for the given index.
   * @throws InvalidOperationException if no child type for the given index exists.
   */
  AnyType* GetChildType(std::size_t idx);
  const AnyType* GetChildType(std::size_t idx) const;

private:
  static std::unique_ptr<AnyType> MakeAnyType(
    const AnyValue& anyvalue, std::vector<std::unique_ptr<AnyType>>&& children);
  static std::unique_ptr<AnyType> MakeStructAnyType(
    const AnyValue& anyvalue, std::vector<std::unique_ptr<AnyType>>&& children);
  static std::unique_ptr<AnyType> MakeArrayAnyType(const AnyValue& anyvalue);
  static std::unique_ptr<AnyType> MakeScalarAnyType(const AnyValue& anyvalue);
  static std::unique_ptr<AnyType> MakeEmptyAnyType();
  explicit AnyType(std::unique_ptr<ITypeData>&& data);
  bool HasChild(const std::string& child_name) const;
  const AnyType* GetChildType(const std::string& child_name) const;
  std::unique_ptr<AnyType> CloneFromChildren(
    std::vector<std::unique_ptr<AnyType>>&& children) const;
  // Equality function that disregards child types
  bool ShallowEquals(const AnyType& other) const;
  std::unique_ptr<ITypeData> m_data;
};

/**
 * @brief Constructs an empty structured type.
 *
 * @param name Name for the underlying structured type.
 *
 * @return AnyType with structure type.
 */
AnyType EmptyStructType(const std::string& name);

/**
 * @brief Constructs an empty structured type with empty name.
 *
 * @return AnyType with structure type.
 */
AnyType EmptyStructType();

bool IsEmptyTypeCode(TypeCode type_code);
bool IsStructTypeCode(TypeCode type_code);
bool IsArrayTypeCode(TypeCode type_code);
bool IsScalarTypeCode(TypeCode type_code);

bool IsEmptyType(const AnyType& anytype);
bool IsStructType(const AnyType& anytype);
bool IsArrayType(const AnyType& anytype);
bool IsScalarType(const AnyType& anytype);

const std::vector<std::pair<TypeCode, std::string>>& ScalarTypeDefinitions();

using HeadTailFunction = std::function<std::pair<std::string, std::string>(const std::string&)>;
std::deque<std::string> SplitFieldname(const std::string& fieldname, HeadTailFunction func);

/**
 * @brief Splits a possibly nested fieldname for an AnyType into its component names.
 *
 * @param fieldname Full fieldname.
 * @return List of component names.
 *
 * @throws InvalidOperationException Thrown when the fieldname cannot be properly parsed.
 *
 * @note Optional dots '.' after the square brackets will be removed too.
 *
 * @code {.cpp}
 * auto names_1 = SplitAnyTypeFieldname("[]subfieldname");   // returns {"[]", "subfieldname"}
 * auto names_2 = SplitAnyTypeFieldname("[].subfieldname");  // idem
 * auto names_3 = SplitAnyTypeFieldname("[oops]");           // throws InvalidOperationException
 * @endcode
 */
std::deque<std::string> SplitAnyTypeFieldname(const std::string& fieldname);

#ifdef _WIN32
  #ifdef SUP_DTO_EXPORTS
    #define SUP_DTO_API __declspec(dllexport)
  #else
    #define SUP_DTO_API __declspec(dllimport)
  #endif
#else
  #define SUP_DTO_API
#endif

SUP_DTO_API extern const AnyType EmptyType;
SUP_DTO_API extern const AnyType BooleanType;
SUP_DTO_API extern const AnyType Character8Type;
SUP_DTO_API extern const AnyType SignedInteger8Type;
SUP_DTO_API extern const AnyType UnsignedInteger8Type;
SUP_DTO_API extern const AnyType SignedInteger16Type;
SUP_DTO_API extern const AnyType UnsignedInteger16Type;
SUP_DTO_API extern const AnyType SignedInteger32Type;
SUP_DTO_API extern const AnyType UnsignedInteger32Type;
SUP_DTO_API extern const AnyType SignedInteger64Type;
SUP_DTO_API extern const AnyType UnsignedInteger64Type;
SUP_DTO_API extern const AnyType Float32Type;
SUP_DTO_API extern const AnyType Float64Type;
SUP_DTO_API extern const AnyType StringType;

}  // namespace dto

}  // namespace sup

#if (__cplusplus <= 201402L)
namespace std
{
/**
 * @brief Related to defect report LWG 2148
*/
template <> struct hash<::sup::dto::TypeCode>
{
  size_t operator()(const ::sup::dto::TypeCode& val) const
  {
    return std::hash<::sup::dto::uint32>{}(static_cast<::sup::dto::uint32>(val));
  }
};
}
#endif

#endif  // SUP_DTO_ANYTYPE_H_
