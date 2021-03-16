# SMoS Simple Switch Example

* <- [Back](README.md)

![Simple GPIO Setup](images/smos_example.png)

Lets consider the above scenario, which consists of the following components:

###### Controller

A user controlled or automated device which communicates with the edge device using SMoS messages over a wired/wireless connection.

###### Edge Device

A device that act as an interface between the digital world and the real world.
It communicates with the Controller using SMoS messages over a wired/wireless connection.
It has a digital output pin which connects to a relay/switch.

###### Switch

An electrical switch which connects to the Edge Device's digital output pin.
It takes the signal from the Edge Device and set it's state to on/off.

From the Controller point of view, we want to be able to check the state and control the Switch.

From the system point of view:
* The *Controller* is the client.
* The *Edge Device* is the server with 1 resource i.e. the *Switch*.
* The Switch in this example was given a resource index of 0x01 (the index is defined by the server and can be anything from 0x00 - 0xFF).

The resource's state can be expressed as:
* 0x00 = OFF
* 0x01 = ON

### Message Examples

#### The *Controller* query the *Edge Device* of the state of the *Switch*

* Start Code = ':'
* Byte Count = 0
* Version = 1
* Context Type = Confirmable (i.e. 0)
* Last Block Flag = True
* Block Sequence Index = 0
* Code Class = Request (i.e. 0)
* Code Detail = GET (i.e. 1)
* Message Id = Sender defined (e.g. 1)
* Observe Request Flag = False
* Observe Notification ID = N/A (i.e 0)
* Resource Index = 0x01
* Payload = None
* Checksum = 0xB5

| Byte Index | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 | Hex Value |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 1 | 1 | 1 | 0 | 1 | 0 | 0x3A |
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0x00 |
| 2 | 0 | 1 | 0 | 0 | 1 | 0 | 0 | 0 | 0x48 |
| 3 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0x01 |
| 4 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0x01 |
| 5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0x00 |
| 6 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0x01 |
| 7 | 1 | 0 | 1 | 1 | 0 | 1 | 0 | 1 | 0xB5 |

Converting the PDU above to SMoS Hex string gives `:004801010001B5`

#### The *Edge Device* responding to the confirmed query request indicating the switch is on

When the Edge Device received a request for the state of the switch, it can either respond with an ACK follow by a separate response indicating the switch state or it can respond with an ACK and the switch state included (i.e piggy back response). The following is an example of a piggy back response indicating the switch is on.

* Start Code = ':'
* Byte Count = 1
* Version = 1
* Context Type = Acknowledgement (i.e 2)
* Last Block Flag = True
* Block Sequence Index = 0
* Code Class = SUCCESS (i.e 2)
* Code Detail = CONTENT (i.e 5)
* Message Id = Same as request message ID (i.e. 1)
* Observe Request Flag = False
* Observe Notification ID = N/A (i.e 0)
* Resource Index = 0x01
* Payload = 0x01
* Checksum = 0x4F

| Byte Index | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 | Hex Value |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 1 | 1 | 1 | 0 | 1 | 0 | 0x3A |
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0x01 |
| 2 | 0 | 1 | 1 | 0 | 1 | 0 | 0 | 0 | 0x68 |
| 3 | 0 | 1 | 0 | 0 | 0 | 1 | 0 | 1 | 0x45 |
| 4 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0x01 |
| 5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0x00 |
| 6 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0x01 |
| 7 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0x01 |
| 8 | 0 | 1 | 0 | 0 | 1 | 1 | 1 | 1 | 0x4F |

Converting the PDU above to SMoS Hex string gives `:016845010001014F`

#### The *Controller* request the *Edge Device* to turn the *Switch* off

* Start Code = ':'
* Byte Count = 1
* Version = 1
* Context Type = Confirmable (i.e 0)
* Last Block Flag = True
* Block Sequence Index = 0
* Code Class = Request (i.e 0)
* Code Detail = PUT (i.e 3)
* Message Id = Sender defined (e.g. 2)
* Observe Request Flag = False
* Observe Notification ID = N/A (i.e 0)
* Resource Index = 0x01
* Payload = 0x00
* Checksum = 0xB1

| Byte Index | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 | Hex Value |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 1 | 1 | 1 | 0 | 1 | 0 | 0x3A |
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0x01 |
| 2 | 0 | 1 | 0 | 0 | 1 | 0 | 0 | 0 | 0x48 |
| 3 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 | 0x03 |
| 4 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0x02 |
| 5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0x00 |
| 6 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0x01 |
| 7 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0x00 |
| 8 | 1 | 0 | 1 | 1 | 0 | 0 | 0 | 1 | 0xB1 |

Converting the PDU above to SMoS Hex string gives `:01480302000100B1`

#### The *Edge Device* responding to the confirmed request to turn the switch off

When the edge device received a request to change the state of the switch, it can either respond with an ACK follow by a separate response or it can respond with an ACK plus the outcome of the request included (i.e piggy back response). The following is an example of a piggy back response.

