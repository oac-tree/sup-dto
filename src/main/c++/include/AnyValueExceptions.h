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
 * @file AnyValueExceptions.h
 * @brief Header file for AnyValue Exceptions.
 * @date 04/01/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definitions of the AnyValue Exception classes.
 */

#ifndef _SUP_AnyValueExceptions_h_
#define _SUP_AnyValueExceptions_h_

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
 * @brief Exception thrown when trying to create a duplicate key.
 */
class DuplicateKeyException : public MessageException
{
public:
  DuplicateKeyException(const std::string& message);
};

/**
 * @brief Exception thrown when using a key that's not allowed.
 */
class KeyNotAllowedException : public MessageException
{
public:
  KeyNotAllowedException(const std::string& message);
};

/**
 * @brief Exception thrown when trying to access an element with an empty key.
 */
class EmptyKeyException : public MessageException
{
public:
  EmptyKeyException(const std::string& message);
};

/**
 * @brief Exception thrown when trying to access an element with unknown key.
 */
class UnknownKeyException : public MessageException
{
public:
  UnknownKeyException(const std::string& message);
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_AnyValueExceptions_h_
