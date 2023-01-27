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

#include "scalar_value_data_t.h"

using namespace sup::dto;

//! @cond HIDDEN_FROM_DOXYGEN
constexpr TypeCode TypeToCode<boolean>::code;
constexpr TypeCode TypeToCode<char8>::code;
constexpr TypeCode TypeToCode<int8>::code;
constexpr TypeCode TypeToCode<uint8>::code;
constexpr TypeCode TypeToCode<int16>::code;
constexpr TypeCode TypeToCode<uint16>::code;
constexpr TypeCode TypeToCode<int32>::code;
constexpr TypeCode TypeToCode<uint32>::code;
constexpr TypeCode TypeToCode<int64>::code;
constexpr TypeCode TypeToCode<uint64>::code;
constexpr TypeCode TypeToCode<float32>::code;
constexpr TypeCode TypeToCode<float64>::code;
constexpr TypeCode TypeToCode<std::string>::code;
//! @endcond
