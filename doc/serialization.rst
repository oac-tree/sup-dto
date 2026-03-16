Serialization and parsing
=========================

Both the ``AnyType`` and ``AnyValue`` objects can be serialized to, and parsed from, different
formats.This section provides documentation on the public API for serialiation and parsing.

.. contents::
   :local:

JSON Serialization
------------------

AnyType
^^^^^^^

``AnyType`` objects can be serialized to JSON format.

.. code-block:: json

    {
      "type": "",
      "attributes": [
        {
          "array": {
            "type": "",
            "multiplicity": 4,
            "element": {
              "type": "",
              "attributes": [
                {
                  "id": {
                    "type": "string"
                  }
                },
                {
                  "number": {
                    "type": "uint64"
                  }
                }
              ]
            }
          }
        },
        {
          "validated": {
            "type": "bool"
          }
        }
      ]
    }

The library contains the following global functions for serialization and parsing of AnyType:

.. function:: std::string AnyTypeToJSONString(const AnyType& anytype, bool pretty)

   :param anytype: AnyType object to serialize.
   :param pretty: Use pretty printing.
   :return: JSON string.

   Serialize an AnyType to a JSON string. This serialization is reversible.

.. function:: std::string AnyTypeToJSONString(const AnyType& anytype)

   :param anytype: AnyType object to serialize.
   :return: JSON string.

   Same as :func:`std::string AnyTypeToJSONString(const AnyType& anytype, bool pretty)`. with
   'pretty' set to false.

.. function:: void AnyTypeToJSONFile(const AnyType& anytype, const std::string& filename, bool pretty)

   :param anytype: AnyType object to serialize.
   :param filename: Filename to use.
   :param pretty: Use pretty printing.
   :throws SerializeException: When the JSON representation of the AnyType could not be
                               written to the file with given filename.

   Serialize an AnyType to a JSON file. This serialization is meant to be reversible.

.. function:: void AnyTypeToJSONFile(const AnyType& anytype, const std::string& filename)

   :param anytype: AnyType object to serialize.
   :param filename: Filename to use.
   :throws SerializeException: When the JSON representation of the AnyType could not be
                               written to the file with given filename.

   Same as :func:`void AnyTypeToJSONFile(const AnyType& anytype, const std::string& filename, bool pretty)`. with
   'pretty' set to false.

AnyValue
^^^^^^^^

``AnyValue`` objects can be serialized to JSON format.

.. code-block:: json

    [
      {
        "encoding": "sup-dto/v1.0/JSON"
      },
      {
        "datatype": {
          "type": "",
          "attributes": [
            {
              "id": {
                "type": "string"
              }
            },
            {
              "number": {
                "type": "int32"
              }
            },
            {
              "weight": {
                "type": "float64"
              }
            }
          ]
        }
      },
      {
        "instance": {
          "id": "my_id",
          "number": 1729,
          "weight": 50.25
        }
      }
    ]

The library contains the following global functions for serialization and parsing of AnyValue:

.. function:: std::string ValuesToJSONString(const AnyValue& anyvalue, bool pretty)

   :param anyvalue: AnyValue object to serialize.
   :param pretty: Use pretty printing.
   :return: JSON string.

   Serialize the values of an AnyValue using a JSON serializer. This serialization only contains
   a map of the values and is insufficient to reconstruct the exact AnyValue back. Reversible
   serialization also requires the type (see AnyValueToJSONString function).

.. function:: std::string ValuesToJSONString(const AnyValue& anyvalue)

   :param anyvalue: AnyValue object to serialize.
   :return: JSON string.

   Same as :func:`std::string ValuesToJSONString(const AnyValue& anyvalue, bool pretty)`. with
   'pretty' set to false.

.. function:: std::string AnyValueToJSONString(const AnyValue& anyvalue, bool pretty)

   :param anyvalue: AnyValue object to serialize.
   :param pretty: Use pretty printing.
   :return: JSON string.

   Serialize an AnyValue to a JSON string. This serialization is meant to be reversible.
   The JSON string will contain both type information as specific values of leaf nodes.

.. function:: std::string AnyValueToJSONString(const AnyValue& anyvalue)

   :param anyvalue: AnyValue object to serialize.
   :return: JSON string.

   Same as :func:`std::string AnyValueToJSONString(const AnyValue& anyvalue, bool pretty)`. with
   'pretty' set to false.

