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

#ifndef SUP_DTO_ANYVALUE_EXCEPTIONS_H_
#define SUP_DTO_ANYVALUE_EXCEPTIONS_H_

#include <exception>
#include <string>

namespace sup
{
namespace dto
{
  /**
 * @brief Base Exception class with message.
 */
class MessageException : public std::exception
{
public:
  explicit MessageException(std::string message);
  ~MessageException() override = default;
  MessageException(const MessageException& other) = default;
  MessageException(MessageException&& other) = default;
  MessageException& operator=(const MessageException& other) & = default;
  MessageException& operator=(MessageException&& other) & = default;

  const char* what() const noexcept override;
private:
  std::string m_message;
};

/**
 * @brief Exception thrown when trying to perform an invalid conversion.
 */
class InvalidConversionException : public MessageException
{
public:
  explicit InvalidConversionException(const std::string& message);
  ~InvalidConversionException() override = default;
  InvalidConversionException(const InvalidConversionException& other) = default;
  InvalidConversionException(InvalidConversionException&& other) = default;
  InvalidConversionException& operator=(const InvalidConversionException& other) & = default;
  InvalidConversionException& operator=(InvalidConversionException&& other) & = default;
};

/**
 * @brief Exception thrown when trying to call an operation that is not supported by the object.
 */
class InvalidOperationException : public MessageException
{
public:
  explicit InvalidOperationException(const std::string& message);
  ~InvalidOperationException() override = default;
  InvalidOperationException(const InvalidOperationException& other) = default;
  InvalidOperationException(InvalidOperationException&& other) = default;
  InvalidOperationException& operator=(const InvalidOperationException& other) & = default;
  InvalidOperationException& operator=(InvalidOperationException&& other) & = default;
};

/**
 * @brief Exception thrown when serializing an object failed.
 */
class SerializeException : public MessageException
{
public:
  explicit SerializeException(const std::string& message);
  ~SerializeException() override = default;
  SerializeException(const SerializeException& other) = default;
  SerializeException(SerializeException&& other) = default;
  SerializeException& operator=(const SerializeException& other) & = default;
  SerializeException& operator=(SerializeException&& other) & = default;
};

/**
 * @brief Exception thrown when parsing to an object failed.
 */
class ParseException : public MessageException
{
public:
  explicit ParseException(const std::string& message);
  ~ParseException() override = default;
  ParseException(const ParseException& other) = default;
  ParseException(ParseException&& other) = default;
  ParseException& operator=(const ParseException& other) & = default;
  ParseException& operator=(ParseException&& other) & = default;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ANYVALUE_EXCEPTIONS_H_
