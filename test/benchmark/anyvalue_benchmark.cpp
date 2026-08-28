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

#include <sup/dto/anyvalue.h>

#include <benchmark/benchmark.h>

namespace sup
{
namespace dto
{
namespace test
{

namespace
{

// Copy constructor. Measures creating and destroying the copy.
void BM_CopyAnyValue(benchmark::State& state, Shape shape)
{
  const auto& anyvalue = GetValue(shape);
  for ([[maybe_unused]] auto loop_state : state)
  {
    AnyValue copy{anyvalue};
    benchmark::DoNotOptimize(copy);
    benchmark::ClobberMemory();
  }
}

// Compares equal instances on purpose: the worst case, since operator!= walks the whole tree.
void BM_CompareAnyValue(benchmark::State& state, Shape shape)
{
  const auto& anyvalue = GetValue(shape);
  const AnyValue copy{anyvalue};
  for ([[maybe_unused]] auto loop_state : state)
  {
    benchmark::DoNotOptimize(copy != anyvalue);
  }
}

BENCHMARK_CAPTURE(BM_CopyAnyValue, ScalarMix, Shape::kScalarMix)->Unit(benchmark::kMicrosecond);
BENCHMARK_CAPTURE(BM_CopyAnyValue, ScalarMixArray, Shape::kScalarMixArray)
    ->Unit(benchmark::kMicrosecond);
BENCHMARK_CAPTURE(BM_CopyAnyValue, SystemConfigs, Shape::kSystemConfigs)
    ->Unit(benchmark::kMicrosecond);
BENCHMARK_CAPTURE(BM_CopyAnyValue, FullConfig, Shape::kFullConfig)->Unit(benchmark::kMicrosecond);
BENCHMARK_CAPTURE(BM_CopyAnyValue, ManyFullConfig, Shape::kManyFullConfig)
    ->Unit(benchmark::kMicrosecond);

BENCHMARK_CAPTURE(BM_CompareAnyValue, ScalarMix, Shape::kScalarMix)->Unit(benchmark::kMicrosecond);
BENCHMARK_CAPTURE(BM_CompareAnyValue, ScalarMixArray, Shape::kScalarMixArray)
    ->Unit(benchmark::kMicrosecond);
BENCHMARK_CAPTURE(BM_CompareAnyValue, SystemConfigs, Shape::kSystemConfigs)
    ->Unit(benchmark::kMicrosecond);
BENCHMARK_CAPTURE(BM_CompareAnyValue, FullConfig, Shape::kFullConfig)
    ->Unit(benchmark::kMicrosecond);
BENCHMARK_CAPTURE(BM_CompareAnyValue, ManyFullConfig, Shape::kManyFullConfig)
    ->Unit(benchmark::kMicrosecond);

}  // namespace

}  // namespace test

}  // namespace dto

}  // namespace sup
