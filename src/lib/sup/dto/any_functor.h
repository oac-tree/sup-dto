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

#ifndef SUP_DTO_ANY_FUNCTOR_H_
#define SUP_DTO_ANY_FUNCTOR_H_

#include <mutex>

namespace sup
{
namespace dto
{
class AnyValue;

/**
 * @brief The AnyFunctor interface is used to model a function object with AnyValue input/output.
 */
class AnyFunctor
{
public:
  virtual ~AnyFunctor();
  /**
   * @brief Call the function object.
   *
   * @param input an AnyValue input parameter.
   * @return The output of the function object call.
   */
  virtual sup::dto::AnyValue operator()(const sup::dto::AnyValue& input) = 0;

protected:
  AnyFunctor() = default;

  AnyFunctor(const AnyFunctor&) = default;
  AnyFunctor& operator=(const AnyFunctor&) = default;
  AnyFunctor(AnyFunctor&&) = default;
  AnyFunctor& operator=(AnyFunctor&&) = default;
};

/**
 * @brief AnyFunctor decorator that effectively serializes concurrent calls to the call operator.
 */
class ThreadsafeAnyFunctorDecorator : public AnyFunctor
{
public:
  explicit ThreadsafeAnyFunctorDecorator(AnyFunctor& functor);
  ~ThreadsafeAnyFunctorDecorator() override;

  ThreadsafeAnyFunctorDecorator(const ThreadsafeAnyFunctorDecorator&) = delete;
  ThreadsafeAnyFunctorDecorator& operator=(const ThreadsafeAnyFunctorDecorator&) = delete;
  ThreadsafeAnyFunctorDecorator(ThreadsafeAnyFunctorDecorator&&) = default;
  ThreadsafeAnyFunctorDecorator& operator=(ThreadsafeAnyFunctorDecorator&&) = default;

  /**
   * @brief Call the underlying functor while holding a lock.
   */
  sup::dto::AnyValue operator()(const sup::dto::AnyValue& input) override;
private:
  AnyFunctor& m_functor;
  std::mutex m_mtx;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ANY_FUNCTOR_H_
