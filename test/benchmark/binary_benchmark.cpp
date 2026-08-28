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

// Serialization into a byte vector, allocated anew on every iteration.
void BM_SerializeBinary(benchmark::State& state, Shape shape)
{
  const auto& anyvalue = GetValue(shape);
  const auto bytes = static_cast<std::int64_t>(GetBinary(shape).size());
  for ([[maybe_unused]] auto loop_state : state)
  {
    auto representation = AnyValueToBinary(anyvalue);
    benchmark::DoNotOptimize(representation);
  }
  state.SetBytesProcessed(bytes * state.iterations());
}

// Parsing. AnyValueFromBinary returns the decoded value, so creating and destroying it is measured
// too. BM_ParseJSON does not do that, so the two parse figures are not directly comparable.
void BM_ParseBinary(benchmark::State& state, Shape shape)
{
  const auto& representation = GetBinary(shape);
  for ([[maybe_unused]] auto loop_state : state)
  {
    auto decoded = AnyValueFromBinary(representation);
    benchmark::DoNotOptimize(decoded);
  }
  state.SetBytesProcessed(static_cast<std::int64_t>(representation.size()) * state.iterations());
}

BENCHMARK_CAPTURE(BM_SerializeBinary, ScalarMix, Shape::kScalarMix)->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(BM_SerializeBinary, ScalarMixArray, Shape::kScalarMixArray)
    ->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(BM_SerializeBinary, SystemConfigs, Shape::kSystemConfigs)
    ->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(BM_SerializeBinary, FullConfig, Shape::kFullConfig)
    ->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(BM_SerializeBinary, ManyFullConfig, Shape::kManyFullConfig)
    ->Unit(benchmark::kMillisecond);

BENCHMARK_CAPTURE(BM_ParseBinary, ScalarMix, Shape::kScalarMix)->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(BM_ParseBinary, ScalarMixArray, Shape::kScalarMixArray)
    ->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(BM_ParseBinary, SystemConfigs, Shape::kSystemConfigs)
    ->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(BM_ParseBinary, FullConfig, Shape::kFullConfig)->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(BM_ParseBinary, ManyFullConfig, Shape::kManyFullConfig)
    ->Unit(benchmark::kMillisecond);

}  // namespace

}  // namespace test

}  // namespace dto

}  // namespace sup
