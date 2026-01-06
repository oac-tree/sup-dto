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
 * Copyright (c) : 2010-2026 ITER Organization,
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

#include <sup/dto/anyvalue_exceptions.h>

namespace sup
{
namespace dto
{

MessageException::MessageException(std::string message)
  : std::exception(), m_message{std::move(message)}
{}

const char* MessageException::what() const noexcept
{
  return m_message.c_str();
}

InvalidConversionException::InvalidConversionException(const std::string& message)
  : MessageException{message}
{}

InvalidOperationException::InvalidOperationException(const std::string& message)
  : MessageException{message}
{}

SerializeException::SerializeException(const std::string& message)
  : MessageException{message}
{}

ParseException::ParseException(const std::string& message)
  : MessageException{message}
{}

}  // namespace dto

}  // namespace sup
