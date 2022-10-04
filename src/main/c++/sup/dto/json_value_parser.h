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

#ifndef SUP_DTO_JSON_VALUE_PARSER_H_
#define SUP_DTO_JSON_VALUE_PARSER_H_

#include <memory>

namespace sup
{
namespace dto
{
class AnyValue;
class AnyTypeRegistry;

class JSONAnyValueParser
{
public:
  JSONAnyValueParser();
  ~JSONAnyValueParser();

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
   * @brief Return the parsed AnyValue with move semantics.
   *
   * @return Parsed AnyValue, or empty value if nothing was parsed.
   */
  AnyValue MoveAnyValue();

private:
  std::unique_ptr<AnyValue> m_anyvalue;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_JSON_VALUE_PARSER_H_
