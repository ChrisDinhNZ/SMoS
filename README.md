# SMoS - Structured Messaging over Serial
![Cover](images/smos_cover_moritz_erken.jpg) *Photo by Moritz Erken*

SMoS is a client/server REST based messaging protocol, originally intended as a mechanism to encapsulate data and it's context when transmitted over a serial link.

Every message has a beginning and an end. Currently all we know is that data is being sent from one point to the other, bit by bit across the serial link. We needed some kind protocol to make sense of these data. SMoS is a way of conveying binary data in a form of a hex string. It's structure was inspired by the [Intel Hex Format](https://en.wikipedia.org/wiki/Intel_HEX).

Given we now have the capability to sync to the start and end of a message, our next task is to make sense of the message's content. It could be a string, a number, a toggle state. Currently SMoS messages includes the reason for the message, generic application data if any, and assumes the receiver will know how to handle the data given the reason of the message.

* -> [SMoS Defined](smos_defined.md)
* -> [SMoS Generic Content Example](smos_generic_content_example.md)
* -> SMoS GATT Content Example
* -> [SMoS C++ Utility Library](https://github.com/ChrisDinhNZ/SMoS-cpp)