## SMoS - Structured Messaging over Serial

A SMoS is structured as follow:
* First byte will be the '*' character indicating start of message
* Second byte is reserved (message max length is 255 for now. If larger message is to be supported, this byte will be used.)
* Third byte indicate length of message including start and end characters
* Forth byte will be used to indicate message options as follows:
  + Private message type   (BIT0 = TRUE)
  + Create request         (BIT1 = TRUE)
  + Read request           (BIT2 = TRUE)
  + Update request         (BIT3 = TRUE)
  + Delete request         (BIT4 = TRUE)
  + Notify response        (BIT5 = TRUE)

* Fifth byte is reserved (number of message types is 255 for now, if more message types need to be supported, this byte will be used)
* Sixth byte is message service type
* Remaining bytes are message content defined by the message type
* Last byte will be the '#' character indicating end of message
* String with "*#" which consist of start character followed immediately with end character indicates a message reset.

### Examples

#### Reset Message

The reset message, which can be used to sync the sender and the recipient consists of a '*' immediately followed by a '#' character.

| Byte Index | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 1 | 0 | 1 | 0 | 1 | 0 |
| 1 | 0 | 0 | 1 | 0 | 0 | 0 | 1 | 1 |

#### Read Toggle State Message

The Toggle service consist of 2 states, ON or OFF. A sender can query the state of the service by sending the following message to the recipient.
The `read toggle state` message contains 1 byte of content, which indicate `read toggle state of what` and the value can be from 0 - 255. It is
up to the recipient to determine what the value is associate with what.

| Byte Index | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 1 | 0 | 1 | 0 | 1 | 0 |
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 2 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 |
| 3 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 |
| 4 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 |
| 6 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 7 | 0 | 0 | 1 | 0 | 0 | 0 | 1 | 1 |

`Byte index 0`
Binary representation of '*' indicating the start of the message.

`Byte index 1`
Reserved.

`Byte index 2`
Total bytes in message i.e 8 bytes

`Byte index 3`
This byte indicates the type of the message and whether the message service type is public or proprietry.
* BIT0 is false, therefore this is a public message service type
* BIT2 is true, this is a `read toggle state` request

`Byte index 4`
Reserved.

`Byte index 5`
Message service type, this `Toggle State Service`.

`Byte index 6`
The message specific content i.e. in this example is 0. So the sender is asking the recipient `what is the toggle state of the item id 0`.

`Byte index 7`
Binary representation of '#' indicating the end of the message.