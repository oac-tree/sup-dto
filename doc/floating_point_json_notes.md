# Floating-point serialization: known behavior

Summary of how `AnyValue`'s `float32`/`float64` scalars behave through JSON
serialization (`ValuesToJSONString`/`AnyValueToJSONString`) and parsing
(`JSONAnyValueParser`), based on the vendored RapidJSON 1.1. Pinned by
`anyvalue_json_serialize_tests.cpp` and `json_value_parser_tests.cpp`. The
[Binary serialization](#binary-serialization-contrast) section below contrasts
this with the binary format, which does not share these issues.

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

## Parsing behavior for hand-written JSON literals

The tests above all start from a C++ `float`/`double` value, serialize it, then
parse the result back (value -> JSON -> value). Starting instead from a
hand-written JSON number literal (JSON -> value [-> JSON -> value]) surfaces
mostly the same picture, plus one distinct bug:

- Out-of-range literals (`1e400`, `1e309`) are rejected cleanly (`false`), via
  the same conversion check that rejects C++ `Infinity` at construction.
- Underflow (`1e-400`) parses to `0.0`, as expected.
- Invalid JSON number syntax (leading zeros, e.g. `00.1`) is rejected, as is
  the literal text `NaN`/`Infinity`/`-Infinity` (none of these are valid JSON
  tokens, unlike a NaN `AnyValue` built in C++, which parses fine and only
  breaks at serialization time — see above).
- A literal parsed correctly, then re-serialized, then re-parsed can still
  land on a different double than the first parse (e.g. the literal
  `1.0000000000000002220446049250313080847263336181640625`, or
  `0.30000000000000004`) — the same Grisu2 imprecision as above, just
  triggered from the JSON side instead of the C++ side.
- **New, distinct bug**: `Float32Type` literals are parsed by reading every
  JSON float as a `float64` first, then narrowing. The literal `3.4028235e38`
  is the textbook correctly-rounded decimal form of
  `std::numeric_limits<float32>::max()` (confirmed against `strtof`, which
  resolves it to exactly `FLT_MAX`), but the library's parser **rejects it
  outright** instead of rounding it down to `FLT_MAX`: the intermediate
  `float64` value is numerically larger than `static_cast<float64>(FLT_MAX)`,
  and the narrowing range check does not account for `float32`'s own
  round-to-nearest tolerance up to halfway to infinity. So even a *correct*
  JSON encoding of `FLT_MAX` (not one produced by this library's own buggy
  writer) fails to parse.

## Binary serialization (contrast)

None of the above apply to the binary format: it copies the underlying
IEEE-754 bytes directly with no decimal string involved, so all of these
cases (including NaN's bit pattern) round-trip exactly — pinned by
`binary_value_encoding_tests.cpp`.

## Not yet investigated

- Whether upgrading the vendored RapidJSON (or patching in a Ryu/Grisu3-style
  fallback) would be in scope — RapidJSON is vendored in-tree and the project
  convention is not to modify it.
- Whether the `float32` narrowing range check (used both when parsing JSON
  literals and when constructing an `AnyValue` directly from a `double`) could
  be fixed independently of RapidJSON, by rounding to nearest `float32` instead
  of doing a strict "fits in double-cast range" comparison.
