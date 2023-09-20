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
 * Copyright (c) : 2010-2023 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#ifndef SUP_DTO_JSON_VALUE_PARSER_H_
#define SUP_DTO_JSON_VALUE_PARSER_H_

#include <sup/dto/anyvalue.h>

#include <memory>

namespace sup
{
namespace dto
{
class AnyTypeRegistry;

class JSONAnyValueParser
{
public:
  JSONAnyValueParser();
  ~JSONAnyValueParser();

  JSONAnyValueParser(const JSONAnyValueParser& other) = delete;
  JSONAnyValueParser(JSONAnyValueParser&& other) = delete;
  JSONAnyValueParser& operator=(const JSONAnyValueParser& other) = delete;
  JSONAnyValueParser& operator=(JSONAnyValueParser&& other) = delete;

  /**
   * @brief Parse an AnyValue from a JSON string.
   *
   * @param json_str JSON string.
   * @param anytype_registry AnyType registry to use during parsing (default: nullptr).
   *
   * @return true on successful parsing, false otherwise.
   */
  bool ParseString(const std::string& json_str, const AnyTypeRegistry* type_registry = nullptr);

  /**
   * @brief Parse an AnyValue from a JSON file.
   *
   * @param filename name of the file containing the JSON representation.
   * @param anytype_registry AnyType registry to use during parsing (default: nullptr).
   *
   * @return true on successful parsing, false otherwise.
   */
  bool ParseFile(const std::string& filename, const AnyTypeRegistry* type_registry = nullptr);

  /**
   * @brief Parse an AnyValue with given type from a JSON string.
   *
   * @param anytype Type to use for resulting value.
   * @param json_str JSON string.
   *
   * @return true on successful parsing, false otherwise.
   */
  bool TypedParseString(const AnyType& anytype, const std::string& json_str);

  /**
   * @brief Parse an AnyValue with given type from a JSON file.
   *
   * @param anytype Type to use for resulting value.
   * @param filename name of the file containing the JSON representation.
   *
   * @return true on successful parsing, false otherwise.
   */
  bool TypedParseFile(const AnyType& anytype, const std::string& filename);

  /**
   * @brief Return the parsed AnyValue with move semantics.
   *
   * @return Parsed AnyValue, or empty value if nothing was parsed.
   */
  AnyValue MoveAnyValue();

private:
  AnyValue m_anyvalue;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_JSON_VALUE_PARSER_H_
