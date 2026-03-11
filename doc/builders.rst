AnyType/AnyValue builders
=========================

The library provides two classes that can be used to programmatically construct an AnyType/AnyValue
by sending signals the indicate the start/end of a specific node. This can be used to implement
custom parsers.

AnyTypeComposer
---------------

The ``AnyTypeComposer`` class builds an ``AnyType`` in a step-wise manner by calling methods to
add fields, structures and arrays. It is non-copyable and non-movable.

.. class:: AnyTypeComposer

   .. function:: AnyTypeComposer()

      Construct a new composer instance.

   .. function:: AnyType MoveAnyType()

      :return: The composed ``AnyType``, or empty type if nothing was composed.

      Return the composed ``AnyType`` with move semantics.

   **Scalar/empty type methods:**

   Each of the following methods sets the current node to the corresponding scalar type:

   .. function:: void Empty()
   .. function:: void Bool()
   .. function:: void Char8()
   .. function:: void Int8()
   .. function:: void UInt8()
   .. function:: void Int16()
   .. function:: void UInt16()
   .. function:: void Int32()
   .. function:: void UInt32()
   .. function:: void Int64()
   .. function:: void UInt64()
   .. function:: void Float32()
   .. function:: void Float64()
   .. function:: void String()

   **Structure methods:**

   .. function:: void StartStruct(const std::string& struct_name)

      :param struct_name: Name for the structured type.

      Start composing a new structured type with the given name.

   .. function:: void StartStruct()

      Start composing a new structured type with an empty name.

   .. function:: void EndStruct()

      End the current structured type.

   .. function:: void StartField(const std::string& field_name)

      :param field_name: Name of the field.

      Start composing a new field within the current structure.

   .. function:: void EndField()

      End the current field.

   **Array methods:**

   .. function:: void StartArray(const std::string& array_name, uint64 array_size)

      :param array_name: Name for the array type.
      :param array_size: Number of elements in the array.

      Start composing a new array type with the given name and size.

   .. function:: void EndArray()

      End the current array type.

   .. function:: void StartArrayElement()

      Start composing the element type of the current array.

   .. function:: void EndArrayElement()

      End the current array element type.

   **Utility methods:**

   .. function:: uint64 GetStackSize() const

      :return: Current size of the internal composition stack.

      Retrieve the current depth of the composition stack. Useful for verifying that all
      started nodes have been properly closed.

AnyValueComposer
----------------

The ``AnyValueComposer`` class builds an ``AnyValue`` in a step-wise manner by calling methods to
add fields, structures, arrays and scalar values. It is non-copyable and non-movable.

.. class:: AnyValueComposer

   .. function:: AnyValueComposer()

      Construct a new composer instance.

   .. function:: AnyValue MoveAnyValue()

      :return: The composed ``AnyValue``, or empty value if nothing was composed.

      Return the composed ``AnyValue`` with move semantics.

   **Scalar/ampty value methods:**

   Each of the following methods sets the current node to a scalar value of the corresponding type:

   .. function:: void Empty()
   .. function:: void Bool(boolean value)
   .. function:: void Char8(char8 value)
   .. function:: void Int8(int8 value)
   .. function:: void UInt8(uint8 value)
   .. function:: void Int16(int16 value)
   .. function:: void UInt16(uint16 value)
   .. function:: void Int32(int32 value)
   .. function:: void UInt32(uint32 value)
   .. function:: void Int64(int64 value)
   .. function:: void UInt64(uint64 value)
   .. function:: void Float32(float32 value)
   .. function:: void Float64(float64 value)
   .. function:: void String(const std::string& value)

   .. function:: void AddValue(const AnyValue& anyvalue)

      :param anyvalue: ``AnyValue`` to add at the current position.

      Add an existing ``AnyValue`` at the current position in the composition.

   **Structure methods:**

   .. function:: void StartStruct(const std::string& struct_name)

      :param struct_name: Name for the structured type.

      Start composing a new structured value with the given name.

   .. function:: void StartStruct()

      Start composing a new structured value with an empty name.

   .. function:: void EndStruct()

      End the current structured value.

   .. function:: void StartField(const std::string& field_name)

      :param field_name: Name of the field.

      Start composing a new field within the current structure.

   .. function:: void EndField()

      End the current field.

   .. function:: void AddMember(const std::string& name, AnyValue anyvalue)

      :param name: Member name.
      :param anyvalue: ``AnyValue`` to add as a member.

      Add a complete member to the current structure in a single call.

   **Array methods:**

   .. function:: void StartArray(const std::string& array_name)

      :param array_name: Name for the array type.

      Start composing a new array value with the given name.

   .. function:: void StartArray()

      Start composing a new array value with an empty name.

   .. function:: void StartArrayElement()

      Start composing a new element within the current array.

   .. function:: void EndArrayElement()

      End the current array element.

   .. function:: void AddArrayElement(const AnyValue& anyvalue)

      :param anyvalue: ``AnyValue`` to add as an array element.

      Add a complete element to the current array in a single call.

   .. function:: void EndArray()

      End the current array value.

   **Utility methods:**

   .. function:: uint64 GetStackSize() const

      :return: Current size of the internal composition stack.

      Retrieve the current depth of the composition stack. Useful for verifying that all
      started nodes have been properly closed.
