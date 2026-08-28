/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : SUP - DTO
 *
 * Description   : Performance test code
 *
 * Author        : Marcelo Mariano (External)
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

#ifndef SUP_DTO_SHAPE_FIXTURES_H_
#define SUP_DTO_SHAPE_FIXTURES_H_

#include <sup/dto/anytype.h>
#include <sup/dto/anyvalue.h>
#include <sup/dto/basic_scalar_types.h>

#include <string>
#include <vector>

namespace sup
{
namespace dto
{
namespace test
{

/**
 * @brief Nesting ladder of AnyType shapes measured by the benchmarks.
 *
 * Each shape contains the previous one, so the number of leaf nodes grows by roughly two orders
 * of magnitude per rung: 13, 1560, 9362, 149792, 2995840.
 */
enum class Shape
{
  kScalarMix,       //!< struct with one member per scalar type, "a".."m"
  kScalarMixArray,  //!< array of 120 scalar_mix_t
  kSystemConfigs,   //!< struct with a description, six scalar_mix_array_t and a boolean
  kFullConfig,      //!< array of 16 system_configs_t
  kManyFullConfig   //!< array of 20 full_config_t
};

/**
 * @brief Returns the AnyType of the given shape.
 *
 * @param shape the shape to build
 * @return reference to the cached AnyType
 *
 * @note Built on first use and cached for the lifetime of the process, so that building it is
 * never timed and never repeated per benchmark repetition.
 */
const AnyType& GetType(Shape shape);

/**
 * @brief Returns a default constructed AnyValue of the given shape.
 *
 * @param shape the shape to build
 * @return reference to the cached AnyValue
 */
const AnyValue& GetValue(Shape shape);

/**
 * @brief Returns the JSON representation of GetValue(shape).
 *
 * @param shape the shape to serialize
 * @return reference to the cached JSON string
 */
const std::string& GetJSON(Shape shape);

/**
 * @brief Returns the binary representation of GetValue(shape).
 *
 * @param shape the shape to serialize
 * @return reference to the cached binary representation
 */
const std::vector<uint8>& GetBinary(Shape shape);

}  // namespace test

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_SHAPE_FIXTURES_H_
