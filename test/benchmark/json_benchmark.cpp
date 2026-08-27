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

#include "shape_fixtures.h"

#include <sup/dto/anyvalue_helper.h>
#include <sup/dto/json_value_parser.h>

#include <benchmark/benchmark.h>

#include <cstdint>

namespace sup
{
namespace dto
{
namespace test
{

namespace
{

// Serialization to a JSON string, non pretty printed, as measured by JSONEncoder::Encode.
void BM_SerializeJSON(benchmark::State& state, Shape shape)
{
  const auto& anyvalue = GetValue(shape);
  const auto bytes = static_cast<std::int64_t>(GetJSON(shape).size());
  for ([[maybe_unused]] auto loop_state : state)
  {
    auto json = AnyValueToJSONString(anyvalue);
    benchmark::DoNotOptimize(json);
  }
  state.SetBytesProcessed(bytes * state.iterations());
}

// Parsing of a JSON string. The parser is constructed inside the timed region and the parsed value
// is left in it, exactly as measured by JSONEncoder::Decode: the result is never moved out.
void BM_ParseJSON(benchmark::State& state, Shape shape)
{
  const auto& json = GetJSON(shape);
  for ([[maybe_unused]] auto loop_state : state)
  {
    JSONAnyValueParser parser;
    benchmark::DoNotOptimize(parser.ParseString(json));
  }
  state.SetBytesProcessed(static_cast<std::int64_t>(json.size()) * state.iterations());
}

BENCHMARK_CAPTURE(BM_SerializeJSON, ScalarMix, Shape::kScalarMix)->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(BM_SerializeJSON, ScalarMixArray, Shape::kScalarMixArray)
    ->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(BM_SerializeJSON, SystemConfigs, Shape::kSystemConfigs)
    ->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(BM_SerializeJSON, FullConfig, Shape::kFullConfig)->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(BM_SerializeJSON, ManyFullConfig, Shape::kManyFullConfig)
    ->Unit(benchmark::kMillisecond);

BENCHMARK_CAPTURE(BM_ParseJSON, ScalarMix, Shape::kScalarMix)->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(BM_ParseJSON, ScalarMixArray, Shape::kScalarMixArray)
    ->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(BM_ParseJSON, SystemConfigs, Shape::kSystemConfigs)
    ->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(BM_ParseJSON, FullConfig, Shape::kFullConfig)->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(BM_ParseJSON, ManyFullConfig, Shape::kManyFullConfig)
    ->Unit(benchmark::kMillisecond);

}  // namespace

}  // namespace test

}  // namespace dto

}  // namespace sup
