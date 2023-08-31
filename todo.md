# To-do list

* Complete documentation (mostly serialize/parse)
* Binary parsing
  * Handle empty arrays: AnyValueComposer considers these to be empty AnyValues
  * Parsing values by type first could remove repeated size checks on the buffer
  * Enable empty array test
  * Parsing performance is currently below that of JSON: investigate and fix
* XML serialization/parsing
