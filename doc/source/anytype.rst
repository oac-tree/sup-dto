AnyType
=======

Description
-----------

The ``AnyType`` class represents runtime introspectable types for empty, scalar, structured or array
values.

.. class:: AnyType

Construction
------------

``AnyType`` provides multiple constructors to facilitate the creation of different types:

.. function:: AnyType::AnyType()

   Constructs an empty type object.

.. function:: AnyType::AnyType(TypeCode type_code)

   Constructs a scalar type object, corresponding to the given ``TypeCode``.

   :param type_code: Type code (enumerator) for a scalar type.
