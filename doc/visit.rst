Visitors
========

The library contains methods to visit AnyTypes/AnyValues with a custom-defined visitor. This
facilitates extensions to the library, mainly for the purpose of serialization.

IAnyVisitor
-----------

The ``IAnyVisitor<T>`` class template is an interface that gets called repeatedly while visiting
an ``AnyType`` or ``AnyValue`` tree. Users can implement this interface to define custom behavior
for each node type encountered during traversal. The template parameter ``T`` is typically
``const AnyType`` or ``const AnyValue``.

The traversal is depth-first, pre-order.

The interface is non-copyable and non-movable.

.. class:: template <typename T> IAnyVisitor

   **Empty node callbacks:**

   The passed value in these methods is a pointer to an empty AnyType/AnyValue.

   .. function:: virtual void EmptyProlog(T* val) = 0

      Called before visiting an empty node.

   .. function:: virtual void EmptyEpilog(T* val) = 0

      Called after visiting an empty node.

   **Structured node callbacks:**

   The passed value in these methods is a pointer to the structured AnyType/AnyValue.

   .. function:: virtual void StructProlog(T* val) = 0

      Called before visiting the members of a structured node.

   .. function:: virtual void StructMemberSeparator() = 0

      Called between consecutive members of a structured node.

   .. function:: virtual void StructEpilog(T* val) = 0

      Called after visiting all members of a structured node.

   **Member callbacks:**

   The passed value in these methods is a pointer to the structured AnyType/AnyValue member value.

   .. function:: virtual void MemberProlog(T* val, const std::string& member_name) = 0

      Called before visiting a specific member of a structured node.

   .. function:: virtual void MemberEpilog(T* val, const std::string& member_name) = 0

      Called after visiting a specific member of a structured node.

   **Array node callbacks:**

   The passed value in these methods is a pointer to the AnyType/AnyValue array.

   .. function:: virtual void ArrayProlog(T* val) = 0

      Called before visiting the elements of an array node.

   .. function:: virtual void ArrayElementSeparator() = 0

      Called between consecutive elements of an array node.

   .. function:: virtual void ArrayEpilog(T* val) = 0

      Called after visiting all elements of an array node.

   **Scalar node callbacks:**

   The passed value in these methods is a pointer to the AnyType/AnyValue scalar.

   .. function:: virtual void ScalarProlog(T* val) = 0

      Called before visiting a scalar node.

   .. function:: virtual void ScalarEpilog(T* val) = 0

      Called after visiting a scalar node.

Visit functions
---------------

.. function:: void SerializeAnyType(const AnyType& anytype, IAnyVisitor<const AnyType>& serializer)

   :param anytype: ``AnyType`` object to serialize.
   :param serializer: Serializer object implementing ``IAnyVisitor<const AnyType>``.

   Serialize an ``AnyType`` using the given generic serializer. The serializer's member functions
   will be invoked for each node encountered during the depth-first traversal of the type tree.

.. function:: void SerializeAnyValue(const AnyValue& anyvalue, IAnyVisitor<const AnyValue>& serializer)

   :param anyvalue: ``AnyValue`` object to serialize.
   :param serializer: Serializer object implementing ``IAnyVisitor<const AnyValue>``.

   Serialize an ``AnyValue`` using the given generic serializer. The serializer's member functions
   will be invoked for each node encountered during the depth-first traversal of the value tree.
