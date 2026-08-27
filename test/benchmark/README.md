# Performance benchmarks for sup-dto

Google Benchmark based measurements of `AnyType` / `AnyValue` copy and comparison, and of the JSON
and binary serialization round trip. Covers the same cases as the hand-made harness in
`test/performance`, which is kept for reference.

## Dependency

Google Benchmark, found with `find_package(benchmark QUIET)` in `test/CMakeLists.txt`. When it is
absent the target is skipped and configuration prints
`Could NOT find Google Benchmark, skipping benchmark tests` — the rest of the test tree, the
hand-made harness included, is unaffected.

```bash
dnf install google-benchmark-devel                # or build it from source and pass
cmake -Dbenchmark_DIR=<prefix>/lib64/cmake/benchmark ..
```

## Measured shapes

Five nested `AnyType` shapes, copied verbatim from `test/performance/performance.cpp`. Each contains
the previous one, so the leaf count grows by roughly two orders of magnitude per rung.

| Shape | Definition | Leaves | JSON B | Binary B |
|---|---|---|---|---|
| `ScalarMix` | struct with one member per scalar type, `"a"`..`"m"` | 13 | 493 | 115 |
| `ScalarMixArray` | array of 120 `scalar_mix_t` | 1 560 | 11 145 | 5 493 |
| `SystemConfigs` | `description` + `system_01`..`06` + `enabled` | 9 362 | 66 866 | 33 060 |
| `FullConfig` | array of 16 `system_configs_t` | 149 792 | 1 029 906 | 519 108 |
| `ManyFullConfig` | array of 20 `full_config_t` | 2 995 840 | 20 546 500 | 10 369 339 |

The fixtures are built once per process and cached, so their construction is never part of a timed
region and is not repeated for each repetition.

## Running

```bash
taskset -c 2 ./test_bin/benchmark-tests \
      --benchmark_repetitions=5 --benchmark_display_aggregates_only=true \
      --benchmark_counters_tabular=true \
      --benchmark_out=benchmark-output.json --benchmark_out_format=json \
      2>&1 | tee benchmark.log
```

- **Repetitions.** Use at least 5 and compare medians. The noise floor on CODAC development
  hardware is 10 to 20 %.
- **Pinning.** `taskset` is not optional on a machine with heterogeneous cores: without it a run can
  migrate between performance and efficiency cores mid repetition. Pick a core from the fast group
  as reported by `lscpu -e=CPU,CORE,MAXMHZ`.
- **Never measure a coverage build.** `-DCOA_COVERAGE=ON` implies `Debug` and `-O0`.
- **Filtering.** `--benchmark_filter='.*ManyFullConfig'` selects the largest shape only; the fixture
  cache is lazy per shape, so the smaller ones are never built.
- **Comparing two runs.** `tools/compare.py benchmarks old.json new.json` from the Google Benchmark
  sources gives per benchmark deltas with U test p values.

## Results

Measured on `codacDevel`, 20 x 4600 MHz, pinned to CPU 2, 5 repetitions. Raw output in
`benchmark.log` and `benchmark-output.json`. The `cv` column is the coefficient of variation over
the 5 repetitions; the largest observed is 15.8 %.

Read the two time columns as orders of magnitude, not as a delta:

1. **Different hardware.** `test/performance/performance.log` was produced on 2025-02-20 on a CODAC
   virtual machine. Only the shape to shape scaling and the throughput figures carry over.
2. **The copy benchmarks now include destruction of the copy.** The hand-made loop took its second
   timestamp before the copy went out of scope, so destruction was counted in neither of its two
   buckets. The new copy figures are therefore legitimately larger.
3. **The JSON parse benchmark does not move the parsed value out of the parser**, matching what
   `JSONEncoder::Decode` measured. The binary parse benchmark does materialise and destroy the
   decoded value, again matching `BinaryEncoder::Decode`. The two parse figures are not directly
   comparable to each other.
4. **The legacy `ScalarMix` encoder rows are reported as `n/a`.** The old harness measured them in
   whole milliseconds and got 0 ms, hence its `inf bytes/s`.

