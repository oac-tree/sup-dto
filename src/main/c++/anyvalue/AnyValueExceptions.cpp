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

#include "AnyValueExceptions.h"

namespace sup
{
namespace dto
{

MessageException::MessageException(std::string message_)
  : message{std::move(message_)}
{}

const char* MessageException::what() const noexcept
{
  return message.c_str();
}

DuplicateKeyException::DuplicateKeyException(const std::string& message)
  : MessageException{message}
{}

KeyNotAllowedException::KeyNotAllowedException(const std::string& message)
  : MessageException{message}
{}

EmptyKeyException::EmptyKeyException(const std::string& message)
  : MessageException{message}
{}

UnknownKeyException::UnknownKeyException(const std::string& message)
  : MessageException{message}
{}

}  // namespace dto

}  // namespace sup
