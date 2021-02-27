# SMoS - Structured Messaging over Serial

SMoS is a client/server REST based messaging protocol, originally intended as a mechanism to encapsulate data and it's context when transmitted over a serial link.

Every message has a beginning and an end. Currently all we know is that data is being sent from one point to the other, bit by bit across the serial link. We needed some kind protocol to make sense of these data. SMoS is a way of conveying binary data in a form of a hex string. It's structure was inspired by the [Intel Hex Format](https://en.wikipedia.org/wiki/Intel_HEX).

* -> [SMoS Defined](smos_defined.md)
* -> [SMoS Generic Content Example](smos_generic_content_example.md)
* -> SMoS GATT Content Example
* -> [SMoS C++ Utility Library](https://github.com/ChrisDinhNZ/SMoS-cpp)