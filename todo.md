# To-do list for v1.0

* Investigate arrays of arrays: one element array could be extended by `AddElement`, causing the element types not to be homogeneous anymore. The same could occur for structs as elements.
* Complete documentation (mostly serialize/parse)
* XML serialization/parsing

# Relax assignment while enforcing class invariants

Shortlist:

- [x] AnyType: remove constraints.
- [ ] AnyValue: disallow violating value invariants in case of arrays, i.e. all elements of an array should have the exact same type.
  - [ ] Remove default constraint parameter in IValueData constructors
- [ ] Documentation

## AnyType

No constraints on AnyType: since array types only contain a single element type (and a size), they can never violate the constraint of having different type elements. Furthermore, the constraint to not allow empty types as non-root nodes will be removed.

## AnyValue

The only constraint on AnyValues will be that elements of array values need to have the exact same type. Since the size of an array is part of its type, this means that arrays of arrays should always have equally sized arrays as array elements.
