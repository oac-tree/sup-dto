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

#include <map>

namespace sup
{
namespace dto
{
namespace test
{

namespace
{

AnyType CreateScalarMixType()
{
  return AnyType({{"a", BooleanType},
                  {"b", Character8Type},
                  {"c", SignedInteger8Type},
                  {"d", UnsignedInteger8Type},
                  {"e", SignedInteger16Type},
                  {"f", UnsignedInteger16Type},
                  {"g", SignedInteger32Type},
                  {"h", UnsignedInteger32Type},
                  {"i", SignedInteger64Type},
                  {"j", UnsignedInteger64Type},
                  {"k", Float32Type},
                  {"l", Float64Type},
                  {"m", StringType}},
                 "scalar_mix_t");
}

AnyType CreateScalarMixArrayType()
{
  return AnyType(120, CreateScalarMixType(), "scalar_mix_array_t");
}

AnyType CreateSystemConfigsType()
{
  auto scalar_mix_array_t = CreateScalarMixArrayType();
  return AnyType({{"description", StringType},
                  {"system_01", scalar_mix_array_t},
                  {"system_02", scalar_mix_array_t},
                  {"system_03", scalar_mix_array_t},
                  {"system_04", scalar_mix_array_t},
                  {"system_05", scalar_mix_array_t},
                  {"system_06", scalar_mix_array_t},
                  {"enabled", BooleanType}},
                 "system_configs_t");
}

AnyType CreateFullConfigType()
{
  return AnyType(16, CreateSystemConfigsType(), "full_config_t");
}

AnyType CreateManyFullConfigType()
{
  return AnyType(20, CreateFullConfigType(), "many_full_config_t");
}

AnyType CreateType(Shape shape)
{
  switch (shape)
  {
  case Shape::kScalarMix:
    return CreateScalarMixType();
  case Shape::kScalarMixArray:
    return CreateScalarMixArrayType();
  case Shape::kSystemConfigs:
    return CreateSystemConfigsType();
  case Shape::kFullConfig:
    return CreateFullConfigType();
  case Shape::kManyFullConfig:
    return CreateManyFullConfigType();
  }
  return {};
}

// Lazy per shape, so a filtered run over the small shapes never builds the largest one. Google
// Benchmark runs these single threaded, hence no synchronisation.
template <typename T, typename Factory>
const T& GetCached(Shape shape, Factory factory)
{
  static std::map<Shape, T> cache;
  auto it = cache.find(shape);
  if (it == cache.end())
  {
    it = cache.emplace(shape, factory(shape)).first;
  }
  return it->second;
}

}  // namespace

const AnyType& GetType(Shape shape)
{
  return GetCached<AnyType>(shape, [](Shape s) { return CreateType(s); });
}

const AnyValue& GetValue(Shape shape)
{
  return GetCached<AnyValue>(shape, [](Shape s) { return AnyValue{GetType(s)}; });
}

const std::string& GetJSON(Shape shape)
{
  return GetCached<std::string>(shape, [](Shape s) { return AnyValueToJSONString(GetValue(s)); });
}

const std::vector<uint8>& GetBinary(Shape shape)
{
  return GetCached<std::vector<uint8>>(shape,
                                       [](Shape s) { return AnyValueToBinary(GetValue(s)); });
}

}  // namespace test

}  // namespace dto

}  // namespace sup
