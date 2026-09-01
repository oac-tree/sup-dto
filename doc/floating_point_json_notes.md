# Floating-point JSON representation: known behavior

Summary of how `AnyValue`'s `float32`/`float64` scalars behave through JSON
serialization (`ValuesToJSONString`/`AnyValueToJSONString`) and parsing
(`JSONAnyValueParser`), based on the vendored RapidJSON 1.1. Pinned by
`anyvalue_json_serialize_tests.cpp` and `json_value_parser_tests.cpp`.

## NaN

Silently serializes to an **empty string** instead of valid JSON or an error.
RapidJSON's `Writer::Double()` is not built with `kWriteNanAndInfFlag`, so it
fails internally, but that failure is not propagated by the writer wrapper in
`json_writer_t.h`. The empty string then fails to parse back at all.

## Infinity

`AnyValue{Float64Type, inf}` (and `-inf`) **throws `InvalidConversionException`
at construction time**, before any JSON serialization is attempted. So unlike
NaN, `±Infinity` can never end up in an `AnyValue` in the first place.

## Round-trip precision (`float64`)

RapidJSON 1.1 uses the plain **Grisu2** double-to-string algorithm with no
Dragon4/correctness fallback. Grisu2 has a known, small but nonzero rate of
producing digits that do not round-trip to the exact original double (it is
"shortest, not always correct", unlike Grisu3 or Ryu). Confirmed concrete
failures, each off by one ULP after a full JSON round trip:

- `1.5e-300`
- `123456789.123456789`

Values with fewer significant digits or "nicer" binary representations
(`DBL_MAX`, `DBL_MIN`, `DBL_DENORM_MIN`, `-0.0`, `1e300`, etc.) round-trip
correctly.

## `float32` round-trip

`Float()` in `json_writer_t.h` writes a `float32` by implicitly promoting it
to `double` and reusing the same `Double()`/Grisu2 path — there is no
float32-specific shortest-round-trip formatting. For most values this is
harmless, but for `std::numeric_limits<float32>::max()` the promoted double's
Grisu2 output overflows back to `+Infinity` when narrowed to `float32` on
reparse, so `TypedParseString(Float32Type, ...)` **fails outright** instead of
losing precision gracefully.

## Not yet investigated

- Whether `binary_serializer`/`ctype_serializer` share any of these issues
  (this note only covers the JSON path).
- Whether upgrading the vendored RapidJSON (or patching in a Ryu/Grisu3-style
  fallback) would be in scope — RapidJSON is vendored in-tree and the project
  convention is not to modify it.
