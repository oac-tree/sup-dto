# To-do list for v1.0

* Investigate arrays of arrays: one element array could be extended by `AddElement`, causing the element types not to be homogeneous anymore. The same could occur for structs as elements.
* Add `HasField` member function to indicate presence of possibly nested fields (works already for structs of structs, but not for arrays)
* Complete documentation (mostly serialize/parse)
* XML serialization/parsing
