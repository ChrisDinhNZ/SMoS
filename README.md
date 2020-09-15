## SMoS - Structured Messaging over Serial

A SMoS is structured as follow:
* First byte is the '*' character indicating start of message
* Second byte is used to indicate message type:
  + Create request        (BIT0)
  + Read request          (BIT1)
  + Update request        (BIT2)
  + Delete request        (BIT3)
  + Notify response       (BIT4)
  + Reserved              (BIT5)
  + Reserved              (BIT6)
  + Reserved              (BIT7)
* Third byte is reserved for future use (this byte will be used to indicate message Id if confirmed messaging is required) 
* Forth byte is reserved for future use (number of message service types is capped at 255 for now, this byte will be used if more is required)
* Fifth byte is message service type
* Sixth byte indicate length of message content
* Remaining bytes minus the last byte are message content
* Last byte will be the '#' character indicating end of message

String with "*#" which consist of start character followed immediately with end character indicates a reset message.

### Message Examples

#### Reset

The Reset message, which can be used to sync the sender and the recipient consists of a '*' immediately followed by a '#' character.

| Byte Index | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 1 | 0 | 1 | 0 | 1 | 0 |
| 1 | 0 | 0 | 1 | 0 | 0 | 0 | 1 | 1 |

#### Toggle Service (0x01)

The Toggle service allows the sender to query the state, update the state or be notified of state changes of a property belonging to the recipient.
The Toggle service message contains 1 byte of content, an Id between 0 - 255 which maps to a property on the recipient side. It is
up to the recipient to determine what the Id is mapped to what.

##### LED example

Consider an Arduino with an toggleable LED which it exposed as a Toggle Service with a property Id 0x02. A data terminal equipment (DTE) can interact with the LED as follow:

###### Query current LED state (DTE --> Arduino)

| Byte Index | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 1 | 0 | 1 | 0 | 1 | 0 |
| 1 | - | - | - | 0 | 0 | 0 | 1 | 0 |
| 2 | - | - | - | - | - | - | - | - |
| 3 | - | - | - | - | - | - | - | - |
| 4 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 |
| 5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 |
| 6 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 |
| 7 | 0 | 0 | 1 | 0 | 0 | 0 | 1 | 1 |

`Byte index 0`
Binary representation of '*' indicating the start of the message.

`Byte index 1`
BIT1 is true, this is a `read` message.

`Byte index 2`
Reserved.

`Byte index 3`
Reserved.

`Byte index 4`
Service type, 0x01.

`Byte index 5`
Content length, 1 byte.

`Byte index 6`
Message content, the Id associated with the LED i.e. 0x02.

`Byte index 7`
Binary representation of '#' indicating the end of the message.

###### Toggle current LED state (DTE --> Arduino)

| Byte Index | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 1 | 0 | 1 | 0 | 1 | 0 |
| 1 | - | - | - | 0 | 0 | 1 | 0 | 0 |
| 2 | - | - | - | - | - | - | - | - |
| 3 | - | - | - | - | - | - | - | - |
| 4 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 |
| 5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 |
| 6 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 |
| 7 | 0 | 0 | 1 | 0 | 0 | 0 | 1 | 1 |

`Byte index 0`
Binary representation of '*' indicating the start of the message.

`Byte index 1`
BIT2 is true, this is an `update` message.

`Byte index 2`
Reserved.

`Byte index 3`
Reserved.

`Byte index 4`
Service type, 0x01.

`Byte index 5`
Content length, 1 byte.

`Byte index 6`
Message content, the Id associated with the LED i.e. 0x02.

`Byte index 7`
Binary representation of '#' indicating the end of the message.

###### Report current LED state (Arduino --> DTE)
This message can be triggered by:
* Read request from DTE
* Update request from DTE
* Internal event from within the Arduino

| Byte Index | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 1 | 0 | 1 | 0 | 1 | 0 |
| 1 | - | - | - | 1 | 0 | 0 | 0 | 0 |
| 2 | - | - | - | - | - | - | - | - |
| 3 | - | - | - | - | - | - | - | - |
| 4 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 |
| 5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 |
| 6 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 |
| 7 | 0 | 0 | 1 | 0 | 0 | 0 | 1 | 1 |

`Byte index 0`
Binary representation of '*' indicating the start of the message.

`Byte index 1`
BIT4 is true, this is a `notify` message.

`Byte index 2`
Reserved.

`Byte index 3`
Reserved.

`Byte index 4`
Service type, 0x01.

`Byte index 5`
Content length, 1 byte.

`Byte index 6`
Message content, the Id associated with the LED i.e. 0x02.

`Byte index 7`
Binary representation of '#' indicating the end of the message.