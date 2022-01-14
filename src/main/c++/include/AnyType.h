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
 * @file AnyType.h
 * @brief Header file for AnyType.
 * @date 03/01/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the AnyType class.
 */

#ifndef _SUP_AnyType_h_
#define _SUP_AnyType_h_

#include <initializer_list>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace sup
{
namespace dto
{
enum class TypeCode
{
  Empty,
  Struct,
  Array,
  Bool,
  Int8,
  UInt8,
  Int16,
  UInt16,
  Int32,
  UInt32,
  Int64,
  UInt64,
};

const std::string EMPTY_TYPE_NAME = "empty";
const std::string BOOLEAN_TYPE_NAME = "bool";
const std::string INT8_TYPE_NAME = "int8";
const std::string UINT8_TYPE_NAME = "uint8";
const std::string INT16_TYPE_NAME = "int16";
const std::string UINT16_TYPE_NAME = "uint16";
const std::string INT32_TYPE_NAME = "int32";
const std::string UINT32_TYPE_NAME = "uint32";
const std::string INT64_TYPE_NAME = "int64";
const std::string UINT64_TYPE_NAME = "uint64";

class ITypeData;

/**
 * @brief Class for structured data transfer object types.
 */
class AnyType
{
public:
  /**
   * @brief Default constructor creates empty type.
   */
  AnyType();

  /**
   * @brief Constructor with typecode. Only for scalar types.
   *
   * @param type_code typecode.
   */
  explicit AnyType(TypeCode type_code);

  /**
   * @brief Constructor for structures.
   *
   * @param members list of member names and types.
   * @param name Optional name for the type.
   */
  AnyType(std::initializer_list<std::pair<std::string, AnyType>> members,
          const std::string& name = {});

  /**
   * @brief Copy constructor.
   */
  AnyType(const AnyType& other);

  /**
   * @brief Copy assignment.
   *
   * @note Always succeeds and overwrites the currently hold type.
   */
  AnyType& operator=(const AnyType& other);

  /**
   * @brief Move constructor.
   */
  AnyType(AnyType&& other);

  /**
   * @brief Move assignment.
   *
   * @note Always succeeds and overwrites the currently hold type.
   */
  AnyType& operator=(AnyType&& other);

  /**
   * @brief Destructor.
   */
  ~AnyType();

  /**
   * @brief Get type code.
   */
  TypeCode GetTypeCode() const;

  /**
   * @brief Get type name.
   */
  std::string GetTypeName() const;

  /**
   * @brief Add member type.
   *
   * @param name Name to use for registering the member type.
   * @param type AnyType to register as a member type.
   * @note Only supported for structured types. Throws otherwise.
   * Also throws when member couldn't be added (e.g. invalid name).
   */
  void AddMember(const std::string& name, const AnyType& type);

  /**
   * @brief Checks if this type has a member with the given name.
   *
   * @param name Name of the member to check.
   * @return true if a member with the given name exists.
   * @note Doesn't throw when the type doesn't support members, but returns false.
   */
  bool HasMember(const std::string& name) const;

  /**
   * @brief Get list of member names.
   *
   * @return List of member names.
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
   * @brief Index operators.
   *
   * @details Retrieves the embedded AnyType by following the fields in fieldname, seperated
   * by '[]' and '.'. Note that the '[]' seperator does not allow for an index since the element
   * type of an array type must be independent of the element's index.
   * @code
     // Get type of messages from a structure with field 'messages', which is an array of messages:
     auto message_type = my_type["messages[]"]
     @endcode
   */
  AnyType& operator[](std::string fieldname);
  const AnyType& operator[](std::string fieldname) const;

  /**
   * @brief Comparison operators.
   */
  bool operator==(const AnyType& other) const;
  bool operator!=(const AnyType& other) const;

private:
  std::unique_ptr<ITypeData> data;
};

bool IsEmptyTypeCode(TypeCode type_code);
bool IsStructTypeCode(TypeCode type_code);
bool IsArrayTypeCode(TypeCode type_code);
bool IsScalarTypeCode(TypeCode type_code);

bool IsEmptyType(const AnyType& anytype);
bool IsStructType(const AnyType& anytype);
bool IsArrayType(const AnyType& anytype);
bool IsScalarType(const AnyType& anytype);

extern const AnyType EmptyType;
extern const AnyType Boolean;
extern const AnyType SignedInteger8;
extern const AnyType UnsignedInteger8;
extern const AnyType SignedInteger16;
extern const AnyType UnsignedInteger16;
extern const AnyType SignedInteger32;
extern const AnyType UnsignedInteger32;
extern const AnyType SignedInteger64;
extern const AnyType UnsignedInteger64;

}  // namespace dto

}  // namespace sup

#endif  // _SUP_AnyType_h_
