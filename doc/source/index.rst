.. sup-dto documentation master file, created by
   sphinx-quickstart on Thu Jan 20 15:49:09 2022.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to sup-dto's documentation!
===================================

**sup-dto** is a C++ library for Data Transfer Objects, used for transferring generic structured (or
scalar) types and values accross architectural boundaries. The library is created as a part of the
ITER CODAC Operation Applications and will be mainly consumed by the Supervision and Automation
System (SUP) and the Pulse Schedule Preparation System (PSPS).

Both the types and values are designed to respect value semantics. This has a number of benefits
with respect to reference semantics:

* Types/values can be easily passed and returned to/from functions and methods;
* It avoids memory management issues as no pointers are required as handles to such objects;
* It presents no issues with object slicing (i.e. reference aliasing);
* Referential transparency: objects are not modified behind the scenes;
* They are safer to use in multithreaded environments.

.. toctree::
   :maxdepth: 2
   :caption: Contents:

   anytype

Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
