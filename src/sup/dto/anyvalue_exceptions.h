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
  MessageException(std::string message);
  const char* what() const noexcept override;
private:
  std::string message;
};

/**
 * @brief Exception thrown when trying to perform an invalid conversion.
 */
class InvalidConversionException : public MessageException
{
public:
  InvalidConversionException(const std::string& message);
};

/**
 * @brief Exception thrown when trying to call an operation that is not supported by the object.
 */
class InvalidOperationException : public MessageException
{
public:
  InvalidOperationException(const std::string& message);
};

/**
 * @brief Exception thrown when serializing an object failed.
 */
class SerializeException : public MessageException
{
public:
  SerializeException(const std::string& message);
};

/**
 * @brief Exception thrown when parsing to an object failed.
 */
class ParseException : public MessageException
{
public:
  ParseException(const std::string& message);
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ANYVALUE_EXCEPTIONS_H_