.. function:: void ValuesToJSONFile(const AnyValue& anyvalue, const std::string& filename, bool pretty)

   :param anyvalue: AnyValue object to serialize.
   :param filename: Filename to use.
   :param pretty: Use pretty printing.
   :throws SerializeException: When the JSON representation of the AnyValue could not be
                               written to the file with given filename.

   Serialize the values of an AnyValue to a JSON file. This serialization only contains
   a map of the values and is insufficient to reconstruct the exact AnyValue back. Reversible
   serialization also requires the type (see AnyValueToJSONFile function).

.. function:: void ValuesToJSONFile(const AnyValue& anyvalue, const std::string& filename)

   :param anyvalue: AnyValue object to serialize.
   :param filename: Filename to use.
   :throws SerializeException: When the JSON representation of the AnyValue could not be
                               written to the file with given filename.

   Same as :func:`void ValuesToJSONFile(const AnyValue& anyvalue, const std::string& filename, bool pretty)`. with
   'pretty' set to false.

.. function:: void AnyValueToJSONFile(const AnyValue& anyvalue, const std::string& filename, bool pretty)

   :param anyvalue: AnyValue object to serialize.
   :param filename: Filename to use.
   :param pretty: Use pretty printing.
   :throws SerializeException: When the JSON representation of the AnyValue could not be
                               written to the file with given filename.

   Serialize an AnyValue to a JSON file. This serialization is meant to be reversible.
   The JSON file will contain both type information as specific values of leaf nodes.

.. function:: void AnyValueToJSONFile(const AnyValue& anyvalue, const std::string& filename)

   :param anyvalue: AnyValue object to serialize.
   :param filename: Filename to use.
   :throws SerializeException: When the JSON representation of the AnyValue could not be
                               written to the file with given filename.

   Same as :func:`void AnyValueToJSONFile(const AnyValue& anyvalue, const std::string& filename, bool pretty)`. with
   'pretty' set to false.

JSON parsing
------------

The library provides dedicated parser classes for parsing ``AnyType`` and ``AnyValue`` objects from
JSON. These classes allow incremental parsing and optionally accept an ``AnyTypeRegistry`` for
resolving type references during parsing.

JSONAnyTypeParser
^^^^^^^^^^^^^^^^^

The ``JSONAnyTypeParser`` class parses JSON representations into ``AnyType`` objects. It is
non-copyable and non-movable. After a successful parse, the result can be retrieved using
``MoveAnyType()``.

Some of the parse functions have a parameter that points to an ``AnyTypeRegistry``. In such cases,
the JSON representation that is to be parsed can refer directly to the name of a type, which will
be retrieved from the registry. This avoids repeating the same type definitions in the JSON
representation. See :class:`AnyTypeRegistry` for more information.

.. class:: JSONAnyTypeParser

   .. function:: JSONAnyTypeParser()

      Construct a new parser instance.

   .. function:: bool ParseString(const std::string& json_str, const AnyTypeRegistry* type_registry)

      :param json_str: JSON string to parse.
      :param type_registry: ``AnyTypeRegistry`` to use during parsing.
      :return: ``true`` on successful parsing, ``false`` otherwise.

      Parse an ``AnyType`` from a JSON string using a type registry for resolving type references.

   .. function:: bool ParseString(const std::string& json_str)

      :param json_str: JSON string to parse.
      :return: ``true`` on successful parsing, ``false`` otherwise.

      Parse an ``AnyType`` from a JSON string without use of a type registry.

   .. function:: bool ParseFile(const std::string& filename, const AnyTypeRegistry* type_registry)

      :param filename: Name of the file containing the JSON representation.
      :param type_registry: ``AnyTypeRegistry`` to use during parsing.
      :return: ``true`` on successful parsing, ``false`` otherwise.

      Parse an ``AnyType`` from a JSON file using a type registry for resolving type references.

   .. function:: bool ParseFile(const std::string& filename)

      :param filename: Name of the file containing the JSON representation.
      :return: ``true`` on successful parsing, ``false`` otherwise.

      Parse an ``AnyType`` from a JSON file without use of a type registry.

   .. function:: AnyType MoveAnyType()

      :return: Parsed ``AnyType``, or empty type if nothing was parsed.

      Return the parsed ``AnyType`` with move semantics.

JSONAnyValueParser
^^^^^^^^^^^^^^^^^^

