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

#include "performance.h"

#include <sup/dto/anytype.h>
#include <sup/dto/anyvalue.h>
#include <sup/dto/anyvalue_helper.h>
#include <sup/dto/json_value_parser.h>

#include <ctime>
#include <iomanip>

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

JSONEncoder::JSONEncoder(const AnyValue& value)
  : m_value{value}
  , m_representation{}
{}

JSONEncoder::~JSONEncoder() = default;

void JSONEncoder::Encode()
{
  m_representation = AnyValueToJSONString(m_value);
}

void JSONEncoder::Decode()
{
  JSONAnyValueParser parser;
  parser.ParseString(m_representation);
}

std::size_t JSONEncoder::Size() const
{
  return m_representation.size();
}

BinaryEncoder::BinaryEncoder(const AnyValue& value)
  : m_value{value}
  , m_representation{}
{}

BinaryEncoder::~BinaryEncoder() = default;

void BinaryEncoder::Encode()
{
  m_representation = AnyValueToBinary(m_value);
}

void BinaryEncoder::Decode()
{
  auto decoded_val = AnyValueFromBinary(m_representation);
  (void)decoded_val;
}
std::size_t BinaryEncoder::Size() const
{
  return m_representation.size();
}

}  // namespace performance

}  // namespace dto

}  // namespace sup