* Start Code = ':'
* Byte Count = 0
* Version = 1
* Context Type = Acknowledgement (i.e 2)
* Last Block Flag = True
* Block Sequence Index = 0
* Code Class = SUCCESS (i.e 2)
* Code Detail = CHANGED (i.e. 4)
* Message Id = Same as request message ID (i.e. 2)
* Observe Request Flag = False
* Observe Notification ID = N/A (i.e 0)
* Resource Index = 0x01
* Payload = None
* Checksum = 0x52

| Byte Index | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 | Hex Value |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 1 | 1 | 1 | 0 | 1 | 0 | 0x3A |
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0x00 |
| 2 | 0 | 1 | 1 | 0 | 1 | 0 | 0 | 0 | 0x68 |
| 3 | 0 | 1 | 0 | 0 | 0 | 1 | 0 | 0 | 0x44 |
| 4 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0x02 |
| 5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0x00 |
| 6 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0x01 |
| 7 | 0 | 1 | 0 | 1 | 0 | 0 | 1 | 0 | 0x51 |

Converting the PDU above to SMoS Hex string gives `:00684402000151`

#### The *Controller* request the *Edge Device* to turn the *Switch* on

* Start Code = ':'
* Byte Count = 1
* Version = 1
* Context Type = Confirmable (i.e 0)
* Last Block Flag = True
* Block Sequence Index = 0
* Code Class = Request (i.e 0)
* Code Detail = PUT (i.e 3)
* Message Id = Sender defined (e.g. 3)
* Observe Request Flag = False
* Observe Notification ID = N/A (i.e 0)
* Resource Index = 0x01
* Payload = 0x01
* Checksum = 0xAF

| Byte Index | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 | Hex Value |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 1 | 1 | 1 | 0 | 1 | 0 | 0x3A |
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0x01 |
| 2 | 0 | 1 | 0 | 0 | 1 | 0 | 0 | 0 | 0x48 |
| 3 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 | 0x03 |
| 4 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 | 0x03 |
| 5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0x00 |
| 6 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0x01 |
| 7 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0x01 |
| 8 | 1 | 0 | 1 | 0 | 1 | 1 | 1 | 1 | 0xAF |

Converting the PDU above to SMoS Hex string gives `:01480303000101AF`

#### The *Edge Device* responding to the confirmed request to turn the switch on

When the edge device received a request to change the state of the switch, it can either respond with an ACK follow by a separate response or it can respond with an ACK plus the outcome of the request included (i.e piggy back response). The following is an example of a separate response (the edge device will ACK the request, then separately send the response).
Note that an ACK response without piggy-backed data is an empty message with only the message ID to map to the request. This indicates to the sender that the request has been received and that a response will be provided shortly.

* Start Code = ':'
* Byte Count = 0
* Version = 1
* Context Type = Acknowledgement 
* Last Block Flag = True
* Block Sequence Index = 0
* Code Class = 0
* Code Detail = 0
* Message Id = Same as request message ID (i.e. 3)
* Observe Request Flag = False
* Observe Notification ID = N/A (i.e 0)
* Resource Index = 0x01
* Payload = None
* Checksum = 0x94

| Byte Index | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 | Hex Value |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 1 | 1 | 1 | 0 | 1 | 0 | 0x3A |
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0x00 |
| 2 | 0 | 1 | 1 | 0 | 1 | 0 | 0 | 0 | 0x68 |
| 3 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0x00 |
| 4 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 | 0x03 |
| 5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0x00 |
| 6 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0x01 |
| 7 | 0 | 1 | 1 | 0 | 0 | 0 | 0 | 0 | 0x94 |

Converting the PDU above to SMoS Hex string gives `:00680003000194`

#### The *Edge Device* sends a delayed response to the confirmed request to turn the switch on

Once we have a response ready we can send it to the Controller. However since we already acknowledged the original request we will need to use a new message ID. If we want an acknowledgement to this respone then we can send it as a confirmable response but in this example we don't, so send it as a non-confirmable message.

* Start Code = ':'
* Byte Count = 0
* Version = 1
* Context Type = Non Confirmable (i.e 1)
* Last Block Flag = True
* Block Sequence Index = 0
* Code Class = SUCCESS (i.e 2)
* Code Detail = CHANGED (i.e. 4)
* Message Id = Server defined (e.g. 0x4)
* Observe Request Flag = False
* Observe Notification ID = N/A (i.e 0)
* Resource Index = 0x01
* Payload = None
* Checksum = 0x5F

| Byte Index | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 | Hex Value |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 1 | 1 | 1 | 0 | 1 | 0 | 0x3A |
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0x00 |
| 2 | 0 | 1 | 0 | 1 | 1 | 0 | 0 | 0 | 0x58 |
| 3 | 0 | 1 | 0 | 0 | 0 | 1 | 0 | 0 | 0x44 |
| 4 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0x04 |
| 5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0x00 |
| 6 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0x01 |
| 7 | 0 | 0 | 1 | 1 | 1 | 0 | 0 | 0 | 0x5F |

Converting the PDU above to SMoS Hex string gives `:0058440400015F`