The ``JSONAnyValueParser`` class parses JSON representations into ``AnyValue`` objects. It is
non-copyable and non-movable. In addition to the standard parse methods, it provides typed
parsing methods that accept an ``AnyType`` to use for the resulting value. After a successful
parse, the result can be retrieved using ``MoveAnyValue()``.

.. class:: JSONAnyValueParser

   .. function:: JSONAnyValueParser()

      Construct a new parser instance.

   .. function:: bool ParseString(const std::string& json_str, const AnyTypeRegistry* type_registry)

      :param json_str: JSON string to parse.
      :param type_registry: ``AnyTypeRegistry`` to use during parsing.
      :return: ``true`` on successful parsing, ``false`` otherwise.

      Parse an ``AnyValue`` from a JSON string using a type registry for resolving type references.

   .. function:: bool ParseString(const std::string& json_str)

      :param json_str: JSON string to parse.
      :return: ``true`` on successful parsing, ``false`` otherwise.

      Parse an ``AnyValue`` from a JSON string without use of a type registry.

   .. function:: bool ParseFile(const std::string& filename, const AnyTypeRegistry* type_registry)

      :param filename: Name of the file containing the JSON representation.
      :param type_registry: ``AnyTypeRegistry`` to use during parsing.
      :return: ``true`` on successful parsing, ``false`` otherwise.

      Parse an ``AnyValue`` from a JSON file using a type registry for resolving type references.

   .. function:: bool ParseFile(const std::string& filename)

      :param filename: Name of the file containing the JSON representation.
      :return: ``true`` on successful parsing, ``false`` otherwise.

      Parse an ``AnyValue`` from a JSON file without use of a type registry.

   .. function:: bool TypedParseString(const AnyType& anytype, const std::string& json_str)

      :param anytype: Type to use for the resulting value.
      :param json_str: JSON string to parse.
      :return: ``true`` on successful parsing, ``false`` otherwise.

      Parse an ``AnyValue`` with a given type from a JSON string.

   .. function:: bool TypedParseFile(const AnyType& anytype, const std::string& filename)

      :param anytype: Type to use for the resulting value.
      :param filename: Name of the file containing the JSON representation.
      :return: ``true`` on successful parsing, ``false`` otherwise.

      Parse an ``AnyValue`` with a given type from a JSON file.

   .. function:: AnyValue MoveAnyValue()

      :return: Parsed ``AnyValue``, or empty value if nothing was parsed.

      Return the parsed ``AnyValue`` with move semantics.

Binary Serialization and parsing
--------------------------------

The library also provides a binary format for both ``AnyType`` and ``AnyValue``. While it is not
designed to be human-readable, its format is more compact and serialization/parsing is faster.

AnyType
^^^^^^^

.. function:: std::vector<uint8> AnyTypeToBinary(const AnyType& anytype)

   :param anytype: AnyType object to serialize.
   :return: Binary representation of the AnyType.

   Serialize an AnyType to a binary representation.

.. function:: AnyType AnyTypeFromBinary(const std::vector<uint8>& representation)

   :param representation: Binary representation of an AnyType object.
   :return: AnyType.
   :throws ParseException: When the binary representation could not be correctly parsed.

   Parse an AnyType from a binary representation.

AnyValue
^^^^^^^^

.. function:: std::vector<uint8> AnyValueToBinary(const AnyValue& anyvalue)

   :param anyvalue: AnyValue object to serialize.
   :return: Binary representation of the AnyValue.

   Serialize an AnyValue to a binary representation.

.. function:: AnyValue AnyValueFromBinary(const std::vector<uint8>& representation)

   :param representation: Binary representation of an AnyValue object.
   :return: AnyValue.
   :throws ParseException: When the binary representation could not be correctly parsed.

   Parse an AnyValue from a binary representation.

Casting to/from plain C types
-----------------------------

The library provides functions for converting ``AnyValue`` objects to and from plain C-type
structures via byte arrays. These are mainly useful for interfacing with C-style APIs.

They can also be used in applications where it is required that all scalar types are represented
by fixed size byte arrays, e.g. for low-level network libraries. Note that all strings will be
represented by zero-terminated char arrays with fixed length (64).

.. function:: std::vector<uint8> ToBytes(const AnyValue& anyvalue)

   :param anyvalue: ``AnyValue`` object to serialize.
   :return: Byte array representation of the value.
   :throws SerializeException: When the ``AnyValue`` cannot be correctly serialized into a byte
      array (e.g. string field too long or unknown scalar type).

   Serialize an ``AnyValue`` to an array of bytes in host byte order.

