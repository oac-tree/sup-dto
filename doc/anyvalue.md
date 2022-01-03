# AnyValue API

## Use cases

### As DTO's

These objects should be easily transferred over a network connection. As such, their serialization is important. This serialization could come in many different forms, of which the following are common in ITER software:

* Serialization to/from json: mainly used for logging and storing/retrieving values on file.
* Serialization to/from EPICS process variables: mainly for network transfer.

## Types

What do types need to contain?

### Scalar types

* Indication of which scalar type it is. This could be either
  * String name, or
  * Tag object, or
  * Enumerator
* Size of the type should also be runtime retrievable, since applications cannot always know which types they may need to handle.

### Structure types

* Marker that unambiguously marks the type as being a structure. Again, this could be an enumerator or tag.
* [Optional] Unique (within the current context) type identifier. Could be a String name, although it is unclear why this might be needed.
* Ordered list of entries, each consisting of:
  * A String member name, and
  * Member type: this could be a reference to the unique identifier, or a pointer to a real Type object.

### Array types

* Marker that unambiguously marks the type as being an array. Again, this could be an enumerator or tag.
* [Optional] Unique (within the current context) type identifier. Could be a String name, although it is unclear why this might be needed.
* Element type: this could be a reference to the unique identifier, or a pointer to a real Type object.
* [optional] Number of elements.

## Construction of types and values

### Scalar values

```c++
// From global scalar type tags:
extern const AnyType Int32;

AnyValue my_default_int32(Types::Int32)
AnyValue my_int32(Types::Int32, 24)
```

### Structured values

```c++
// From global scalar type tags:
AnyType my_struct_t(Tag::Struct, "my_struct_name").addMember("membername", Tag::Int32);

AnyValue my_default_struct(Tag::Struct, "my_struct_name")
AnyValue my_int32(Tag::Int32, 24)
```

## API based on pvxs

Construction of types and default values for these types:

```c++
// Full specification of the type:
AnyValue MyStructure = AnyType(TypeCode::Struct, "CustomerType",
                          {
                            Members::Struct("account", "account_t",
                              {
                                 Members::String("bank"),
                                 Members::Uint64("client_id")
                              }),
                            Members::Uint32("index"),
                            Members::String("name")
                          }).create();

// Specification depending on previously registered named types:
AnyValue MyStructure = AnyType(TypeCode::Struct, "CustomerListType",
                          {
                            Members::Array("customers", "customers_t", "CustomerType"),
                            Members::String("listname")
                          }).create();
```

Construction of values:

```c++
// Partial specification of nested values (unspecified members are untouched)
auto customer_a = AnyValue("CustomerType",
                    {
                      {"account",
                        {
                          {"bank", "GoldStar"},
                          {"client_id", 15}
                        }
                      },
                      {"name", "Jimmy Money"}
                    });

// Specification by referring to existing values
auto global_customers = AnyValue("CustomerListType",
                          {
                            {"customers",
                              {customer_a, customer_b}
                            },
                            {"listname", "All customers worldwide"}
                          });
```
