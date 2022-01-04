/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : SUP - Sequencer
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
 * @brief Exception thrown when trying to create a duplicate key.
 */
class DuplicateKeyException : public std::exception
{
public:
  DuplicateKeyException(std::string message);
  const char* what() const noexcept override;
private:
  std::string message;
};

/**
 * @brief Exception thrown when trying to create a key that's not allowed.
 */
class KeyNotAllowedException : public std::exception
{
public:
  KeyNotAllowedException(std::string message);
  const char* what() const noexcept override;
private:
  std::string message;
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_AnyValueExceptions_h_
