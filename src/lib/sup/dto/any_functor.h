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

#ifndef SUP_DTO_ANY_FUNCTOR_H_
#define SUP_DTO_ANY_FUNCTOR_H_

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
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ANY_FUNCTOR_H_
