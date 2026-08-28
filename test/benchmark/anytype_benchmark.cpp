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

#include <sup/dto/anytype.h>

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
void BM_CopyAnyType(benchmark::State& state, Shape shape)
{
  const auto& anytype = GetType(shape);
  for ([[maybe_unused]] auto loop_state : state)
  {
    AnyType copy{anytype};
    benchmark::DoNotOptimize(copy);
    benchmark::ClobberMemory();
  }
}

// Compares equal instances on purpose: the worst case, since operator!= walks the whole tree.
void BM_CompareAnyType(benchmark::State& state, Shape shape)
{
  const auto& anytype = GetType(shape);
  const AnyType copy{anytype};
  for ([[maybe_unused]] auto loop_state : state)
  {
    benchmark::DoNotOptimize(copy != anytype);
  }
}

BENCHMARK_CAPTURE(BM_CopyAnyType, ScalarMix, Shape::kScalarMix)->Unit(benchmark::kMicrosecond);
BENCHMARK_CAPTURE(BM_CopyAnyType, ScalarMixArray, Shape::kScalarMixArray)
    ->Unit(benchmark::kMicrosecond);
BENCHMARK_CAPTURE(BM_CopyAnyType, SystemConfigs, Shape::kSystemConfigs)
    ->Unit(benchmark::kMicrosecond);
BENCHMARK_CAPTURE(BM_CopyAnyType, FullConfig, Shape::kFullConfig)->Unit(benchmark::kMicrosecond);
BENCHMARK_CAPTURE(BM_CopyAnyType, ManyFullConfig, Shape::kManyFullConfig)
    ->Unit(benchmark::kMicrosecond);

BENCHMARK_CAPTURE(BM_CompareAnyType, ScalarMix, Shape::kScalarMix)->Unit(benchmark::kMicrosecond);
BENCHMARK_CAPTURE(BM_CompareAnyType, ScalarMixArray, Shape::kScalarMixArray)
    ->Unit(benchmark::kMicrosecond);
BENCHMARK_CAPTURE(BM_CompareAnyType, SystemConfigs, Shape::kSystemConfigs)
    ->Unit(benchmark::kMicrosecond);
BENCHMARK_CAPTURE(BM_CompareAnyType, FullConfig, Shape::kFullConfig)->Unit(benchmark::kMicrosecond);
BENCHMARK_CAPTURE(BM_CompareAnyType, ManyFullConfig, Shape::kManyFullConfig)
    ->Unit(benchmark::kMicrosecond);

}  // namespace

}  // namespace test

}  // namespace dto

}  // namespace sup
