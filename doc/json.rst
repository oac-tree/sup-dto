JSON Serialization
==================

Both the ``AnyType`` and ``AnyValue`` objects can be (de)serialized to and from a JSON
representation. This section provides documentation on the public API and some details on this
representation.

.. contents::
   :local:

AnyType
-------

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
--------

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
