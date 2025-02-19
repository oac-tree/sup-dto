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
 * Copyright (c) : 2010-2025 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
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

MessageException::~MessageException() = default;

const char* MessageException::what() const noexcept
{
  return m_message.c_str();
}

InvalidConversionException::InvalidConversionException(const std::string& message)
  : MessageException{message}
{}

InvalidConversionException::~InvalidConversionException() = default;

InvalidOperationException::InvalidOperationException(const std::string& message)
  : MessageException{message}
{}

InvalidOperationException::~InvalidOperationException() = default;

SerializeException::SerializeException(const std::string& message)
  : MessageException{message}
{}

SerializeException::~SerializeException() = default;

ParseException::ParseException(const std::string& message)
  : MessageException{message}
{}

ParseException::~ParseException() = default;

}  // namespace dto

}  // namespace sup