| Benchmark | legacy mean (ms) | new median (ms) | cv | legacy MB/s | new MB/s |
|---|---|---|---|---|---|
| `BM_CopyAnyType/ScalarMix` | 0.00073 | 0.0011 | 2.1% | n/a | - |
| `BM_CopyAnyType/ScalarMixArray` | 0.00084 | 0.00114 | 1.5% | n/a | - |
| `BM_CopyAnyType/SystemConfigs` | 0.00574 | 0.00713 | 6.9% | n/a | - |
| `BM_CopyAnyType/FullConfig` | 0.00568 | 0.0073 | 2.3% | n/a | - |
| `BM_CopyAnyType/ManyFullConfig` | 0.00589 | 0.00745 | 1.4% | n/a | - |
| `BM_CompareAnyType/ScalarMix` | 0.00036 | 0.00033 | 2.6% | n/a | - |
| `BM_CompareAnyType/ScalarMixArray` | 0.00043 | 0.00037 | 0.8% | n/a | - |
| `BM_CompareAnyType/SystemConfigs` | 0.00268 | 0.00242 | 1.8% | n/a | - |
| `BM_CompareAnyType/FullConfig` | 0.00277 | 0.00253 | 6.8% | n/a | - |
| `BM_CompareAnyType/ManyFullConfig` | 0.00288 | 0.0026 | 4.4% | n/a | - |
| `BM_CopyAnyValue/ScalarMix` | 0.00096 | 0.00116 | 0.9% | n/a | - |
| `BM_CopyAnyValue/ScalarMixArray` | 0.12023 | 0.14001 | 1.6% | n/a | - |
| `BM_CopyAnyValue/SystemConfigs` | 0.7792 | 0.85182 | 0.5% | n/a | - |
| `BM_CopyAnyValue/FullConfig` | 17.8401 | 17.34329 | 3.2% | n/a | - |
| `BM_CopyAnyValue/ManyFullConfig` | 378.077 | 364.68707 | 5.2% | n/a | - |
| `BM_CompareAnyValue/ScalarMix` | 0.00042 | 0.0004 | 0.2% | n/a | - |
| `BM_CompareAnyValue/ScalarMixArray` | 0.05066 | 0.04913 | 9.6% | n/a | - |
| `BM_CompareAnyValue/SystemConfigs` | 0.31678 | 0.34274 | 0.6% | n/a | - |
| `BM_CompareAnyValue/FullConfig` | 6.89963 | 6.5464 | 0.8% | n/a | - |
| `BM_CompareAnyValue/ManyFullConfig` | 138.769 | 135.35933 | 1.3% | n/a | - |
| `BM_SerializeJSON/ScalarMix` | n/a | 0.00913 | 3.3% | n/a | 54.0 |
| `BM_SerializeJSON/ScalarMixArray` | 0.197 | 0.21076 | 0.8% | 56.6 | 52.9 |
| `BM_SerializeJSON/SystemConfigs` | 1.182 | 1.27377 | 1.1% | 56.6 | 52.5 |
| `BM_SerializeJSON/FullConfig` | 20.9811 | 20.45241 | 2.4% | 49.1 | 50.4 |
| `BM_SerializeJSON/ManyFullConfig` | 407.667 | 404.62845 | 1.3% | 50.4 | 50.8 |
| `BM_ParseJSON/ScalarMix` | n/a | 0.0218 | 1.4% | n/a | 22.6 |
| `BM_ParseJSON/ScalarMixArray` | 0.596 | 0.70531 | 0.7% | 18.7 | 15.8 |
| `BM_ParseJSON/SystemConfigs` | 3.551 | 4.45131 | 2.7% | 18.8 | 15.0 |
| `BM_ParseJSON/FullConfig` | 62.2075 | 70.01263 | 1.5% | 16.6 | 14.7 |
| `BM_ParseJSON/ManyFullConfig` | 1234.67 | 1421.19241 | 4.0% | 16.6 | 14.5 |
| `BM_SerializeBinary/ScalarMix` | 0.004 | 0.00507 | 0.6% | 28.8 | 22.7 |
| `BM_SerializeBinary/ScalarMixArray` | 0.155 | 0.15344 | 13.1% | 35.4 | 35.8 |
| `BM_SerializeBinary/SystemConfigs` | 0.993 | 0.96397 | 4.2% | 33.3 | 34.3 |
| `BM_SerializeBinary/FullConfig` | 18.4096 | 14.78995 | 1.1% | 28.2 | 35.1 |
| `BM_SerializeBinary/ManyFullConfig` | 306.5 | 356.05653 | 10.9% | 33.8 | 29.1 |
| `BM_ParseBinary/ScalarMix` | 0.011 | 0.01953 | 15.8% | 10.5 | 5.9 |
| `BM_ParseBinary/ScalarMixArray` | 0.376 | 0.4462 | 1.2% | 14.6 | 12.3 |
| `BM_ParseBinary/SystemConfigs` | 2.341 | 2.66946 | 2.6% | 14.1 | 12.4 |
| `BM_ParseBinary/FullConfig` | 39.0602 | 46.77943 | 4.9% | 13.3 | 11.1 |
| `BM_ParseBinary/ManyFullConfig` | 903.75 | 862.53738 | 6.1% | 11.5 | 12.0 |

### Observations

- **`AnyType` copy and comparison are flat from `SystemConfigs` upwards.** An array `AnyType`
  stores its element type once, so the cost does not grow with the number of elements. The
  hand-made harness shows the same plateau.
- **`AnyValue` copy scales linearly with the leaf count**, ending at 365 ms for 3 million leaves.
- **JSON serialization sustains about 51 MB/s and parsing about 15 MB/s** across all shapes; the
  binary format is slower at about 35 MB/s and 12 MB/s, but produces roughly half the bytes.
- **Parsing costs 3 to 4 times more than serializing** in both formats.