.. function:: std::vector<uint8> ToNetworkOrderBytes(const AnyValue& anyvalue)

   :param anyvalue: ``AnyValue`` object to serialize.
   :return: Byte array representation of the value.
   :throws SerializeException: When the ``AnyValue`` cannot be correctly serialized into a byte
      array (e.g. string field too long or unknown scalar type).

   Serialize an ``AnyValue`` to an array of bytes in network byte order.

.. function:: void FromBytes(AnyValue& anyvalue, const uint8* bytes, std::size_t total_size)

   :param anyvalue: ``AnyValue`` object to assign to.
   :param bytes: Array of bytes.
   :param total_size: Size of the array of bytes.
   :throws ParseException: When the byte array cannot be correctly parsed (e.g. sizes don't
      match, absence of null terminator in C-style string or unknown scalar type).

   Parse ``AnyValue`` content from an array of bytes in host byte order.

.. function:: template <typename T> T AnyValue::ToCType() const

   :return: This value as a ``T`` value when successful.
   :throws SerializeException: When this value could not be serialized to ``T``.

   Cast this ``AnyValue`` to a given plain C-type structure. Internally serializes the value
   to bytes and copies the result into the target type. Requires that the byte size of ``T``
   matches the serialized size exactly.

.. function:: template <typename T> bool AnyValue::ToCType(T& value) const

   :param value: Reference to value to copy into.
   :return: ``true`` on success, ``false`` otherwise.

   Non-throwing version of :func:`template \<typename T\> T AnyValue::ToCType() const`.

.. function:: template <typename T> void AssignFromCType(AnyValue& anyvalue, const T& object)

   :param anyvalue: ``AnyValue`` to assign to.
   :param object: C-type source object.
   :throws ParseException: When the source object cannot be correctly parsed into the
      existing structure of the ``AnyValue``.

   Assigns to an ``AnyValue`` using a plain C-type structure. The source object must be a
   packed structure of values that corresponds to the structure of the ``AnyValue`` object.

.. function:: template <typename T> bool SafeAssignFromCType(AnyValue& anyvalue, const T& object)

   :param anyvalue: ``AnyValue`` to assign to.
   :param object: C-type source object.
   :return: ``true`` on success, ``false`` otherwise.

   Non-throwing version of :func:`template \<typename T\> void AssignFromCType(AnyValue& anyvalue, const T& object)`.

AnyTypeRegistry
---------------

The ``AnyTypeRegistry`` class allows registering ``AnyType`` instances by name, so they can be
looked up during parsing. The default constructor creates a registry pre-populated with all scalar
and empty types.

The class is copyable and movable.

.. class:: AnyTypeRegistry

   .. function:: AnyTypeRegistry()

      Construct a new registry pre-populated with scalar and empty types.

   .. function:: void RegisterType(AnyType anytype)

      :param anytype: ``AnyType`` instance to register.
      :throws InvalidOperationException: When the type's own name was already used to register
         a different type. Re-registering the same name and type is allowed.

      Register an ``AnyType`` instance under its own name.

   .. function:: void RegisterType(const std::string& name, AnyType anytype)

      :param name: Name under which to register the ``AnyType``.
      :param anytype: ``AnyType`` instance to register.
      :throws InvalidOperationException: When the given name was already used to register
         a different type. Re-registering the same name and type is allowed.

      Register an ``AnyType`` instance under the given name.

   .. function:: bool HasType(const std::string& name) const

      :param name: Name to look up.
      :return: ``true`` if an ``AnyType`` instance is registered under the given name.

      Query the existence of a registered ``AnyType`` instance under the given name.

   .. function:: std::vector<std::string> RegisteredAnyTypeNames() const

      :return: List of all names under which ``AnyType`` instances are registered.

      Retrieve all registered type names.

   .. function:: AnyType GetType(const std::string& name) const

      :param name: Name under which the ``AnyType`` was registered.
      :return: The registered ``AnyType`` instance.
      :throws InvalidOperationException: When the given name does not correspond to a registered
         ``AnyType`` instance.

      Retrieve a registered ``AnyType`` instance by name.

.. function:: std::map<std::string, AnyType> NameToAnyTypeLeafMap()

   :return: Map of type names to their corresponding scalar and empty ``AnyType`` instances.

   Retrieve a map of all leaf (scalar and empty) type names to their ``AnyType`` instances.
