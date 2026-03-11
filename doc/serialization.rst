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

.. function:: std::vector<uint8> AnyValueToBinary(const AnyValue& anyvalue)

   :param anyvalue: AnyValue object to serialize.
   :return: Binary representation of the AnyValue.

   Serialize an AnyValue to a binary representation.

.. function:: AnyValue AnyValueFromBinary(const std::vector<uint8>& representation)

   :param representation: Binary representation of an AnyValue object.
   :return: AnyValue.
   :throws ParseException: When the binary representation could not be correctly parsed.

   Parse an AnyValue from a binary representation.

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
