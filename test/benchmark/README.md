# Performance benchmarks

Google Benchmark measurements of `AnyType` and `AnyValue` copy and comparison, and of the JSON and
binary serialization round trip, over five shapes of growing size.

Google Benchmark is an optional dependency. Without it this target is skipped and the rest of the
test tree builds as usual.

## Shapes

Each shape contains the previous one, so the leaf count grows by about two orders of magnitude per
rung.

| Shape | Definition | Leaves | JSON B | Binary B |
|---|---|---|---|---|
| `ScalarMix` | struct, one member per scalar type | 13 | 493 | 115 |
| `ScalarMixArray` | array of 120 `scalar_mix_t` | 1 560 | 11 145 | 5 493 |
| `SystemConfigs` | struct of six `scalar_mix_array_t` | 9 362 | 66 866 | 33 060 |
| `FullConfig` | array of 16 `system_configs_t` | 149 792 | 1 029 906 | 519 108 |
| `ManyFullConfig` | array of 20 `full_config_t` | 2 995 840 | 20 546 500 | 10 369 339 |

## Running

```bash
taskset -c 2 ./test_bin/benchmark-tests \
      --benchmark_repetitions=5 --benchmark_display_aggregates_only=true \
      --benchmark_counters_tabular=true \
      --benchmark_out=benchmark-output.json --benchmark_out_format=json \
      2>&1 | tee benchmark.log
```

Pin the run and compare medians: the noise floor is 10 to 20 %, and on heterogeneous cores an
unpinned run drifts between core types. Do not measure a `COA_COVERAGE=ON` build, it is `-O0`.
`--benchmark_filter='.*ManyFullConfig'` selects the largest shape only, which the fixture cache
builds lazily.

`benchmark.log` holds the committed run. The JSON is not committed; keep two of them locally and
`tools/compare.py benchmarks old.json new.json` from the Google Benchmark sources diffs them.
