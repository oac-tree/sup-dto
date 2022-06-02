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

#include "json_performance.h"

#include <sup/dto/anytype.h>
#include <sup/dto/anyvalue.h>

#include <algorithm>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

namespace sup
{
namespace dto
{
namespace performance
{

void PrintDateTime()
{
  auto now = std::chrono::system_clock::now();
  auto t = std::chrono::system_clock::to_time_t(now);
  std::cout << "Performance tests ("
            << std::put_time(std::localtime(&t), "%FT%TZ") << ")" << std::endl;
  std::cout << "========================================" << std::endl;
  std::cout << std::endl;
}

AnyType CreateScalarMix_Type()
{
  AnyType scalar_mix_t({
    {"a", BooleanType},
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
    {"m", StringType}
  }, "scalar_mix_t");
  return scalar_mix_t;
}
AnyType CreateScalarMixArray_Type()
{
  auto scalar_mix_t = CreateScalarMix_Type();
  AnyType scalar_mix_array_t(120, scalar_mix_t, "scalar_mix_array_t");
  return scalar_mix_array_t;
}

AnyType CreateSystemConfigs_Type()
{
  auto scalar_mix_array_t = CreateScalarMixArray_Type();
  AnyType system_configs_t({
    {"description", StringType},
    {"system_01", scalar_mix_array_t},
    {"system_02", scalar_mix_array_t},
    {"system_03", scalar_mix_array_t},
    {"system_04", scalar_mix_array_t},
    {"system_05", scalar_mix_array_t},
    {"system_06", scalar_mix_array_t},
    {"enabled", BooleanType}
  }, "system_configs_t");
  return system_configs_t;
}

AnyType CreateFullConfig_Type()
{
  auto system_configs_t = CreateSystemConfigs_Type();
  AnyType full_config_t(16, system_configs_t, "full_config_t");
  return full_config_t;
}

AnyType CreateManyFullConfig_t_Type()
{
  auto full_config_t = CreateFullConfig_Type();
  AnyType many_full_config_t(20, full_config_t, "many_full_config_t");
  return many_full_config_t;
}

void MeasureSerializeParse(const AnyType& anytype)
{
  std::cout << "Test JSON serialize/parse performance" << std::endl;
  std::cout << "*************************************" << std::endl;
  AnyValue value(anytype);
  auto start = std::chrono::system_clock::now();
  auto json_string = AnyValueToJSONString(value);
  auto json_size = json_string.size();
  std::cout << "JSON string size: " << json_size << std::endl;
  auto parsed = AnyValueFromJSONString(json_string);
  auto one_cycle = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now() - start).count();
  if (one_cycle < 1)
  {
    one_cycle = 1;
  }
  unsigned N = std::min(1000L, 5000 / one_cycle);  // max 5s
  N = std::max(N, 3u);  // at least 3 iterations
  std::chrono::nanoseconds serialize_duration{0};
  std::chrono::nanoseconds parse_duration{0};
  for (unsigned i=0; i<N; ++i)
  {
    auto start = std::chrono::system_clock::now();
    json_string = AnyValueToJSONString(value);
    auto middle = std::chrono::system_clock::now();
    serialize_duration += middle - start;
    parsed = AnyValueFromJSONString(json_string);
    parse_duration += std::chrono::system_clock::now() - middle;
  }
  auto serialize_duration_ms =
      std::chrono::duration_cast<std::chrono::milliseconds>(serialize_duration).count();
  auto parse_duration_ms =
      std::chrono::duration_cast<std::chrono::milliseconds>(parse_duration).count();
  std::cout << "Results for " << N << " iterations:" << std::endl;
  std::cout << "  Total serialize time (ms) : " << serialize_duration_ms << std::endl;
  std::cout << "  Total parse time (ms)     : " << parse_duration_ms << std::endl;
  auto mean_serialize_ms = (double)serialize_duration_ms / N;
  auto mean_parse_ms = (double)parse_duration_ms / N;
  std::cout << "  Mean serialize time (ms) : " << mean_serialize_ms << std::endl;
  std::cout << "  Mean parse time (ms)     : " << mean_parse_ms << std::endl;
  auto serialize_bytes_per_s = (1000.0 / mean_serialize_ms) * json_size;
  auto parse_bytes_per_s = (1000.0 / mean_parse_ms) * json_size;
  std::cout << "  Mean bytes/s (serialize) : " << serialize_bytes_per_s << std::endl;
  std::cout << "  Mean bytes/s (parse)     : " << parse_bytes_per_s << std::endl;
  std::cout << std::endl;
}

}  // namespace performance

}  // namespace dto

}  // namespace sup