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

namespace sup
{
namespace dto
{
enum class TypeCode
{
  Empty,
  Struct,
  Array,
  Int8,
  UInt8
};

const std::string EMPTY_TYPE_NAME = "empty";
const std::string INT8_TYPE_NAME = "int8";
const std::string UINT8_TYPE_NAME = "uint8";

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
   */
  AnyType& operator=(const AnyType& other);

  /**
   * @brief Move constructor.
   */
  AnyType(AnyType&& other);

  /**
   * @brief Move assignment.
   */
  AnyType& operator=(AnyType&& other);

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
extern const AnyType SignedInteger8;
extern const AnyType UnsignedInteger8;

}  // namespace dto

}  // namespace sup

#endif  // _SUP_AnyType_h_
