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