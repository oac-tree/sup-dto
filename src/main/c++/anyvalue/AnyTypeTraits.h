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
 * @file AnyTypeTraits.h
 * @brief Header file for AnyTypeTraits.
 * @date 03/01/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the AnyTypeTraits class templates.
 */

#ifndef _SUP_AnyTypeTraits_h_
#define _SUP_AnyTypeTraits_h_

#include "AnyType.h"

#include <type_traits>

namespace sup
{
namespace dto
{

/**
 * @brief Type trait indicating a scalar type.
 */
template<TypeCode t>
struct IsScalar : std::false_type
{};

template<>
struct IsScalar<TypeCode::Int8> : std::true_type
{};

template<>
struct IsScalar<TypeCode::UInt8> : std::true_type
{};

/**
 * @brief Variable template for IsScalar<>.
 */
template<TypeCode t>
constexpr bool IsScalar_v = IsScalar<t>::value;

}  // namespace dto

}  // namespace sup

#endif  // _SUP_AnyTypeTraits_h_
