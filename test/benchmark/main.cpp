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

#include <sys/utsname.h>

#include <benchmark/benchmark.h>

#include <iostream>
#include <string_view>

namespace
{

// Google Benchmark reports the CPU and its caches, but not the host, so the committed output
// cannot otherwise be attributed to a machine.
void PrintMachineSpecs()
{
  utsname sys_info{};
  uname(&sys_info);
  std::cout << "--------------------------------------------------------------------------------\n"
               "Performance tests on system:\n"
            << "sysname: " << std::string_view(sys_info.sysname) << "\n"
            << "nodename: " << std::string_view(sys_info.nodename) << "\n"
            << "release: " << std::string_view(sys_info.release) << "\n"
            << "version: " << std::string_view(sys_info.version) << "\n"
            << "machine: " << std::string_view(sys_info.machine) << "\n"
               "--------------------------------------------------------------------------------\n";
}

}  // namespace

int main(int argc, char** argv)
{
  PrintMachineSpecs();
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
  benchmark::Shutdown();
  return 0;
}
