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

#ifndef SUP_DTO_PERFORMANCE_H_
#define SUP_DTO_PERFORMANCE_H_

#include <sup/dto/anyvalue.h>
#include <sup/dto/basic_scalar_types.h>

#include <chrono>
#include <iostream>
#include <vector>

namespace sup
{
namespace dto
{
namespace performance
{
using TestFunction = std::function<void(const AnyType&)>;

void RunTestFunction(TestFunction func);

void PrintDateTime();
AnyType CreateScalarMix_Type();
AnyType CreateScalarMixArray_Type();
AnyType CreateSystemConfigs_Type();
AnyType CreateFullConfig_Type();
AnyType CreateManyFullConfig_t_Type();

class JSONEncoder
{
public:
  JSONEncoder(const AnyValue& value);
  ~JSONEncoder();

  void Encode();
  void Decode();
  std::size_t Size() const;

private:
  const AnyValue& m_value;
  std::string m_representation;
};

class BinaryEncoder
{
public:
  BinaryEncoder(const AnyValue& value);
  ~BinaryEncoder();

  void Encode();
  void Decode();
  std::size_t Size() const;

private:
  const AnyValue& m_value;
  std::vector<sup::dto::uint8> m_representation;
};

template <typename Encoder>
void MeasureEncoderWithValue(const AnyType& anytype)
{
  AnyValue anyvalue{anytype};
  Encoder encoder(anyvalue);
  auto start = std::chrono::system_clock::now();
  encoder.Encode();
  auto representation_size = encoder.Size();
  std::cout << "Encoded size: " << representation_size << std::endl;
  encoder.Decode();
  auto one_cycle = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now() - start).count();
  if (one_cycle < 1)
  {
    one_cycle = 1;
  }
  unsigned N = std::min(1000u, static_cast<unsigned>(5000 / one_cycle));  // max 5s
  N = std::max(N, 3u);  // at least 3 iterations
  std::chrono::nanoseconds serialize_duration{0};
  std::chrono::nanoseconds parse_duration{0};
  for (unsigned i=0; i<N; ++i)
  {
    auto start = std::chrono::system_clock::now();
    encoder.Encode();
    auto middle = std::chrono::system_clock::now();
    encoder.Decode();
    parse_duration += std::chrono::system_clock::now() - middle;
    serialize_duration += middle - start;
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
  auto serialize_bytes_per_s = (1000.0 / mean_serialize_ms) * representation_size;
  auto parse_bytes_per_s = (1000.0 / mean_parse_ms) * representation_size;
  std::cout << "  Mean bytes/s (serialize) : " << serialize_bytes_per_s << std::endl;
  std::cout << "  Mean bytes/s (parse)     : " << parse_bytes_per_s << std::endl;
  std::cout << std::endl;
}

void MeasureCopyAnyType(const AnyType& anytype);

void MeasureCopyAnyValue(const AnyType& anytype);

}  // namespace performance

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_PERFORMANCE_H_
