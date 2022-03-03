# To-do list for v1.0

* Provide non-throwing implementations for assignment, serialization, parsing, etc.
* Implement performance test for parsing
* Unit test coverage: mostly for json parsing of streams that do not conform to the (implicit) schema
* Cast from C-type
* Provide depth-first iterator (currently IAnySerializeNode<T> and derived classes) and expose this as a generic way
  to visit all nodes in an AnyType/AnyValue tree
* Complete documentation (mostly serialize/parse)
