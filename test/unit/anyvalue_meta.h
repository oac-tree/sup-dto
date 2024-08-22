/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : SUP - DTO
 *
 * Description   : Unit test code
 *
 * Author        : Walter Van Herck (IO)
 *
 * Copyright (c) : 2010-2024 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#ifndef SUP_DTO_ANYVALUE_META_H_
#define SUP_DTO_ANYVALUE_META_H_

#include <sup/dto/anyvalue.h>


namespace sup
{
namespace dto
{
namespace internal
{
template<typename... Ts> struct make_void { typedef void type; };
template<typename... Ts> using void_t = typename make_void<Ts...>::type;
}  // namespace internal

template <typename T, typename = void>
struct IsValidAnyValueConstructorArgument : public std::false_type
{};

template <typename T>
struct IsValidAnyValueConstructorArgument<T,
  internal::void_t<decltype(AnyValue(std::declval<T>()))>> : public std::true_type
{};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ANYVALUE_META_H_
