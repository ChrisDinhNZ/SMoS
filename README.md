## SMoS - Structured Messaging over Serial

A SMoS is structured as follow:
* First byte will be the '*' character indicating start of message
* Second byte is reserved (message max length is 255 for now. If larger message is to be supported, this byte will be used.)
* Third byte indicate length of message including start and end characters
* Forth byte will be used to indicate whether message type is for public or private use (0 = public, 1 = private)
* The fifth and sixth bytes indicate message type. This is loosely based on the [GATT characteristics assigned number](https://www.bluetooth.com/specifications/gatt/characteristics/)
* Remaining bytes are message content defined by the message type
* Last byte will be the '#' character indicating end of message
* String with "*#" which consist of start character followed immediately with end character indicates a message reset.