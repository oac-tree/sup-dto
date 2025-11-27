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
 * SPDX-License-Identifier: MIT
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file LICENSE located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include <sup/dto/any_functor.h>

#include <sup/dto/anyvalue.h>

namespace sup
{
namespace dto
{

AnyFunctor::~AnyFunctor() = default;

ThreadsafeAnyFunctorDecorator::ThreadsafeAnyFunctorDecorator(AnyFunctor& functor)
  : m_functor{functor}
  , m_mtx{}
{}

ThreadsafeAnyFunctorDecorator::~ThreadsafeAnyFunctorDecorator() = default;

sup::dto::AnyValue ThreadsafeAnyFunctorDecorator::operator()(const sup::dto::AnyValue& input)
{
  std::lock_guard<std::mutex> lk{m_mtx};
  return m_functor(input);
}

}  // namespace dto

}  // namespace sup
