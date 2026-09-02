# Floating-point serialization: known behavior

Summary of how `AnyValue`'s `float32`/`float64` scalars behave through JSON
serialization (`ValuesToJSONString`/`AnyValueToJSONString`) and parsing
(`JSONAnyValueParser`), based on the vendored RapidJSON 1.1. Pinned by
`anyvalue_json_serialize_tests.cpp` and `json_value_parser_tests.cpp`. The
[Binary serialization](#binary-serialization-contrast) section below contrasts
this with the binary format, which does not share these issues.

## NaN and Infinity

An `AnyValue` can never hold `NaN` or `±Infinity`: both are rejected with
`InvalidConversionException` at construction time (checked in
`low_level/scalar_conversion.h` and `anyvalue/anyvalue.cpp`), so no
serializer — JSON, binary, or C-type — ever has to deal with them.

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

`Float()` in `json_writer_t.h` writes a `float32` by promoting it to `double`
and reusing the `Double()`/Grisu2 path, which for
`std::numeric_limits<float32>::max()` (and its negative) can produce a JSON
number past `static_cast<float64>(FLT_MAX)`. This still round-trips
correctly: the `float32` narrowing conversion (`ConvertScalar` in
`low_level/scalar_conversion.h`) rounds to nearest and only rejects a
genuinely non-finite result, rather than rejecting anything past the exact
bound. Pinned by `JSONValueParserTest.Float32MaxValueRoundTrip` and
`Float32MinValueNegatedRoundTrip`.

## Parsing behavior for hand-written JSON literals

The tests above all start from a C++ `float`/`double` value, serialize it, then
parse the result back (value -> JSON -> value). Starting instead from a
hand-written JSON number literal (JSON -> value [-> JSON -> value]) surfaces
mostly the same picture:

- Out-of-range literals (`1e400`, `1e309`) are rejected cleanly (`false`), via
  the same conversion check that rejects C++ `Infinity` at construction.
- Underflow (`1e-400`) parses to `0.0`, as expected.
- Invalid JSON number syntax (leading zeros, e.g. `00.1`) is rejected, as is
  the literal text `NaN`/`Infinity`/`-Infinity` — none of these are valid JSON
  tokens, so they are rejected by the JSON grammar itself, independently of
  the `AnyValue`-level rejection described above.
- A literal parsed correctly, then re-serialized, then re-parsed can still
  land on a different double than the first parse (e.g. the literal
  `1.0000000000000002220446049250313080847263336181640625`, or
  `0.30000000000000004`) — the same Grisu2 imprecision as above, just
  triggered from the JSON side instead of the C++ side.
- `Float32Type` literals are parsed by reading every JSON float as a
  `float64` first, then narrowing. The literal `3.4028235e38` — the textbook
  correctly-rounded decimal form of `std::numeric_limits<float32>::max()`
  (confirmed against `strtof`, which resolves it to exactly `FLT_MAX`) —
  correctly rounds down to `FLT_MAX` on narrowing, same as the value ->
  JSON -> value case above. A literal past the true halfway point to
  infinity (e.g. `3.4028236e38`) is still correctly rejected. Pinned by
  `Float32CorrectlyRoundedMaxLiteralAccepted`,
  `Float32CorrectlyRoundedNegatedMaxLiteralAccepted`, and
  `Float32GenuineOverflowLiteralRejected`.

## Binary serialization (contrast)

None of the above apply to the binary format: it copies the underlying
IEEE-754 bytes directly with no decimal string involved, so every case above
round-trips exactly — pinned by `binary_value_encoding_tests.cpp`. NaN and
Infinity are rejected the same way as for JSON, since that happens at
`AnyValue` construction, before either serializer ever sees the value.

## Not yet investigated

- Whether upgrading the vendored RapidJSON (or patching in a Ryu/Grisu3-style
  fallback) would be in scope — RapidJSON is vendored in-tree and the project
  convention is not to modify it. This would only help the `float64`
  round-trip precision cases above; the `float32` narrowing issue is already
  fixed independently of RapidJSON (see `float32` round-trip above).
